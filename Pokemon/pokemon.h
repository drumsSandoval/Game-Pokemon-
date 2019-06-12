//
//  pokemon.h
//  Pokemon
//
//  Created by Oscar  Sandoval Arellano  on 11/11/18.
//  Copyright © 2018 Oscar  Sandoval Arellano . All rights reserved.
//

#ifndef pokemon_h
#define pokemon_h
#include <iostream>
#include <list>
#include "move.h"
#include <string>
#include <ctime>
#include <fstream>
#include <random>
using namespace std;
class Pokemon{
public:
    //Constructor
    Pokemon();
    //Constructor copia
    Pokemon(const Pokemon &cpy);
    //Constructor parametrisado
    Pokemon(string line);
    Pokemon(const int&);
    //Setters
    void setName(string n);
    void setLevel(unsigned &l);
    void setHellPoints(int &hp);
    void setAttack(unsigned &a);
    void setExperience(unsigned &e);
    void setWinExperience(unsigned);
    void setMaxHp(unsigned &m);
    void setMoves();
    void hitHellPoints(int hit);
    void setAvaliable(int&);
    ///////////////Leer MOVIMIENTOS DE PARTIDA////
    void readMoves(const string&);
    //getters
    string getName();
    unsigned getLevel();
    int getHellPoints();
    unsigned getAttack();
    unsigned getAvailable();
    unsigned getExperience();
    unsigned getMaxHp();
    unsigned getWinExperience();
    ///Etapa 5 Echauri/////
    void randomLevel();
    void randomHellPoints();
    void randomMaxHP();
    void randomAttack();
    void randomExperience();
    //ToString
    string toString();
    string toStringHospital();
    //Funcion Amiga para Serealizar el objeto
    friend std::ostream& operator<< (std::ostream& os,  Pokemon& poke);
    list<Move> moves;
private:
    enum types{
        acero=1,
        agua,
        dragon,
        electrico,
        fantasma,
        fuego,
        hada,
        hielo,
        hierba,
        insecto,
        normal,
        oscuro,
        pelea,
        psiquico,
        roca,
        tierra,
        venenoso,
        volador
    };
    types tipo;
    std::string name;//nombre
    unsigned  level;//level
    int hellPoints;//puntos de vida
    unsigned  maxHP;///puntos maximos de vida
    unsigned  attack;//ataque
    unsigned  experience;//experiencia
};
//Constructor
Pokemon::Pokemon():maxHP(15),level(5),hellPoints(15),attack(10),experience(20){
    
}
//Constructor copia
Pokemon::Pokemon( const Pokemon& cpy):name(cpy.name),level(cpy.level),hellPoints(cpy.hellPoints),maxHP(cpy.maxHP),attack(cpy.attack),experience(cpy.experience),tipo(cpy.tipo),moves(cpy.moves){}
//Constructor parametrisado pokemon usuario
Pokemon::Pokemon(string line):name(line),maxHP(15),level(5),hellPoints(15),attack(10),experience(20){
    if(line=="BULBASAUR")
        tipo=hierba;
    else if(line=="SQUIRTLE")
        tipo=agua;
    else if(line=="CHARIZARD")
        tipo=fuego;
    else if(line=="PIKACHU")
        tipo=electrico;
    else{
        tipo=normal;
    }
    setMoves();
}
//Constructor para pokemon salvaje
Pokemon::Pokemon(const int& t){
    switch(t){
        case 1:
            tipo=acero;
            break;
        case 2:
            tipo=agua;
            break;
        case 3:
            tipo=dragon;
            break;
        case 4:
            tipo=electrico;
            break;
        case 5:
            tipo=fantasma;
            break;
        case 6:
            break;
        case 7:
            tipo=fuego;
            break;
        case 8:
            tipo=hada;
            break;
        case 9:
            tipo=hielo;
            break;
        case 10:
            tipo=hierba;
            break;
        case 11:
            tipo=insecto;
            break;
        case 12:
            tipo=normal;
            break;
        case 13:
            tipo=oscuro;
            break;
        case 14:
            tipo=pelea;
            break;
        case 15:
            tipo=psiquico;
            break;
        case 16:
            tipo=roca;
            break;
        case 17:
            tipo=tierra;
            break;
        case 18:
            tipo=venenoso;
            break;
        case 19:
            tipo=volador;
            break;
    }
    setMoves();
    maxHP=15;
    randomLevel();
    randomHellPoints();
    randomAttack();
    randomExperience();
}
//setters
void Pokemon::setName(string n){
    name=n;
}
void Pokemon::setLevel(unsigned int &l){
    level=l;
}
void Pokemon::setMaxHp(unsigned int &m){
    maxHP=m;
}
void Pokemon::setAttack(unsigned int &a){
    attack=a;
}
void Pokemon::setHellPoints(int &hp){
    hellPoints=hp;
}
void Pokemon::setExperience(unsigned int &e){
    experience=e;
}
void Pokemon::setAvaliable(int & a){
    list<Move>::iterator it=moves.begin();
    it->setAvaliable(a);
}
//Golpear puntos de Vida
void Pokemon::hitHellPoints(int hit){
    if(hit>=hellPoints){
        hellPoints=0;
        return;
    }
    hellPoints-=hit;
}
//Sumar Experiencia
void Pokemon::setWinExperience(unsigned int e){
    experience+=e;
}
//Agregar Movimientos
void Pokemon::setMoves(){
    string line;
    string myStr;
    switch (tipo) {
        case acero:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/normal.txt";
            break;
        case agua:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/agua.txt";
            break;
        case dragon:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/dragon.txt";
            break;
        case electrico:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/electrico.txt";
            break;
        case fantasma:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/fantasma.txt";
            break;
        case fuego:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/fuego.txt";
            break;
        case hada:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/normal.txt";
            break;
        case hielo:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/hielo.txt";
            break;
        case hierba:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/hierba.txt";
            break;
        case insecto:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/insecto.txt";
            break;
        case normal:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/normal.txt";
            break;
        case oscuro:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/oscuro.txt";
            break;
        case pelea:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/pelea.txt";
            break;
        case psiquico:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/psiquico.txt";
            break;
        case roca:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/roca.txt";
            break;
        case tierra:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/tierra.txt";
            break;
        case venenoso:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/venenoso.txt";
            break;
        case volador:
            myStr="/Users/drumssand/Desktop/Pokemon/Pokemon/tipos/volador.txt";
            break;
    }
    ifstream archivo(myStr.c_str());
    if(!archivo.is_open()){
        cout<<"No se pudo abrir el archivo"<<endl
        <<myStr<<endl;
        return;
    }
    getline(archivo,line);
    Move aux(line);
    moves.push_back(aux);
}
//Leer Movimientos de partida
void Pokemon::readMoves(const string &line){
    stringstream stream(line);
    Move aux;
    int myInt;
    string myStr;
    getline(stream,myStr,',');
    aux.setName(myStr);
    getline(stream,myStr,',');
    myInt=stoi(myStr);
    aux.setAvaliable(myInt);
    moves.push_back(aux);
}
//Getters
string Pokemon::getName(){
    return name;
}
unsigned Pokemon::getLevel(){
    return level;
}
unsigned Pokemon::getMaxHp(){
    return maxHP;
}
int Pokemon::getHellPoints(){
    return hellPoints;
}
unsigned Pokemon::getAttack(){
    return attack;
}
unsigned Pokemon::getAvailable(){
    list<Move>::iterator it=moves.begin();
    return it->getAvaliable();
}
unsigned Pokemon::getExperience(){
    return experience;
}
unsigned Pokemon::getWinExperience(){
    return experience/2;
}
///////////Valores Random///////
//random Level
void Pokemon::randomLevel(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,4);
    level=dis(gen);

}
//Random hell Points;
void Pokemon::randomHellPoints(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10,15);
    hellPoints=dis(gen);
}
//Random Attack
void Pokemon::randomAttack(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(5,9);
    attack=dis(gen);

}
//Random Experience
void Pokemon::randomExperience(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(10,19);
    experience=dis(gen);
}
//ToString
string Pokemon::toString(){
    string myStr;
    char aux[30];
    list<Move>::iterator it;
    myStr="Nombre : "+name+"\n";
    sprintf(aux,"Level  : %d\n",level);
    myStr+=aux;
    sprintf(aux,"Hell Points : %d\n",hellPoints);
    myStr+=aux;
    sprintf(aux,"Ataque : %d\n",attack);
    myStr+=aux;
    sprintf(aux,"Experiencia : %d\n",experience);
    myStr+=aux;
    myStr+="\tMovimientos:\n";
    for(it=moves.begin();it!=moves.end();++it){
        myStr+=it->toString();
    }
    return myStr;
}
string Pokemon::toStringHospital(){
    string myStr;
    char aux[30];
    myStr="Nombre : "+name+"\n";
    sprintf(aux,"Health Points :  %d \n",getHellPoints());
    myStr+=aux;
    sprintf(aux,"Avaliable : %d",getAvailable());
    myStr+=aux;
    return myStr;
}
ostream& operator << (ostream &os, Pokemon &poke){
     list<Move>::iterator it;
    os<<poke.name<<"|"<<poke.level<<"|"<<poke.hellPoints<<"|"<<poke.attack<<"|"<<poke.experience<<"|";
    for(it=poke.moves.begin();it!=poke.moves.end();++it){
        os<<*it;
    }
    os<<endl;
    return os;
}
//name|level|hellpoints||attack|experience|moves,0
#endif /* pokemon_h */
