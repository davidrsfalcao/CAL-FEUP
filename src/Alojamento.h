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


class Alojamento {
private:
  std::string nome;
  std::vector<Epoca*> epocas;

public:
  Alojamento();
  Alojamento(std::string nome, std::vector<Epoca*>epocas);
  Epoca* getEpoca(int dia, int mes);
  int getPreco(int dia, int mes);


};




#endif /* SRC_ALOJAMENTO_H_ */
