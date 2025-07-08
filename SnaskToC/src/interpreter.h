#ifndef SNASK_INTERPRETER_H
#define SNASK_INTERPRETER_H

#include "ast.h"
#include "environment.h"
#include "snask_value.h"

// Função principal para interpretar a AST
SnaskValue interpret(ASTNode* node, Environment* env);

#endif // SNASK_INTERPRETER_H
