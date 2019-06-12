//
//  gamer.hpp
//  Pokemon
//
//  Created by Oscar  Sandoval Arellano  on 11/11/18.
//  Copyright © 2018 Oscar  Sandoval Arellano . All rights reserved.
//
#ifndef gamer_hpp
#define gamer_hpp
#include <vector>
#include <algorithm>
#include "player.h"
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;
class Game{
public:
    //Constructor
    Game();
    //Crear
    void crearPartida();
    //Cargar
    void cargarPartida(int &idx);
    //Eliminar
    void eliminarPlayer(int &idx);
    //Menu
    void menu();
    //Mostrar Partidas
    void mostrarPartidas();
    //Elegir pokemon
    void elegirPokemon();
        /////Etapa 4/// Echauri
    //Leer Partidas
    void leerPartidas();
    //CargarPlayers
    void loadGame(const string&);
    //Guardar Partidas
    void saveGame(size_t&);
    //Eliminar Player
    void deleteGame(const string&);
    //Save Data
    void saveData(string&);
private:
    vector<Player> players;
    vector<string> partidasGuardadas;
    const size_t max=3;
    size_t size;
    Player player;
};
//Constructor
Game::Game():size(0){
    leerPartidas();
    menu();
}
//crear Partida
void Game::crearPartida(){
    if(players.size()==max){
        cout<<"Accion no permitida, numero de partidas Saturado"<<endl;
        return;
    }
    string name;
    size_t repetir;
    int coins= 10000;
    player.setCoins(coins);
    do{
        system("clear");
        repetir=0;
        cout<<"/////Bienvenido////"<<endl;
        cout<<"Elige un nombre para continuar : ";
        getline(cin,name);
        if(players.size()>0){
            for(size_t i=0;i<players.size();i++)
                if(name==players[i].getName()){
                    repetir=1;
                    cout<<"Existe un usuario con este nombre"<<endl;
                }
        }
    }while(repetir==1);
    player.setName(name);
    players.push_back(player);
    cout<<"Usuario creado"<<std::endl;
    elegirPokemon();
    repetir=players.size()-1;
    saveGame(repetir);
    players[players.size()-1].Menu();
}
//Elegir Pokemon
void Game::elegirPokemon(){
    Pokemon Bulbasaur("BULBASAUR");
    Pokemon Squirtle("SQUIRTLE");
    Pokemon Charizard("CHARIZARD");
    Pokemon Pikachu("PIKACHU");
    string opc;int repetir;
    system("clear");
    do{
        repetir=0;
        cout<<"Elegir Pokemon\n";
        cout<<"Estos son los pokemones que tienes disponibles hata el momento"<<endl;
        cout<<"\t\tPokemones :"<<endl
        <<"1.Bulbasaur"<<endl
        <<"2.Squirtle"<<endl
        <<"3.Charizard"<<endl
        <<"4.Pikachu"<<endl
        <<"Escoge sabiamente :";
        getline(cin,opc);
        if(opc=="1")
            players[players.size()-1].setPokemones(Bulbasaur);
        else if(opc=="2")
            players[players.size()-1].setPokemones(Squirtle);
        else if(opc=="3")
            players[players.size()-1].setPokemones(Charizard);
        else if(opc=="4")
            players[players.size()-1].setPokemones(Pikachu);
        else{
            system("clear");
            cout<<"Opcion no valida, vuelve a intentarlo"<<endl;
            repetir=1;
        }
    }while(repetir==1);
}
//Cargar partida
void Game::cargarPartida(int &idx){
    system("clear");
    players[idx].Menu();
}
//Mostrar partidas
void Game::mostrarPartidas(){
    system("clear");
    if(players.size()==0)
        cout<<"No hay partidas que mostrar"<<endl;
    for(int i=0;i<players.size();i++){
        cout<<"Partida "<<i+1<<endl<<players[i].toString();
     
    }
}
//Eliminar
void Game::eliminarPlayer(int &idx){
    if(idx>players.size()||idx<=0){
        cout<<"La partida No existe"<<endl;
        return;
    }
    idx--;
    string myStr=(players.begin()+idx)->getRuta();
    partidasGuardadas.erase(partidasGuardadas.begin()+idx);
    deleteGame(myStr);
    players.erase(players.begin()+idx);
    size--;
}
//Menu
void Game::menu(){
    string opc;
    int idx;
    system("clear");
    do{
        cout<<"\t\tPokeMon"<<endl
        <<"\tMenu"<<endl
        <<"1) Nueva Partida"<<endl
        <<"2) Mostrar Partidas"<<endl
        <<"3) Cargar partida"<<endl
        <<"4) Eliminar Partida"<<endl
        <<"5) Exit"<<endl<<"Elige una opcion : ";
        getline(cin,opc);
        if(opc=="1")
            crearPartida();
        else if(opc=="2")
            mostrarPartidas();
        else if(opc=="3"){
            if(players.size()==0){
                cout<<"No hay partidas, que cargar"<<endl;
            }
            else{
                mostrarPartidas();
                cout<<"Que partida quieres cargar : "<<endl;
                cin>>idx;
                cin.ignore();
                if(idx>players.size())
                    cout<<"Opcion no valida "<<endl;
                else{
                    idx--;
                    cargarPartida(idx);
                }
            }
        }
        else if(opc=="4"){
            if(players.size()==0)
                cout<<"Accion no permitida "<<endl;
            else{
                mostrarPartidas();
                cout<<"Que partida deseas eliminar : ";
                cin>>idx;
                cin.ignore();
                eliminarPlayer(idx);
            }
        }
        else if(opc=="5"){
            cout<<"Hasta pronto"<<endl;
        }
        else{
            system("clear");
            cout<<"Opcion no valida"<<endl;
        }
        
    }while(opc!="5");
}
///////////////Etapa 4 Echauri////////////////////
void Game::leerPartidas(){
    bool band;
    string line;
    ifstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/Partidas.txt");
    if(!archive.is_open()){
        cout<<"Partidas.txt no se pudo abrir"<<endl;
        return;
    }
    band=false;
    while(getline(archive,line)){
        band=true;
        cout<<line<<endl;
        partidasGuardadas.push_back(line);
        loadGame(line);
    }
    if(band==false)
        cout<<"\t\t\tBienvenido\n"<<endl;
}
void Game::loadGame(const string &load){
    string game;
    string aux;
    string line,myStr;
    int myInt;
    if(load=="Player1"){
        ifstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/Player1/Data.txt");
        if(!archive.is_open()){
            cout<<"Data.txt no se pudo abrir Player1"<<endl;
            return;
        }
        getline(archive,line);
        stringstream stream(line);
        getline(stream,myStr,'|');
        player.setName(myStr);
        getline(stream,myStr,'|');
        myInt=stoi(myStr);
        player.setCoins(myInt);
        getline(stream,myStr,'|');
        player.setRuta(myStr);
        archive.close();
        players.push_back(player);
        ifstream archive2("/Users/drumssand/Desktop/Pokemon/Pokemon/Player1/Pokemones.txt");
        if(!archive2.is_open()){
            cout<<"Pokemones.txt no se pudo abrir Player1"<<endl;
            return;
        }
        while(getline(archive2,line)){
            players[players.size()-1].readPokemon(line);
        }
        archive2.close();
        ifstream archive3("/Users/drumssand/Desktop/Pokemon/Pokemon/Player1/BackPack.txt");
        if(!archive3.is_open()){
            cout<<"BackPack.txt no se pudo abrir Player1"<<endl;
            return;
        }
        while(getline(archive3,line)){
            players[players.size()-1].readBackPack(line);
        }
        archive3.close();
    }
    else if(load=="Player2"){
        ifstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/Player2/Data.txt");
        if(!archive.is_open()){
            cout<<"Data.txt no se pudo abrir Player2"<<endl;
            return;
        }
        getline(archive,line);
        stringstream stream(line);
        getline(stream,myStr,'|');
        player.setName(myStr);
        getline(stream,myStr,'|');
        myInt=stoi(myStr);
        player.setCoins(myInt);
        getline(stream,myStr,'|');
        player.setRuta(myStr);
        archive.close();
        players.push_back(player);
        ifstream archive2("/Users/drumssand/Desktop/Pokemon/Pokemon/Player2/Pokemones.txt");
        if(!archive2.is_open()){
            cout<<"Pokemones.txt no se pudo abrir Player2"<<endl;
            return;
        }
        while(getline(archive2,line)){
            players[players.size()-1].readPokemon(line);
        }
        archive2.close();
        ifstream archive3("/Users/drumssand/Desktop/Pokemon/Pokemon/Player2/BackPack.txt");
        if(!archive3.is_open()){
            cout<<"BackPack.txt no se pudo abrir Player2"<<endl;
            return;
        }
        while(getline(archive3,line)){
            players[players.size()-1].readBackPack(line);
        }
        archive3.close();
    }
    else if(load=="Player3"){
        ifstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/Player3/Data.txt");
        if(!archive.is_open()){
            cout<<"Data.txt no se pudo abrir Player3"<<endl;
            return;
        }
        getline(archive,line);
        stringstream stream(line);
        getline(stream,myStr,'|');
        player.setName(myStr);
        getline(stream,myStr,'|');
        myInt=stoi(myStr);
        player.setCoins(myInt);
        getline(stream,myStr,'|');
        player.setRuta(myStr);
        archive.close();
        players.push_back(player);
        ifstream archive2("/Users/drumssand/Desktop/Pokemon/Pokemon/Player3/Pokemones.txt");
        if(!archive2.is_open()){
            cout<<"Pokemones.txt no se pudo abrir Player3"<<endl;
            return;
        }
        while(getline(archive2,line)){
            players[players.size()-1].readPokemon(line);
        }
        archive2.close();
        ifstream archive3("/Users/drumssand/Desktop/Pokemon/Pokemon/Player3/BackPack.txt");
        if(!archive3.is_open()){
            cout<<"BackPack.txt no se pudo abrir Player3"<<endl;
            return;
        }
        while(getline(archive3,line)){
            players[players.size()-1].readBackPack(line);
        }
        archive3.close();
    }
    else{
        cout<<":V";
        return;
    }
}
void Game::deleteGame(const string &ruta){
    string aux=ruta;
    int i;
    aux+="/Data.txt";
    cout<<"Ruta -> "<<aux<<endl;
    ofstream archive;
    archive.open(aux.c_str(),ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo Data deleteGame"<<endl;
        return;
    }
    archive.close();
    aux=ruta;
    aux+="/Pokemones.txt";
    archive.open(aux.c_str(),ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo  Pokemones deleteGame"<<endl;
        return;
    }
    archive.close();
    aux=ruta;
    aux+="/BackPack.txt";
    archive.open(aux.c_str(),ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo BackPack deleteGame"<<endl;
        return;
    }
    archive.close();
    archive.open("/Users/drumssand/Desktop/Pokemon/Pokemon/Partidas.txt",ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo Partidad deleteGame"<<endl;
        return;
    }
    i=0;
    while(i<partidasGuardadas.size()){
        archive<<partidasGuardadas[i]<<endl;
        i++;
    }
    archive.close();
    
}
void Game::saveData(string &myStr){
    myStr+="/Data.txt";
    ofstream archive(myStr.c_str(),ios::out);
    if(!archive.is_open()){
        cout<<"No se pudo abrir el archivo SaveData"<<endl;
        return;
    }
    archive<<players[players.size()-1];
    archive.close();
}
void Game::saveGame(size_t &aux){
    if(players.size()==0)
        return;
    string partida;
    string myStr;
    switch (players.size()-1) {
        case 0:
            myStr="Player1";
            partida="/Users/drumssand/Desktop/Pokemon/Pokemon/Player1";
            break;
        case 1:
            myStr="Player2";
            partida="/Users/drumssand/Desktop/Pokemon/Pokemon/Player2";
            break;
        case 2:
            partida="/Users/drumssand/Desktop/Pokemon/Pokemon/Player3";
            myStr="Player3";
            break;
            
    }
    players[aux].setRuta(partida);
    players[aux].savePokemones();
    ofstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/Partidas.txt",ios::app);
    if(!archive.is_open()){
        cout<<"No se pudo abrir el archivo SaveGame"<<endl;
        return;
    }
    archive<<myStr<<endl;
    archive.close();
    partidasGuardadas.push_back(myStr);
    saveData(partida);
}
#endif /* gamer_hpp */
