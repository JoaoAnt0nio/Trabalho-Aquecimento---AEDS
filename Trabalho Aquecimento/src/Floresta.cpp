#include "Floresta.hpp"


Floresta::Floresta(int linhas, int colunas, int focoInicialX, int focoInicialY, int posInicialAnimalX, int posInicialAnimalY) : linhas(linhas), colunas(colunas), focoInicialX(focoInicialX), focoInicialY(focoInicialY), posInicialAnimalX(posInicialAnimalX), posInicialAnimalY(posInicialAnimalY){
    celulas.resize(linhas, vector<int>(colunas, 1));
}

void Floresta::armazenarFloresta(Floresta &floresta, ofstream &arquivo){
    arquivo << "\nPosição do animal: (" << floresta.getPosAnimalX() << ", " 
            << floresta.getPosAnimalY() << ")" << "\n" << endl; 
            
    
    for (int i = 0; i < floresta.getLinhas(); i++) {
        for (int j = 0; j < floresta.getColunas(); j++) {
            arquivo << floresta.getValor(i, j) << " ";
        }
        arquivo << endl;
    }
    arquivo << endl;
}

int Floresta::getColunas(){
    return colunas;
}

int Floresta::getLinhas(){
    return linhas;
}

void Floresta::lerMatriz(string nomeArquivo){
    ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()){
        cerr << "O arquivo não foi aberto corretamente" << endl;
        return;
    }

    arquivo >> linhas >> colunas >> focoInicialX >> focoInicialY >> posInicialAnimalX >> posInicialAnimalY;

    celulas.resize(linhas, vector<int>(colunas));

    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            arquivo >> celulas[i][j];
        }
    }

    if (focoInicialX >= 0 && focoInicialX < linhas && focoInicialY >= 0 && focoInicialY < colunas) {
        celulas[focoInicialX][focoInicialY] = 2;
    }
}

int Floresta::getValor(int i, int j) {
    return celulas[i][j];
}

void Floresta::setValor(int i, int j, int valor) {
    celulas[i][j] = valor;
}

int Floresta::getPosAnimalX(){
    return posInicialAnimalX;
}

int Floresta::getPosAnimalY(){
    return posInicialAnimalY;
}

void Floresta::setPosAnimal(int x, int y){

    if (x >= 0 && x < linhas && y >= 0 && y < colunas) {
        posInicialAnimalX = x;
        posInicialAnimalY = y;
    } else {
        std::cerr << "Erro: Posição do animal fora dos limites da floresta!" << std::endl;
    }
}

void Floresta::executarSimulacao(Floresta &floresta, Fogo &fogo, Animal &animal, ofstream &output){
    
    bool fogoAtivo = true;
    
    for (int iteracao = 0; iteracao < MAX_ITERACOES && fogoAtivo; iteracao++) {
        output << "---------------------------------------------\nIteração " << iteracao << ":" << endl;

        bool mover = animal.Mover(floresta, floresta.getLinhas(), floresta.getColunas(), output);
        floresta.armazenarFloresta(floresta, output);

        if (!mover) {
            output << "Animal ficou sem saída na iteração: " << iteracao << endl;
            break;
        }

        fogoAtivo = fogo.Propagar(floresta);

        if (!fogoAtivo) {
            output << "---------------------------------------------\nFogo parou de se propagar na iteração: " << iteracao << endl;
        }
    }

    output << "\nNúmero total de passos: " << animal.numPassos() - 1 << endl;
    if (!fogoAtivo) {
        output << "\nSimulação terminada porque o fogo não pode mais se propagar." << endl;
    }
}

