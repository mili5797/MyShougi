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
    static int get_total_num();
    static void add_total_num();
protected:
    Where where;
    Owner owner;
    bool can_promotion;
    bool promotion;
private:
    static int total_num;
}Koma; //abstract class of koma

typedef class _rush_koma:public Koma{
public:

protected:
    bool direct[Dir_total];
}Rush; //abstract class of koma which using rush to move

typedef class _jump_koma:public Koma{
public:

protected:
     std::vector<Move> can_go;
}Jump; //abstract class of koma which using jump to move

#endif // __KOMA_H_
