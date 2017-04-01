/*
* Alojamento.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_ALOJAMENTO_H_
#define SRC_ALOJAMENTO_H_


class Alojamento {
private:
  std::string nome;
  std::vector<*Epoca> epocas;

public:
  Alojamento();
  Alojamento(std::string nome);
  void getPreco(int dia, int mes);
};




#endif /* SRC_ALOJAMENTO_H_ */
