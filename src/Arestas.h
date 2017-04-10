/*
* Cidade.h
*
*  Created on: 08/04/2017
*      Author: David
*/

#ifndef ARESTAS_H_
#define ARESTAS_H_

class Aresta{
private:
	unsigned int id_origem;
	unsigned int id_destino;
	int custo;
	int tempo;

public:
	/**
	* @brief Constructor sem parametros da Classe Aresta
	*
	*/
	Aresta();
	/**
	* @brief Construtor com parametros da Classe Aresta
	*
	* @param id_origem ID da cidade de onde começa a areta
	* @param id_destino ID da cidade para onde vai a resta
	* @param custo Custo da viagem representada pela Aresta
	* @param tempo Tempo que demora a viagem representada pela Aresta
	*/
	Aresta(unsigned int id_origem, unsigned int id_destino, int custo, int tempo);
	/**
	* @brief Função que retorna o Id da cidade de origem da Aresta
	*
	* @return O Id da Cidade de origem da Aresta
	*/
	unsigned int getIdOrigem();
	/**
	* @brief Função que retorna o Id da cidade de destino da Aresta
	*
	* @return O Id da Cidade de destino da Aresta
	*/
	unsigned int getIdDestino();
	/**
	*	@brief Funcao que compara duas arestas pelos ids de origem
	*
	*	@param a Aresta a ser comparada
	*
	*	@return True se o id_origem de uma aresta for menor que o id_origem da outra,False se não.
	*/
	bool operator <(const Aresta a);
};




#endif /* ARESTAS_H_ */
