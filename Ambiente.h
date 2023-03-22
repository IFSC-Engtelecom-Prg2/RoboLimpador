//
// Created by msobral on 22/03/2023.
//

#ifndef ROBO_AMBIENTE_H
#define ROBO_AMBIENTE_H

#include <cstdint>

struct Posicao {
    uint8_t x,y;
};

enum class PosStatus:uint8_t {
    Livre,
    Visitada,
    Obstaculo
};

class Ambiente {
public:
    Ambiente(uint8_t linhas, uint8_t colunas, uint8_t obstaculos);
    ~Ambiente();

    // desenha o espaço na tela, incluindo as posições já visitadas pelo robô
    void mostra() const;

    // Verifica a posição. Resultado:
    //  PosStatus::Livre: posição ainda não foi visitada
    //  PosStatus::Visitada: posição já foi visitada
    //  PosStatus::Obstaculo: posição contém um obstáculo
    PosStatus verifica(const Posicao & pos) const;

    // Visita a posição. Resultado:
    //  PosStatus::Livre: posição ainda não foi visitada
    //  PosStatus::Visitada: posição já foi visitada
    //  PosStatus::Obstaculo: posição contém um obstáculo
    PosStatus visita(const Posicao & pos);

};

// faz uma pausa
void espera(uint32_t milissegundos);

#endif //ROBO_AMBIENTE_H
