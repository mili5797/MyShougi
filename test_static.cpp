#include <iostream>

class test_static_parent_class{
public:
    test_static_parent_class(){test_static_parent_class::add_num();};
    static int add_num();
    static int get_num();
private:
    static int num;
};
int test_static_parent_class::num=0;
int test_static_parent_class::add_num(){return num++;}
int test_static_parent_class::get_num(){return num;}

class test_static_child_class_a:public test_static_parent_class{
public:
    test_static_child_class_a(){test_static_child_class_a::add_num();}
    static int add_num();
    static int get_num();
private:
    static int num;
};
int test_static_child_class_a::num=0;
int test_static_child_class_a::add_num(){return num++;}
int test_static_child_class_a::get_num(){return num;}

class test_static_child_class_b:public test_static_parent_class{
public:
    test_static_child_class_b(){test_static_parent_class::add_num();}
    static int get_num();
private:
    static int num;
};
int test_static_child_class_b::num=0;
int test_static_child_class_b::get_num(){return num;}

int test_static()
{
    class test_static_parent_class class_f_a;
    std::cout<<test_static_parent_class::get_num()<<std::endl;
    class test_static_child_class_a class_c_a;
    std::cout<<test_static_parent_class::get_num()<<std::endl;
    std::cout<<test_static_child_class_a::get_num()<<std::endl;
    std::cout<<test_static_child_class_b::get_num()<<std::endl;
    class test_static_child_class_b class_c_b;
    std::cout<<test_static_parent_class::get_num()<<std::endl;
    std::cout<<test_static_child_class_a::get_num()<<std::endl;
    std::cout<<test_static_child_class_b::get_num()<<std::endl;

    return 0;
}
/*
output:
1
2
1
0
4
1
0
*/
