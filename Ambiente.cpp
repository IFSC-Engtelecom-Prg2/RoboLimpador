//
// Created by msobral on 22/03/2023.
//

#include "Ambiente.h"
#include <sys/time.h>
#include <time.h>

void espera(uint32_t milissegundos) {
    timespec ts{milissegundos/1000, 1000000*(milissegundos % 1000)};

    nanosleep(&ts, NULL);
}
