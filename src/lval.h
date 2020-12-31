#ifndef _LVAL_H
#define _LVAL_H
#include <common.h>
lval *lval_num(long x);
lval *lval_err(char *fmt, ...);
lval *lval_sym(char *s);
void unicodeCodePoint(char *target);
lval *lval_str(char *s);
lval *lval_builtin(lbuiltin func);
lval *lval_lambda(lval *formals, lval *body);
lval *lval_sexpr(void);
lval *lval_qexpr(void);
void lval_del(lval *v);
lval *lval_copy(lval *v);
lval *lval_add(lval *v, lval *x);
lval *lval_join(lval *x, lval *y);
lval *lval_pop(lval *v, int i);
lval *lval_take(lval *v, int i);
void lval_print_expr(lval *v, char open, char close);

void lval_print_str(lval *v);
void lval_print(lval *v);
void lval_println(lval *v);
int lval_eq(lval *x, lval *y);
lval *lval_eval(lenv *e, lval *v);
lval *lval_eval_sexpr(lenv *e, lval *v);
lval *lval_read(mpc_ast_t *t);
lval *lval_call(lenv *e, lval *f, lval *a);
lval *lval_read_num(mpc_ast_t *t);
lval *lval_read_str(mpc_ast_t *t);
#endif