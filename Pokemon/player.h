//
//  player.h
//  Pokemon
//
//  Created by Oscar  Sandoval Arellano  on 11/11/18.
//  Copyright © 2018 Oscar  Sandoval Arellano . All rights reserved.
//

#ifndef player_h
#define player_h
#include <iostream>
#include <list>
#include "pokemon.h"
#include "item.h"
#include <exception>
#include <string>
#include <cmath>
using namespace std;
class PlayerException : public exception{
private:
    string msg;
public:
    explicit PlayerException(const char* message) : msg(message) {}
    explicit PlayerException(const string& message) :msg(message) {}
    virtual ~PlayerException() throw () {}
    virtual const char* what() const throw () {
        return msg.c_str();
    }
};
class Player{
public:
    //Constructor
    Player();
    //Constructor copia
    Player(const Player &copy);
    //Constructor parametrizado
    Player(const std::string &line);
    //Menu
    void Menu();
    //Informacion
    void information();
    void verPokemones();
    void verBackPack();
    //setters
    void setCoins(const int &);
    void setName(const std::string&);
    void setPokemones(Pokemon &);
    void setBuy(const unsigned &);
    void setSale(const unsigned &);
    void setRuta(const string &);
    //getters
    string getName();
    int getCoins();
    string getRuta();
    //Funciones de la tienda
    void readItem();
    void menuShop();
    void comprarArticulos();
    void venderArticulos();
    //////Archivos///////////////Guardar Partidas//////////////////
    void savePokemones();
    void saveData();
    void addBackPack();
    //////////////////Leer Archivos/////////////
    void readPokemon(const string&);
    void readBackPack(const string&);
    ////Ultima etapa/////////Explorar
    void Explorar();
    void encontrarPokemonSalvaje();
    void encontrarCoins();
    void capturarPokemon(Pokemon&);
    void CentroPokemon();
    void hospitalPokemon();
    void levelPokemon(Pokemon &);
    ///Randoms//////
    int randomSituation(int&);
    int randomCoins(int&);
    int randomPokemon(int&);
    void randomPokeBolas(int&);
    //ToString
    std::string toString();
    //Serializar el objeto
    friend std::ostream& operator << (std::ostream& os, Player& elem);
    //Operator =
    Player operator = (const Player& player);
    //Operator ==
    bool operator == (const Player game)const;
private:
    string name;
    int coins;
    list<Pokemon> pokemones;
    list<Item> backPack;
    list<Item> shop;
    string ruta;
};
//Constructores
Player::Player():coins(10000){
    
}
//Constructor Copia
Player::Player(const Player &copy):name(copy.name),coins(copy.coins),backPack(copy.backPack),shop(copy.shop),pokemones(copy.pokemones),ruta(copy.ruta){}
//Constructor parametrizado
Player::Player(const string &line){
    
}
//Menu
void Player::Menu(){
    string opc;
    system("clear");
    do{
        cout<<"\t\tMenu de Jugador"<<endl;
        cout<<"\t\t\t\t"<<getName()<<endl;
        cout<<"1)Informacion"<<endl
        <<"2)Ver Pokemones"<<endl
        <<"3)BackPack"<<endl
        <<"4)Centro Pokemon"<<endl
        <<"5)Explorar"<<endl
        <<"6)//Exit///"<<endl
        <<"Eliga una opcion : ";
        getline(cin,opc);
        if(opc=="1")
            information();
        else if(opc=="2")
            verPokemones();
        else if(opc=="4")
            CentroPokemon();
        else if(opc=="3")
            verBackPack();
        else if(opc=="5")
            Explorar();
        else if(opc=="6")
            cout<<"Hasta pronto"<<endl;
        else{
            cout<<"Opcion no valida"<<endl;
            system("clear");
        }
    }while(opc!="6");
}
//Informacion
void Player::information(){
    system("clear");
    cout<<"Nombre : "<<this->name<<endl
    <<"Monedas : "<<this->coins<<std::endl;
    verBackPack();
}
//Setters
void Player::setName(const std::string &Name){
    this->name=Name;
}
void Player::setCoins(const int & coins){
    this->coins=coins;
}
void Player::setPokemones(Pokemon &p){
    pokemones.push_back(p);
}
void Player::setBuy(const unsigned int &price){
    if(price>coins){
        throw PlayerException("Erros, proceso de Venta :,(");
    }
    this->coins=coins-price;
}
void Player::setSale(const unsigned int &sale){
    coins+=sale;
}
void Player::setRuta(const string &rut){
    ruta=rut;
   // Cuando llegamos a este punto el usuario ya escogio su pokemon y todo, momento de crear los archivos correspondientes
    //para esa informacion
}
//SavePokemones
void Player::savePokemones(){
    string aux=ruta;
    list<Pokemon>::iterator it;
    aux+="/Pokemones.txt";
    ofstream archive(aux.c_str(),ios::out);
    if(!archive.is_open()){
        cout<<"No se pudo abrir el archivo SavePokemones"<<endl;
        return;
    }
    for(it=pokemones.begin();it!=pokemones.end();++it)
        archive<<*it;
    archive.close();
}
//Add Backpack to disk
void Player::addBackPack(){
    string myStr=ruta;
    list<Item>::iterator it;
    myStr+="/BackPack.txt";
    ofstream archive;
    archive.open(myStr.c_str(),ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo AddBackPack"<<endl;
        return;
    }
    for(it=backPack.begin();it!=backPack.end();it++){
        archive<<*it;
    }
    archive.close();
}
//Guardar Informacion
void Player::saveData(){
    string myStr=ruta;
    myStr+="/Data.txt";
    ofstream archive;
    archive.open(myStr.c_str(),ios::out);
    if(archive.fail()){
        cout<<"No se pudo abrir el archivo SaveData"<<endl;
        return;
    }
    archive<<name<<" |"<<coins<<"|"<<ruta;
    archive.close();
}
//Leer Pokemones
void Player::readPokemon(const string& line){
    Pokemon aux;
    string myStr;
    unsigned myInt;
    int i;
    //name|level|hellpoints||attack|experience|moves,0
    stringstream stream(line);
    getline(stream,myStr,'|');
    aux.setName(myStr);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setLevel(myInt);
    getline(stream,myStr,'|');
    i=stoi(myStr);
    aux.setHellPoints(i);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setAttack(myInt);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setExperience(myInt);
    getline(stream,myStr,'|');
    aux.readMoves(myStr);
    pokemones.push_back(aux);
}
//Leer BackPack
void Player::readBackPack(const string & line){
    Item aux;
    stringstream stream(line);
    string myStr;
    unsigned myInt;
    //name|price|value|description|stock
    getline(stream,myStr,'|');
    aux.setName(myStr);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setPrice(myInt);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setValue(myInt);
    getline(stream,myStr,'|');
    aux.setDescription(myStr);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    aux.setStock(myInt);
    backPack.push_back(aux);
    readItem();
}
//getTers
string Player::getName(){
    return name;
}
int Player::getCoins(){
    return coins;
}
string Player::getRuta(){
    return ruta;
}
//Verpokemones
void Player::verPokemones(){
    system("clear");
    if(pokemones.size()==0){
        std::cout<<"No tienes pokemones disponibles";
        return;
    }
    std::list<Pokemon>::iterator it=pokemones.begin();
    it=pokemones.begin();
    for(it=pokemones.begin();it!=pokemones.end();++it)
        cout<<it->toString()<<endl;
}
//Ver BackPack
void Player::verBackPack(){
    if(backPack.size()==0){
        cout<<"BackPack vacio :,("<<endl;
        return;
    }
    size_t i=1;
    list<Item>::iterator it;
    for(it=backPack.begin();it!=backPack.end();++it){
        cout<<"Articulo "<<i<<endl;
        cout<<it->toString()<<endl;
        i++;
    }
}
//ToString
std::string Player::toString(){
    std::string line;
    char a[20];
    sprintf(a,"Coins : %d\n",this->coins);
    line="Nombre : "+this->name+"\n";
    line+=a;
    return line;
}
//Serializar
std::ostream& operator <<(std::ostream& os,Player& game){
    os<<game.name<<"|"<<game.coins<<"|"<<game.ruta;
    return os;
}
//Operador de asignacion
Player Player::operator=(const Player &player){
    name=player.name;
    coins=player.coins;
    return *this;
}
//Operador ==
bool Player::operator==(const Player game)const{
    return this->name==game.name;
}
//Leer tienda
void Player::readItem(){
    ifstream archive("/Users/drumssand/Desktop/Pokemon/Pokemon/items.txt");
    string line;
    if(!archive.is_open()){
        cout<<"No se pudo abrir la tienda"<<endl;
        return;
    }
    while(getline(archive,line)){
        Item aux(line);
        shop.push_back(aux);
    }
}
//Tienda Menu
void Player::menuShop(){
    string opc;
    system("clear");
    do{
        cout<<"\t\tShop Pokemon"<<endl
        <<"1)Comprar Articulos"<<endl
        <<"2)Vender Articulo"<<endl
        <<"3)Regresar"<<endl
        <<"Elige una opcion : ";
        getline(cin,opc);
        if(opc=="1")
            comprarArticulos();
        else if(opc=="2")
            venderArticulos();
        else if(opc=="3"){
            cout<<"Vuelve pronto :,) "<<endl;
        }
        else{
            system("clear");
            cout<<"Opcion no valida"<<endl;
        }
    }while(opc!="3");
}
//Comprar Articulos
void Player::comprarArticulos(){
    if(shop.size()==0)
        readItem();
    int aux=1;
    string myStr;
    size_t venta;
    list<Item>::iterator it;
    list<Item>::iterator ite;
    unsigned stock;
    do{
        system("clear");
        aux=1;
        cout<<"\t\t\t\t\tUsuario : "<<name<<endl<<"\t\t\t\t\tCoins Disponibles : "<<coins<<endl<<endl;
        cout<<"\t\tBienvenido"<<endl
        <<"\tEstos son los articulos que tenemos disponibles "<<endl<<endl;
        it=shop.begin();
        while(aux<=9){
            cout<<aux<<")"<<it->getName()<<"\t";
            it++;
            aux++;
            cout<<aux<<")"<<it->getName()<<"\t  ";
            it++;
            aux++;
            cout<<aux<<")"<<it->getName()<<"\t  "<<endl;
            it--;
            it--;
            cout<<"Precio : "<<it->getPrice()<<"\t";
            it++;
            cout<<" Precio : "<<it->getPrice()<<"\t";
            it++;
            cout<<"   Precio : "<<it->getPrice()<<"\t"<<endl<<endl;
            it++;
            aux++;
        }
        cout<<endl<<"\t\t  "<<aux<<")Salir"<<endl<<endl;
        cout<<"Elige una opcion : ";
        cin>>aux;
        cin.ignore();
        if(aux==shop.size()+1)
            return;
    }while(aux<=0||aux>shop.size());
    it=shop.begin();
    for(int i=0;i<aux-1;i++)
        it++;
    system("clear");
    cout<<"\t\t\tComprar Articulo"<<endl;
    cout<<it->toStringShop();
    cout<<"Cuantos "<<it->getName()<<" quieres comprar  : ";
    cin>>venta;
    cin.ignore();
    if(venta<=0){
        cout<<"No seas payaso xd"<<endl;
        return;
    }
    unsigned price=it->getPrice();
    price*=venta;
    if(price>getCoins()){
        cout<<"Uppps!!, no tienes suficientres coins para obtener este articulo"<<endl;
        return;
    }
    try{
        setBuy(price);
    }catch(PlayerException ex){
        cout<<"Uppsss!!!, algo salio mal :,(,no tienes suficiente dinero"<<endl;
        return;
    }
    for(ite=backPack.begin();ite!=backPack.end();++ite){
        if(*it==*ite){
            stock=ite->getStock();
            stock+=venta;
            ite->setStock(stock);
            cout<<"Proceso de venta de Articulo fue realizado con exito "<<endl;
            addBackPack();
            saveData();
            return;
        }
    }
    stock=1;
    stock*=venta;
    it->setStock(stock);
    backPack.push_back(*it);
    addBackPack();
    saveData();
    cout<<"Proceso de venta de Articulo fue realizado con exito "<<endl;
}
//Venta de Articulos
void Player::venderArticulos(){
    if(backPack.size()==0){
        cout<<"Upss!, no tienes articulos"<<endl;
        cout<<"Vuelve cuando haya comprado algun articulo"<<endl;
        return;
    }
    list<Item>::iterator it;
    int aux=1;
    list<Item>::iterator ite;
    int myInt;
    int venta;
    do{
        system("clear");
        aux=1;
        cout<<"\t\t\t\t\tUsuario : "<<name<<endl<<"\t\t\t\t\tCoins Disponibles : "<<coins<<endl<<endl;
        cout<<"\t\t\tVender Aticulos"<<endl<<endl;
        cout<<"\tEstos son los articulos que "<<endl<<"\tNos interesa comprarte : "<<endl<<endl;
        for(it=backPack.begin();it!=backPack.end();++it){
            cout<<aux<<")"<<it->getName()<<endl;
            cout<<" stock :  "<<it->getStock()<<endl;
            aux++;
        }
        cout<<endl<<aux<<")Regresar"<<endl<<"¿Que nos vas a vender?  : ";
        cin>>aux;
        cin.ignore();
        if(aux==backPack.size()+1)
            return;
    }while(aux<=0||aux>backPack.size());
    it=backPack.begin();
    for(int i=0;i<aux-1;++i)
        it++;
    do{
        system("clear");
        cout<<"//////////Proceso de venta de Articulo/////////"<<endl;
        cout<<it->toStringSale();
        cout<<"¿Que quieres hacer?"<<endl
        <<"1.Vender"<<endl
        <<"2.Salir"<<endl
        <<"Elige una opcion : ";
        cin>>aux;
        cin.ignore();
        if(aux==2)
            return;
    }while(aux>2||aux<=0);
    if(it->getStock()>1){
        cout<<it->toStringSale();
        cout<<"Cuantas "<<it->getName()<<" quieres vender : "<<endl;
        cin>>venta;
        cin.ignore();
        if(venta>it->getStock()||venta<=0){
            cout<<"No sea payaso xD"<<endl;
            return;
        }
        aux=it->getStock();
        aux-=venta;
        myInt=it->getPriceSale();
        myInt*=venta;
        it->setStock(aux);
        setSale(myInt);
        if(it->getStock()==0)
            backPack.erase(it);
        addBackPack();
        saveData();
        cout<<"Hiciste lo correcto Bob"<<endl;
        cout<<"Disfruta tus coins, y vuelve mas seguido :v "<<endl;
        return;
    }
    setSale(it->getPriceSale());
    backPack.erase(it);
    addBackPack();
    saveData();
    cout<<"Hiciste lo correcto Bob"<<endl;
    cout<<"Disfruta tus coins, y vuelve mas seguido :v "<<endl;
}
void Player::Explorar(){
    int opc;
    switch(randomSituation(opc)){
        case 1:
            encontrarPokemonSalvaje();
            savePokemones();
            break;
        case 2:
            encontrarCoins();
            saveData();
            break;
        case 3:
            system("clear");
            cout<<"Todo esta tranquilo por aqui :3 "<<endl;
            break;
    }
}
int Player::randomSituation(int &opc){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,3);
    opc=dis(gen);
    return opc;
}
void Player::encontrarPokemonSalvaje(){
    int pekemon,index;
    string opc;
    size_t attack;
    randomPokemon(pekemon);
    Pokemon salvaje(pekemon);
    cout<<salvaje<<endl;
    list<Pokemon>::iterator it=pokemones.begin();
    system("clear");
    cout<<":O HAZ ENCONTRADO UN  POKEMON SALVAJE"<<endl;
    do{
        attack=0;
        cout<<"_________________________"<<"\t\t_______________________"<<endl
            <<"|   Pokemon Salvaje     |"<<"\t\t   "<<it->getName()<<"      "<<endl
            <<"|_______________________|"<<"\t\t|_____________________|"<<endl
        <<"Level : "<<salvaje.getLevel()<<"\tExperience : "<<salvaje.getExperience()
        <<"\t\tLevel : "<<it->getLevel()<<"\tExperience : "<<it->getExperience()<<endl
        <<"\tHell points "<<salvaje.getHellPoints()<<"\t\t\t\tHell Points : "<<it->getHellPoints()<<endl
        <<"Attack : "<<salvaje.getAttack()<<"\tAvailable : "<<salvaje.getAvailable()
        <<"\t\tAttack : "<<it->getAttack()<<"\tAvailable : "<<it->getAvailable()<<endl;
        cout<<endl<<"\t\tOpciones : "<<endl
        <<"\t1)Fight"<<endl
        <<"\t2)Item"<<endl
        <<"\t3)Pokemon"<<endl
        <<"\t4)Run :C"<<endl
        <<"\tQue haremos : ";
        getline(cin,opc);
        if(opc=="1"){
            if(it->getAvailable()==10){
                system("clear");
                cout<<"Tu pokemon "<<it->getName()<<"  esta agotado, no tiene mas movimientos disponibles"<<endl;
            }
            else if(it->getHellPoints()==0){
                system("clear");
                cout<<"Tu pokemon no tiene mas Health Points"<<endl;
            }
            else{
                index=it->getAvailable()+1;
                salvaje.hitHellPoints(it->getAttack());
                it->setAvaliable(index);
                if(salvaje.getHellPoints()==0)
                    attack=0;
                else
                    attack=1;
                system("clear");
            }
        }
        else if(opc=="2"){
            if(backPack.size()==0){
                system("clear");
                cout<<"Tu backPack esta vacion"<<endl;
            }
            else{
                int op,pokeBola;
                list<Item>::iterator ite=backPack.begin();
                size_t i;
                i=1;
                string pekeBall="Peke Ball";
                cout<<"  Articulo         Stock       Desciption  "<<endl;
                cout<<"------------------------------------------------------"<<endl;
                while(ite!=backPack.end()){
                    cout<<i<<"."<<ite->toStringBackPack();
                    ite++;
                    i++;
                }
                do{
                    cout<<"Que producto usaremos  : "<<endl;
                    cin>>op;
                    cin.ignore();
                }while(op<=0||op>backPack.size());
                ite=backPack.begin();
                for(int i=1;i<op;i++)
                    ite++;
                cout<<*ite;
                if(ite->getName()=="Peke Ball"){
                    randomPokeBolas(pokeBola);
                    if(pokeBola<=50){
                        system("clear");
                        cout<<"Demonios, El pokemon Salvaje esquivo tu Poke Ball"<<endl;
                        attack=1;
                    }
                    else{
                        system("clear");
                        capturarPokemon(salvaje);
                        int stock;
                        stock=ite->getStock()-1;
                        ite->setStock(stock);
                        if(ite->getStock()==0){
                            backPack.erase(ite);
                        }
                        return;
                      
                    }
                }
                else if(ite->getName()=="Great Ball"){
                    randomPokeBolas(pokeBola);
                    if(pokeBola<15){
                        system("clear");
                        cout<<"Demonios, El pokemon Salvaje esquivo tu Great Ball"<<endl;
                        attack=1;
                    }
                    else{
                        system("clear");
                        capturarPokemon(salvaje);
                        int stock;
                        stock=ite->getStock()-1;
                        ite->setStock(stock);
                        if(ite->getStock()==0){
                            backPack.erase(ite);
                        }
                        return;
                    }
                }
                else if(ite->getName()=="Ultra Ball"){
                    randomPokeBolas(pokeBola);
                    if(pokeBola<10){
                        system("clear");
                        cout<<"Demonios, El pokemon Salvaje esquivo tu Ultra Ball"<<endl;
                        attack=1;
                    }
                    else{
                        system("clear");
                        capturarPokemon(salvaje);
                        int stock;
                        stock=ite->getStock()-1;
                        ite->setStock(stock);
                        if(ite->getStock()==0){
                            backPack.erase(ite);
                        }
                        return;
                    }
                }
                else if(ite->getName()=="Max Potion"){
                    int potion(it->getMaxHp());
                    it->setHellPoints(potion);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                }
                else if(ite->getName()=="Hyper Potion"){
                    int potion(it->getMaxHp());
                    it->setHellPoints(potion);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                }
                else if(ite->getName()=="Super Potion"){
                    int potion(it->getMaxHp());
                    it->setHellPoints(potion);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                }
                else if(ite->getName()=="Potion"){
                    int potion(it->getMaxHp());
                    it->setHellPoints(potion);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                }
                else if(ite->getName()=="Hp Up    "){
                    int potion(it->getMaxHp());
                    int max=potion+2560;
                    it->setHellPoints(max);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                    
                }
                else if(ite->getName()=="Protein"){
                    int potion(it->getMaxHp());
                    int max=potion+2560;
                    it->setHellPoints(max);
                    potion=0;
                    it->setAvaliable(potion);
                    cout<<"Tu pokemon se ha hecho mas fuertee"<<endl;
                }
                int stock;
                stock=ite->getStock()-1;
                ite->setStock(stock);
                if(ite->getStock()==0){
                    backPack.erase(ite);
                }
            }
        }
        else if(opc=="3"){
            if(pokemones.size()==1){
                cout<<"No tienes Pokemones disponibles"<<endl;
            }
            else{
                list<Pokemon>::iterator aux;
                int i=1;
                cout<<"\t\t\tLista de Pokemones"<<endl<<endl;
                for(aux=pokemones.begin();aux!=pokemones.end();++aux){
                    cout<<i<<")"<<aux->getName()<<endl;
                    i++;
                }
                cout<<"Que pokemon quieres utilizar : ";
                cin>>i;
                cin.ignore();
                aux=pokemones.begin();
                for(size_t a=0;a<i-1;a++)
                    aux++;
                it=aux;
                attack=1;
                system("clear");
            }
        }
        else if(opc=="4"){
            cout<<"Estuvo cerca, pero debes armarte de valor"<<endl;
            return;
        }
        else{
            cout<<"Si no te decides rapido, el pokemon te atacara :C"<<endl;
        }
        if(attack==1){
            it->hitHellPoints(salvaje.getAttack());
        }
    }while(opc!="4" && salvaje.getHellPoints()>0);
    cout<<"Felicidades has Vencido a este pokemon Salvaje"<<endl;
    cout<<it->getName()<<" ha obtenido "<<salvaje.getWinExperience()<<" puntos de experiencia "<<endl;
    it->setWinExperience(salvaje.getWinExperience());
    savePokemones();
}
void Player::encontrarCoins(){
    int money;
    randomCoins(money);
    if(money<0){
        system("clear");
        if(coins==0){
            cout<<"Lo bueno de no tener nada es que no te pueden quitar nada :v"<<endl;
        }
        cout<<"Demonios, te han robado "<<money*-1<<" coins"<<endl<<"sorry sir :C"<<endl;
    }
    else if(money>0){
        system("clear");
        cout<<"Yay!!!, has encontrado "<<money<<" coins"<<endl<<"genial uwur"<<endl;
    }
    else{
        system("clear");
        cout<<"No has encontrado nada"<<endl;
        return;
    }
    if(money*-1>=coins)
        coins=0;
    coins+=money;
}
int Player::randomCoins(int &money){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-70,50);
    money=dis(gen);
    return money;
}
int Player::randomPokemon(int &poke){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,19);
    poke=dis(gen);
    return poke;
}
void Player::randomPokeBolas(int &win){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);
    win=dis(gen);
}
void Player::capturarPokemon(Pokemon & salvaje){
    string nombre;
    int repetir;
    cout<<"Buen tiro!!!!, has capturado un pokemon salvaje"<<endl;
    do{
        repetir=0;
        cout<<"\t\tAsinale un nombre al nuevo Pokemon :3"<<endl
        <<"Nombre : ";
        getline(cin,nombre);
        for(list<Pokemon>::iterator it=pokemones.begin();it!=pokemones.end();++it)
            if(nombre==it->getName()){
                cout<<"Ya tienes un pokemon con este nombre, intenta otro"<<endl;
                repetir=1;
            }
    }while(repetir==1);
    salvaje.setName(nombre);
    pokemones.push_back(salvaje);
    savePokemones();
    cout<<"Se ha añadido correctamente  a tus Pokemones "<<name<<" Yayyyy"<<endl;
}
void Player::CentroPokemon(){
    string opc;
    system("clear");
    do{
        cout<<"\t\tBienvenido al Centro Pokemon"<<endl<<endl;
        cout<<"1)Rehabilitacion a tus Pokemon"<<endl
        <<"2)Poke Tienda"<<endl
        <<"3)Regresar"<<endl
        <<"Vamos, elige una opcion : ";
        getline(cin,opc);
        if(opc=="1"){
            hospitalPokemon();
            savePokemones();
        }
        else if(opc=="2")
            menuShop();
        else if(opc=="3"){
            system("clear");
            cout<<"Adios vaquero"<<endl;
        }
        else{
            cout<<"Dato no valido compañero"<<endl;
        }
    }while(opc!="3");
}
void Player::hospitalPokemon(){
    int i,opc;
    list<Pokemon>::iterator it;
    cout<<"\t\tCual de tus pequeñines necesita Rehabilitacion  : "<<endl;
    i=1;
    for(it=pokemones.begin();it!=pokemones.end();it++){
        cout<<i<<")"<<it->toStringHospital()<<endl;
        i++;
    }
    cout<<endl<<endl<<"Internar : ";
    cin>>opc;
    cin.ignore();
    it=pokemones.begin();
    for(i=1;i<opc;i++){
        it++;
    }
    levelPokemon(*it);
    i=it->getMaxHp();
    it->setHellPoints(i);
    i=0;
    it->setAvaliable(i);
    cout<<it->getName()<<" Esta listo para la batalla, se ha rehabilitado correctamente"<<endl;
}
void Player::levelPokemon(Pokemon &poke){
    unsigned aux(poke.getLevel());
    int myInt;
    if(poke.getExperience()>=pow(2,aux)){
        aux++;
        poke.setLevel(aux);
        cout<<"Felicidades tu pokemon es ahora nivel "<<aux<<endl;
        aux=poke.getMaxHp()+poke.getMaxHp()/2;
        poke.setMaxHp(aux);
        myInt=aux;
        poke.setHellPoints(myInt);
        aux=poke.getAttack()+poke.getAttack()/2;
        poke.setAttack(aux);
    }
}
#endif /* player_h */
