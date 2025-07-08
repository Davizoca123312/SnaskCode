%{
#include "snask_parser.tab.h" // Inclui o cabeçalho gerado pelo Bison
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variável para a linha atual, usada pelos nós da AST
int yylineno = 1;

// Define yylval (união para passar valores entre lexer e parser)
// A macro YYSTYPE é definida em snask_parser.tab.h
// Se não estiver definida, defina aqui.
// #ifndef YYSTYPE
// #define YYSTYPE ASTNode* // Exemplo se for um nó AST, mas aqui será um union
// #endif

// Função para lidar com erros léxicos
void yyerror(const char *s);

%}

%option noyywrap
%option yylineno // Permite que Flex mantenha o controle da linha atual

digit       [0-9]
letter      [a-zA-Z]
id          {letter}({letter}|{digit}|_)*
int_literal {digit}+
float_literal {digit}+\.{digit}+([eE][+-]?{digit}+)?
string_char [^"\\\n]
escape_seq  \\([nrt\\"]|u[0-9a-fA-F]{4}) // Adiciona sequências de escape básicas e Unicode (ex: \u000a)

%%

"//".* { /* Ignora comentários de linha única */ }
"/*"            { BEGIN(COMMENT); }
<COMMENT>"*/"   { BEGIN(INITIAL); }
<COMMENT>.      { /* Ignora tudo dentro do comentário de bloco */ }
<COMMENT>\n     { yylineno++; } // Conta linhas dentro de comentários de bloco
<COMMENT><<EOF>> { fprintf(stderr, "Erro léxico na linha %d: Comentário de bloco não fechado.\n", yylineno); return 0; }


"make"          { return MAKE; }
"keep"          { return KEEP; }
"set"           { return SET; }
"zap"           { return ZAP; }

"shoo"          { return SHOO; }
"grab"          { return GRAB; }
"grabnum"       { return GRABNUM; }
"grabtxt"       { return GRABTXT; }

"craft"         { return CRAFT; }
"back"          { return BACK; }

"when"          { return WHEN; }
"whenn"         { return WHENN; }
"whenem"        { return WHENEM; }
"spin"          { return SPIN; }
"loopy"         { return LOOPY; }
"breaky"        { return BREAKY; }
"skipit"        { return SKIPIT; }

"pack"          { return PACK; }
"packadd"       { return PACKADD; }
"packget"       { return PACKGET; }
"box"           { return BOX; }
"boxget"        { return BOXGET; }
"boxset"        { return BOXSET; }

"to"            { return TO; }
"use"           { return USE; }

"null"          { yylval.bool_val = false; return NULL_LITERAL; } // Representa null como um bool_val (false)
"true"          { yylval.bool_val = true; return BOOL_LITERAL; }
"false"         { yylval.bool_val = false; return BOOL_LITERAL; }

{float_literal} { yylval.float_val = atof(yytext); return FLOAT_LITERAL; }
{int_literal}   { yylval.int_val = atoll(yytext); return INT_LITERAL; }

\"({string_char}|{escape_seq})*\" {
    // Remove as aspas e lida com sequências de escape
    char *str = strdup(yytext + 1); // Ignora a primeira aspa
    str[strlen(str) - 1] = '\0';    // Remove a última aspa

    // Processa sequências de escape (ex: \n, \t, \", \\)
    char *read_ptr = str;
    char *write_ptr = str;
    while (*read_ptr) {
        if (*read_ptr == '\\') {
            read_ptr++; // Pula a barra invertida
            switch (*read_ptr) {
                case 'n': *write_ptr = '\n'; break;
                case 't': *write_ptr = '\t'; break;
                case 'r': *write_ptr = '\r'; break;
                case '\\': *write_ptr = '\\'; break;
                case '"': *write_ptr = '"'; break;
                // Adicione outros casos de escape se necessário (ex: \uXXXX para Unicode)
                default:
                    fprintf(stderr, "Erro léxico na linha %d: Sequência de escape desconhecida '\\%c'.\n", yylineno, *read_ptr);
                    exit(EXIT_FAILURE);
            }
        } else {
            *write_ptr = *read_ptr;
        }
        read_ptr++;
        write_ptr++;
    }
    *write_ptr = '\0'; // Termina a string

    yylval.string_val = str;
    return STRING_LITERAL;
}


{id}            { yylval.id_name = strdup(yytext); return IDENTIFIER; }

"+"             { return ADD; }
"-"             { return SUB; }
"*"             { return MUL; }
"/"             { return DIV; }
"=="            { return EQ; }
"!="            { return NEQ; }
"<"             { return LT; }
">"             { return GT; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; } // Operador unário

"="             { return ASSIGN; }
";"             { return SEMICOLON; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
","             { return COMMA; }
"."             { return DOT; } // Para acesso a propriedades de objetos/módulos (futuro)
":"             { return COLON; } // Para dicionários

[ \t\r]+        { /* Ignora espaços em branco e tabulações */ }
\n              { yylineno++; }

.               { fprintf(stderr, "Erro léxico na linha %d: Caractere inesperado '%s'.\n", yylineno, yytext); exit(EXIT_FAILURE); }

%%

// Função de erro do lexer (Flex)
void yyerror(const char *s) {
    fprintf(stderr, "Erro de parsing na linha %d: %s\n", yylineno, s);
}

// Para usar com yyparse no main.c, precisa de yyget_current_buffer()
// e yy_scan_string() ou yy_scan_buffer() se você for ler de string/memória.
// Mas para leitura de arquivo, yyin é suficiente.