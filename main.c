#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

Lista L;

int main()  {

    Tribunal Eleitoral;

    InicializarLista(&L);
    PesquisarMunicipio(&L, Eleitoral, "Aquiraz");
};
