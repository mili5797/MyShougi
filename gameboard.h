#ifndef __GAMEBOARD_H_
#define __GAMEBOARD_H_

#include <vector>
#include "AnimalShougiSkoma.h"

typedef class _gameboard{
public:
    _gameboard();
    _gameboard& initial_board();
protected:
    _gameboard& set_owner_where(unsigned int koma_id,Owner owner,Where where);
    _gameboard& set_owner(unsigned int koma_id,Owner owner);
    _gameboard& set_where(unsigned int koma_id,Where where);
    std::vector<Move> koma_can_go(unsigned int koma_id);
    std::vector<Move> koma_can_go(unsigned int koma_x,unsigned int koma_y);
    std::vector<Move> koma_can_put(unsigned int koma_id);
    std::vector<Move> koma_can_put(Owner owner,unsigned int index);
    bool if_koma_can_move_in(unsigned int koma_id,unsigned int board_x,unsigned int board_y);
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

private:

}SGameboard;

typedef class _midium_gameboard:public _gameboard{
public:
    _midium_gameboard();
protected:

private:

}MGameboard;

typedef class _normal_gameboard:public _gameboard{
public:
    _normal_gameboard();
protected:

private:

}NGameboard;
typedef class _normal_gameboard LGameboard;

#endif // __GAMEBOARD_H_
