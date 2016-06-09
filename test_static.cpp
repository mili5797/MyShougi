#include <iostream>

class test_static_parent_class{
public:
    test_static_parent_class();
    static int get_num();
private:
    static int num;
};

int test_static_parent_class::num=0;
int test_static_parent_class::get_num()
{
    return test_static_parent_class::num;
}

test_static_parent_class::test_static_parent_class()
{
    num++;
}

int test_static()
{
    std::cout<<test_static_parent_class::get_num()<<std::endl;
    class test_static_parent_class class_f_a;
    std::cout<<test_static_parent_class::get_num()<<std::endl;
    class test_static_parent_class class_f_b,class_f_c;
    std::cout<<test_static_parent_class::get_num()<<std::endl;

    return 0;
}
