#include <stdio.h>
#include "include/Exception.h"
#include "include/Class.h"
interface
{
    int a;
    string s;
    void (*f)(void);
}
Test;
class Persion implements(Test)
{
    constructor(arguments){
        this->a = next(int);
        this->s = next(string);
    }
};

int main()
{
    
    Test *t = new(Test,Persion,12,"hello constructor");
    printf("Persion.s:%s\n",t->s);
    printf("Persion.a:%d\n",t->a);
    
    fn(void, f, (void), {
        printf("123\n");
    });
    f();
    lamda(void, (void), {
        printf("456\n");
    })();
    try
    {
        int a = 1, b = 0, c;
        c = a / b;
        fprintf(stdout, "c = %d\n", c);
    }
    catch (err)
    {
        throw(err);
    };

    return 0;
}