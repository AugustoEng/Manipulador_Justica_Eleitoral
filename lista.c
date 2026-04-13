#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"

//TODO LEITURA
static const char *parse_field(const char *p, char *out, int outsize) {
    int i = 0;
    if (*p == '"') {
        p++; 
        while (*p && !(*p == '"' && *(p + 1) != '"')) {
            if (i < outsize - 1) out[i++] = *p;
            p++;
        }
        if (*p == '"') p++; 
    } else {
        while (*p && *p != ',' && *p != '\n' && *p != '\r') {
            if (i < outsize - 1) out[i++] = *p;
            p++;
        }
    }
    out[i] = '\0';
    if (*p == ',') p++; 
    return p;
}

//TODO LIMPAR TERMINAL
void LimparTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

//TODO PAUSAR TERMINAL
void Pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

//TODO INICIALIZA
void InicializarLista(Lista *L) {
    L->Tamanho = 0;
    L->Capacidade = MAX_TRIBUNAIS;
}

//TODO CHEIA
//? 1 se estiver cheia
int ListaCheia(const Lista *L) {
    return L->Tamanho >= L->Capacidade;
}

//TODO VAZIA
//? 1 se estiver vazia
int ListaVazia(const Lista *L) {
    return L->Tamanho == 0;
}

//TODO ADICIONA NA STRUCT
int AdicionarTribunal(Lista *L, Tribunal A) {
    if (ListaCheia(L)) {
        printf("ERRO: Lista Cheia");
        return 0;
    }
    L->Dados[L->Tamanho] = A;
    L->Tamanho++;
    return 1;
}

//TODO CABEÇALHO | CONCATENAÇÃO
int EscreverCabecalhoConcatenado(int comando, const char *NomeArquivo) {
    if (comando == 0) {
        FILE *D = fopen(NomeArquivo, "w");
        if (D == NULL) {
            printf("ERRO: O arquivo não foi devidamente aberto");
            return 0;
        }
        fprintf(D, "\"sigla_tribunal\",\"procedimento\",\"ramo_justica\",\"sigla_grau\","
                   "\"uf_oj\",\"municipio_oj\",\"id_ultimo_oj\",\"nome\",\"mesano_cnm1\",\"mesano_sent\","
                   "\"casos_novos_2026\",\"julgados_2026\",\"prim_sent2026\",\"suspensos_2026\","
                   "\"dessobrestados_2026\",\"cumprimento_meta1\",\"distm2_a\",\"julgm2_a\",\"suspm2_a\","
                   "\"cumprimento_meta2a\",\"distm2_ant\",\"julgm2_ant\",\"suspm2_ant\",\"desom2_ant\","
                   "\"cumprimento_meta2ant\",\"distm4_a\",\"julgm4_a\",\"suspm4_a\",\"cumprimento_meta4a\","
                   "\"distm4_b\",\"julgm4_b\",\"suspm4_b\",\"cumprimento_meta4b\"\n");
        fclose(D);
    }
    return 1;
}

//TODO CABEÇALHO | RESUMO
int EscreverCabecalhoResumido(int comando, const char *NomeArquivo) {
    if (comando == 0) {
        FILE *D = fopen(NomeArquivo, "w");
        if (D == NULL) {
            printf("ERRO: O arquivo não foi devidamente aberto");
            return 0;
        }
        fprintf(D, "sigla_tribunal,total_julgados_2026,Meta1,Meta2A,Meta2Ant,Meta4A,Meta4B\n");
        fclose(D);
    }
    return 1;
}

//TODO LÊ CSV E ADICIONA NA STRUCT
int CarregarCSV(Lista *L, const char *Nome_Arquivo, Tribunal t) {
    FILE *F = fopen(Nome_Arquivo, "r");
    if (F == NULL) {
        perror("ERRO: O arquivo não foi aberto com sucesso");
        return -1;
    }

    char linha[MAX_LINHA];
    fgets(linha, sizeof(linha), F);

    char buf[256];
    int lidos = 0;

    while (fgets(linha, sizeof(linha), F) != NULL) {
        if (strlen(linha) <= 1) continue;
        linha[strcspn(linha, "\r\n")] = '\0';

        const char *p = linha;

        // Campos string
        p = parse_field(p, t.sigla_tribunal, sizeof(t.sigla_tribunal));
        p = parse_field(p, t.procedimento,   sizeof(t.procedimento));
        p = parse_field(p, t.ramo_justica,   sizeof(t.ramo_justica));
        p = parse_field(p, t.sigla_grau,     sizeof(t.sigla_grau));
        p = parse_field(p, t.uf_oj,          sizeof(t.uf_oj));
        p = parse_field(p, t.municipio_oj,   sizeof(t.municipio_oj));

        p = parse_field(p, buf, sizeof(buf));
        t.id_ultimo_oj = atoi(buf);

        p = parse_field(p, t.nome,        sizeof(t.nome));
        p = parse_field(p, t.mesano_cnm1, sizeof(t.mesano_cnm1)); 
        p = parse_field(p, t.mesano_sent, sizeof(t.mesano_sent)); 

        p = parse_field(p, buf, sizeof(buf)); t.casos_novos_2026    = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.julgados_2026       = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.prim_sent2026       = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.suspensos_2026      = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.dessobrestados_2026 = atoi(buf);

        p = parse_field(p, buf, sizeof(buf)); t.cumprimento_meta1   = (float)atof(buf);

        p = parse_field(p, buf, sizeof(buf)); t.distm2_a  = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.julgm2_a  = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.suspm2_a  = atoi(buf);

        p = parse_field(p, buf, sizeof(buf)); t.cumprimento_meta2a  = (float)atof(buf);

        p = parse_field(p, buf, sizeof(buf)); t.distm2_ant = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.julgm2_ant = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.suspm2_ant = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.desom2_ant = atoi(buf);

        p = parse_field(p, buf, sizeof(buf)); t.cumprimento_meta2ant = (float)atof(buf);

        p = parse_field(p, buf, sizeof(buf)); t.distm4_a = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.julgm4_a = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.suspm4_a = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.cumprimento_meta4a  = atoi(buf);

        p = parse_field(p, buf, sizeof(buf)); t.distm4_b = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.julgm4_b = atoi(buf);
        p = parse_field(p, buf, sizeof(buf)); t.suspm4_b = atoi(buf);

        p = parse_field(p, buf, sizeof(buf)); t.cumprimento_meta4b  = (float)atof(buf);

        AdicionarTribunal(L, t);
        lidos++;
    }

    fclose(F);
    return lidos;
}

//TODO DESCARREGA OS DADOS DA STRUCT NO DESTINO
int EscreverCSV(Lista *L, Tribunal t, const char *Nome_Arquivo) {
    FILE *D = fopen(Nome_Arquivo, "a");

    int escritos = 0;
    for (int i = 0; i < L->Tamanho; i++) {
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
            L->Dados[i].sigla_tribunal, L->Dados[i].procedimento, L->Dados[i].ramo_justica,
            L->Dados[i].sigla_grau, L->Dados[i].uf_oj, L->Dados[i].municipio_oj,
            L->Dados[i].id_ultimo_oj,
            L->Dados[i].nome, L->Dados[i].mesano_cnm1, L->Dados[i].mesano_sent,
            L->Dados[i].casos_novos_2026, L->Dados[i].julgados_2026, L->Dados[i].prim_sent2026,
            L->Dados[i].suspensos_2026, L->Dados[i].dessobrestados_2026,
            L->Dados[i].cumprimento_meta1,
            L->Dados[i].distm2_a, L->Dados[i].julgm2_a, L->Dados[i].suspm2_a,
            L->Dados[i].cumprimento_meta2a,
            L->Dados[i].distm2_ant, L->Dados[i].julgm2_ant, L->Dados[i].suspm2_ant, L->Dados[i].desom2_ant,
            L->Dados[i].cumprimento_meta2ant,
            L->Dados[i].distm4_a, L->Dados[i].julgm4_a, L->Dados[i].suspm4_a, L->Dados[i].cumprimento_meta4a,
            L->Dados[i].distm4_b, L->Dados[i].julgm4_b, L->Dados[i].suspm4_b,
            L->Dados[i].cumprimento_meta4b
        );
        escritos++;
    }
    fclose(D);
    return escritos;
}

//TODO FUNÇÃO CONCATENAR
int ConcatenarDados(Lista *L, Tribunal T, const char *NomeArquivo) {
    int n_arquivos = 27, header = 0;
    char *arquivos[] = {
        "teste_TRE-AC.csv", "teste_TRE-AL.csv", "teste_TRE-AM.csv", "teste_TRE-AP.csv",
        "teste_TRE-BA.csv", "teste_TRE-CE.csv", "teste_TRE-DF.csv", "teste_TRE-ES.csv",
        "teste_TRE-GO.csv", "teste_TRE-MA.csv", "teste_TRE-MG.csv", "teste_TRE-MS.csv",
        "teste_TRE-MT.csv", "teste_TRE-PA.csv", "teste_TRE-PB.csv", "teste_TRE-PE.csv",
        "teste_TRE-PI.csv", "teste_TRE-PR.csv", "teste_TRE-RJ.csv", "teste_TRE-RN.csv",
        "teste_TRE-RO.csv", "teste_TRE-RR.csv", "teste_TRE-RS.csv", "teste_TRE-SC.csv",
        "teste_TRE-SE.csv", "teste_TRE-SP.csv", "teste_TRE-TO.csv"
    };

    for (int i = 0; i < n_arquivos; i++) {
        EscreverCabecalhoConcatenado(header, NomeArquivo);
        int carregados = CarregarCSV(L, arquivos[i], T);
        int escritos   = EscreverCSV(L, T, NomeArquivo);
        L->Tamanho = 0;
        header = 1;

        if (escritos != carregados)
            printf("Houve um deficit de %d na escrita do arquivo %s", carregados - escritos, arquivos[i]);
        else
            printf("Arquivo [ %s ] concatenado com sucesso\n", arquivos[i]);
    }
    printf("\nArquivo %s foi criado", NomeArquivo);
    return 1;
}

//TODO FUNÇÃO RESUMO
int GerarResumo(Lista *L, Tribunal T, const char *NomeArquivo) {
    int n_arquivos = 27;
    char *arquivos[] = {
        "teste_TRE-AC.csv", "teste_TRE-AL.csv", "teste_TRE-AM.csv", "teste_TRE-AP.csv",
        "teste_TRE-BA.csv", "teste_TRE-CE.csv", "teste_TRE-DF.csv", "teste_TRE-ES.csv",
        "teste_TRE-GO.csv", "teste_TRE-MA.csv", "teste_TRE-MG.csv", "teste_TRE-MS.csv",
        "teste_TRE-MT.csv", "teste_TRE-PA.csv", "teste_TRE-PB.csv", "teste_TRE-PE.csv",
        "teste_TRE-PI.csv", "teste_TRE-PR.csv", "teste_TRE-RJ.csv", "teste_TRE-RN.csv",
        "teste_TRE-RO.csv", "teste_TRE-RR.csv", "teste_TRE-RS.csv", "teste_TRE-SC.csv",
        "teste_TRE-SE.csv", "teste_TRE-SP.csv", "teste_TRE-TO.csv"
    };

    EscreverCabecalhoResumido(0, NomeArquivo);
    FILE *D = fopen(NomeArquivo, "a");
    if (D == NULL) {
        printf("ERRO: O arquivo %s não pôde ser aberto para escrita\n", NomeArquivo);
        return 0;
    }

    for (int i = 0; i < n_arquivos; i++) {
        int carregados = CarregarCSV(L, arquivos[i], T);
        (void)carregados;

        int sum_julgados_2026 = 0, sum_casos_novos_2026 = 0, sum_dessobrestados_2026 = 0, sum_suspensos_2026 = 0,
            sum_julgm2_a = 0,      sum_distm2_a = 0,         sum_suspm2_a = 0,
            sum_julgm2_ant = 0,    sum_distm2_ant = 0,       sum_suspm2_ant = 0,   sum_desom2_ant = 0,
            sum_julgm4_a = 0,      sum_distm4_a = 0,         sum_suspm4_a = 0,
            sum_julgm4_b = 0,      sum_distm4_b = 0,         sum_suspm4_b = 0;

        int denominador = 0;

        char sigla_atual[8] = "";
        if (L->Tamanho > 0) {
            strncpy(sigla_atual, L->Dados[0].sigla_tribunal, sizeof(sigla_atual) - 1);
        }

        for (int j = 0; j < L->Tamanho; j++) {
            sum_julgados_2026       += L->Dados[j].julgados_2026;
            sum_casos_novos_2026    += L->Dados[j].casos_novos_2026;
            sum_dessobrestados_2026 += L->Dados[j].dessobrestados_2026;
            sum_suspensos_2026      += L->Dados[j].suspensos_2026;

            sum_julgm2_a += L->Dados[j].julgm2_a;
            sum_distm2_a += L->Dados[j].distm2_a;
            sum_suspm2_a += L->Dados[j].suspm2_a;

            sum_julgm2_ant += L->Dados[j].julgm2_ant;
            sum_distm2_ant += L->Dados[j].distm2_ant;
            sum_suspm2_ant += L->Dados[j].suspm2_ant;
            sum_desom2_ant += L->Dados[j].desom2_ant;

            sum_julgm4_a += L->Dados[j].julgm4_a;
            sum_distm4_a += L->Dados[j].distm4_a;
            sum_suspm4_a += L->Dados[j].suspm4_a;

            sum_julgm4_b += L->Dados[j].julgm4_b;
            sum_distm4_b += L->Dados[j].distm4_b;
            sum_suspm4_b += L->Dados[j].suspm4_b;
        }

        //Meta 1
        denominador = sum_casos_novos_2026 + sum_dessobrestados_2026 - sum_suspensos_2026;
        if (denominador != 0)
            fprintf(D, "%s,%d,%.2f,", sigla_atual, sum_julgados_2026,
                    ((float)sum_julgados_2026 / denominador) * 100.0f);
        else
            fprintf(D, "%s,%d,%.2f,", sigla_atual, sum_julgados_2026, 0.0f);

        //Meta 2A
        denominador = sum_distm2_a - sum_suspm2_a;
        if (denominador != 0)
            fprintf(D, "%.2f,", ((float)sum_julgm2_a / denominador) * (1000.0f / 7.0f));
        else
            fprintf(D, "%.2f,", 0.0f);

        //Meta 2Ant
        denominador = sum_distm2_ant - sum_suspm2_ant - sum_desom2_ant;
        if (sum_distm2_ant == 0 && sum_julgm2_ant == 0)
            fprintf(D, "0.00,");
        else if (denominador != 0)
            fprintf(D, "%.2f,", ((float)sum_julgm2_ant / denominador) * 100.0f);
        else
            fprintf(D, "%.2f,", 0.0f);

        //Meta 4A
        denominador = sum_distm4_a - sum_suspm4_a;
        if (sum_distm4_a == 0 && sum_julgm4_a == 0)
            fprintf(D, "0.00,");
        else if (denominador != 0)
            fprintf(D, "%.2f,", ((float)sum_julgm4_a / denominador) * 100.0f);
        else
            fprintf(D, "%.2f,", 0.0f);

        //Meta 4B
        denominador = sum_distm4_b - sum_suspm4_b;
        if (denominador != 0)
            fprintf(D, "%.2f\n", ((float)sum_julgm4_b / denominador) * 100.0f);
        else
            fprintf(D, "%.2f\n", 0.0f);

        L->Tamanho = 0;
        printf("Arquivo [ %s ] resumido com sucesso\n", arquivos[i]);
    }

    fclose(D);
    printf("\nArquivo %s criado com sucesso", NomeArquivo);
    return 1;
}

//TODO FUNÇÃO PESQUISA
void PesquisarMunicipio(Lista *L, Tribunal T, const char *NomeMunicipio) {
    char ext[5] = ".csv";
    char destino[30];

    strcpy(destino, NomeMunicipio);
    for (int k = 0; destino[k]; k++) {
        if (destino[k] == ' ') destino[k] = '_';
    }
    strcat(destino, ext);

    FILE *D = fopen(destino, "w");
    fclose(D);
    D = fopen(destino, "a");

    char MunicipioUpper[35];
    strncpy(MunicipioUpper, NomeMunicipio, sizeof(MunicipioUpper) - 1);
    MunicipioUpper[sizeof(MunicipioUpper) - 1] = '\0';

    int n_arquivos = 27, header = 0;
    char *arquivos[] = {
        "teste_TRE-AC.csv", "teste_TRE-AL.csv", "teste_TRE-AM.csv", "teste_TRE-AP.csv",
        "teste_TRE-BA.csv", "teste_TRE-CE.csv", "teste_TRE-DF.csv", "teste_TRE-ES.csv",
        "teste_TRE-GO.csv", "teste_TRE-MA.csv", "teste_TRE-MG.csv", "teste_TRE-MS.csv",
        "teste_TRE-MT.csv", "teste_TRE-PA.csv", "teste_TRE-PB.csv", "teste_TRE-PE.csv",
        "teste_TRE-PI.csv", "teste_TRE-PR.csv", "teste_TRE-RJ.csv", "teste_TRE-RN.csv",
        "teste_TRE-RO.csv", "teste_TRE-RR.csv", "teste_TRE-RS.csv", "teste_TRE-SC.csv",
        "teste_TRE-SE.csv", "teste_TRE-SP.csv", "teste_TRE-TO.csv"
    };

    for (int i = 0; i < n_arquivos; i++) {
        EscreverCabecalhoConcatenado(header, destino);
        int carregados = CarregarCSV(L, arquivos[i], T);
        (void)carregados;

        for (int l = 0; l < L->Tamanho; l++) {
            if (strcmp(L->Dados[l].municipio_oj, MunicipioUpper) == 0) {
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
                    L->Dados[l].sigla_tribunal, L->Dados[l].procedimento, L->Dados[l].ramo_justica,
                    L->Dados[l].sigla_grau, L->Dados[l].uf_oj, L->Dados[l].municipio_oj,
                    L->Dados[l].id_ultimo_oj,
                    L->Dados[l].nome, L->Dados[l].mesano_cnm1, L->Dados[l].mesano_sent,
                    L->Dados[l].casos_novos_2026, L->Dados[l].julgados_2026, L->Dados[l].prim_sent2026,
                    L->Dados[l].suspensos_2026, L->Dados[l].dessobrestados_2026,
                    L->Dados[l].cumprimento_meta1,
                    L->Dados[l].distm2_a, L->Dados[l].julgm2_a, L->Dados[l].suspm2_a,
                    L->Dados[l].cumprimento_meta2a,
                    L->Dados[l].distm2_ant, L->Dados[l].julgm2_ant, L->Dados[l].suspm2_ant, L->Dados[l].desom2_ant,
                    L->Dados[l].cumprimento_meta2ant,
                    L->Dados[l].distm4_a, L->Dados[l].julgm4_a, L->Dados[l].suspm4_a, L->Dados[l].cumprimento_meta4a,
                    L->Dados[l].distm4_b, L->Dados[l].julgm4_b, L->Dados[l].suspm4_b,
                    L->Dados[l].cumprimento_meta4b
                );
            }
        }
        printf("Arquivo [ %s ] lido com sucesso\n", arquivos[i]);
        L->Tamanho = 0;
        header = 1;
    }
    fclose(D);
    printf("\nArquivo %s foi criado", destino);
}