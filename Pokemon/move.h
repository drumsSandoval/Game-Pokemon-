//
//  move.h
//  Pokemon
//
//  Created by Oscar  Sandoval Arellano  on 11/11/18.
//  Copyright © 2018 Oscar  Sandoval Arellano . All rights reserved.
//

#ifndef move_h
#define move_h
#include <iostream>
using namespace std;
class Move{
public:
    //Constructor
    Move();
    //Constructor copia
    Move(const Move &copy);
    //Constructor parametrisado
    Move( string &line);
    //Setters
    void setName(string &n);
    void setAvaliable(int &a);
    //ToString
    string toString();
    //Getters
    string getName();
    unsigned getAvaliable();
    unsigned getMax();
    //Funcion Amiga para Serealizar el objeto
    friend std::ostream& operator<< (std::ostream& os,  Move& move);
private:
    string name;
    const unsigned  max=10;//Cantidad maxima de veces que se puede realizar el movimiento
    unsigned avalilable;//cuantas veces te quedan del movimiento
};
Move::Move():avalilable(0){}
Move::Move(const Move &copy):name(copy.name),avalilable(copy.avalilable){}
Move::Move(string &line):name(line),avalilable(0){
    
}
void Move::setName(string &n){
    name=n;
}
void Move::setAvaliable(int &a){
    avalilable=a;
}
string Move::getName(){
    return name;
}
unsigned Move::getAvaliable(){
    return avalilable;
}
unsigned Move::getMax(){
    return max;
}
string Move::toString(){
    string myStr;
    char aux[30];
    myStr="Movimiento : "+name+"\n";
    sprintf(aux,"Movimientos Maximos : %d\n",max);
    myStr+=aux;
    sprintf(aux,"Movimientos utilizados: %d\n",avalilable);
    myStr+=aux;
    return myStr;
}
ostream& operator << (ostream& os,Move &move){
    //name|avaliable
    os<<move.name<<","<<move.avalilable;
    return os;
}
#endif /* move_h */
