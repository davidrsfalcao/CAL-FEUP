/*
* Algoritmos.cpp
*
*  Created on: 02/04/2017
*      Author: David
*/

#include "Algoritmos.h"
#include <iostream>
#include <string>
#include <cmath>

//QuickSort
std::vector<Cidade> ordenarPorId(std::vector<Cidade> vect, int left, int right) {
	int i = left, j = right;
	Cidade tmp;
	Cidade pivot = vect[(floor)((left + right) / 2)];

	/* partition */
	while (i <= j) {
		while (vect[i].getId() < pivot.getId())
		i++;
		while (vect[j].getId() > pivot.getId())
		j--;
		if (i <= j) {
			tmp = vect[i];
			vect[i] = vect[j];
			vect[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
	vect = ordenarPorId(vect, left, j);
	if (i < right)
	vect = ordenarPorId(vect, i, right);

	return vect;
}

std::vector<Cidade> ordenarPorNome(std::vector<Cidade> vect, int left, int right) {

	int i = left, j = right;
	Cidade tmp;
	Cidade pivot = vect[(floor)((left + right) / 2)];

	/* partition */
	while (i <= j) {
		while (vect[i].getNome() < pivot.getNome())
		i++;
		while (vect[j].getNome() > pivot.getNome())
		j--;
		if (i <= j) {
			tmp = vect[i];
			vect[i] = vect[j];
			vect[j] = tmp;
			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		vect = ordenarPorNome(vect, left, j);
	if (i < right)
		vect = ordenarPorNome(vect, i, right);

	return vect;
}

// Pesquisa Binaria
Cidade pesquisaNome(std::vector<Cidade> vect, std::string chave) {
	int inf = 0;
	int sup = vect.size() - 1;
	int meio;
	while (vect[inf].getNome() <= vect[sup].getNome()) {
		meio = floor((inf + sup) / 2);
		if (chave == vect[meio].getNome())
			return vect[meio];
		if (chave < vect[meio].getNome())
			sup = meio - 1;
		else
			inf = meio + 1;
	}

	return *(new Cidade());
}

Cidade pesquisaId(std::vector<Cidade> vect, unsigned int chave){
	int inf = 0;
	int sup = vect.size() - 1;
	int meio;
	while (vect[inf].getId() <= vect[sup].getId()) {
		meio = floor((inf + sup) / 2);
		if (chave == vect[meio].getId())
			return vect[meio];
		if (chave < vect[meio].getId())
			sup = meio - 1;
		else
			inf = meio + 1;
	}

	return *(new Cidade());
}
