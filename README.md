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
definidas no documento '[pratica.pdf](./pratica.pdf)'.

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

#### Função transformarCelulasAoRedorDaAgua

A função `transformarCelulasAoRedorDaAgua` transforma a célula 4 em 0 e as células ortogonais a 4 em 1, baseando-se em 4 'ifs' diferentes que alteram o valor destas células ortogonais. 

### Propagaçao do Fogo

#### Função Propagar

A função `Propagar` percorre a matriz usando dois 'for' simples, identifica células de valor 2 e então verifica ortogonalmente estas células de valor 2; após isso, as células de valor 1 ortogonais a 2 são armazenadas utilizando um vetor de pares inteiros; após serem armazenadas, um contador é atribuido a cada célula separadamente utilizando `map<pair<int, int>, int> contadorQueima`, este contador nos permite transformar as células 1 em 2, e 2 em 3 da maneira solicitada no documento '[pratica.pdf](./pratica.pdf)'.

### Configurações 

#### Direções do Vento

Foi criado um booleano `COM_VENTO` que, quando ativado nos permite ativar outros 4 booleanos (`VENTO_CIMA`, `VENTO_BAIXO`, `VENTO_DIREITA`, `VENTO_ESQUERDA`), que direcionam a maneira com que o fogo se propaga. Caso ativados, estes booleanos retornam 0 ou um valor especifico. Por exemplo, `VENTO_CIMA` retorna -1 caso ativado e 0 caso desativado.

```
bool COM_VENTO = false;
bool VENTO_CIMA = false;
bool VENTO_BAIXO = false;
bool VENTO_ESQUERDA = false;
bool VENTO_DIREITA = false;
```
```
int dx[] = {config.vento_cima(), config.vento_baixo(), 0, 0};
int dy[] = {0, 0, config.vento_esquerda(), config.vento_direita()}
```











