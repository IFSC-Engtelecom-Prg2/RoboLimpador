//
// Created by msobral on 22/03/2023.
//

#ifndef ROBO_AMBIENTE_H
#define ROBO_AMBIENTE_H

#include <cstdint>
#include <vector>
#include <ostream>
#include <optional>

struct Posicao {
    uint8_t x,y;
};

enum class PosStatus:uint8_t {
    Livre,
    Visitada,
    Obstaculo,
    Invalida
};


class Ambiente {
public:
    Ambiente(uint8_t linhas, uint8_t colunas, uint8_t obstaculos);
    ~Ambiente();

    // desenha o espaço na tela, incluindo as posições já visitadas pelo robô
    void mostra(std::ostream & out) const;

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

    Posicao obtem_dimensoes() const;
private:
    std::vector<PosStatus> area;
    uint8_t lin, col;

#define DOUBLE_SPACE 0

#if DOUBLE_SPACE
#       define SPC "　"
#else
#       define SPC " "
#endif

    using iterador = std::vector<PosStatus>::const_iterator;
    constexpr static wchar_t glyph[] = L"" SPC "│││─┘┐┤─└┌├─┴┬┼" SPC "┆┆┆┄╯╮ ┄╰╭ ┄";

    std::optional<uint32_t> calc_pos(const Posicao & pos) const;
    void desenha_topo(int colunas) const;
    void desenha_linha(iterador inicio, iterador fim, bool ultima) const;
};

// faz uma pausa
void espera(uint32_t milissegundos);

void bloco(std::ostream & out);

#endif //ROBO_AMBIENTE_H
