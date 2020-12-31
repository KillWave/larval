#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <mpc.h>
#include <unicodeUtf8.h>
#include <string.h>
/* Forward Declarations */

struct lval;
struct lenv;
typedef struct lval lval;
typedef struct lenv lenv;

/* Lisp Value */

enum
{
  LVAL_ERR,
  LVAL_NUM,
  LVAL_SYM,
  LVAL_STR,
  LVAL_FUN,
  LVAL_SEXPR,
  LVAL_QEXPR
};

typedef lval *(*lbuiltin)(lenv *, lval *);

struct lval
{
  int type;

  /* Basic */
  long num;
  char *err;
  char *sym;
  char *str;

  /* Function */
  lbuiltin builtin;
  lenv *env;
  lval *formals;
  lval *body;

  /* Expression */
  int count;
  lval **cell;
};

/* Lisp Environment */

struct lenv
{
  lenv *par;
  int count;
  char **syms;
  lval **vals;
};



char *ltype_name(int t);
lenv *lenv_new(void);
void lenv_del(lenv *e);
lenv *lenv_copy(lenv *e);
void lval_print(lval *v);
#endif