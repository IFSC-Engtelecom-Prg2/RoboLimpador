//
// Created by msobral on 22/03/2023.
//

#include "Ambiente.h"
#include <sys/time.h>
#include <time.h>
#include <stdexcept>

void espera(uint32_t milissegundos) {
    timespec ts{milissegundos/1000, 1000000*(milissegundos % 1000)};

    nanosleep(&ts, NULL);
}

Ambiente::Ambiente(uint8_t linhas, uint8_t colunas, uint8_t obstaculos): lin(linhas), col(colunas) {
    area.assign(lin*col, PosStatus::Livre);
    while (obstaculos > 0) {
        Posicao pos{static_cast<uint8_t>(rand()% lin), static_cast<uint8_t>(rand()% col)};
        auto rpos = calc_pos(pos);
        if (area[rpos] == PosStatus::Livre) {
            area[rpos] = PosStatus::Obstaculo;
            obstaculos--;
        }
    }
}

Ambiente::~Ambiente() {

}

PosStatus Ambiente::verifica(const Posicao &pos) const {
    auto rpos = calc_pos(pos);
    return area[rpos];
}

PosStatus Ambiente::visita(const Posicao &pos) {
    auto rpos = calc_pos(pos);
    if (area[rpos] != PosStatus::Obstaculo) {
        area[rpos] = PosStatus::Visitada;
    }
    return area[rpos];
}

Posicao Ambiente::obtem_dimensoes() const {
    return Posicao();
}

void Ambiente::mostra() const {

}

uint32_t Ambiente::calc_pos(const Posicao &pos) const {
    if (pos.x >= col || pos.y >= lin) {
        throw std::invalid_argument("pos inválida");
    }
    return pos.x + pos.y*lin;
}

