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
typedef enum _koma_name{Koma_King  = 0,Koma_Oushou  = 0,Koma_Ou  = 0,Koma_K  = 0,Koma_Lion=0     ,
                                                                                 Koma_Elephant=1 ,
                                                                                 Koma_Giraffe=2  ,
                        Koma_Pawn  = 3,Koma_Fuhyou  = 3,Koma_Fu  = 3,Koma_P  = 3,Koma_Chick=3    ,
                        Koma_pPawn = 4,Koma_Tokin   = 4,Koma_To  = 4,Koma_pP = 4,Koma_Chicken=4  ,
                        Koma_Gold  = 5,Koma_Kinshou = 5,Koma_Kin = 5,Koma_G  = 5,
                        Koma_Silver= 6,Koma_Ginshou = 6,Koma_Gin = 6,Koma_S  = 6,
                        Koma_pSilver=7,Koma_Narigin = 7,Koma_Zen = 7,Koma_pS = 7,
                        Koma_Knight= 8,Koma_Keima   = 8,Koma_Kei = 8,Koma_N  = 8,
                        Koma_pKnight=9,Koma_Narikei = 9,             Koma_pN = 9,
                        Koma_Lance =10,Koma_Kyousha =10,Koma_Kyou=10,Koma_L  =10,
                        Koma_pLance=11,Koma_Narikyou=11,Koma_An  =11,Koma_pL =11,
                        Koma_Rock  =12,Koma_Hisha   =12,Koma_Hi  =12,Koma_R  =12,
                        Koma_Dragon=13,Koma_Ryuuou  =13,Koma_Ryuu=13,Koma_pR =13,
                        Koma_Bishop=14,Koma_Kakugyou=14,Koma_Kaku=14,Koma_B  =14,
                        Koma_Horse =15,Koma_Ryuuma  =15,Koma_Uma =15,Koma_pB =15,
Name_total} Name;

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
    _koma(const _koma&);
    _koma(const _koma*);

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
