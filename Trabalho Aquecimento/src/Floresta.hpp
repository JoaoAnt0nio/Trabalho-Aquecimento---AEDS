#ifndef FLORESTA_HPP
#define FLORESTA_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "Fogo.hpp"
#include "Animal.hpp"
#include "Config.hpp"

using namespace std;

class Floresta{
    private:
        int linhas, colunas, focoInicialX, focoInicialY, posInicialAnimalX, posInicialAnimalY;
        vector<vector<int>> celulas;

    public:
        Floresta(int linhas, int colunas, int focoInicialX, int focoInicialY, int posInicialAnimalX, int posInicialAnimalY);
        int getLinhas();
        int getColunas();
        int getValor(int i, int j);
        int getPosAnimalX();
        int getPosAnimalY();
        void setPosAnimal(int x, int y);
        void setValor(int i, int j, int valor);
        void lerMatriz(string nomeArquivo);
        void armazenarFloresta(Floresta &floresta, ofstream &arquivo);
        void executarSimulacao(Floresta &floresta, Fogo &fogo, Animal &animal, ofstream &output);
};

#endif