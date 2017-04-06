/*
 * Algoritmos.h
 *
 *  Created on: 02/04/2017
 *      Author: David
 */

#ifndef SRC_ALGORITMOS_H_
#define SRC_ALGORITMOS_H_

#include <vector>
#include <string>
#include "Cidade.h"
/**
* Função que ordena as cidades por ID
*
* @param vect Vector de Cidades para ordenar
* @param left Elemento mais a esquerda
* @param right Elemento mais a direita
*
* @return O Vetor já ordenado
*/
std::vector<Cidade> ordenarPorId(std::vector<Cidade> vect, int left, int right);
/**
* Função que ordena as cidades por Nome
*
* @param vect Vector de Cidades para ordenar
* @param left Elemento mais a esquerda
* @param right Elemento mais a direita
*
* @return O Vetor já ordenado
*/
std::vector<Cidade> ordenarPorNome(std::vector<Cidade> vect, int left, int right);
/**
* Função que procura e retorna uma cidade pelo seu Nome
*
* @param vect Vector de Cidades para pesquisar
* @param chave Nome da Cidade a procurar
*
* @return A Cidade pesquisada
*/
Cidade pesquisaNome( std::vector<Cidade> vect , std::string chave);
/**
* Função que procura e retorna uma cidade pelo seu ID
*
* @param vect Vector de Cidades para pesquisar
* @param chave ID da Cidade a procurar
*
* @return A Cidade pesquisada
*/
Cidade pesquisaId(std::vector<Cidade> vect, unsigned int chave);

#endif /* SRC_ALGORITMOS_H_ */
