/*
* Cidade.h
*
*  Created on: 08/04/2017
*      Author: David
*/

#ifndef ARESTAS_H_
#define ARESTAS_H_

class Aresta{
private:
	unsigned int id_origem;
	unsigned int id_destino;
	int custo;
	int tempo;

public:
	Aresta();
	Aresta(unsigned int id_origem, unsigned int id_destino, int custo, int tempo);
	unsigned int getIdOrigem();
	unsigned int getIdDestino();
	bool operator <(const Aresta a);
};




#endif /* ARESTAS_H_ */
