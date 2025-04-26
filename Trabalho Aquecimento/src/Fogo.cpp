#include "Fogo.hpp"
#include "Config.hpp"
#include "Floresta.hpp"

Fogo::Fogo(){}

bool Fogo::Propagar(Floresta &floresta) {
    int linhas = floresta.getLinhas();
    int colunas = floresta.getColunas();
    vector<pair<int, int>> novosFocos;
    Config config;
    bool propagou = false;

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            
            //Verifica se a célula está em chamas//
            if (floresta.getValor(i, j) == 2) {
                
                //Booleanos que se comportam com base nas configurações (Config.cpp)//
                int dx[] = {config.vento_cima(), config.vento_baixo(), 0, 0};
                int dy[] = {0, 0, config.vento_esquerda(), config.vento_direita()};

                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    //Verifica se não estão sendo acessadas células fora da matriz//
                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
                        
                        //verifica se células ortogonais a células em chamas têm valor 1 e as armazena em um vetor de pares//
                        if (floresta.getValor(ni, nj) == 1) {
                            novosFocos.emplace_back(ni, nj);
                            propagou = true;
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            //Incrementa o contador de queima das células de valor 2//
            if (floresta.getValor(i, j) == 2) {
                auto pos = make_pair(i, j);
                contadorQueima[pos]++;

                //Caso o contador seja maior ou igual a 2, transforma a célula de valor 2 em 3//
                if (contadorQueima[pos] >= 2) {
                    floresta.setValor(i, j, 3);
                    contadorQueima.erase(pos);
                }
            }
        }
    }

    //Transforma as células de valor 1 em 2 e inicia seu contador de queima em 0//
    for (auto [i, j] : novosFocos) {
        floresta.setValor(i, j, 2);
        contadorQueima[make_pair(i, j)] = 0;  
        
    }

    return propagou;

}