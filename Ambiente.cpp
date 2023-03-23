//
// Created by msobral on 22/03/2023.
//

#include "Ambiente.h"
#include <sys/time.h>
#include <time.h>
#include <stdexcept>
#include <string>

void Ambiente::desenha_topo(int colunas) const {
    printf("%lc%lc", glyph[10], glyph[8]);
    for (auto i=colunas-1; i > 0; i--) {
        printf("%lc%lc", glyph[14], glyph[8]);
    }
    printf("%lc\n", glyph[6]);
}

void Ambiente::desenha_linha(iterador inicio, iterador fim, bool ultima) const {
    // lambda para conversão
    auto status_para_letra = [](const PosStatus & pos) {
        switch (pos) {
            case PosStatus::Obstaculo:
                return 'O';
            case PosStatus::Visitada:
                return 'X';
            default:
                return ' ';
        }
    };

    printf("%lc", glyph[1]);
    for (auto it=inicio; it != fim; it++) {
        printf("%c%lc", status_para_letra(*it), glyph[1]);
    }
    printf("\n");
    printf("%lc", ultima?glyph[9]:glyph[11]);
    for (auto it=inicio; it != fim; it++) {
        auto sep = std::next(it)==fim?(ultima?glyph[5]:glyph[7]):(ultima?glyph[13]:glyph[15]);
        printf("%lc%lc", glyph[8],sep);
    }
    printf("\n");
}

void espera(uint32_t milissegundos) {
    timespec ts{milissegundos/1000, 1000000*(milissegundos % 1000)};

    nanosleep(&ts, NULL);
}

Ambiente::Ambiente(uint8_t linhas, uint8_t colunas, uint8_t obstaculos): lin(linhas), col(colunas) {
    area.assign(lin*col, PosStatus::Livre);
    srand(clock());
    while (obstaculos > 0) {
        Posicao pos{static_cast<uint8_t>(rand()% lin), static_cast<uint8_t>(rand()% col)};
        auto rpos = calc_pos(pos).value();
        if (area[rpos] == PosStatus::Livre) {
            area[rpos] = PosStatus::Obstaculo;
            obstaculos--;
        }
    }
}

Ambiente::~Ambiente() {

}

PosStatus Ambiente::verifica(const Posicao &pos) const {
    auto op_pos = calc_pos(pos);
    if (op_pos.has_value()) {
        return area[op_pos.value()];
    }
    return PosStatus::Invalida;
}

PosStatus Ambiente::visita(const Posicao &pos) {
    auto op_pos = calc_pos(pos);
    if (op_pos.has_value()) {
        auto rpos = op_pos.value();
        if (area[rpos] != PosStatus::Obstaculo) {
            area[rpos] = PosStatus::Visitada;
        }
        return area[rpos];
    }
    return PosStatus::Invalida;
}

Posicao Ambiente::obtem_dimensoes() const {
    return Posicao{lin, col};
}

void Ambiente::mostra(std::ostream & out) const {
    setlocale(LC_ALL, "");

    desenha_topo(col);
    auto ultima = lin-1;
    for (uint8_t j=0; j < lin; j++) {
        auto start = area.begin() + j*lin;
        auto fim = start + col;
        desenha_linha(start, fim, j == ultima);
    }
}

std::optional<uint32_t> Ambiente::calc_pos(const Posicao &pos) const {
    if (pos.x >= col || pos.y >= lin) {
        return std::nullopt;
    }
    return std::make_optional(pos.x + pos.y*lin);
}

