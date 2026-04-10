#ifndef LISTA_H
#define LISTA_H

#define MAX_LINHA 500

typedef struct {
    // Os nomes
    char sigla_tribunal[8];
    char procedimento[30];
    char ramo_justica[20];
    char sigla_grau[4];
    char uf_oj[4];
    char municipio_oj[35];
    int  id_ultimo_oj;
    char nome[70];
    char mesano_cnm1[10];
    char mesano_sent[10];

    //Separei em blocos para a gente conseguir ver melhor, sempre "acabando" num float pra ficar bonito
    //! Tentar manter a ordem, por favor

    int   casos_novos_2026;
    int   julgados_2026;
    int   prim_sent2026;
    int   suspensos_2026;
    int   dessobrestados_2026;
    float cumprimento_meta1;

    int   distm2_a;
    int   julgm2_a;
    int   suspm2_a;
    float cumprimento_meta2a;

    int   distm2_ant;
    int   julgm2_ant;
    int   suspm2_ant;
    int   desom2_ant;
    float cumprimento_meta2ant;

    int   distm4_a;
    int   julgm4_a;
    int   suspm4_a;
    int   cumprimento_meta4a;

    int   distm4_b;
    int   julgm4_b;
    int   suspm4_b;
    float cumprimento_meta4b;
} Tribunal;

int concatenar_csv(const char *nome_arquivo);
int resumo_tribunais(const char *nome_arquivo);
int busca_municipio(const char * nome_arquivo, char *nome_municipio);

#endif