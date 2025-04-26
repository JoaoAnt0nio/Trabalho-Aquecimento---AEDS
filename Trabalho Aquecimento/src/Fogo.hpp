#ifndef FOGO_HPP
#define FOGO_HPP

#include <iostream>
#include <vector>
#include <map>
#include <utility>

using namespace std;

class Floresta;

class Fogo{

    private:
        map<pair<int, int>, int> contadorQueima; 

    public:
        Fogo();
        bool Propagar(Floresta &floresta);
};

#endif