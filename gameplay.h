#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include<QObject>

class Gameplay
{
public:
    Gameplay();

    void reset();
    void put(int row,int col);
    QString getCurrentVoard();
    QString getWhosTurn();
    void hasSomeoneWon();
    QString whosWinner();

private:

};

#endif // GAMEPLAY_H
