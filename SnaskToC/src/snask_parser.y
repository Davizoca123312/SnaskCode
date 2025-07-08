%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"        // Inclui as definições da AST
#include "snask_value.h" // Inclui os tipos de valor Snask (para literais)

// Variável externa para a raiz da AST que será construída
ASTNode* program_ast_root = NULL;

// Variável de linha do lexer (flex)
extern int yylineno;

// Função de erro do parser (bison)
void yyerror(const char *s);

// Variável para a entrada do lexer (flex)
extern FILE *yyin;

// Define a união de tipos para YYSTYPE (valores passados entre os símbolos da gramática)
// A união deve conter todos os tipos de dados que serão passados como valores semânticos.
// ASTNode* para nós da árvore, char* para nomes, long long para int, double para float, bool para booleanos.
%}

%token MAKE KEEP SET ZAP SHOO GRAB GRABNUM GRABTXT
%token CRAFT BACK
%token WHEN WHENN WHENEM SPIN LOOPY BREAKY SKIPIT
%token PACK PACKADD PACKGET BOX BOXGET BOXSET
%token TO USE
%token IDENTIFIER
%token INT_LITERAL FLOAT_LITERAL STRING_LITERAL BOOL_LITERAL NULL_LITERAL
%token ADD SUB MUL DIV EQ NEQ LT GT LE GE AND OR NOT ASSIGN
%token SEMICOLON LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET COMMA DOT COLON

%type <ast_node> program statement statement_list declaration assignment if_statement while_statement for_statement return_statement print_statement block expression_statement
%type <ast_node> expression unary_expression binary_expression primary function_declaration function_call arguments parameter_list list_literal list_elements
%type <id_name> IDENTIFIER
%type <int_val> INT_LITERAL
%type <float_val> FLOAT_LITERAL
%type <string_val> STRING_LITERAL
%type <bool_val> BOOL_LITERAL NULL_LITERAL

%left OR
%left AND
%left EQ NEQ
%left LT GT LE GE
%left ADD SUB
%left MUL DIV
%right NOT

%%

program:
    statement_list      { program_ast_root = $1; }
;

statement_list:
    %empty              { $$ = ast_create_statement_list(yylineno); }
    | statement_list statement { ast_statement_list_add($1, $2); $$ = $1; }
;

statement:
    declaration SEMICOLON           { $$ = $1; }
    | assignment SEMICOLON          { $$ = $1; }
    | if_statement                  { $$ = $1; }
    | while_statement               { $$ = $1; }
    | for_statement                 { $$ = $1; }
    | return_statement SEMICOLON    { $$ = $1; }
    | print_statement SEMICOLON     { $$ = $1; }
    | block                         { $$ = $1; }
    | function_declaration          { $$ = $1; }
    | function_call SEMICOLON       { $$ = ast_create_expression_statement($1, yylineno); } // Trata chamadas de função como statements
    | expression SEMICOLON          { $$ = ast_create_expression_statement($1, yylineno); } // Para expressões que são statements por si só
    | GRAB IDENTIFIER SEMICOLON     { $$ = ast_create_grab_statement($2, GRAB_TYPE_ANY, yylineno); free($2); } // Assumindo AST_GRAB_STATEMENT para input
    | GRABNUM IDENTIFIER SEMICOLON  { $$ = ast_create_grab_statement($2, GRAB_TYPE_NUM, yylineno); free($2); }
    | GRABTXT IDENTIFIER SEMICOLON  { $$ = ast_create_grab_statement($2, GRAB_TYPE_TXT, yylineno); free($2); }
    | BREAKY SEMICOLON              { $$ = ast_create_break_statement(yylineno); }
    | SKIPIT SEMICOLON              { $$ = ast_create_skip_statement(yylineno); }
    | TO USE STRING_LITERAL SEMICOLON { $$ = ast_create_use_statement($3, yylineno); free($3); } // Para 'to use "module"'
;


declaration:
    MAKE IDENTIFIER ASSIGN expression { $$ = ast_create_var_declaration($2, $4, yylineno); free($2); }
    | KEEP IDENTIFIER ASSIGN expression { $$ = ast_create_const_declaration($2, $4, yylineno); free($2); } // Assumindo que você diferencia const no AST/interpreter
;

assignment:
    SET IDENTIFIER ASSIGN expression { $$ = ast_create_assignment($2, $4, yylineno); free($2); }
    // TODO: Adicionar atribuição para elementos de lista/dicionário (packget/boxget no lado esquerdo)
;

if_statement:
    WHEN LPAREN expression RPAREN block %prec WHEN { $$ = ast_create_if_statement($3, $5, NULL, NULL, yylineno); }
    | WHEN LPAREN expression RPAREN block WHENN block %prec WHENN { $$ = ast_create_if_statement($3, $5, $7, NULL, yylineno); }
    | WHEN LPAREN expression RPAREN block WHENEM LPAREN expression RPAREN block %prec WHENEM { $$ = ast_create_if_statement($3, $5, NULL, ast_create_if_statement($8, $10, NULL, NULL, yylineno), yylineno); } // Nested for whenem
;

while_statement:
    SPIN LPAREN expression RPAREN block { $$ = ast_create_while_statement($3, $5, yylineno); }
;

for_statement:
    LOOPY LPAREN declaration SEMICOLON expression SEMICOLON expression RPAREN block { $$ = ast_create_for_statement($3, $5, $7, $9, yylineno); }
;

return_statement:
    BACK expression { $$ = ast_create_return_statement($2, yylineno); }
;

print_statement:
    SHOO expression { $$ = ast_create_print_statement($2, yylineno); }
;

block:
    LBRACE statement_list RBRACE { $$ = ast_create_block($2, yylineno); }
;

function_declaration:
    CRAFT IDENTIFIER LPAREN parameter_list RPAREN block { $$ = ast_create_function_declaration($2, $4, $6, yylineno); free($2); }
;

parameter_list:
    %empty              { $$ = ast_create_statement_list(yylineno); } // Lista vazia de parâmetros
    | IDENTIFIER        { $$ = ast_create_statement_list(yylineno); ast_statement_list_add($$, ast_create_identifier($1, yylineno)); free($1); }
    | parameter_list COMMA IDENTIFIER { ast_statement_list_add($1, ast_create_identifier($3, yylineno)); $$ = $1; free($3); }
;

function_call:
    IDENTIFIER LPAREN arguments RPAREN { $$ = ast_create_function_call($1, yylineno); ast_function_call_add_arguments($$, $3); free($1); }
;

arguments:
    %empty              { /* no action needed, arguments list will be empty */ }
    | expression        { $$ = ast_create_statement_list(yylineno); ast_statement_list_add($$, $1); }
    | arguments COMMA expression { ast_statement_list_add($1, $3); $$ = $1; }
;

expression:
    unary_expression            { $$ = $1; }
    | binary_expression         { $$ = $1; }
    | primary                   { $$ = $1; }
;

unary_expression:
    NOT expression              { $$ = ast_create_unary_expr(OP_NOT, $2, yylineno); }
    | SUB expression %prec NOT  { $$ = ast_create_unary_expr(OP_NEGATE, $2, yylineno); } // Negativo unário
;

binary_expression:
    expression ADD expression   { $$ = ast_create_binary_expr(OP_ADD, $1, $3, yylineno); }
    | expression SUB expression { $$ = ast_create_binary_expr(OP_SUB, $1, $3, yylineno); }
    | expression MUL expression { $$ = ast_create_binary_expr(OP_MUL, $1, $3, yylineno); }
    | expression DIV expression { $$ = ast_create_binary_expr(OP_DIV, $1, $3, yylineno); }
    | expression EQ expression  { $$ = ast_create_binary_expr(OP_EQ, $1, $3, yylineno); }
    | expression NEQ expression { $$ = ast_create_binary_expr(OP_NEQ, $1, $3, yylineno); }
    | expression LT expression  { $$ = ast_create_binary_expr(OP_LT, $1, $3, yylineno); }
    | expression GT expression  { $$ = ast_create_binary_expr(OP_GT, $1, $3, yylineno); }
    | expression LE expression  { $$ = ast_create_binary_expr(OP_LE, $1, $3, yylineno); }
    | expression GE expression  { $$ = ast_create_binary_expr(OP_GE, $1, $3, yylineno); }
    | expression AND expression { $$ = ast_create_binary_expr(OP_AND, $1, $3, yylineno); }
    | expression OR expression  { $$ = ast_create_binary_expr(OP_OR, $1, $3, yylineno); }
;

primary:
    INT_LITERAL             { $$ = ast_create_int_literal($1, yylineno); }
    | FLOAT_LITERAL         { $$ = ast_create_float_literal($1, yylineno); }
    | STRING_LITERAL        { $$ = ast_create_string_literal($1, yylineno); free($1); }
    | BOOL_LITERAL          { $$ = ast_create_bool_literal($1, yylineno); }
    | NULL_LITERAL          { $$ = ast_create_null_literal(yylineno); }
    | IDENTIFIER            { $$ = ast_create_identifier($1, yylineno); free($1); }
    | LPAREN expression RPAREN { $$ = $2; } // Agrupamento de expressão
    | function_call         { $$ = $1; } // Chamada de função como parte de uma expressão
    | list_literal          { $$ = $1; }
    // | box_literal          // TODO: Adicionar dicionários quando tiver o ASTNode correspondente
;

list_literal:
    PACK LBRACKET list_elements RBRACKET { $$ = $3; }
;

list_elements:
    %empty              { $$ = ast_create_list_literal(yylineno); } // Lista vazia
    | expression        { $$ = ast_create_list_literal(yylineno); ast_list_literal_add_element($$, $1); }
    | list_elements COMMA expression { ast_list_literal_add_element($1, $3); $$ = $1; }
;

%%

// Definição da união YYSTYPE para o Bison
typedef union {
    ASTNode* ast_node;
    char* id_name;
    long long int_val;
    double float_val;
    char* string_val;
    bool bool_val;
} YYSTYPE;

// Função de erro do parser (Bison)
void yyerror(const char *s) {
    fprintf(stderr, "Erro de parsing na linha %d: %s\n", yylineno, s);
    // exit(EXIT_FAILURE); // Pode causar saída abrupta, dependendo da estratégia de tratamento de erros
}