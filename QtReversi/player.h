#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

class Player
{
public:
    virtual ~Player() {}
    virtual void get_move(const Board&, int& r, int& c) = 0;
    virtual void skip_move(const Board&) {}
    virtual void win() {}
    virtual void lose() {}
    virtual void tie() {}
protected:
    explicit Player(Color color);
    const Color _color;
private:
    Player(const Player&);
    Player& operator=(const Player&);

};

inline Player::Player(Color color)
    : _color(color)
{
}

#endif //PLAYER_H
