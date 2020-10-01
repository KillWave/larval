#include <stdio.h>
#include "include/prelude.h"
#include "include/Exception.h"
#include "include/Class.h"

int main()
{
    fn(void, f, (void), {
        printf("123\n");
    });
    f();

    lamda(void, (void), {
        printf("456\n");
    })();

    interface
    {
        int a;
        void (*f)(void);
    }
    Test;

    Test t = {12, lamda(void, (void), {
                  printf("test,a:%d\n", t.a);
              })};

    printf("%d\n", t.a);
    t.f();

    try
    {
        int a = 1, b = 0, c;
        c = a / b;
        fprintf(stdout, "c = %d\n", c);
    }
    catch (e)
    {
        throw(null);
    };
    return 0;
}