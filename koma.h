#ifndef __KOMA_H_
#define __KOMA_H_

#include <vector>

#ifndef NUM_PLAYER
#define NUM_PLAYER 2
#endif // NUM_PLAYER

#ifndef END_OF_ARG
#define END_OF_ARG '~'
#endif // END_OF_ARG

typedef enum _where{on_table=0,in_hand,now_hidden,where_total} Where;
typedef enum _owner{pub=0,player1,player2,owner_total=NUM_PLAYER+1} Owner;
typedef enum _dir{Dir_Forward=0,Dir_RFront,Dir_Right,Dir_RBack,Dir_Backward,Dir_LBack,Dir_Left,Dir_LFront,Dir_total} Direct;
typedef enum _koma_name{Koma_King=0,Koma_Elephant,Koma_Giraffe,Koma_Pawn} Name;

typedef class _koma_move{
public:
    _koma_move();
    _koma_move(int move_x,int move_y);
    _koma_move(int move_x,int move_y,int num_if,...);
    _koma_move& set_move(int move_x,int move_y);
    _koma_move& set_if(int num_if,...);
    unsigned int get_num_if();
    int get_move_x();
    int get_move_y();
    std::vector<int> get_if_x();
    std::vector<int> get_if_y();
private:
    int x,y;
    std::vector<int> if_x,if_y; //if there(if_x,if_y) is koma then can't move
}Move; //data class

typedef class _koma{
public:
    _koma();

    _koma& promote();
    bool promotable();

    Where get_where();
    Owner get_owner();
    Name get_koma_name();

    static unsigned int get_total_num();
protected:
    virtual _koma& koma_promote()=0;
    virtual _koma& koma_be_token(Owner new_owner);

    Where where;
    Owner owner;
    bool can_promotion;

    Name koma_name;
    friend class _gameboard;

    bool direct[Dir_total]; //Rush
    std::vector<Move> can_go; //Jump
    bool promotion;
    bool rush,jump;
private:
    static void add_total_num();
    static unsigned int total_num;
}Koma; //abstract class of koma

typedef class _rush_koma:public Koma{
public:
    _rush_koma();
protected:
    virtual _koma& koma_promote()=0;
}Rush; //abstract class of koma which using rush to move

typedef class _jump_koma:public Koma{
public:
    _jump_koma();
protected:
    virtual _koma& koma_promote()=0;
}Jump; //abstract class of koma which using jump to move

#endif // __KOMA_H_
