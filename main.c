#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

Lista L;

void LimparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

int main()  {

    Tribunal Eleitoral;
    int opcao = -1;
    char municipio[30];
 
    while (opcao != 0) {
 
        printf("=======================================================\n");
        printf("       SISTEMA DE DADOS - TRIBUNAIS ELEITORAIS         \n");
        printf("             Consolidacao CNJ - Metas 2026             \n");
        printf("=======================================================\n\n");
        printf("  Selecione uma operacao:\n\n");
        printf("  [1]  Concatenar todos os CSVs em um unico arquivo\n");
        printf("  [2]  Gerar resumo de metas por tribunal\n");
        printf("  [3]  Pesquisar registros por municipio\n");
        printf("  [0]  Sair\n\n");
        printf("-------------------------------------------------------\n");
        printf("  Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                LimparTerminal();
                InicializarLista(&L);
                ConcatenarDados(&L, Eleitoral, "Tribunais_Concatenados.csv");
                Pausar();
                LimparTerminal();
                break;
            case 2:
                LimparTerminal();
                InicializarLista(&L);
                GerarResumo(&L, Eleitoral, "Resumo_Tribunais.csv");
                Pausar();
                LimparTerminal();
                break;
            case 3:
                LimparTerminal();
                InicializarLista(&L);
                printf("Selecione qual Município deseja pesquisar, em maiúsculo (ex: ACREÚNA): ");
                scanf(" ");                          
                fgets(municipio, sizeof(municipio), stdin);
                municipio[strcspn(municipio, "\r\n")] = '\0';  
                PesquisarMunicipio(&L, Eleitoral, municipio);
                Pausar();
                LimparTerminal();
                break;
            case 0:
                LimparTerminal();
                printf("  Encerrando o sistema. Ate logo!\n\n");
                break;
            default:
                printf("\n  ERRO: Opcao invalida. Tente novamente.");
                Pausar();
                break;
        }
    }
};
