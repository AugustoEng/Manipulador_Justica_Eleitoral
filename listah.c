#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

//Todo INICIALIZA
void InicializarLista(Lista *L) {
    L->Tamanho = 0;
    L->Capacidade = MAX_TRIBUNAIS;
}

//TODO CHEIA
//? 1 Se nestiver cheia
int ListaCheia(const Lista *L) {
    return L->Tamanho >= L->Capacidade;
}

//TODO VAZIA
//? 1 se estiver vazia
int ListaVazia(const Lista *L)  {
    return L->Tamanho == 0;
}

//TODO ADICIONA
int AdicionarTribunal(Lista *L, Tribunal A) {
    if(ListaCheia(L))   {
        printf("ERRO: Lista Cheia");
        return 0;
    }
    L->Dados[L->Tamanho] = A;
    L->Tamanho++;
    return 1;
}

void EscreverCabecalho(int comando){
    if(comando = 1){
        
    }
}

int CarregarCSV(Lista *L, const char *Nome_Arquivo, Tribunal t) {
    FILE * F;
    F = fopen(Nome_Arquivo, "r");
    if(F == NULL)   {
        perror("ERRO: O arquivo não foi aberto com sucesso");
        return -1;
    }

    char linha [MAX_LINHA];
    fgets(linha, sizeof(linha), F);

    int lidos = 0;
    while (fgets(linha, sizeof(linha), F) != NULL) {
        if (strlen(linha) <= 1) continue;

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
        if (AdicionarTribunal(L, t))
        lidos++;
        
    }
    fclose(F);
    return lidos;
}

int EscreverCSV(Lista *L, Tribunal t, const char *Nome_Arquivo)  {
    FILE *D;
    D = fopen(Nome_Arquivo, "a");

    int escritos = 0;
    for(int i = 0; i < L->Tamanho; i++){
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
        escritos ++;
    }
    fclose(D);
    return escritos;
}

int ConcatenarDados(Lista *L, Tribunal T, const char *NomeArquivo){
    int n_arquivos = 27;
    char *arquivos[] = {"teste_TRE-AC.csv", "teste_TRE-AL.csv", "teste_TRE-AM.csv", "teste_TRE-AP.csv", "teste_TRE-BA.csv", "teste_TRE-CE.csv", "teste_TRE-DF.csv", "teste_TRE-ES.csv", "teste_TRE-GO.csv",
        "teste_TRE-MA.csv", "teste_TRE-MG.csv", "teste_TRE-MS.csv", "teste_TRE-MT.csv", "teste_TRE-PA.csv", "teste_TRE-PB.csv", "teste_TRE-PE.csv", "teste_TRE-PI.csv", "teste_TRE-PR.csv",
        "teste_TRE-RJ.csv", "teste_TRE-RN.csv", "teste_TRE-RO.csv", "teste_TRE-RR.csv", "teste_TRE-RS.csv", "teste_TRE-SC.csv", "teste_TRE-SE.csv", "teste_TRE-SP.csv", "teste_TRE-TO.csv"
    }; 
    for(int i = 0; i < n_arquivos; i++) {
        int carregados =    CarregarCSV(L, arquivos[i], T);
        int escritos =      EscreverCSV(L, T, NomeArquivo);
        L->Tamanho = 0;

        if (escritos != carregados){
            printf("Houve um deficit de %d na escrita do arquivo %s", carregados - escritos, arquivos[i]);
        }

    }
}