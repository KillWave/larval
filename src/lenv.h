#ifndef _LENV_H
#define _LENV_H
#include <common.h>
#include <lval.h>

lval *lenv_get(lenv *e, lval *k);
void lenv_put(lenv *e, lval *k, lval *v);
void lenv_def(lenv *e, lval *k, lval *v);
#endif