/*
* Cidade.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef CIDADE_H_
#define CIDADE_H_
#include <vector>
#include <iostream>
#include "Alojamento.h"
#include "Coordenadas.h"


class Cidade {
private:
	unsigned int id;
	std::string nome;
	Coordenadas coordenadas;
	std::vector<Alojamento*> hoteis;
	std::vector<int> destinos; // {id1,custo1,tempo1,id2,custo2,tempo2}


public:
	/**
	* @brief Constructor sem parametros da Classe Cidade
	*
	*/
	Cidade();
	/**
	* @brief Construtor com parametros da Classe Cidade
	*
	* @param id ID da cidade
	* @param nome Nome da Cidade
	* @param coordenadas Coordenadas da cidade no mapa
	* @param hoteis Vector com os hoteis disponiveis na Cidade
	* @param destinos Vector com os destinos para os quais e possivel voar a partir da cidade
	*/
	Cidade(unsigned int id, std::string nome, Coordenadas coordenadas, std::vector<Alojamento*> hoteis, std::vector<int> destinos);
	/**
	* @brief Função que retorna o Id da cidade
	*
	* @return O Id da Cidade
	*/
	unsigned int getId();
	/**
	* @brief Função que define o Id da cidade
	*
	* @param id ID para ser definido
	*/
	void setId(unsigned int id);
	/**
	* @brief Função que define o Nome da cidade
	*
	* @param nome Nome para ser definido
	*/
	void setNome(std::string nome);
	/**
	* @brief Função que retorna o Nome da cidade
	*
	* @return O Nome da Cidade
	*/
	std::string getNome();
	/**
	* @brief Função que retorna as coordenadas da cidade
	*
	* @return Coordenadas da Cidade
	*/
	Coordenadas getCoordenadas();
	/**
	* @brief Função que define as coordenadas da cidade
	*
	* @param coordenadas Coordenadas para serem definidas
	*/
	void setCoordenadas(Coordenadas coordenadas);
	/**
	* @brief Função que retorna os hoteis da cidade
	*
	* @return Vector com os Heteis da Cidade
	*/
	std::vector<Alojamento*> getTodosHoteis();
	/**
	* @brief Função que retorna o Hotel mais barato da cidade numa determindada data
	*
	* @param dia Dia da data
	* @param mes Mes da data
	* @return Hotel mais barato na data pedida
	*/
	Alojamento* HotelMaisBarato(int dia, int mes);
	/**
	* @brief Função que retorna os destinos para os quais e possivel ir a partir da cidade
	*
	* @return vector com os Destinos para os quais e possivel ir a partir da cidade
	*/
	std::vector<int> getDestinos();
	/**
	* @brief Função que retorna o numero de destinos para os quais e possivel ir a partir da cidade
	*
	* @return numero de destinos para os quais e possivel ir a partir da cidade
	*/
	unsigned int getNumeroDestinos();
	/**
	* @brief Função que retorna o ID de um destino
	* @param n Destino que se pretende saber o Id
	*
	*
	* @return Id do destino
	*/
	int getIdDestino(int n);
	/**
	* @brief Função que retorna o Custo de Viagem para um destino
	* @param n Destino que se pretende saber o custo da viagem
	*
	* @return O custo da viagem para o destino
	*/
	int getCustoViagem(int n);
	/**
	* @brief Função que retorna o tempo de Viagem para um destino
	* @param n Destino que se pretende saber o tempo da viagem
	*
	* @return O tempo em minutos da viagem para o destino
	*/
	int getTempoViagem(int n);
	/**
	*	@brief para mostrar uma Cidade
	*
	* @param of ostream para mostrar a cidade
	*	@param ci cidade que vai ser mostrada
	*/
	friend std::ostream & operator <<(std::ostream &of, const Cidade &ci);
	/**
	*	@brief Funcao que compara duas cidades
	*
	*	@param ci cidade a ser comparada
	*
	*	@return True se as cidades forem iguais,False se nao
	*/
	bool operator==(const Cidade &ci);
	/**
	*	@brief Funcao que compara duas cidades
	*
	*	@param ci cidade a ser comparada
	*
	*	@return True se as cidades nao forem iguais,False se forem
	*/
	bool operator!=(const Cidade &ci);
};



#endif /* CIDADE_H_ */
