#include <iostream>
#include "Ambiente.h"
#include "Robo.h"

// PASSO representa 250 milissegundos
const int PASSO = 250;

int main(int c, char *v[])
{
    // Cria um espaço com 16 colunas e 16 linhas, e 3 obstáculos
    Ambiente sala(16, 16, 5);

    // Cria um robo, que deve percorrer o ambiente especificado
    Robo robo(sala);

    // enquanto conseguir avançar para a direita ...
    while (robo.avanca(Direcao::Direita) != Status::NaoAvancou) {
        // desenha o espaço na tela
        sala.mostra(std::cout);
        // Espera 250 ms entre cada movimentação do robô
        espera(PASSO);
    }

    // enquanto conseguir avançar para cima ...
    while (robo.avanca(Direcao::Acima) != Status::NaoAvancou) {
        sala.mostra(std::cout);
        espera(PASSO);
    }

    std::cout << "Não pode mais avançar. Tecle ENTER para terminar !" << std::endl;
    std::string algo;
    getline(std::cin, algo);

    return 0;
}