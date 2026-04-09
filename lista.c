#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int concatenar_csv(const char *nome_arquivo) {
    FILE *F, *D; // F de File | D de destino       não me pergunte o porquê, eu só quis
    char linha[MAX_LINHA];
    Tribunal t;

    // Aqui ele abre o arquiv csv que o professor passou - Um dos, no caso
    F = fopen(nome_arquivo, "r");
    if  (F == NULL) {
        perror("ERROR: Arquivo nao foi devidamente aberto ou encontrado");
        return 1;
    }

    // Aqui ele cria o arquivo onde vamos jogar tudo dentro
    // Meu notebook é linux, isso funciona pra ele não explodir no processo
    #if defined(_WIN32) || defined(_WIN64)
        system("type nul > tribunais_concatenados.csv");
    #else //! Impede que meu Linux exploda
        system("touch tribunais_concatenados.csv");
    #endif  //? Pesquisar sobre as possibilidades do #if defined
    

    D = fopen("tribunais_concatenados.csv", "a");

    fprintf(D, "\"sigla_tribunal\",\"procedimento\",\"ramo_justica\",\"sigla_grau\","
           "\"uf_oj\",\"municipio_oj\",\"id_ultimo_oj\",\"nome\",\"mesano_cnm1\",\"mesano_sent\","
           "\"casos_novos_2026\",\"julgados_2026\",\"prim_sent2026\",\"suspensos_2026\","
           "\"dessobrestados_2026\",\"cumprimento_meta1\",\"distm2_a\",\"julgm2_a\",\"suspm2_a\","
           "\"cumprimento_meta2a\",\"distm2_ant\",\"julgm2_ant\",\"suspm2_ant\",\"desom2_ant\","
           "\"cumprimento_meta2ant\",\"distm4_a\",\"julgm4_a\",\"suspm4_a\",\"cumprimento_meta4a\","
           "\"distm4_b\",\"julgm4_b\",\"suspm4_b\",\"cumprimento_meta4b\"\n");

    fgets(linha, sizeof(linha), F);

    // Lendo os dados de uma linha por vez
    while   (fgets(linha, sizeof(linha), F) != NULL)    {
        sscanf(linha,
            
            //! Deixe esta parte em lista, NÃO coloque em linha, senão fica um inferno de ler
            // Aqui ela não lê as aspas, elas são colocadas no fprintf
                "\"%[^\"]\","   // t.sigla_tribunal
                "\"%[^\"]\","   // t.procedimento
                "\"%[^\"]\","   // t.ramo_justica
                "\"%[^\"]\","   // t.sigla_grau
                "\"%[^\"]\","   // t.uf_oj
                "\"%[^\"]\","   // t.municipio_oj
                "%d,"           // t.id_ultimo_oj
                "\"%[^\"]\","   // t.nome
                "\"%[^\"]\","   // t.mesano_cnm1
                "\"%[^\"]\"," // t.mesano_sent
                "%d,%d,%d,%d,%d,"
                "%f,"
                "%d,%d,%d,"
                "%f,"
                "%d,%d,%d,%d,"
                "%f,"
                "%d,%d,%d,%d,"
                "%d,%d,%d,"
                "%f",
                t.sigla_tribunal, t.procedimento, t.ramo_justica,
                t.sigla_grau, t.uf_oj, t.municipio_oj,
                &t.id_ultimo_oj,
                t.nome, t.mesano_cnm1, t.mesano_sent,
                &t.casos_novos_2026, &t.julgados_2026, &t.prim_sent2026,
                &t.suspensos_2026, &t.dessobrestados_2026,
                &t.cumprimento_meta1,
                &t.distm2_a, &t.julgm2_a, &t.suspm2_a,
                &t.cumprimento_meta2a,
                &t.distm2_ant, &t.julgm2_ant, &t.suspm2_ant, &t.desom2_ant,
                &t.cumprimento_meta2ant,
                &t.distm4_a, &t.julgm4_a, &t.suspm4_a, &t.cumprimento_meta4a,
                &t.distm4_b, &t.julgm4_b, &t.suspm4_b,
                &t.cumprimento_meta4b
            );

        // Colocando a linha no novo arquivo
        // O /" faz com que as aspas sejam colocadas de forma literal sem explodir o encadeamento 
        fprintf(D,
            "\"%s\",\"%s\",\"%s\",\"%s\",\"%s\",\"%s\","
            "%d,"
            "\"%s\",\"%s\",\"%s\","
            "%d,%d,%d,%d,%d,"
            "%.2f,"
            "%d,%d,%d,"
            "%.2f,"
            "%d,%d,%d,%d,"
            "%.2f,"
            "%d,%d,%d,%d,"
            "%d,%d,%d,"
            "%.2f\n",
            t.sigla_tribunal, t.procedimento, t.ramo_justica,
            t.sigla_grau, t.uf_oj, t.municipio_oj,
            t.id_ultimo_oj,
            t.nome, t.mesano_cnm1, t.mesano_sent,
            t.casos_novos_2026, t.julgados_2026, t.prim_sent2026,
            t.suspensos_2026, t.dessobrestados_2026,
            t.cumprimento_meta1,
            t.distm2_a, t.julgm2_a, t.suspm2_a,
            t.cumprimento_meta2a,
            t.distm2_ant, t.julgm2_ant, t.suspm2_ant, t.desom2_ant,
            t.cumprimento_meta2ant,
            t.distm4_a, t.julgm4_a, t.suspm4_a, t.cumprimento_meta4a,
            t.distm4_b, t.julgm4_b, t.suspm4_b,
            t.cumprimento_meta4b
        );
    }
    fclose(F);
    fclose(D);
    printf("Arquivo %s anexado com sucesso\n",  nome_arquivo);

}

