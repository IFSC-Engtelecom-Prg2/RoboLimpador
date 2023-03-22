//
// Created by msobral on 22/03/2023.
//

#include "Robo.h"

Robo::Robo(Ambiente &espaco): espaco(espaco), pos_atual{0,0}, passos(0) {
    while (espaco.verifica(pos_atual) == PosStatus::Obstaculo) {
        while (espaco.verifica(pos_atual) == PosStatus::Obstaculo) {
            pos_atual.x++;
        }
        if (espaco.verifica(pos_atual) != PosStatus::Livre) {
            pos_atual.y++;
            pos_atual.x = 0;
        }
    }
    if (espaco.verifica(pos_atual) != PosStatus::Livre) {
        throw std::runtime_error("espaço não possui nenhuma posição livre !");
    }
    espaco.visita(pos_atual);
}

Robo::~Robo() {

}

Posicao Robo::obtem_posicao() const {
    return pos_atual;
}

int Robo::obtem_passos() const {
    return passos;
}

Status Robo::avanca(Direcao dir, bool volta) {
    auto pos = pos_atual;
    Status status = Status::NaoAvancou;

    auto tenta_mover = [this](const Posicao & pos) {
        if (espaco.verifica(pos) == PosStatus::Livre) {
            espaco.visita(pos);
            pos_atual = pos;
            return Status::Avancou;
        }
        return Status::NaoAvancou;
    };

    switch (dir) {
        case Direcao::Direita: {
            pos.x += 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Esquerda: {
            pos.x -= 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Acima: {
            pos.y -= 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Abaixo: {
            pos.y += 1;
            status = tenta_mover(pos);
            break;
        }
    }
    return status;
}
