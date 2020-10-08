#include <stdio.h>
#include "include/Exception.h"
#include "include/Class.h"

interface
{
    int a;
    void (*f)(void);
}
Test;

class Persion implements(Test)
{
    
    constructor(arguments){
       
        
        printf("%d\n",next(int));
        printf("%s\n",next(string));

        destroy(arguments);
    }
    // printf("args = %d\n",*arguments);
    // va_arg(arguments,int);
     
    // printf("%d\n",*arguments);
    // va_end(arguments);	
  
    // this->a = 12;
    // this->f = lamda(void, (void), {
    //     printf("class Test %d\n", this->a);
    // });
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

    autofree Test *t = new(Test,Persion,0,"hello constructor");
    // t->f();

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