/*
 * matcher.h
 *
 *  Created on: 20/05/2017
 *      Author: David
 */

#include "Cidade.h"
#include "Candidato.h"

/**
* @brief Função que faz uma pesquisa exata de uma string sobre um vetor de cidades
*
* @param cidades vetor com todas as cidades
* @param cmp string a comparar
*
* @return vetor com as strings encontradas
*/
std::vector<std::string> pesquisaExata(std::vector<Cidade> cidades, std::string cmp);

/**
* @brief Função que faz uma pesquisa aproximada de uma string sobre um vetor de cidades
*
* @param cidades vetor com todas as cidades
* @param cmp string a comparar
*
* @return vetor com as strings encontradas (10 melhores aproximações)
*/
std::vector<std::string> pesquisaAproximada(std::vector<Cidade> cidades, std::string cmp);

/**
* @brief Algoritmo para avaliar as parecencas entre 2 strings ( algoritmo de Levenshtein)
*
* @param string1 string a comparar
* @param cmp string a comparar
*
* @return numero de modificacoes que seriam necessarias fazer para as 2 strings ficarem iguais
*/
int verificarSimilaridade(std::string string1, std::string cmp);

/**
* @brief Divide a palavra1 em várias palavras (pelos espaços) e calcula o melhor score de parecença
* de cada uma.
*
* @param string1 string a comparar
* @param cmp string a comparar
*
* @return best_score score da melhor divisão da palavra
*/
int dividir_palavra(std::string palavra1, std::string cmp);

/**
* @brief Encontra o candidato com maior score num vetor de candidatos
*
* @param candidatos vetor a ser pesquisado
*
* @return ind indice do candidado com o score maximo
*/
int findMaxVector(std::vector<Candidato> candidatos);
