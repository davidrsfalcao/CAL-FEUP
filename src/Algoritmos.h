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

std::vector<Cidade> ordenarPorId(std::vector<Cidade> vect, int left, int right);

std::vector<Cidade> ordenarPorNome(std::vector<Cidade> vect, int left, int right);

Cidade pesquisaNome( std::vector<Cidade> vect , std::string chave);


#endif /* SRC_ALGORITMOS_H_ */
