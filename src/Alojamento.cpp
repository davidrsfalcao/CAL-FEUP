/*
* Alojamento.cpp
*
*  Created on: 01/04/2017
*      Author: David
*/
#include "Alojamento.h"
#include <vector>

using namespace std;

Alojamento::Alojamento() {
	this->nome = "";
}

Alojamento::Alojamento(std::string nome, std::vector<Epoca*> epocas) {
	this->nome = nome;
	this->epocas = epocas;
}

std::string Alojamento::getNome() {
	return nome;
}

int Alojamento::getPreco(int dia, int mes) {

	Epoca *epoca = getEpoca(dia, mes);

	return epoca->getPreco();

}

Epoca* Alojamento::getEpoca(int dia, int mes) {

	std::vector<Epoca*>ep = epocas;
	for (size_t i = 0; i < ep.size(); i++) {
		bool passaAno;
		bool mesM = (ep[i]->getMesInicio() < ep[i]->getMesFim());
		bool mesI = (ep[i]->getMesInicio() == ep[i]->getMesFim());
		bool diaM = (ep[i]->getDiaInicio() < ep[i]->getDiaFim());

		if (mesM || (mesI && diaM)){
			passaAno = false;
		}
		else passaAno = true;

		if (!passaAno){
			if((ep[i]->getMesInicio() < mes) && (ep[i]->getMesFim() > mes)){
				return ep[i];
			}
			else {
				bool mesII = (ep[i]->getMesInicio() == mes);
				bool mesIF = (ep[i]->getMesFim() == mes);

				if(mesII){
					if(dia >= ep[i]->getDiaInicio()){
						return ep[i];
					}
				}

				if (mesIF){
					if(dia <= ep[i]->getDiaFim()){
						return ep[i];
					}
				}

			}
		}
		else {
			bool anoAtual = ((ep[i]->getMesInicio() <= mes) && (mes <= 12));

			if (anoAtual){
				if((ep[i]->getMesInicio() < mes) && (12 > mes)){
					return ep[i];
				}
				else {
					bool mesII = (ep[i]->getMesInicio() == mes);
					bool mesIF = (12 == mes);

					if(mesII){
						if(dia >= ep[i]->getDiaInicio()){
							return ep[i];
						}
					}

					if (mesIF){
						if(dia <= 31){
							return ep[i];
						}
					}
				}
			}

			else {
				if((1 < mes) && (ep[i]->getMesFim() > mes)){
					return ep[i];
				}
				else {
					bool mesII = (1 == mes);
					bool mesIF = (ep[i]->getMesFim() == mes);

					if(mesII){
						if(dia >= 1){
							return ep[i];
						}
					}

					if (mesIF){
						if(dia <= ep[i]->getDiaFim()){
							return ep[i];
						}
					}

				}
			}
		}

	}
	
	return new Epoca();
}

std::vector<Epoca*> Alojamento::getTodasEpocas(){
	return epocas;
}

std::ostream & operator <<(std::ostream &of, const Alojamento &ht){

	of << "Hotel: " << ht.nome << std::endl;

	of << "Todas as epocas: " << std::endl << std::endl;

	for (size_t i = 0; i < ht.epocas.size(); i++) {
		of << (*ht.epocas[i]) << std::endl;
	}

	return of;


}
