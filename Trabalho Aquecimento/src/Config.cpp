#include "Config.hpp"

int MAX_ITERACOES = 30;
bool COM_VENTO = false;
bool VENTO_CIMA = false;
bool VENTO_BAIXO = false;
bool VENTO_ESQUERDA = false;
bool VENTO_DIREITA = false;

int Config::vento_cima(){
    if(COM_VENTO){
        return VENTO_CIMA ? -1 : 0;
    }
    else{
        return -1;
    }
}

int Config::vento_direita(){
    if(COM_VENTO){
        return VENTO_DIREITA ? 1 : 0;
    }
    else{
        return 1;
    }
}

int Config::vento_esquerda(){
    if(COM_VENTO){
        return VENTO_ESQUERDA ? -1 : 0;
    }
    else{
        return -1;
    }
}

int Config::vento_baixo(){
    if(COM_VENTO){
        return VENTO_BAIXO ? 1 : 0;
    }
    else{
        return 1;
    }
}