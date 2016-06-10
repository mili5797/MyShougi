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
        this->board[i].resize(this->y,-1);
    }

    return *this;
}


_small_gameboard::_small_gameboard()
{
    this->x=3;
    this->y=4;
    this->initial_board();

    this->koma_list.push_back(new King);
    this->board[1][0]=0;
    this->koma_list.push_back(new King);
    this->board[1][3]=1;
    this->koma_list.push_back(new Elephant);
    this->board[2][0]=2;
    this->koma_list.push_back(new Elephant);
    this->board[0][3]=3;
    this->koma_list.push_back(new Giraffe);
    this->board[0][0]=4;
    this->koma_list.push_back(new Giraffe);
    this->board[2][3]=5;
    this->koma_list.push_back(new Pawn);
    this->board[1][1]=6;
    this->koma_list.push_back(new Pawn);
    this->board[1][2]=7;
//          y
//   E K G  3
//     P    2
//     P    1
//   G K E  0
//
// x 0 1 2
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
