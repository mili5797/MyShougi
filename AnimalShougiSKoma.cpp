#include "koma.h"
#include "AnimalShougiSKoma.h"

int _king::total_num_king=0;
int _elephant::total_num_elephant=0;
int _giraffe::total_num_giraffe=0;
int _pawn::total_num_pawn=0;

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

    _king::add_total_num_king();
}

int _king::get_total_num()
{
    return _king::total_num_king;
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

    _elephant::add_total_num_elephant();
}

int _elephant::get_total_num()
{
    return _elephant::total_num_elephant;
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

    _giraffe::add_total_num_giraffe();
}

int _giraffe::get_total_num()
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

    _pawn::add_total_num_pawn();
}

int _pawn::get_total_num()
{
    return _pawn::total_num_pawn;
}

void _pawn::add_total_num_pawn()
{
    _pawn::total_num_pawn++;
    return;
}

