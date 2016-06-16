#ifndef __GAMEBOARD_H_
#define __GAMEBOARD_H_

#include <vector>
#include "AnimalShougiSkoma.h"

typedef class _gameboard{
public:
    _gameboard();
    _gameboard& initial_board();

    std::vector<Move> koma_can_go(unsigned int koma_id);
    std::vector<Move> koma_can_go(unsigned int koma_x,unsigned int koma_y);

    std::vector<Move> koma_can_drop(unsigned int koma_id);
    std::vector<Move> koma_can_drop(Owner owner,unsigned int index);

    _gameboard& koma_move(unsigned int koma_id,Move dest);
    _gameboard& koma_move(unsigned int koma_id,unsigned int dest_x,unsigned int dest_y);
    _gameboard& koma_move(unsigned int koma_x,unsigned int koma_y,Move dest);
    _gameboard& koma_move(unsigned int koma_x,unsigned int koma_y,unsigned int dest_x,unsigned int dest_y);
    _gameboard& koma_move(Owner owner,unsigned int index,Move dest);
    _gameboard& koma_move(Owner owner,unsigned int index,unsigned int dest_x,unsigned int dest_y);

    bool is_win(Owner player);
    bool is_checkmate(Owner player);
    bool is_check(Owner player);
    bool is_check(Owner player,unsigned int koma_id,unsigned int dest_x,unsigned int dest_y);
protected:
    _gameboard& set_owner_where(unsigned int koma_id,Owner owner,Where where);
    _gameboard& set_owner(unsigned int koma_id,Owner owner);
    _gameboard& set_where(unsigned int koma_id,Where where);

    Move& where_koma(unsigned int koma_id);
    bool is_koma_on_board(unsigned int koma_id);
    bool is_koma_in_hand(unsigned int koma_id);

    virtual bool pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y)=0;
    bool is_koma_can_move_in(unsigned int koma_id,unsigned int board_x,unsigned int board_y);
    bool is_koma_id(unsigned int koma_id);

    _gameboard& koma_go(unsigned int koma_x,unsigned int koma_y,unsigned int dest_x,unsigned int dest_y);
    _gameboard& koma_drop(unsigned int owner,unsigned int index,unsigned int dest_x,unsigned int dest_y);

    unsigned int x,y;
    std::vector<std::vector<int> > board;
    std::vector<int> owner_hand[owner_total];
    std::vector<Koma*> koma_list;
private:

} Gameboard;

typedef class _small_gameboard:public _gameboard{
public:
    _small_gameboard();
protected:
    virtual bool pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y);
private:

}SGameboard;

typedef class _midium_gameboard:public _gameboard{
public:
    _midium_gameboard();
protected:
    virtual bool pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y);
private:

}MGameboard;

typedef class _normal_gameboard:public _gameboard{
public:
    _normal_gameboard();
protected:
    virtual bool pawn_spec_rule(unsigned int koma_id,unsigned int board_x,unsigned int board_y);
private:

}NGameboard;
typedef class _normal_gameboard LGameboard;

#endif // __GAMEBOARD_H_
