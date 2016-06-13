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

_gameboard& _gameboard::set_owner_where(unsigned int koma_id,Owner owner,Where where)
{
    this->set_owner(koma_id,owner);
    this->set_where(koma_id,where);
    return *this;
}
_gameboard& _gameboard::set_owner(unsigned int koma_id,Owner owner)
{
    this->koma_list[koma_id]->owner=owner;
    return *this;
}

_gameboard& _gameboard::set_where(unsigned int koma_id,Where where)
{
    this->koma_list[koma_id]->where=where;
    return *this;
}

std::vector<Move> _gameboard::koma_can_go(unsigned int koma_id)
{
    std::vector<Move> vecMove;

    return vecMove;
}

std::vector<Move> _gameboard::koma_can_go(unsigned int koma_x,unsigned int koma_y)
{
    if (this->board[koma_x][koma_y]==-1)
    {
        throw "bad koma_x and koma_y in Gameboard koma_can_go";
    }

    return this->koma_can_go(this->board[koma_x][koma_y]);
}

_small_gameboard::_small_gameboard()
{
    this->x=3;
    this->y=4;
    this->initial_board();

    this->koma_list.push_back(new King);
    this->board[1][0]=0;
    this->set_owner_where(0,player1,on_table);
    this->koma_list.push_back(new King);
    this->board[1][3]=1;
    this->set_owner_where(1,player2,on_table);
    this->koma_list.push_back(new Elephant);
    this->board[2][0]=2;
    this->set_owner_where(2,player1,on_table);
    this->koma_list.push_back(new Elephant);
    this->board[0][3]=3;
    this->set_owner_where(3,player2,on_table);
    this->koma_list.push_back(new Giraffe);
    this->board[0][0]=4;
    this->set_owner_where(4,player1,on_table);
    this->koma_list.push_back(new Giraffe);
    this->board[2][3]=5;
    this->set_owner_where(5,player2,on_table);
    this->koma_list.push_back(new Pawn);
    this->board[1][1]=6;
    this->set_owner_where(6,player1,on_table);
    this->koma_list.push_back(new Pawn);
    this->board[1][2]=7;
    this->set_owner_where(7,player2,on_table);

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
