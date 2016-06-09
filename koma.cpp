#include "koma.h"
#include <cstdarg>

_koma_move::_koma_move()
{
    this->x=0;
    this->y=0;
}

_koma_move::_koma_move(int move_x,int move_y)
{
    this->x=x;
    this->y=y;
}

_koma_move::_koma_move(int move_x,int move_y,int num_if,...)
{

    if (num_if%2!=0)
    {
        throw "bad num_if in new Koma";
    }

    va_list arglist;
    std::vector<int> tmp_x,tmp_y;
    va_start(arglist,num_if);

    for (int i=0;;i++)
    {
        int val;
        val=va_arg(arglist,int);

        if(val!=END_OF_ARG)
        {
            if(i%2==0)
            {
                tmp_x.push_back(val);
            }
            else if(i%2==1)
            {
                tmp_y.push_back(val);
            }
        }
        else if(i==num_if)
        {
            break;
        }
        else
        {
            throw "bad number of arg in new Koma"
        }
    }
    va_end(arglist);

    this->x=x;
    this->y=y;

}
