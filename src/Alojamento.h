/*
* Alojamento.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_ALOJAMENTO_H_
#define SRC_ALOJAMENTO_H_

#include "Epoca.h"
#include <vector>
#include <string>
#include <iostream>


class Alojamento {
private:
	std::string nome;
	std::vector<Epoca*> epocas;

public:
	/**
	* Constructor sem parametros da Classe Alojamento
	*
	*/
	Alojamento();
	/**
	* Construtor com parametros da Classe Alojamento
	*
	* @param nome Nome do Alojamento
	* @param epocas Vector com as epocas em que existem diferentes precos
	*/
	Alojamento(std::string nome, std::vector<Epoca*>epocas);
	/**
	* Função que retorna a Epoca de uma data
	*
	* @param dia Dia da data que se quer saber a epoca
	* @param mes Mes da data que se quer saber a epoca
	*
	* @return A Epoca em que a data se encontra
	*/
	Epoca* getEpoca(int dia, int mes);
	/**
	* Função que retorna o Nome do Alojamento
	*
	* @return O Nome do Alojamento
	*/
	std::string getNome();
	/**
	* Função que retorna O preco de uma data
	*
	* @param dia Dia da data que se quer saber o preco
	* @param mes Mes da data que se quer saber o preco
	*
	* @return O preco do Alojamento na Data pretendida
	*/
	int getPreco(int dia, int mes);
	/**
	* Função que retorna um vetor com as Epocas
	*
	* @return As epocas em que ha precos diferentes no Alojamento
	*/
	std::vector<Epoca*> getTodasEpocas();
	/**
	*	para mostrar um Alojamento
	*
	* @param of ostream para mostrar o alojamento
	*	@param ht alojamento que vai ser mostrado
	*/
	friend std::ostream & operator <<(std::ostream &of, const Alojamento &ht);

};




#endif /* SRC_ALOJAMENTO_H_ */
