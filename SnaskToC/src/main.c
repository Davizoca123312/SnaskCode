#include <stdio.h>
#include "snask_parser.tab.h" // Inclui o cabeçalho gerado pelo Bison
#include "ast.h"             // Inclui a definição da AST
#include "environment.h"     // Inclui o ambiente
#include "interpreter.h"     // Inclui o interpretador

// Variável externa para o Flex (definida em snask_lexer.l)
extern FILE *yyin;

// Variável externa para a raiz da AST (definida em snask_parser.y)
extern ASTNode* program_ast_root;

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *input_file = fopen(argv[1], "r");
        if (!input_file) {
            perror("Erro ao abrir o arquivo de entrada");
            return 1;
        }
        yyin = input_file; // Redireciona a entrada do Flex para o arquivo
    } else {
        yyin = stdin; // Usa a entrada padrão se nenhum arquivo for fornecido
    }

    printf("Iniciando análise sintática e construção da AST...\n");
    int parse_result = yyparse();

    if (parse_result == 0) {
        printf("Análise sintática concluída com sucesso!\n");
        if (program_ast_root) {
            printf("AST gerada:\n");
            ast_print(program_ast_root, 0);

            printf("\nIniciando interpretação...\n");
            Environment* global_env = environment_create(NULL); // Cria o ambiente global
            SnaskValue result = interpret(program_ast_root, global_env);
            printf("Interpretação concluída.\n");

            // Libera a memória
            snask_value_free(result); // Libera o resultado final da interpretação
            environment_free(global_env);
            ast_free(program_ast_root);
            printf("Memória da AST e ambiente liberados.\n");
        }
    } else {
        printf("Erro na análise sintática.\n");
    }

    if (argc > 1) {
        fclose(yyin);
    }

    return 0;
}