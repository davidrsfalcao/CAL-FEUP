/*
* Coordenadas.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_COORDENADAS_H_
#define SRC_COORDENADAS_H_
#include <iostream>

class Coordenadas {

private:
	int x; //longitude
	int y; //latitude

public:
	/**
	* @brief Construtor da classe Coordenadas
	*/
	Coordenadas();

	/**
	* @brief Construtor da classe Coordenadas com inicializa��o de x e y
	*/
	Coordenadas(int x, int y);

	int getX();

	int getY();

	void setX(int x);

	void setY(int y);

	void setCoordenadas(int x, int y);

	friend std::ostream & operator <<(std::ostream &of, const Coordenadas &coord);


};

#endif /* SRC_COORDENADAS_H_ */
