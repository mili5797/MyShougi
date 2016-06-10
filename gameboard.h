#ifndef __GAMEBOARD_H_
#define __GAMEBOARD_H_

#include <vector>
#include "AnimalShougiSkoma.h"

typedef class _gameboard{
public:
    _gameboard();
    _gameboard& initial_board();
protected:
    unsigned int x,y;
    std::vector<std::vector<int> > board;
    std::vector<Koma> koma_list;
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
