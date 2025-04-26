#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class Floresta;

class Animal{
    private:
        int linhasFlorestaAuxiliar, colunasFlorestaAuxiliar;
        vector<vector<int>> celulasAuxiliares;
        int paradoEmZero;
        int passos;
    
    public:
        Animal();
        bool Mover(Floresta &floresta, int linhasFlorestaAuxiliar, int colunasFlorestaAuxiliar, ofstream &arquivo);
        void transformarCelulasAoRedorDaAgua(Floresta &floresta, int linhasFlorestaAuxiliar, int colunasFlorestaAuxiliar);
        int numPassos();
};

#endif