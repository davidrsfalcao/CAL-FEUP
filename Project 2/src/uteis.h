#ifndef UTEIS_H_
#define UTEIS_H_

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <windows.h>
#include <cmath>

#define ENTER 13
#define DOWN_KEY 22472
#define UP_KEY 22480
#define LEFT_KEY 22475
#define RIGHT_KEY 22477


/**
 * @brief verifica se uma data existe
 *
 * @param dia Dia da Data
 * @param mes Mes da Data
 * @param ano Ano da Data
 *
 * @return True se o dia existe,False se não existir
 */
bool dia_existe(int dia, int mes, int ano);

/**
 * @return Retorna as horas do sistema
 */
int horas_do_sistema();

/**
 * @return Retorna os minutos do sistema
 */
int minutos_do_sistema();

/**
 * @return Retorna o dia do sistema
 */
int dia_do_sistema();

/**
 * @return Retorna o mes do sistema
 *
 */
int mes_do_sistema();

/**
 * @brief Passa um mes de numerico a escrito,como 1->janeiro
 *
 * @param mes Mes que se quer transformar
 * @return O mes transformado
 */
std::string mostrar_mes(unsigned int mes);

/**
 * @return retorna o Ano do Sistema
 */
int ano_do_sistema();

/**
 * @brief Limpa a tela onde se está a aparesentar o programa
 */
void limparEcra();

/**
 *
 * @brief le se a opcao esta entre os valores possiveis
 *
 * @param min Opcao minima
 * @param max Opcao maxima
 *
 * @return a opcao depois de analisada
 */
unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max);

/**
 * @brief Elimina os espaços antes e depois numa string
 *
 * @param str String que se pretende formatar
 *
 * @return Retorna a string ja sem os espaços
 */
std::string delete_space(std::string str);

/**
 * @brief Calcula que dia da semana corresponde a uma data
 *
 * @param dia Dia da Data
 * @param mes Mes da Data
 * @param ano Ano da Data
 *
 * @return Retorna o dia da semana
 */
std::string calculo_dia_da_semana(int dia, int mes, int ano);

/**
 * @brief Mostra a data atual
 */
void cabecalho();

/**
*@brief Lê o input do utilizador e vê se a entrada é a up_key, down_key ou ENTER e ajusta a opcao
*
*@param opcao valor a alterar
*
*@param min opcao mininma
*
*@param max opcao máxima
*
*@return Retorna a tecla primida
*/
int opcao_valida(int &opcao, int min, int max);

/**
*@brief Lê o input do utilizador e vê se a entrada é a left_key, right_key ou ENTER e ajusta a opcao
*
*@param opcao valor a alterar
*
*@param min opcao mininma
*
*@param max opcao máxima
*
*@return Retorna a tecla primida
*/
int opcao_valida_listas(int &opcao, int min, int max);

/**
*@brief Lê o input do utilizador e vê se a entrada do teclado
*
*
*@return Retorna a tecla primida
*/
int tecla_pressionada();
/**
*@brief Definir cores
*
*/
enum DOS_COLORS{
	black, blue, green, cyan, red, magenta, brown,
	light_gray, dark_gray, light_blue, light_green, light_cyan,
	light_red, light_magenta, yellow, white
};

/**
 * @brief Algoritmo de pesquisa de uma palavra num vetor
 *
 * @param palavra A palavra que se pretende encontrar
 * @param v1 Vetor onde se vai procurar
 *
 * @return Retorn a posicao da palavra no vetor se encontrar ou -1 se nao encontrar
 */
int encontra_string_vetor(std::string palavra, std::vector<std::string> v1);

/**
* @brief Define a côr do texto a imprimir
*
* @param iColor cor escolhida
*/
void textcolor(DOS_COLORS iColor);

/**
* @brief Imprime o título "PISCINA"
*
*/
void titulo();

/**
* @brief Configura o terminal com as especificações pretendidas
*
*/
void configurar_terminal();

/**
* @brief Define a côr do texto a imprimir
*
* @param x posição horizontal
*
* @param y posição vertical
*/
void gotoxy(int x, int y);


#endif /* UTEIS_H_ */
