#include <iostream>
#include <fstream>
#include "Floresta.hpp"
#include "Fogo.hpp"
#include "Animal.hpp"
#include "Config.hpp"

using namespace std;

int main() {
    string nomeArquivo = "src/input.dat";
    string nomeSaida = "output.dat";

    Floresta floresta(0, 0, 0, 0, 0, 0);
    floresta.lerMatriz(nomeArquivo);

    Fogo fogo;
    Animal animal;

    ofstream output(nomeSaida);
    if (!output.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída!\n";
        return 1;
    }

    floresta.executarSimulacao(floresta, fogo, animal, output);

    output.close();
    cout << "Resultado salvo em " << nomeSaida << endl;

    return 0;
}