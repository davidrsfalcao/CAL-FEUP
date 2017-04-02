/*
* Cidade.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/

#include "Cidade.h"

Cidade::Cidade(){
  nome = "";
  coordenadas = new Coordenadas();
  hoteis = *(new std::vector<Alojamento*>()) ;
}

Cidade::Cidade(unsigned int id, std::string nome, Coordenadas coordenadas, std::vector<Alojamento*> hoteis){
  this->id = id;
  this->nome = nome;
  this->coordenadas = coordenadas;
  this->hoteis = hoteis;
}

Coordenadas Cidade::getCoordenadas(){
  return coordenadas;
}

Alojamento* Cidade::HotelMaisBarato(int dia, int mes){

  std::vector<Alojamento*>::iterator it = hoteis.begin();

  Alojamento *hotel = new Alojamento();
  int preco_min = 999999999;
  int preco_temp = 0;


  for(;it != hoteis.end(); it++)
  {
    preco_temp = (*it)->getPreco(dia,mes);
    if (preco_temp < preco_min){
      preco_min = preco_temp;
      hotel = (*it);
    }

  }

  return hotel;
}

unsigned int Alojamento::getId(){
  return id;
}
