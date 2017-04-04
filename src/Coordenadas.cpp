/*
 * Coordenadas.cpp
 *
 *  Created on: 01/04/2017
 *      Author: David
 */

#include "Coordenadas.h"

Coordenadas::Coordenadas() {
  x = 0;
  y = 0;
}

Coordenadas::Coordenadas(int x, int y) {
  this->x = x;
  this->y = y;
}

int Coordenadas::getX(){
  return x;
}

int Coordenadas::getY(){
  return y;
}

void Coordenadas::setX(int x){
  this->x = x;
}

void Coordenadas::setY(int y){
  this->y = y;
}

void Coordenadas::setCoordenadas(int x, int y){
  this->x = x;
  this->y = y;
}

std::ostream & operator <<(std::ostream &of, const Coordenadas &coord){
	of <<"Coordenadas: "<<coord.x << "-" << coord.y << std::endl;

	return of;
}
