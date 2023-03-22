//
// Created by msobral on 22/03/2023.
//

#include "Robo.h"

Robo::Robo(Ambiente &espaco): espaco(espaco), pos_atual{0,0}, passos(0) {
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
            pos.y += 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Esquerda: {
            pos.y -= 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Acima: {
            pos.x -= 1;
            status = tenta_mover(pos);
            break;
        }
        case Direcao::Abaixo: {
            pos.x += 1;
            status = tenta_mover(pos);
            break;
        }
    }
    return status;
}
