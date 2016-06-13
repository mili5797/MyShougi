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
    if (koma_id<0||koma_id>Koma::get_total_num())
    {
        throw "bad koma_id in Gameboard koma_can_go";
    }

    int koma_x=-1,koma_y=-1;

    for (unsigned int i=0;i<this->x;i++)
    {
        for(unsigned int j=0;j<this->y;j++)
        {
            if(this->board[i][j]==(int)koma_id)
            {
                koma_x=i;
                koma_y=j;
                return koma_can_go(koma_x,koma_y);
            }
        }
    }

    return koma_can_go(koma_x,koma_y);
}

std::vector<Move> _gameboard::koma_can_go(unsigned int koma_x,unsigned int koma_y)
{
    std::vector<Move> vecMove;
    if (koma_x<0||koma_y<0||koma_x>=this->x||koma_y>=this->y)
    {
        throw "bad koma_x or koma_y in Gameboard koma_can_go";
    }
    int& koma_id=this->board[koma_x][koma_y];
    if (koma_id<0||koma_id>Koma::get_total_num())
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
                        vecMove.push_back(Move(dx,dy));
                    }
                    else if(this->koma_list[this->board[koma_x+dx][koma_y+dy]]->owner==koma.owner)
                    {
                        break;
                    }
                    else
                    {
                        vecMove.push_back(Move(dx,dy));
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
                ;
            }
            else if(this->koma_list[this->board[koma_x+dx][koma_y+dy]]->owner==koma.owner)
            {
                continue;
            }

            bool can=true;

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
                vecMove.push_back(Move(dx,dy));
            }
        }
    }

    return vecMove;
}

std::vector<Move> _gameboard::koma_can_put(unsigned int koma_id)
{
    if (koma_id<0||koma_id>Koma::get_total_num())
    {
        throw "bad koma_id in Gameboard koma_can_put";
    }

    Owner koma_owner=(Owner)-1;
    unsigned int index=0;
    for(unsigned int i=0;i<owner_total;i++)
    {
        for(unsigned int j=0;j<this->owner_hand[i].size();j++)
        {
            if(this->owner_hand[i][j]==(int)koma_id)
            {
                koma_owner=(Owner)i;
                index=j;
                return koma_can_put(koma_owner,index);
            }
        }
    }

    return koma_can_put(koma_owner,index);
}

std::vector<Move> _gameboard::koma_can_put(Owner owner,unsigned int index)
{
    if (owner<0)
    {
        throw "bad owner in Gameboard koma_can_put";
    }
    std::vector<Move> vecMove;
    int& koma_id=this->owner_hand[owner][index];
    if (koma_id<0||koma_id>Koma::get_total_num())
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
            else if((koma.koma_name!=Koma_Pawn)||false)
            {
                vecMove.push_back(Move(i,j));
            }
            else if((koma.koma_name!=Koma_Pawn)||false)
            {
                if(j!=(this->y)-1)
                {
                    vecMove.push_back(Move(i,j));
                }
            }
        }
    }

    return vecMove;
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
