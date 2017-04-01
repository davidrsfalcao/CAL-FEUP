/*
 * Cidade.h
 *
 *  Created on: 01/04/2017
 *      Author: David
 */

#ifndef CIDADE_H_
#define CIDADE_H_
#include <vector>
#include "Alojamento.h"
#include "Coordenadas.h"


class Cidade {
private:
  std::string nome;
  Coordenadas coordenadas;
  std::vector<Alojamento*> hoteis;

public:
  Cidade();
  Cidade(std::string nome, Coordenadas coordenadas, std::vector<Alojamento*> hoteis);
  Coordenadas getCoordenadas();
  Alojamento* HotelMaisBarato(int dia, int mes);




};



#endif /* CIDADE_H_ */
