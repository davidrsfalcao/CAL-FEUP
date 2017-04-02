/*
 * Algoritmos.cpp
 *
 *  Created on: 02/04/2017
 *      Author: David
 */

#include "Algoritmos.h"
#include <iostream>

std::vector<Cidade> ordenarPorId(std::vector<Cidade> vect, int left, int right) {
      int i = left, j = right;
      Cidade tmp;
      Cidade pivot = vect[(int)((left + right) / 2)];

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
            ordenarPorId(vect, left, j);
      if (i < right)
            ordenarPorId(vect, i, right);

      return vect;
}

std::vector<Cidade> ordenarPorNome(std::vector<Cidade> vect, int left, int right) {


      int i = left, j = right;
      Cidade tmp;
      Cidade pivot = vect[(int)((left + right) / 2)];

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
            ordenarPorId(vect, left, j);
      if (i < right)
            ordenarPorId(vect, i, right);

      return vect;
}
