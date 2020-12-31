#ifndef _CLI_H
#define _CLI_H
#include <mpc.h>
mpc_parser_t *Number;
mpc_parser_t *Symbol;
mpc_parser_t *String;
mpc_parser_t *Comment;
mpc_parser_t *Sexpr;
mpc_parser_t *Qexpr;
mpc_parser_t *Expr;
mpc_parser_t *Lispy;
#include <builtins.h>
void load(lenv *e, char *filename);
#endif