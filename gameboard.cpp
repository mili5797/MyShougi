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

    for(unsigned int i=0;i<owner_total;i++)
    {
        this->owner_hand[i].resize(2,-1);
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
    if (!is_koma_id(koma_id))
    {
        throw "bad koma_id in Gameboard koma_can_go";
    }

    int koma_x=-1,koma_y=-1;

    if(this->is_koma_on_board(koma_id))
    {
        Move& where_koma=this->where_koma(koma_id);
        koma_x=where_koma.get_move_x();
        koma_y=where_koma.get_move_y();
    }

    return this->koma_can_go(koma_x,koma_y);
}

std::vector<Move> _gameboard::koma_can_go(unsigned int koma_x,unsigned int koma_y)
{
    std::vector<Move> vecDest;
    if (koma_x<0||koma_y<0||koma_x>=this->x||koma_y>=this->y)
    {
        throw "bad koma_x or koma_y in Gameboard koma_can_go";
    }
    int& koma_id=this->board[koma_x][koma_y];
    if (!is_koma_id(koma_id))
    {
        throw "bad koma_x or koma_y in Gameboard koma_can_go";
    }

    Koma& koma=*(this->koma_list[koma_id]);

    if(koma.rush==true)
    {
        for(unsigned int i=0;i<Dir_total;i++)
        {
            if(koma.direct[i]==true)
            {
                int dx=0,dy=0;
                while(1)
                {
                    switch (i)
                    {
                        case Dir_Forward:
                            dy++;
                            break;
                        case Dir_RFront:
                            dx++;
                            dy++;
                        case Dir_Right:
                            dx++;
                            break;
                        case Dir_RBack:
                            dx++;
                            dy--;
                            break;
                        case Dir_Backward:
                            dy--;
                            break;
                        case Dir_LBack:
                            dx--;
                            dy--;
                            break;
                        case Dir_Left:
                            dx--;
                            break;
                        case Dir_LFront:
                            dx--;
                            dy++;
                            break;
                    }

                    if(koma_x+dx>this->x||koma_x+dx<0||koma_y+dy>this->y||koma_y+dy<0)
                    {
                        break;
                    }
                    else if(this->board[koma_x+dx][koma_y+dy]==-1)
                    {
                        vecDest.push_back(Move(koma_x+dx,koma_y+dy));
                    }
                    else if(this->koma_list[this->board[koma_x+dx][koma_y+dy]]->owner==koma.owner)
                    {
                        break;
                    }
                    else
                    {
                        vecDest.push_back(Move(koma_x+dx,koma_y+dy));
                        break;
                    }
                }
            }
        }
    }

    if(koma.jump==true)
    {
        for(unsigned int i=0;i<koma.can_go.size();i++)
        {
            int dx=koma.can_go[i].get_move_x();
            int dy=koma.can_go[i].get_move_y();
            if (koma_x+dx>this->x||koma_x+dx<0||koma_y+dy>this->y||koma_y+dy<0)
            {
                continue;
            }
            else if(this->board[koma_x+dx][koma_y+dy]==-1)
            {
                /*if no koma there, then it can*/
            }
            else if(this->koma_list[this->board[koma_x+dx][koma_y+dy]]->owner==koma.owner)
            {
                continue;
            }

            bool can=true;

            /*** testing if ***/
            std::vector<int> if_dx=koma.can_go[i].get_if_x(),if_dy=koma.can_go[i].get_if_y();
            for(unsigned int j=0;j<koma.can_go[i].get_num_if();j++)
            {
                if(this->board[koma_x+if_dx[j]][koma_y+if_dy[j]]!=-1)
                {
                    can=false;
                    break;
                }
            }

            if(can == true)
            {
                vecDest.push_back(Move(koma_x+dx,koma_y+dy));
            }
        }
    }

    return vecDest;
}

std::vector<Move> _gameboard::koma_can_drop(unsigned int koma_id)
{
    if (!this->is_koma_id(koma_id))
    {
        throw "bad koma_id in Gameboard koma_can_put";
    }

    Owner koma_owner=(Owner)-1;
    unsigned int index=0;
    if(this->is_koma_in_hand(koma_id))
    {
        Move& where_koma=this->where_koma(koma_id);
        koma_owner=(Owner)(where_koma.get_move_x()*(-1));
        index=(unsigned int)where_koma.get_move_y();
    }

    return this->koma_can_drop(koma_owner,index);
}

std::vector<Move> _gameboard::koma_can_drop(Owner owner,unsigned int index)
{
    if (owner<0)
    {
        throw "bad owner in Gameboard koma_can_put";
    }
    std::vector<Move> vecDest;
    int& koma_id=this->owner_hand[owner][index];
    if (!this->is_koma_id(koma_id))
    {
        throw "bad owner or index in Gameboard koma_can_put";
    }

    Koma& koma=*(this->koma_list[koma_id]);

    for(unsigned int i;i<this->x;i++)
    {
        for(unsigned int j;j<this->y;j++)
        {
            if(this->board[i][j]!=-1)
            {
                continue;
            }
            else if(this->is_koma_can_move_in((unsigned int)koma_id,i,j))
            {
                if(koma.get_koma_name()==Koma_Pawn)
                {
                    if(this->pawn_spec_rule(koma_id,i,j))
                    {
                        vecDest.push_back(Move(i,j));
                    }
                }
                else
                {
                    vecDest.push_back(Move(i,j));
                }
            }
        }
    }

    return vecDest;
}

Move& _gameboard::where_koma(unsigned int koma_id)
{
    if(this->is_koma_on_board(koma_id))
    {
        for (unsigned int i=0;i<this->x;i++)
        {
            for(unsigned int j=0;j<this->y;j++)
            {
                if(this->board[i][j]==(int)koma_id)
                {
                    return *(new Move(i,j));
                }
            }
        }
    }
    else if(this->is_koma_in_hand(koma_id))
    {
        for(unsigned int i=0;i<owner_total;i++)
        {
            for(unsigned int j=0;j<this->owner_hand[i].size();j++)
            {
                if(this->owner_hand[i][j]==(int)koma_id)
                {
                    return *(new Move(-i,j));
                }
            }
        }
    }
}

bool _gameboard::is_koma_on_board(unsigned int koma_id)
{
    return (this->koma_list[koma_id]->where==on_table);
}

bool _gameboard::is_koma_in_hand(unsigned int koma_id)
{
    return (this->koma_list[koma_id]->where==in_hand);
}

bool _gameboard::is_koma_can_move_in(unsigned int koma_id,unsigned int board_x,unsigned int board_y)
{
    if (board_x>=this->x||board_y>=this->y)
    {
        throw "bad board_x or board_y in Gameboard if_koma_can_move_in";
    }
    if(!this->is_koma_id(koma_id))
    {
        throw "bad koma_id in if_koma_can_move_in";
    }

    Koma& koma=*(this->koma_list[koma_id]);
    if(koma.rush==true)
    {
        for(unsigned int i=0;i<Dir_total;i++)
        {
            if(koma.direct[i]==true)
            {
                int dx=0,dy=0;
                switch (i)
                {
                    case Dir_Forward:
                        dy++;
                        break;
                    case Dir_RFront:
                        dx++;
                        dy++;
                    case Dir_Right:
                        dx++;
                        break;
                    case Dir_RBack:
                        dx++;
                        dy--;
                        break;
                    case Dir_Backward:
                        dy--;
                        break;
                    case Dir_LBack:
                        dx--;
                        dy--;
                        break;
                    case Dir_Left:
                        dx--;
                        break;
                    case Dir_LFront:
                        dx--;
                        dy++;
                        break;
                }

                if(board_x+dx>this->x||board_x+dx<0||board_y+dy>this->y||board_y+dy<0)
                {
                    continue;
                }
                else
                {
                    return true;
                }
            }
        }
    }
    if (koma.jump==true)
    {
        for(unsigned int i=0;i<koma.can_go.size();i++)
        {
            int dx=koma.can_go[i].get_move_x();
            int dy=koma.can_go[i].get_move_y();
            if (board_x+dx>this->x||board_x+dx<0||board_y+dy>this->y||board_y+dy<0)
            {
                continue;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

bool _gameboard::is_koma_id(unsigned int koma_id)
{
    return (koma_id<this->koma_list.size());
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

bool _small_gameboard::pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y)
{
    return true;
}


_midium_gameboard::_midium_gameboard()
{
    this->x=5;
    this->y=6;
    this->initial_board();
}

bool _midium_gameboard::pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y)
{
    return true;
}


_normal_gameboard::_normal_gameboard()
{
    this->x=9;
    this->y=9;
    this->initial_board();
}

bool _normal_gameboard::pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y)
{
    return true;
}

