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
    else
    {
        for (int i=0;i<num_if;i++)
        {

        }
    }

    this->x=x;
    this->y=y;

}
