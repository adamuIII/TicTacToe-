#include "gameplay.h"

QString value {"X"};
Gameplay::Gameplay()
{

}

void Gameplay::reset(){



}
void Gameplay::put(int row,int col){


}
QString Gameplay::getCurrentVoard(){
    return "x=ox=xo";


}

QString Gameplay::getWhosTurn(){
    if (value=="X")
        value="O";
    else
        value="X";
    return value;


}

void Gameplay::hasSomeoneWon(){


}
QString Gameplay::whosWinner(){
    return "";


}
