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
#include <iostream>


class Alojamento {
private:
	std::string nome;
	std::vector<Epoca*> epocas;

public:
	Alojamento();
	Alojamento(std::string nome, std::vector<Epoca*>epocas);
	Epoca* getEpoca(int dia, int mes);
	std::string getNome();
	int getPreco(int dia, int mes);
	std::vector<Epoca*> getTodasEpocas();
	friend std::ostream & operator <<(std::ostream &of, const Alojamento &ht);

};




#endif /* SRC_ALOJAMENTO_H_ */
