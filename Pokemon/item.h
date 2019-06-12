//
//  item.h
//  Pokemon
//
//  Created by Oscar  Sandoval Arellano  on 11/13/18.
//  Copyright © 2018 Oscar  Sandoval Arellano . All rights reserved.
//

#ifndef item_h
#define item_h
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Item{
public:
    Item();
    Item(const Item&);
    Item(const string&);
    //setters
    void setName(const string&);
    void setPrice(const unsigned&);
    void setValue(const unsigned&);
    void setDescription(const string&);
    void setStock(const unsigned&);
    //ToString
    string toString();
    string toStringSale();
    string toStringShop();
    string toStringBackPack();
    //getters
    string getName()const;
    unsigned getValue();
    unsigned getPrice();
    string getDescription();
    unsigned getPriceSale();
    unsigned getStock();
    //Serializacion
    friend ostream& operator << (ostream& os,Item& elem);
    //Operador =
    Item operator = (const Item& item);
    //Funcion Amiga para Serealizar el objeto
    friend ostream& operator<< (ostream& os,Item& poke);
    //Operador ==
    bool operator == (const Item&elem)const;
private:

    string name;
    unsigned price;
    unsigned value;
    string description;
    unsigned stock;
};
//Constructor
Item::Item(){
    
}
//Constructor copia
Item::Item(const Item& cpy):name(cpy.name),price(cpy.price),value(cpy.value),description(cpy.description),stock(cpy.stock){
    
}
//Constructor parametrizado
Item::Item(const string & line){
    //name|price|value|description
    string myStr;
    int myInt;
    stringstream stream(line);
    getline(stream,myStr,'|');
    setName(myStr);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    setPrice(myInt);
    getline(stream,myStr,'|');
    myInt=stoi(myStr);
    setValue(myInt);
    getline(stream,myStr,'|');
    setDescription(myStr);
    setStock(0);
}
//ToString
string Item::toString(){
    string myStr;
    char aux[30];
    myStr="Nombre: "+this->name+"\n";
    sprintf(aux,"Precio : %d\n",this->price);
    myStr+=aux;
    sprintf(aux,"Value  : %d\n",this->value);
    myStr+=aux;
    sprintf(aux,"Stock  : %d\n",stock);
    myStr+=aux;
    myStr+="Descripcion :\n"+this->description;
    return myStr;
}
//ToString Venta
string Item::toStringSale(){
    string myStr;
    char aux[35];
    unsigned sale=price/2;
    myStr="Articulo\nNombre: "+this->name+"\n";
    sprintf(aux,"Stock  : %d\n",stock);
    myStr+=aux;
    sprintf(aux,"Precio de compra  : %d c/u\n",sale);
    myStr+=aux;
    return myStr;
}
//ToString Shop
string Item::toStringShop(){
    string myStr;
    char aux[30];
    myStr="Articulo\nNombre: "+this->name+"\n";
    sprintf(aux,"Precio : %d\n",this->price);
    myStr+=aux;
    sprintf(aux,"Value  : %d\n",this->value);
    myStr+=aux;
    myStr+="Descripcion :\n"+this->description+"\n\n";
    return myStr;
}
//ToString BackPack
string Item::toStringBackPack(){
    string myStr;
    char aux[5];
    sprintf(aux," %d ",getStock());
    myStr="| "+getName()+" |  "+aux+"  | "+getDescription()+" |\n";
    return myStr;
}
//Setters
void Item::setName(const string &n){
    name=n;
}
void Item::setPrice(const unsigned int &p){
    price=p;
}
void Item::setStock(const unsigned int &s){
    stock=s;
}
void Item::setValue(const unsigned int &v){
    value=v;
}
void Item::setDescription(const string &d){
    description=d;
}
//Getters
string Item::getName()const{
    return name;
}
unsigned Item::getValue(){
    return value;
}
unsigned Item::getPrice(){
    return price;
}
unsigned Item::getStock(){
    return stock;
}
string Item::getDescription(){
    return description;
}
unsigned Item::getPriceSale(){
    return price/2;
}
//operator =
Item Item::operator=(const Item &item){
    name=item.name;
    value=item.value;
    price=item.price;
    stock=item.stock;
    description=item.description;
    return *this;
}
//Funcion Amiga para Serealizar el objeto
ostream& operator<< (ostream& os,Item& product){
    //nombre|precio|value|descripcion
    os<<product.name<<"|"<<product.price<<"|"<<product.value<<"|"<<product.description<<"|"<<product.stock<<"\n";
    return os;
}
//Operador de comparacion
bool Item::operator==(const Item &elem)const{
    return this->name==elem.name;
}
#endif /* item_h */
