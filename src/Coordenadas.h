/*
* Coordenadas.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_COORDENADAS_H_
#define SRC_COORDENADAS_H_

class Coordenadas {

private:
	int x; //longitude
	int y; //latitude

public:
	/**
	* @brief Construtor da classe Coordenadas
	*/
	Coordenadas() {
		x = 0;
		y = 0;
	}

	/**
	* @brief Construtor da classe Coordenadas com inicializa��o de x e y
	*/
	Coordenadas(int x, int y);

	int getX();

	int getY();

	void setX(int x);

	void setY(int y);

	void setCoordenadas(int x, int y)
	{
		this->x = x;
		this->y = y;
	}




}

#endif /* SRC_COORDENADAS_H_ */
