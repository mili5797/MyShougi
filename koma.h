#ifndef __KOMA_H_
#define __KOMA_H_

#include <vector>

#ifndef NUM_PLAYER
#define NUM_PLAYER 2
#endif // NUM_PLAYER

typedef enum _where{on_table,in_hand,now_hidden,where_total} Where;
typedef enum _owner{pub=0,player1,player2,owner_total=NUM_PLAYER+1} Owner;
typedef enum _dir{Dir_Forward,Dir_RFront,Dir_Right,Dir_RBack,Dir_Backward,Dir_LBack,Dir_Left,Dir_LFront,Dir_total} Direct;

typedef class _koma_move{
public:
    _koma_move();
    _koma_move& set_move(int x,int y);
    _koma_move& set_if(int num,...);
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
protected:
    static int total_num;
    Where where;
    Owner owner;
    bool can_promotion;
    bool promotion;
}Koma; //abstract class of koma

typedef class _rush_koma:Koma{
public:
    _rush_koma();
protected:
    bool direct[Dir_total];
}Rush; //abstract class of koma which using rush to move

typedef class _jump_koma:Koma{
public:
    _jump_koma();
protected:
     std::vector<Move> can_go;
}Jump; //abstract class of koma which using jump to move

#endif // __KOMA_H_
