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
	* @brief Construtor da classe Coordenadas com inicializacaoo de x e y
	*/
	Coordenadas(int x, int y);
	/**
	* @brief Funcao que retorna a Coordenada X
	*
	* @return A Coordenada X
	*/
	int getX();
	/**
	* @brief Funcao que retorna a Coordenada Y
	*
	* @return A Coordenada Y
	*/
	int getY();
	/**
	* @brief Funcao que define a Coordenada X
	*
	* @param x A Coordenada x que vai ser definida
	*/
	void setX(int x);
	/**
	* @brief Funcao que define a Coordenada Y
	*
	* @param y A Coordenada y que vai ser definida
	*/
	void setY(int y);
	/**
	* @brief Funcao que define a Coordenada X e a Coordenada Y
	*
	* @param x A Coordenada x que vai ser definida
	* @param y A Coordenada y que vai ser definida
	*/
	void setCoordenadas(int x, int y);
	/**
	*	@brief para mostrar coordenadas
	*
	* @param of ostream para mostrar as coordenadas
	*	@param coord coordenadas que vao ser mostradas
	*/
	friend std::ostream & operator <<(std::ostream &of, const Coordenadas &coord);


};

#endif /* SRC_COORDENADAS_H_ */
