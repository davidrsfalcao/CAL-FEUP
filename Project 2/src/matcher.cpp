/*
* matcher.cpp
*
*  Created on: 20/05/2017
*      Author: David
*/

#include "matcher.h"
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <iostream>
#include "Algoritmos.h"

class Candidato;

std::vector<std::string> pesquisaExata(std::vector<Cidade> cidades, std::string cmp){
	std::vector<std::string> result;

	for (size_t i = 0; i < cidades.size(); i++) {
		if(cidades[i].getNome() == cmp){
			result.push_back("cidade");
			result.push_back(cidades[i].getNome());
			result.push_back(cidades[i].getNome());
		}

		for (size_t k = 0; k < cidades[i].getPontosInteresse().size(); k++) {
			if(cidades[i].getPontosInteresse()[k] == cmp){
				result.push_back("PI");
				result.push_back(cidades[i].getPontosInteresse()[k]);
				result.push_back(cidades[i].getNome());
			}
		}

	}

	return result;
}

std::vector<std::string> pesquisaAproximada(std::vector<Cidade> cidades, std::string cmp){

	std::vector<Candidato> candidatos;
	Candidato c1 = Candidato();
	int score;

	for (size_t i = 0; i < 10; i++) {
		candidatos.push_back(c1);
	}

	std::vector<std::string> result;

	for (size_t i = 0; i < cidades.size(); i++) {
		score = dividir_palavra(cidades[i].getNome(),cmp);
		if (score < candidatos[findMaxVector(candidatos)].pontos)
		{
			Candidato cid;
			cid.pontos = score;
			cid.tipo = "cidade";
			cid.nome = cidades[i].getNome();
			cid.cidade = cidades[i].getNome();

			candidatos[findMaxVector(candidatos)] = cid;
		}

		for (size_t k = 0; k < cidades[i].getPontosInteresse().size(); k++) {
			score = dividir_palavra(cidades[i].getPontosInteresse()[k],cmp);
			if (score < candidatos[findMaxVector(candidatos)].pontos)
			{
				Candidato PI;
				PI.pontos = score;
				PI.tipo = "PI";
				PI.cidade = cidades[i].getNome();
				PI.nome = cidades[i].getPontosInteresse()[k];
				candidatos[findMaxVector(candidatos)] = PI;
			}
		}
	}

	candidatos = ordenaPorScore(candidatos, 0, candidatos.size()-1);
	for (size_t i = 0; i < candidatos.size(); i++) {
		result.push_back(candidatos[i].tipo);
		result.push_back(candidatos[i].nome);
		result.push_back(candidatos[i].cidade);
	}

	return result;

}

int dividir_palavra(std::string palavra1, std::string cmp){

	int tam1 = palavra1.size();
	int i = 0, i1 = 0;
	int best_score = 1000000, score = 0;
	std::string temp;

	for (size_t i = 0; i < tam1; i++) {

		if (palavra1[i] == ' '){
			temp = palavra1.substr(i1, i-i1);
			score = verificarSimilaridade(temp, cmp);
			i1 = i+1;
			if (score < best_score){
				best_score = score;
			}
		}
	}

	temp = palavra1.substr(i1, i-1);
	score = verificarSimilaridade(temp, cmp);
	if (score < best_score){
		best_score = score;
	}

	return best_score;
}

int verificarSimilaridade(std::string palavra1, std::string palavra2){

	int tam1 = palavra1.size();
	int tam2 = palavra2.size();
	int count = 0;
	int seq = 0, melhor_seq = 0;


	if (tam1 == 0){
		return tam2;
	}

	if (tam2 == 0){
		return tam1;
	}

	if (palavra1 == palavra2){
		return 0;
	}

	bool stop = false;
	for (size_t i = 0; i < tam2; i++) {
		for (size_t k = 0; k < tam1; k++) {
			int i1 = i;
			int k1 = k;
			while(!stop){
				if (palavra2[i1] == palavra1[k1]){
					seq++;
					i1++;
					k1++;
					if((i1 == tam2) || (k1 == tam1)){
						stop = true;
					}
				} else {
					stop = true;
				}
			}
			if (seq > melhor_seq){
				melhor_seq = seq;
			}
			stop = false;
			seq = 0;
		}
	}

	if (tam1 < tam2){
		count = tam2 - melhor_seq;
	}
	else {
		count = tam1 - melhor_seq;
	}
	return count;

}

int findMaxVector(std::vector<Candidato> candidatos){
	int max = 0;
	int ind = 0;

	for (size_t i = 0; i < candidatos.size(); i++) {

		if(candidatos[i].pontos > max){
			ind = i;
			max = candidatos[i].pontos;
		}
	}

	return ind;
}
