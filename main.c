#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Lista L;

int main()  {

    Tribunal Eleitoral;

    InicializarLista(&L);
    GerarResumo(&L, Eleitoral, "Resumidos.csv");
};
