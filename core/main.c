#include <stdio.h>
#include "include/prelude.h"
#include "include/Exception.h"
#include "include/Class.h"
interface
{
    int a;
    void (*f)(void);
}
Test;

class Persion implements Test *this end
{
    this->a = 12;
    this->f = lamda(void, (void), {
        printf("class Test %d\n", this->a);
    });
    return this;
};
int main()
{
    fn(void, f, (void), {
        printf("123\n");
    });
    f();

    lamda(void, (void), {
        printf("456\n");
    })();
       
    Test *t = new(Test,Persion);
    t->f();

  

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