# Sistema de Dados — Tribunais Eleitorais
 
**Consolidação CNJ · Metas 2026**
 
<br>
 
![C](https://img.shields.io/badge/Linguagem-C-00599C?style=flat-square&logo=c&logoColor=white)
![Linux](https://img.shields.io/badge/Ambiente-Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Status](https://img.shields.io/badge/Status-Concluído-2ea043?style=flat-square)
![UCB](https://img.shields.io/badge/UCB-Engenharia%20de%20Software-7B2D8B?style=flat-square)
![Disciplina](https://img.shields.io/badge/Disciplina-Estrutura%20de%20Dados-orange?style=flat-square)
 
<br>
 
> Trabalho bimestral da matéria Estrutura de Dados ministrada pelo professor Marcelo Eustaquio do curso Engenharia de Software da Universidade Católica de Brasília.
> O trabalho por sua vez, consiste em:
> Sistema em C para leitura, concatenação e análise de dados dos **27 Tribunais Regionais Eleitorais** brasileiros, com cálculo das metas do CNJ e pesquisa por município
 
<br>
 
</div>
 
---
 
## Índice
 
- [Visão Geral](#-visão-geral)
- [Arquitetura](#️-arquitetura)
- [Estruturas de Dados](#️-estruturas-de-dados)
- [Como Compilar](#️-como-compilar)
- [Como Usar](#️-como-usar)
- [Funcionalidades](#-funcionalidades)
- [Fluxo de Execução](#-fluxo-de-execução)
- [Equipe](#-equipe)
 
---
 
## Visão Geral
 
O **Sistema de Dados — Tribunais Eleitorais** processa arquivos CSV de todos os **27 TREs** do Brasil, oferecendo três operações principais via menu interativo:
 
| # | Operação | Saída |
|---|----------|-------|
| 1 | Concatenar todos os CSVs em um único arquivo | `Tribunais_Concatenados.csv` |
| 2 | Gerar resumo de metas por tribunal | `Resumo_Tribunais.csv` |
| 3 | Pesquisar registros por município | `<MUNICIPIO>.csv` |
 
---
 
## Arquitetura
 
O projeto é composto por **3 arquivos** com separação clara de responsabilidades:
 
```
tribunais-eleitorais/
├── main.c          ← Ponto de entrada, loop de menu e chamadas principais
├── lista.h         ← Definição das structs e declaração de todas as funções
├── lista.c         ← Implementação das funções auxiliares e principais
│
├── teste_TRE-AC.csv
├── teste_TRE-AL.csv
├── ...             ← 27 arquivos CSV (um por estado)
└── teste_TRE-TO.csv
```
 
---
 
## Estruturas de Dados
 
### `struct Tribunal`
Representa um único registro de órgão julgador eleitoral, com **33 campos** espelhando as colunas do CSV:
 
<details>
<summary><strong>Ver todos os campos</strong></summary>
 
| Campo | Tipo | Descrição |
|-------|------|-----------|
| `sigla_tribunal` | `char[8]` | Sigla do tribunal (ex: `TRE-DF`) |
| `procedimento` | `char[30]` | Tipo de procedimento processual |
| `ramo_justica` | `char[20]` | Ramo da justiça |
| `sigla_grau` | `char[4]` | Grau de jurisdição (ex: `G1`) |
| `uf_oj` | `char[4]` | UF do órgão julgador |
| `municipio_oj` | `char[35]` | Município do órgão julgador |
| `id_ultimo_oj` | `int` | Identificador numérico do órgão julgador |
| `nome` | `char[70]` | Nome completo da zona eleitoral |
| `mesano_cnm1` | `char[10]` | Mês/ano de referência CNM1 (pode ser `NA`) |
| `mesano_sent` | `char[10]` | Mês/ano da sentença (pode ser `NA`) |
| `casos_novos_2026` | `int` | Número de casos novos em 2026 |
| `julgados_2026` | `int` | Número de casos julgados em 2026 |
| `cumprimento_meta1` | `float` | Percentual de cumprimento da Meta 1 |
| `distm2_a / julgm2_a` | `int` | Distribuídos e julgados da Meta 2A |
| `distm2_ant / julgm2_ant` | `int` | Distribuídos e julgados da Meta 2 Anterior |
| `distm4_a / julgm4_a` | `int` | Distribuídos e julgados da Meta 4A |
| `distm4_b / julgm4_b` | `int` | Distribuídos e julgados da Meta 4B |
| `cumprimento_meta4b` | `float` | Percentual de cumprimento da Meta 4B |
 
</details>
 
### `struct Lista`
Array estático de `MAX_TRIBUNAIS` (`40.000`) elementos do tipo `Tribunal`.
 
> ** Nota de implementação:** A lista é declarada como variável **global** em `main.c`, alocada na região BSS/data — e não na stack — evitando stack overflow dada sua grande dimensão.
 
---
 
## Como Compilar
 
**Requisito:** GCC instalado em ambiente Linux/macOS (ou MinGW no Windows).
 
```bash
gcc -o tribunal main.c lista.c -lm
```
 
> A flag `-lm` vincula a biblioteca matemática, necessária para operações com `float`.
 
**Execute com:**
 
```bash
./tribunal
```
 
> Os 27 arquivos CSV devem estar no **mesmo diretório** do executável. Se um arquivo não for encontrado, o programa imprime um erro via `perror()` e continua com os demais.
 
---
 
## Como Usar
 
Ao executar, o seguinte menu é exibido:
 
```
=======================================================
 SISTEMA DE DADOS - TRIBUNAIS ELEITORAIS 
 Consolidacao CNJ - Metas 2026 
=======================================================
 [1] Concatenar todos os CSVs em um unico arquivo
 [2] Gerar resumo de metas por tribunal
 [3] Pesquisar registros por municipio
 [0] Sair
```
 
---
 
## Funcionalidades
 
### `[1]` Concatenar CSVs
Lê os 27 arquivos em sequência e grava todas as linhas em **`Tribunais_Concatenados.csv`**, com um único cabeçalho. O progresso é exibido em tempo real no terminal.
 
### `[2]` Gerar Resumo de Metas
Acumula os totais de cada tribunal e calcula os **5 percentuais de meta** usando as fórmulas do CNJ:
 
```
Meta 1    =  julgados / (casos_novos + dessobrestados - suspensos) × 100
Meta 2A   =  julgm2_a / (distm2_a - suspm2_a) × (1000 / 7)
Meta 2Ant =  julgm2_ant / (distm2_ant - suspm2_ant - desom2_ant) × 100
Meta 4A   =  julgm4_a / (distm4_a - suspm4_a) × 100
Meta 4B   =  julgm4_b / (distm4_b - suspm4_b) × 100
```
 
Resultado gravado em **`Resumo_Tribunais.csv`**, com uma linha por tribunal.
 
### `[3]` Pesquisar por Município
Filtra registros pelo campo `municipio_oj` e grava em **`<MUNICIPIO>.csv`**.
 
**Regras de input:**
- Nome em **MAIÚSCULAS**, sem acentos
- Espaços viram `_` no nome do arquivo (ex: `SAO PAULO` → `SAO_PAULO.csv`)
- A comparação usa `strcmp` (case-sensitive e sensível a acentos)
 
```
Exemplos válidos: BRASILIA · CEILANDIA · GUARA · SAO PAULO
```
 
---
 
## Fluxo de Execução
 
```
Opção [1]  main → InicializarLista → ConcatenarDados
                   └─ [EscreverCabecalhoConcatenado + CarregarCSV + EscreverCSV] × 27
 
Opção [2]  main → InicializarLista → GerarResumo
                   └─ [EscreverCabecalhoResumido + CarregarCSV + soma + fprintf] × 27
 
Opção [3]  main → InicializarLista → PesquisarMunicipio
                   └─ [EscreverCabecalhoConcatenado + CarregarCSV + strcmp + fprintf] × 27
```
 
---
 
## Equipe
 
<div align="center">
 
| Nome |
|------|
| Guilherme Augusto dos Santos |
 
**Orientador:** Prof. Marcelo Eustaquio  
**Disciplina:** Estrutura de Dados · Engenharia de Software · UCB · 2026
 
</div>
 
---
 
<div align="center">
 
<sub>Desenvolvido com pouco sono e muita cafeína — Universidade Católica de Brasília · 2026</sub>
 
</div>
 
