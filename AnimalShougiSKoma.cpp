#include "koma.h"
#include "AnimalShougiSKoma.h"

unsigned int _king::total_num_king=0;
unsigned int _elephant::total_num_elephant=0;
unsigned int _giraffe::total_num_giraffe=0;
unsigned int _pawn::total_num_pawn=0;

_king::_king()
{
    this->promotion=false;
    this->can_promotion=false;

    this->can_go.push_back(Move(0,1));
    this->can_go.push_back(Move(1,1));
    this->can_go.push_back(Move(1,0));
    this->can_go.push_back(Move(1,-1));
    this->can_go.push_back(Move(0,-1));
    this->can_go.push_back(Move(-1,-1));
    this->can_go.push_back(Move(-1,0));
    this->can_go.push_back(Move(-1,1));

    this->koma_name=Koma_Lion;
    _king::add_total_num_king();
}

unsigned int _king::get_total_num()
{
    return _king::total_num_king;
}

_koma& _king::koma_promote()
{
    if(!this->promotable())
    {
        throw "Undifined error in King::koma_promote";
    }
    return *this;
}

void _king::add_total_num_king()
{
    _king::total_num_king++;
    return;
}


_elephant::_elephant()
{
    this->promotion=false;
    this->can_promotion=false;

    this->can_go.push_back(Move(1,1));
    this->can_go.push_back(Move(1,-1));
    this->can_go.push_back(Move(-1,-1));
    this->can_go.push_back(Move(-1,1));

    this->koma_name=Koma_Elephant;
    _elephant::add_total_num_elephant();
}

unsigned int _elephant::get_total_num()
{
    return _elephant::total_num_elephant;
}

_koma& _elephant::koma_promote()
{
    if(!this->promotable())
    {
        throw "Undifined error in Elephant::koma_promote";
    }
    return *this;
}

void _elephant::add_total_num_elephant()
{
    _elephant::total_num_elephant++;
    return;
}


_giraffe::_giraffe()
{
    this->promotion=false;
    this->can_promotion=false;

    this->can_go.push_back(Move(0,1));
    this->can_go.push_back(Move(1,0));
    this->can_go.push_back(Move(0,-1));
    this->can_go.push_back(Move(-1,0));

    this->koma_name=Koma_Giraffe;
    _giraffe::add_total_num_giraffe();
}

_koma& _giraffe::koma_promote()
{
    if(!this->promotable())
    {
        throw "Undifined error in Giraffe::koma_promote";
    }
    return *this;
}

unsigned int _giraffe::get_total_num()
{
    return _giraffe::total_num_giraffe;
}

void _giraffe::add_total_num_giraffe()
{
    _giraffe::total_num_giraffe++;
    return;
}


_pawn::_pawn()
{
    this->promotion=false;
    this->can_promotion=true;

    this->can_go.push_back(Move(0,1));

    this->koma_name=Koma_Chick;
    _pawn::add_total_num_pawn();
}

_koma& _pawn::koma_promote()
{
    if(!this->promotable())
    {
        throw "Undifined error in Pawn::koma_promote";
    }
    this->can_go.push_back(Move(1,1));
    this->can_go.push_back(Move(1,0));
    this->can_go.push_back(Move(0,-1));
    this->can_go.push_back(Move(-1,0));
    this->can_go.push_back(Move(-1,1));
    this->koma_name=Koma_Chicken;

    this->promotion=true;

    //x -1 0 1
    //   . . .  1
    //   . p .  0
    //     .   -1
    //          y

    return *this;
}

_koma& _pawn::koma_be_token(Owner new_owner)
{
    this->where=in_hand;
    this->owner=new_owner;
    this->can_go.erase(this->can_go.begin()+1,this->can_go.begin()+5);
    this->koma_name=Koma_Chick;

    this->promotion=false;
    this->can_promotion=true;

    return *this;
}

unsigned int _pawn::get_total_num()
{
    return _pawn::total_num_pawn;
}

void _pawn::add_total_num_pawn()
{
    _pawn::total_num_pawn++;
    return;
}


