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
  /**
	* @brief Constructor sem parametros da Classe Epoca
	*
	*/
  Epoca();
  /**
	* @brief Construtor com parametros da Classe Epoca
	*
	* @param nome Nome da Epoca
	* @param dia_inicio Dia da data de inicio da epoca
	* @param mes_inicio Mes da data de inicio da epoca
  * @param dia_fim Dia da data de fim da epoca
  * @param mes_fim Mes da data de fim da epoca
	* @param preco Custo do Hotel na Epoca
	*/
  Epoca(std::string nome, int dia_inicio, int mes_inicio, int dia_fim, int mes_fim, int preco);
  /**
	* @brief Função que retorna o dia da data de inicio da Epoca
	*
	* @return dia da data de inicio da Epoca
	*/
  int getDiaInicio();
  /**
	* @brief Função que retorna o dia da data de fim da Epoca
	*
	* @return dia da data de fim da Epoca
	*/
  int getDiaFim();
  /**
	* @brief Função que retorna o mes da data de inicio da Epoca
	*
	* @return mes da data de inicio da Epoca
	*/
  int getMesInicio();
  /**
	* @brief Função que retorna o mes da data de fim da Epoca
	*
	* @return mes da data de fim da Epoca
	*/
  int getMesFim();
  /**
	* @brief Função que retorna custo do hotel na Epoca
	*
	* @return custo do hotel na Epoca
	*/
  int getPreco();
  /**
	* @brief Função que retorna o Nome da Epoca
	*
	* @return O Nome da Epoca
	*/
  std::string getNome();
  /**
	*	@brief para mostrar uma Epoca
	*
	* @param of ostream para mostrar a Epoca
	*	@param ep Epoca que vai ser mostrada
	*/
  friend std::ostream & operator <<(std::ostream &of, const Epoca &ep);

};




#endif /* SRC_DATA_H_ */
