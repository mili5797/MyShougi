#include "gameboard.h"

_gameboard::_gameboard()
{
    this->x=0;
    this->y=0;
}

_gameboard& _gameboard::initial_board()
{
    if(this->x<=0||this->y<=0)
    {
        throw "bad x or y in initial_board";
    }

    this->board.resize(this->x);
    for(unsigned int i=0;i<this->x;i++)
    {
        this->board[i].resize(this->y);
    }

    return *this;
}


_small_gameboard::_small_gameboard()
{
    this->x=3;
    this->y=4;
    this->initial_board();

    this->koma_list.push_back(new King);
    this->koma_list.push_back(new King);
    this->koma_list.push_back(new Elephant);
    this->koma_list.push_back(new Elephant);
    this->koma_list.push_back(new Giraffe);
    this->koma_list.push_back(new Giraffe);
    this->koma_list.push_back(new Pawn);
    this->koma_list.push_back(new Pawn);
}


_midium_gameboard::_midium_gameboard()
{
    this->x=5;
    this->y=6;
    this->initial_board();
}


_normal_gameboard::_normal_gameboard()
{
    this->x=9;
    this->y=9;
    this->initial_board();
}
