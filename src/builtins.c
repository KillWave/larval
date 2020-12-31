#include <builtins.h>
lval *builtin_lambda(lenv *e, lval *a)
{
  LASSERT_NUM("lambda", a, 2);
  LASSERT_TYPE("lambda", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("lambda", a, 1, LVAL_QEXPR);

  for (int i = 0; i < a->cell[0]->count; i++)
  {
    LASSERT(a, (a->cell[0]->cell[i]->type == LVAL_SYM),
            "Cannot define non-symbol. Got %s, Expected %s.",
            ltype_name(a->cell[0]->cell[i]->type), ltype_name(LVAL_SYM));
  }

  lval *formals = lval_pop(a, 0);
  lval *body = lval_pop(a, 0);
  lval_del(a);

  return lval_lambda(formals, body);
}

lval *builtin_list(lenv *e, lval *a)
{
  a->type = LVAL_QEXPR;
  return a;
}
lval *builtin_head(lenv *e, lval *a)
{
  LASSERT_NUM("head", a, 1);
  LASSERT_TYPE("head", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("head", a, 0);

  lval *v = lval_take(a, 0);
  while (v->count > 1)
  {
    lval_del(lval_pop(v, 1));
  }
  return v;
}
lval *builtin_get(lenv *e, lval *a)
{
  LASSERT_NUM("get", a, 2);
  LASSERT_TYPE("get", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("get", a, 1, LVAL_NUM);
  LASSERT_NOT_EMPTY("get", a, 0);
  long index = a->cell[1]->num;
  lval *v = lval_take(a, 0);
  if (v->cell[index]->type == LVAL_SEXPR)
  {
    return lval_eval_sexpr(e, v->cell[index]);
  }
  lval* result = lval_copy(v->cell[index]);
  lval_del(v);
  return  result;
}
lval *builtin_set(lenv *e, lval *a)
{
  LASSERT_NUM("set", a, 3);
  LASSERT_TYPE("set", a, 0, LVAL_QEXPR);
  LASSERT_TYPE("set", a, 1, LVAL_NUM);
  LASSERT_NOT_EMPTY("set", a, 0);
  long index = a->cell[1]->num;
  lval *v = lval_take(a, 0);
  memcpy(v->cell[index], lval_take(a, 2), sizeof(lval));
  return v;
}
lval *builtin_tail(lenv *e, lval *a)
{
  LASSERT_NUM("tail", a, 1);
  LASSERT_TYPE("tail", a, 0, LVAL_QEXPR);
  LASSERT_NOT_EMPTY("tail", a, 0);

  lval *v = lval_take(a, 0);
  lval_del(lval_pop(v, 0));
  return v;
}
lval *builtin_eval(lenv *e, lval *a)
{
  LASSERT_NUM("eval", a, 1);
  LASSERT_TYPE("eval", a, 0, LVAL_QEXPR);
  //  printf("call:---->");
  //   lval_println(a);
  lval *x = lval_take(a, 0);
  x->type = LVAL_SEXPR;
  return lval_eval(e, x);
}
lval *builtin_join(lenv *e, lval *a)
{

  for (int i = 0; i < a->count; i++)
  {
    LASSERT_TYPE("join", a, i, LVAL_QEXPR);
  }

  lval *x = lval_pop(a, 0);

  while (a->count)
  {
    lval *y = lval_pop(a, 0);
    x = lval_join(x, y);
  }

  lval_del(a);
  return x;
}
lval *builtin_op(lenv *e, lval *a, char *op)
{

  for (int i = 0; i < a->count; i++)
  {
    LASSERT_TYPE(op, a, i, LVAL_NUM);
  }

  lval *x = lval_pop(a, 0);

  if ((strcmp(op, "-") == 0) && a->count == 0)
  {
    x->num = -x->num;
  }

  while (a->count > 0)
  {
    lval *y = lval_pop(a, 0);

    if (strcmp(op, "+") == 0)
    {
      x->num += y->num;
    }
    if (strcmp(op, "-") == 0)
    {
      x->num -= y->num;
    }
    if (strcmp(op, "*") == 0)
    {
      x->num *= y->num;
    }
    if (strcmp(op, "/") == 0)
    {
      if (y->num == 0)
      {
        lval_del(x);
        lval_del(y);
        x = lval_err("Division By Zero.");
        break;
      }
      x->num /= y->num;
    }

    lval_del(y);
  }

  lval_del(a);
  return x;
}
lval *builtin_add(lenv *e, lval *a) { return builtin_op(e, a, "+"); }
lval *builtin_sub(lenv *e, lval *a) { return builtin_op(e, a, "-"); }
lval *builtin_mul(lenv *e, lval *a) { return builtin_op(e, a, "*"); }
lval *builtin_div(lenv *e, lval *a) { return builtin_op(e, a, "/"); }
lval *builtin_var(lenv *e, lval *a, char *func)
{
  LASSERT_TYPE(func, a, 0, LVAL_QEXPR);
  lval *syms = a->cell[0];
  for (int i = 0; i < syms->count; i++)
  {
    LASSERT(a, (syms->cell[i]->type == LVAL_SYM),
            "Function '%s' cannot define non-symbol. "
            "Got %s, Expected %s.",
            func, ltype_name(syms->cell[i]->type), ltype_name(LVAL_SYM));
  }

  LASSERT(a, (syms->count == a->count - 1),
          "Function '%s' passed too many arguments for symbols. "
          "Got %i, Expected %i.",
          func, syms->count, a->count - 1);

  for (int i = 0; i < syms->count; i++)
  {
    if (strcmp(func, "global") == 0)
    {
      lenv_def(e, syms->cell[i], a->cell[i + 1]);
    }
    if (strcmp(func, "local") == 0)
    {
      lenv_put(e, syms->cell[i], a->cell[i + 1]);
    }
  }

  lval_del(a);
  return lval_sexpr();
}
lval *builtin_def(lenv *e, lval *a) { return builtin_var(e, a, "global"); }
// lval *builtin_local(lenv *e, lval *a) { return builtin_var(e, a, "local"); }
lval *builtin_put(lenv *e, lval *a) { return builtin_var(e, a, "local"); }
lval *builtin_ord(lenv *e, lval *a, char *op)
{
  LASSERT_NUM(op, a, 2);
  LASSERT_TYPE(op, a, 0, LVAL_NUM);
  LASSERT_TYPE(op, a, 1, LVAL_NUM);

  int r;
  if (strcmp(op, ">") == 0)
  {
    r = (a->cell[0]->num > a->cell[1]->num);
  }
  if (strcmp(op, "<") == 0)
  {
    r = (a->cell[0]->num < a->cell[1]->num);
  }
  if (strcmp(op, ">=") == 0)
  {
    r = (a->cell[0]->num >= a->cell[1]->num);
  }
  if (strcmp(op, "<=") == 0)
  {
    r = (a->cell[0]->num <= a->cell[1]->num);
  }
  lval_del(a);

  return lval_num(r);
}
lval *builtin_gt(lenv *e, lval *a) { return builtin_ord(e, a, ">"); }
lval *builtin_lt(lenv *e, lval *a) { return builtin_ord(e, a, "<"); }
lval *builtin_ge(lenv *e, lval *a) { return builtin_ord(e, a, ">="); }
lval *builtin_le(lenv *e, lval *a) { return builtin_ord(e, a, "<="); }
lval *builtin_cmp(lenv *e, lval *a, char *op)
{
  LASSERT_NUM(op, a, 2);
  int r;
  if (strcmp(op, "==") == 0)
  {
    r = lval_eq(a->cell[0], a->cell[1]);
  }
  if (strcmp(op, "!=") == 0)
  {
    r = !lval_eq(a->cell[0], a->cell[1]);
  }
  lval_del(a);
  return lval_num(r);
}
lval *builtin_eq(lenv *e, lval *a) { return builtin_cmp(e, a, "=="); }
lval *builtin_ne(lenv *e, lval *a) { return builtin_cmp(e, a, "!="); }
lval *builtin_if(lenv *e, lval *a)
{
  LASSERT_NUM("if", a, a->count > 2 ? 3 : 2);
  LASSERT_TYPE("if", a, 0, LVAL_NUM);
  LASSERT_TYPE("if", a, 1, LVAL_QEXPR);

  lval *x;
  a->cell[1]->type = LVAL_SEXPR;

  if (a->cell[0]->num)
  {
    x = lval_eval(e, lval_pop(a, 1));
  }
  else
  {
    if (a->count > 2)
    {
      LASSERT_TYPE("if", a, 2, LVAL_QEXPR);
      a->cell[2]->type = LVAL_SEXPR;
      x = lval_eval(e, lval_pop(a, 2));
    }
  }

  lval_del(a);
  return x;
}

lval *builtin_load(lenv *e, lval *a)
{
  LASSERT_NUM("load", a, 1);
  LASSERT_TYPE("load", a, 0, LVAL_STR);

  /* Parse File given by string name */
  mpc_result_t r;
  if (mpc_parse_contents(a->cell[0]->str, Lispy, &r))
  {

    /* Read contents */
    lval *expr = lval_read(r.output);
    mpc_ast_delete(r.output);

    /* Evaluate each Expression */
    while (expr->count)
    {
      lval *x = lval_eval(e, lval_pop(expr, 0));
      /* If Evaluation leads to error print it */
      if (x->type == LVAL_ERR)
      {
        lval_println(x);
      }
      lval_del(x);
    }

    /* Delete expressions and arguments */
    lval_del(expr);
    lval_del(a);

    /* Return empty list */
    return lval_sexpr();
  }
  else
  {
    /* Get Parse Error as String */
    char *err_msg = mpc_err_string(r.error);
    mpc_err_delete(r.error);

    /* Create new error message using it */
    lval *err = lval_err("Could not load Library %s", err_msg);
    free(err_msg);
    lval_del(a);

    /* Cleanup and return error */
    return err;
  }
}
lval *builtin_print(lenv *e, lval *a)
{

  /* Print each argument followed by a space */
  for (int i = 0; i < a->count; i++)
  {
    lval_print(a->cell[i]);
    putchar(' ');
  }

  /* Print a newline and delete arguments */
  putchar('\n');
  lval_del(a);

  return lval_sexpr();
}
lval *builtin_error(lenv *e, lval *a)
{
  LASSERT_NUM("error", a, 1);
  LASSERT_TYPE("error", a, 0, LVAL_STR);

  /* Construct Error from first argument */
  lval *err = lval_err(a->cell[0]->str);

  /* Delete arguments and return */
  lval_del(a);
  return err;
}
void lenv_add_builtin(lenv *e, char *name, lbuiltin func)
{
  lval *k = lval_sym(name);
  lval *v = lval_builtin(func);
  lenv_put(e, k, v);
  lval_del(k);
  lval_del(v);
}
void lenv_add_builtins(lenv *e)
{
  /* Variable Functions */
  lenv_add_builtin(e, "lambda", builtin_lambda);
  lenv_add_builtin(e, "global", builtin_def);
  lenv_add_builtin(e, "local", builtin_put);

  /* List Functions */
  lenv_add_builtin(e, "list", builtin_list);
  lenv_add_builtin(e, "get", builtin_get);
  lenv_add_builtin(e, "set", builtin_set);
  lenv_add_builtin(e, "head", builtin_head);
  lenv_add_builtin(e, "tail", builtin_tail);
  lenv_add_builtin(e, "eval", builtin_eval);
  lenv_add_builtin(e, "join", builtin_join);

  /* Mathematical Functions */
  lenv_add_builtin(e, "+", builtin_add);
  lenv_add_builtin(e, "-", builtin_sub);
  lenv_add_builtin(e, "*", builtin_mul);
  lenv_add_builtin(e, "/", builtin_div);

  /* Comparison Functions */
  lenv_add_builtin(e, "if", builtin_if);
  lenv_add_builtin(e, "==", builtin_eq);
  lenv_add_builtin(e, "!=", builtin_ne);
  lenv_add_builtin(e, ">", builtin_gt);
  lenv_add_builtin(e, "<", builtin_lt);
  lenv_add_builtin(e, ">=", builtin_ge);
  lenv_add_builtin(e, "<=", builtin_le);

  /* String Functions */
  lenv_add_builtin(e, "load", builtin_load);
  lenv_add_builtin(e, "error", builtin_error);
  lenv_add_builtin(e, "print", builtin_print);
}