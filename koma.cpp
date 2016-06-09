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

    if (num_if%2!=0||num_if<0)
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
            throw "bad number of arg in new Koma";
        }
    }
    va_end(arglist);

    if(tmp_y.size()!=tmp_x.size()||
       tmp_y.size()!=(unsigned int)num_if/2||
       tmp_x.size()!=(unsigned int)num_if/2)
    {
        throw "bad number of arg in new Koma";
    }

    this->x=x;
    this->y=y;

    this->if_x=tmp_x;
    this->if_y=tmp_y;
}

_koma_move& _koma_move::set_move(int move_x,int move_y)
{
    this->x=move_x;
    this->y=move_y;
    return *this;
}

_koma_move& _koma_move::set_if(int num_if,...)
{
    if (num_if%2!=0||num_if<0)
    {
        throw "bad num_if in Move::set_if";
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
            throw "bad number of arg in Koma::set_if";
        }
    }
    va_end(arglist);

    if(tmp_y.size()!=tmp_x.size()||
       tmp_y.size()!=(unsigned int)num_if/2||
       tmp_x.size()!=(unsigned int)num_if/2)
    {
        throw "bad number of arg in Koma::set_if";
    }

    this->if_x.clear();
    this->if_y.clear();
    this->if_x=tmp_x;
    this->if_y=tmp_y;

    return *this;
}

unsigned int _koma_move::get_num_if()
{
    if(this->if_x.size()!=this->if_y.size())
    {
        throw "undetermind error in Move::get_num_if";
    }

    return this->if_x.size();
}

int _koma_move::get_move_x()
{
    return this->x;
}

int _koma_move::get_move_y()
{
    return this->y;
}

std::vector<int> _koma_move::get_if_x()
{
    return this->if_x;
}

std::vector<int> _koma_move::get_if_y()
{
    return this->if_y;
}

