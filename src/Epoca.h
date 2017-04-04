/*
* Epoca.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_DATA_H_
#define SRC_DATA_H_
#include <string>
#include <iostream>

class Epoca {
private:
  std::string nome;
  int dia_inicio;
  int mes_inicio;
  int dia_fim;
  int mes_fim;
  int preco; // euros

public:
  Epoca();
  Epoca(std::string nome, int dia_inicio, int mes_inicio, int dia_fim, int mes_fim, int preco);
  int getDiaInicio();
  int getDiaFim();
  int getMesInicio();
  int getMesFim();
  int getPreco();
  std::string getNome();
  friend std::ostream & operator <<(std::ostream &of, const Epoca &ep);

};




#endif /* SRC_DATA_H_ */
