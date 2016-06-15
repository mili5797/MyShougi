#ifndef __ANIMAL_SHOUGI_S_KOMA_H_
#define __ANIMAL_SHOUGI_S_KOMA_H_

#include "koma.h"

typedef class _king:public Jump{
public:
    _king();
    static unsigned int get_total_num();
protected:

private:
    virtual _koma& koma_promote();
    static void add_total_num_king();
    static unsigned int total_num_king;
}King;
typedef class _king Oushou; //The king is called Oushou in Shougi in Japanese
typedef class _king Ou; //The Oushou is also called Ou in short
typedef class _king Lion; //The king is called Lion in Animal Shougi

typedef class _elephant:public Jump{
public:
    _elephant();
    static unsigned int get_total_num();
protected:

private:
    virtual _koma& koma_promote();
    static void add_total_num_elephant();
    static unsigned int total_num_elephant;
}Elephant;

typedef class _giraffe:public Jump{
public:
    _giraffe();
    static unsigned int get_total_num();
protected:

private:
    virtual _koma& koma_promote();
    static void add_total_num_giraffe();
    static unsigned int total_num_giraffe;
}Giraffe;

typedef class _pawn:public Jump{
public:
    _pawn();
    static unsigned int get_total_num();
protected:

private:
    virtual _koma& koma_promote();
    virtual _koma& koma_be_token(Owner new_owner);
    static void add_total_num_pawn();
    static unsigned int total_num_pawn;
}Pawn;
typedef class _pawn Fuhyou; //The pawn is called Fuhyou in Shougi in Japanese
typedef class _pawn Fu; //The Fuhyou is also called Fu in short
typedef class _pawn chick; //The pawn is called chick in Animal Shougi
/*
typedef class _tokin:Pawn{
public:
    _tokin();
private:

} Tokin; // The promoted pawn is called Tokin in Japanese
typedef class _tokin To; //The Tokin is also called To in short
typedef class _tokin checken; //The tokin is called checken in Animal Shougi
*/
#endif // __ANIMAL_SHOUGI_S_KOMA_H_
