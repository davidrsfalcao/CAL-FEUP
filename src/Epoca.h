/*
* Epoca.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef SRC_DATA_H_
#define SRC_DATA_H_


class Epoca {
private:
  int dia_inicio;
  int mes_inicio;
  int dia_fim;
  int mes_fim;
  int preco; // euros

public:
  Epoca();
  Epoca(int dia_inicio, int mes_inicio, int dia_fim, int mes_fim);
  int getDiaInicio();
  int getDiaFim();
  int getMesInicio();
  int getMesFim();
  int getPreco();

};




#endif /* SRC_DATA_H_ */
