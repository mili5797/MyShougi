#include <iostream>
#include <cstdarg>


int test_undertermind_arg(int num,...)
{
    int arg[num+2];

    if(num%2!=0)
        throw -1;

    va_list vlist;
    va_start(vlist,num);

    for (int i=0;;i++)
    {
        int val;
        val=va_arg(vlist,int);
        if (val!=-1)
            arg[i]=val;
        else if(i==num)
            break;
        else
            throw -2;
    }

    va_end(vlist);

    for (int i=0;i<num;i++)
    {
        std::cout<<arg[i]<<'\t';
    }
    std::cout<<std::endl;

    return 0;
}

int test()
{
    test_undertermind_arg(2,1,0,-1);
    test_undertermind_arg(4,2,1,20,10,-1);
    try {test_undertermind_arg(5,2,1,20,10,0,-1); }catch(int i){std::cout<<"error :"<<i<<std::endl;}
    try {test_undertermind_arg(6,2,1,20,10,0,-1); }catch(int i){std::cout<<"error :"<<i<<std::endl;}
    try {test_undertermind_arg(4,2,1,20,10,0,-1); }catch(int i){std::cout<<"error :"<<i<<std::endl;}

    return 0;
}
