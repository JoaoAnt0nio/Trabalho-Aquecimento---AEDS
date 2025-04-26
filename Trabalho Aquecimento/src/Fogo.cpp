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
            if (floresta.getValor(i, j) == 2) {
                int dx[] = {config.vento_cima(), config.vento_baixo(), 0, 0};
                int dy[] = {0, 0, config.vento_esquerda(), config.vento_direita()};

                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d];
                    int nj = j + dy[d];

                    if (ni >= 0 && ni < linhas && nj >= 0 && nj < colunas) {
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
            if (floresta.getValor(i, j) == 2) {
                auto pos = make_pair(i, j);
                contadorQueima[pos]++;
                
                if (contadorQueima[pos] >= 2) {
                    floresta.setValor(i, j, 3);
                    contadorQueima.erase(pos);
                }
            }
        }
    }

    for (auto [i, j] : novosFocos) {
        floresta.setValor(i, j, 2);
        contadorQueima[make_pair(i, j)] = 0;  
        
    }

    return propagou;

}