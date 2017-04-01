/*
* Epoca.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/

#include "Epoca.h"
#include <string>

Epoca::Epoca(){
  nome = "";
  dia_inicio = 0;
  dia_fim = 0;
  mes_inicio = 0;
  mes_fim = 0;
  preco = 0;
}

Epoca::Epoca(std::string nome, int dia_inicio, int mes_inicio, int dia_fim, int mes_fim, int preco){
  this->nome = nome;
  this->dia_inicio = dia_inicio;
  this->dia_fim = dia_fim;
  this->mes_inicio = mes_inicio;
  this->mes_fim = mes_fim;
  this->preco = preco;
}

int Epoca::getDiaInicio(){
  return dia_inicio;
}

int Epoca::getDiaFim(){
  return dia_fim;
}

int Epoca::getMesInicio(){
  return mes_inicio;
}

int Epoca::getMesFim(){
  return mes_fim;
}

int Epoca::getPreco(){
  return preco;
}

std::string Epoca::getNome(){
  return nome;
}
