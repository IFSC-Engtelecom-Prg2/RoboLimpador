//
// Created by msobral on 22/03/2023.
//

#ifndef ROBO_ROBO_H
#define ROBO_ROBO_H

#include "Ambiente.h"

// resultado de um movimento no labirinto
enum class Status:uint8_t {
    Avancou,
    NaoAvancou
};

// as possíveis direções de movimento no labirinto
enum class Direcao:uint8_t {
    Acima,
    Abaixo,
    Esquerda,
    Direita
};

class Robo {
public:
    Robo(Ambiente & espaco);
    ~Robo();

    // obtém a posição atual no espaço a ser limpo
    Posicao obtem_posicao() const;

    // Obtém a contagem de passos até o momento
    int obtem_passos() const;

    // avança a posição em alguma direção
    // dir: a direção para o movimento (ver enum Direcao)
    // volta: se true, limpa a casa para onde se avançou. Isso pode ser usado para retroceder no espaço
    // Resultado: um valor do tipo enum Status (ver acima), indicando se:
    //    Status::Avancou: avançou-se na direção solicitada
    //    Status::NaoAvancou: não foi possível avançar na direção solicitada (tem um obstáculo)
    Status avanca(Direcao dir, bool volta=false);
private:
    Ambiente & espaco;
    Posicao pos_atual;
    uint32_t passos;
};


#endif //ROBO_ROBO_H
