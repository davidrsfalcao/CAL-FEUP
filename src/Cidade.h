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


class Cidade {
private:
  std::string nome;
  std::vector<Alojamento*> hoteis;

public:
  Cidade();
  Cidade(std::string nome,  std::vector<Alojamento> hoteis);
  Alojamento* HotelMaisBarato(int dia, int mes);



};



#endif /* CIDADE_H_ */
