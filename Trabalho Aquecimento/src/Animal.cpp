#include "Animal.hpp"
#include "Floresta.hpp" 

Animal::Animal() : paradoEmZero(0), passos(0){}

int Animal::numPassos(){
    return passos;
}

bool Animal::Mover(Floresta &floresta, int linhasFlorestaAuxiliar, int colunasFlorestaAuxiliar, ofstream &arquivo){
    linhasFlorestaAuxiliar = floresta.getLinhas();
    colunasFlorestaAuxiliar = floresta.getColunas();
    
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    //Possibilita que as células ortogonais ao animal sejam visitadas//

    int posX = floresta.getPosAnimalX();
    int posY = floresta.getPosAnimalY();

    
    //Caso o animal esteja em uma célula 0, ele permanece por até 3 iterações//
    if (floresta.getValor(posX, posY) == 0 && paradoEmZero < 3) {
        paradoEmZero++;
        arquivo << "\nO animal está parado em uma célula zero" << endl;
        return true;
    }
    else {
        paradoEmZero = 0;
    }

    vector<pair<int, int>> movimentosPossiveis1; // Células de valor 0 ou 1 //
    vector<pair<int, int>> movimentosPossiveis2; // Células de valor 3 //

    // Células ortogonais são checadas //
    for (int i = 0; i < 4; i++){
        int x = posX + dx[i];
        int y = posY + dy[i];

        //Verifica se não estão sendo acessadas células fora da matriz//
        if (x >= 0 && x < floresta.getLinhas() && y >= 0 && y < floresta.getColunas()){

            int valor = floresta.getValor(x, y);

            if (valor == 4){
                posX = x;
                posY = y;
                floresta.setPosAnimal(posX, posY);
                passos++;
                transformarCelulasAoRedorDaAgua(floresta, linhasFlorestaAuxiliar, colunasFlorestaAuxiliar);
                return true;
                // Busca primeiro uma célula 4 ortogonal (caso exista) e se movimenta para ela //
            }

            if (valor != 2 && valor != 3){
                movimentosPossiveis1.emplace_back(x, y);
                // Caso a célula seja 0 ou 1 (diferente de 2 e 3), armazena a posição //
            }

            else if (valor != 2){
                movimentosPossiveis2.emplace_back(x, y);
                // Caso a célula seja 3 (menor valor na hierarquia prioritária), armazena a posição //
            }
        }
    }

    if (!movimentosPossiveis1.empty()){
        int novoX = movimentosPossiveis1[0].first;
        int novoY = movimentosPossiveis1[0].second;
        floresta.setPosAnimal(novoX, novoY);
        passos++;
        return true;
        // "Seta" a posição do animal para uma célula 0 ou 1 caso não haja nenhuma célula 4 ortogonalmente//

    }

    else if (!movimentosPossiveis2.empty()){
        int novoX = movimentosPossiveis2[0].first;
        int novoY = movimentosPossiveis2[0].second;
        floresta.setPosAnimal(novoX, novoY);
        passos++;
        return true;
        // "Seta" a posição do animal para uma célula 3 caso não haja nenhuma célula 0 ou 1 ortogonalmente//
    }

    else {
       return false;
       // Não há nenhuma célula segura para que o animal possa se movimentar //
    }return true;
}   

void Animal::transformarCelulasAoRedorDaAgua(Floresta &floresta, int linhasFlorestaAuxiliar, int colunasFlorestaAuxiliar){
    int x = floresta.getPosAnimalX();
    int y = floresta.getPosAnimalY();

    if (floresta.getValor(x, y) == 4) {

        //Transforma a célula 4 em 0//
        floresta.setValor(x, y, 0);
        
        //Transforma a célula ortogonal de cima em 1//
        if (x - 1 >= 0){
            floresta.setValor(x - 1, y, 1);
        }

        //Transforma a célula ortogonal de baixo em 1//
        if (x + 1 < linhasFlorestaAuxiliar){
            floresta.setValor(x + 1, y, 1);
        }

        //Transforma a célula ortogonal à esquerda em 1//
        if (y - 1 >= 0){
            floresta.setValor(x, y - 1, 1);
        }

        //Transforma a célula ortogonal à direita em 1//
        if (y + 1 < colunasFlorestaAuxiliar){
            floresta.setValor(x, y + 1, 1);
        }
    }
}