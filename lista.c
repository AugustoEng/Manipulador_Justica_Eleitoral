#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int concatenar_csv(const char *nome_arquivo) {
    FILE *F, *D; // F de File | D de destino       não me pergunte o porquê, eu só quis
    char linha[MAX_LINHA];
    Tribunal t;

    //ABRE UM DOS FILE
    F = fopen(nome_arquivo, "r");
    if  (F == NULL) {
        perror("ERROR: Arquivo nao foi devidamente aberto ou encontrado");
        return 1;
    }

    // Aqui ele cria o arquivo onde vamos jogar tudo dentro
    // Meu notebook é linux, isso funciona pra ele não explodir no processo
    // #if defined(_WIN32) || defined(_WIN64)
    //     system("type nul > tribunais_concatenados.csv");
    // #else 
    //     system("touch tribunais_concatenados.csv");
    // #endif  //? Pesquisar sobre as possibilidades do #if defined
    
    //ABRE O ARQUIVO DESTINO
    D = fopen("tribunais_concatenados.csv", "a");

    //REMOVE O CABEÇALHO DO F
    fgets(linha, sizeof(linha), F);

    //LOOP PARA PEGAR CADA LINHA
    while   (fgets(linha, sizeof(linha), F) != NULL)    {
        //ARMAZENANDO DENTRO DA STRUCT
        sscanf(linha,
                "\"%[^\"]\","   // t.sigla_tribunal
                "\"%[^\"]\","   // t.procedimento
                "\"%[^\"]\","   // t.ramo_justica
                "\"%[^\"]\","   // t.sigla_grau
                "\"%[^\"]\","   // t.uf_oj
                "\"%[^\"]\","   // t.municipio_oj
                "%d,"           
                "\"%[^\"]\","   // t.nome
                "%[^,],"        // t.mesano_cnm1
                "%[^,],"        // t.mesano_sent
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

        //ESCREVENDO NO DESTINO
        //? O /" faz com que as aspas sejam colocadas de forma literal sem explodir o encadeamento 
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
    //FECHAMENTOS E FEEDBACK
    fclose(F);
    fclose(D);
    printf("Arquivo %s anexado com sucesso\n",  nome_arquivo);

}


int resumo_tribunais(const char *nome_arquivo)  {
    FILE *F, *D; // F de File | D de destino       não me pergunte o porquê, eu só quis
    char linha[MAX_LINHA];
    Tribunal t;

    // DEFINIçÃO DAS VARIÁVEI SOMATÓRIA - Ficou lindo
    int sum_julgados_2026 = 0,  sum_casos_novos_2026 = 0,   sum_dessobrestados_2026 = 0,    sum_suspensos_2026 = 0,
        sum_julgm2_a = 0,       sum_distm2_a = 0,           sum_suspm2_a = 0,               sum_julgm2_ant = 0,
        sum_distm2_ant = 0,     sum_suspm2_ant = 0,         sum_desom2_ant = 0,             sum_julgm4_a = 0,
        sum_distm4_a = 0,       sum_suspm4_a = 0,           sum_julgm4_b = 0,               sum_distm4_b = 0,
        sum_suspm4_b = 0;
    
    float   
        meta1 = 0,              meta2a = 0,                 meta2ant = 0,                   meta4a = 0,                     
        meta4b = 0;

    int denominador = 0;



    //ABRE UM DOS FILE
    F = fopen(nome_arquivo, "r");
    if  (F == NULL) {
        perror("ERROR: Arquivo nao foi devidamente aberto ou encontrado");
        return 1;
    }

    //CRIA O ARQUIVO DESTINO
    // #if defined(_WIN32) || defined(_WIN64)
    //     system("type nul > resumo_tribunais.csv");
    // #else
    //     system("touch resumo_tribunais.csv");
    // #endif  //? Pesquisar sobre as possibilidades do #if defined
    
    //ABRE O ARQUIVO DESTINO
    D = fopen("resumo_tribunais.csv", "a");
    if  (D == NULL) {
        perror("ERRO: O arquvivo \"resumo_tribunais.csv\" não foi aberto com sucesso");
    }
    
    //REMOVE O CABEÇALHO DO F
    fgets(linha, sizeof(linha), F);

    //LOOP PARA PEGAR CADA LINHA
    while   (fgets(linha, sizeof(linha), F) != NULL)    {
        
        //ARMAZENANDO DENTRO DA STRUCT
        sscanf(linha,
                "\"%[^\"]\","   // t.sigla_tribunal
                "\"%[^\"]\","   // t.procedimento
                "\"%[^\"]\","   // t.ramo_justica
                "\"%[^\"]\","   // t.sigla_grau
                "\"%[^\"]\","   // t.uf_oj
                "\"%[^\"]\","   // t.municipio_oj
                "%d,"           // t.id_ultimo_oj
                "\"%[^\"]\","   // t.nome
                "%[^,],"        // t.mesano_cnm1
                "%[^,],"        // t.mesano_sent
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

        //FAZENDO AS SOMATÓRIAS - 17 AO TOTAL
        //* Meta1
        sum_julgados_2026       +=  t.julgados_2026;
        sum_casos_novos_2026    +=  t.casos_novos_2026;
        sum_dessobrestados_2026 +=  t.dessobrestados_2026;
        sum_suspensos_2026      +=  t.suspensos_2026;

        //* Meta2A
        sum_julgm2_a += t.julgm2_a;
        sum_distm2_a += t.distm2_a;
        sum_suspm2_a += t.suspm2_a;

        //* Meta2Ant
        sum_julgm2_ant  +=   t.julgm2_ant;
        sum_distm2_ant  +=   t.distm2_ant;
        sum_suspm2_ant  +=   t.suspm2_ant;
        sum_desom2_ant  +=   t.desom2_ant;

        //* Meta4A
        sum_julgm4_a += t.julgm4_a;
        sum_distm4_a += t.distm4_a;
        sum_suspm4_a += t.suspm4_a;

        //* Meta4B
        sum_julgm4_b += t.julgm4_b;
        sum_distm4_b += t.distm4_b;
        sum_suspm4_b += t.suspm4_b;
    }

    //DESENVOLVENDO A FÓRMULAS

    // Meta 1
    denominador = sum_casos_novos_2026 + sum_dessobrestados_2026 + sum_suspensos_2026;
    if (denominador != 0) {
        meta1 = ((float)sum_julgados_2026 / denominador) * 100.0;
    } else {
        meta1 = 0.0;
    }

    // Meta 2A
    denominador = sum_distm2_a + sum_suspm2_a;
    if (denominador != 0) {
        meta2a = ((float)sum_julgm2_a / denominador) * (1000.0 / 7.0);
    } else {
        meta2a = 0.0;
    }

    // Meta 2Ant
    denominador = sum_distm2_ant + sum_suspm2_ant + sum_desom2_ant;
    if (denominador != 0) {
        meta2ant = ((float)sum_julgm2_ant / denominador) * 100.0;
    } else {
        meta2ant = 0.0;
    }

    // Meta 4A
    denominador = sum_distm4_a + sum_suspm4_a;
    if (denominador != 0) {
        meta4a = ((float)sum_julgm4_a / denominador) * 100.0;
    } else {
        meta4a = 0.0;
    }

    // Meta 4B
    denominador = sum_distm4_b + sum_suspm4_b;
    if (denominador != 0) {
        meta4b = ((float)sum_julgm4_b / denominador) * 100.0;
    } else {
        meta4b = 0.0;
    }

    //PRINTA OS RESULTADOS NO ARQUIVO DESTINO
    fprintf(D, "\"%s\", %d, %.2f, %.2f, %.2f, %.2f, %.2f\n", t.sigla_tribunal, sum_julgados_2026, meta1, meta2a, meta2ant, meta4a, meta4b);
    
    //FECHAMENTOS E FEEDBACK
    printf("Arquivo %s resumido com sucesso\n", nome_arquivo);
    fclose(F);
    fclose(D);

}