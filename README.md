# Simulação de Propagação de Incêndios

<div style="display: inline-block;">
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<p align= "justify">
<p>
Este repositório é referente ao trabalho de aquecimento da disciplina <strong>Algoritmos e Estrutura de Dados I</strong>, ministrada pelo docente Michel Pires do Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG).
</p>

# Sumário

- [Introdução e Objetivo](#introdução_e_objetivo)
- [Lógica de Desenvolvimento](#logica_de_desenvolvimento)
- [Implementação](#implementação)
- [Resultado](#resultado)
- [Compilação](#compilação)

# Introdução e Objetivo

O Trabalho de Aquecimento é um trabalho que tem por objetivo a implementação de um sistema de propagação de incêndios que percorre uma matriz e modifica suas células, enquanto um "animal" se movimenta com base em prioridades pré-definidas e procura ao máximo evitar as celulas "em chamas".

# Lógica de Desenvolvimento

A lógica da movimentação do animal é baseada em Algoritmo Guloso utilizando certas prioridades para verificar as vizinhanças e realizar as movimentações, enquanto o fogo se propaga utilizando Vizinhança de Von Neumann.

### Busca Local Gulosa

Na movimentação do animal foi implementada uma espécie de busca local baseada em Algoritmo Guloso, onde as celulas adjacentes ao animal são conferidas, armazenadas e então é tomado o primeiro movimento armazenado como o que será utilizado. Essa seleção de movimentos possíveis é feita com base nas prioridades 
definidas no documento 'pratica.pdf'.

### Vizinhança de Von Neumann

A propagação do fogo é baseada na Vizinhança de Von Neumann, que verifica as quatro células ortogonais ao foco do incêndio e inicia sua propagação.

# Implementação

Aqui abordaremos as funções e implementações principais do código.

### Movimentação do Animal

O algoritmo verifica as células adjacentes e toma a decisão de se movimentar com base nas seguintes prioridades:

*1 -* Caminhos seguros são células de valor 0 (área vazia que não queima), 1 (árvore saudável), 3 (árvore carbonizada) ou 4 (área com presença de água), seguindo a seguinte hierarquia: 4 > 0 || 1 > 3;  
  
*2 -* Caminho inseguro é uma celula de valor 2 (árvore em chamas) que não deve ser visitada.

#### Função Mover
A função `Mover` faz o animal se movimentar, escolhendo sempre células 4 ou o primeiro caminho armazenado em caso de células 0, 1 ou 3. Além disso, o animal permanece imóvel por até 3 iterações quando encontra uma célula de valor 0. Esta função
possui custo computacional O(1), tanto em função de tempo quanto espaço.  
Abaixo a função:  

```

void Animal::Mover(Floresta &floresta, int linhasFlorestaAuxiliar, int colunasFlorestaAuxiliar, ofstream &arquivo){
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
        arquivo << "O animal está parado em uma célula zero" << endl;
        return;
    }
    else {
        paradoEmZero = 0;
    }

    vector<pair<int, int>> movimentosPossiveis1; // Células 0 ou 1 //
    vector<pair<int, int>> movimentosPossiveis2; // Células 3 //

    // Células ortogonais são checadas //
    for (int i = 0; i < 4; i++){
        int x = posX + dx[i];
        int y = posY + dy[i];

        if (x >= 0 && x < floresta.getLinhas() && y >= 0 && y < floresta.getColunas()){

            int valor = floresta.getValor(x, y);

            if (valor == 4){
                posX = x;
                posY = y;
                floresta.setPosAnimal(posX, posY);
                passos++;
                transformarCelulasAoRedorDaAgua(floresta, linhasFlorestaAuxiliar, colunasFlorestaAuxiliar);
                return;
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
        // "Seta" a posição do animal para uma célula 0 ou 1 caso não haja nenhuma célula 4 ortogonalmente//

    }

    else if (!movimentosPossiveis2.empty()){
        int novoX = movimentosPossiveis2[0].first;
        int novoY = movimentosPossiveis2[0].second;
        floresta.setPosAnimal(novoX, novoY);
        passos++;

        // "Seta" a posição do animal para uma célula 3 caso não haja nenhuma célula 0 ou 1 ortogonalmente//
    }

    else {
       arquivo << "Animal sem saída" << endl;
       animalVivo = false;
       // Não há nenhuma célula segura para que o animal possa se movimentar //
    }
}

```









