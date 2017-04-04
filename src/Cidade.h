/*
* Cidade.h
*
*  Created on: 01/04/2017
*      Author: David
*/

#ifndef CIDADE_H_
#define CIDADE_H_
#include <vector>
#include <iostream>
#include "Alojamento.h"
#include "Coordenadas.h"


class Cidade {
private:
	unsigned int id;
	std::string nome;
	Coordenadas coordenadas;
	std::vector<Alojamento*> hoteis;
	std::vector<int> destinos; // {id1,custo1,tempo1,id2,custo2,tempo2}


public:
	Cidade();
	Cidade(unsigned int id, std::string nome, Coordenadas coordenadas, std::vector<Alojamento*> hoteis, std::vector<int> destinos);
	unsigned int getId();
	void setId(unsigned int id);
	void setNome(std::string nome);
	std::string getNome();
	Coordenadas getCoordenadas();
	void setCoordenadas(Coordenadas coordenadas);
	std::vector<Alojamento*> getTodosHoteis();
	Alojamento* HotelMaisBarato(int dia, int mes);
	std::vector<int> getDestinos();
	int getIdDestino(int n);
	int getCustoViagemDestino(int n);
	friend std::ostream & operator <<(std::ostream &of, const Cidade &ci);
	bool operator==(const Cidade &ci);
	bool operator!=(const Cidade &ci);
};



#endif /* CIDADE_H_ */
