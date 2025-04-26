#ifndef CONFIG_HPP
#define CONFIG_HPP

extern int MAX_ITERACOES;
extern bool COM_VENTO;
extern bool VENTO_CIMA;
extern bool VENTO_BAIXO;
extern bool VENTO_ESQUERDA;
extern bool VENTO_DIREITA;

using namespace std;

class Config{
    public:
        int vento_direita();
        int vento_cima();
        int vento_esquerda();
        int vento_baixo();
};

#endif