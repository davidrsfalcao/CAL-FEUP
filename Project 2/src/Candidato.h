/*
 * Candidato.h
 *
 *  Created on: 20/05/2017
 *      Author: David
 */

#ifndef SRC_CANDIDATO_H_
#define SRC_CANDIDATO_H_

class Candidato{

public:
	int pontos;
	std::string tipo;
	std::string nome;
	std::string cidade;

	Candidato(){
		this->pontos = 9999;
		this->tipo = "";
		this->nome = "";
		this->cidade = "";
	}

};



#endif /* SRC_CANDIDATO_H_ */
