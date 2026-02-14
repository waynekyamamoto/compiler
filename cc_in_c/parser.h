#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

Program *parse_program(TokArray toks);

#endif
