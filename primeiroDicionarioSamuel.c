#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void deixaMinuscula(char *palavra);
void removeCaracteresEspeciais(char *palavra);
int buscaBinaria(char[][45], int, char[], int *);
void exibeDicionario();

int main()
{
    FILE *txtEntrada;
    FILE *dicionario;

    txtEntrada = fopen("textoEntrada.txt", "r"); //abre o arquivo que contém a entrada

    char palavra[45];
    char listaPalavras[1000][45];

    int tamanhoListaPalavras = 0;

    while (fscanf(txtEntrada, "%s", palavra) != EOF) //faz a separação palavra por palavra do texto de entrada
    {

        if (strlen(palavra) > 0) //ignora possíveis caracteres nulos
        {

            //tratamento das palavras
            deixaMinuscula(palavra);
            removeCaracteresEspeciais(palavra);

            //busca binaria para verificar se a palavra se encontra no dicionario
            int posicao;
            int procuraPalavra = buscaBinaria(listaPalavras, tamanhoListaPalavras, palavra, &posicao);

            if (procuraPalavra == -1) { //se a busca retorna -1, significa que não encontrou a palavra e devemos adicioná-la 
                int i = 0;
                for (i = tamanhoListaPalavras; i > posicao; i--)
                    strcpy(listaPalavras[i], listaPalavras[i - 1]); //move as palavras para frente para alocar a nova

                strcpy(listaPalavras[posicao], palavra); //adiciona a nova palavra
                tamanhoListaPalavras++;
            }
        }
    }

    dicionario = fopen("dicionario.txt", "w"); //abre o dicionario para escrita 

    int i = 0;

    for (i = 0; i < tamanhoListaPalavras; i++)
        fprintf(dicionario, "%s\n", listaPalavras[i]);

    fclose(txtEntrada);
    fclose(dicionario);

    exibeDicionario();

    printf("total de palavras diferentes no dicionario=%d\n", tamanhoListaPalavras);

    return 0;
}

void deixaMinuscula(char *palavra)
{
    int i = 0;
    for (i = 0; palavra[i]; i++)
        palavra[i] = tolower(palavra[i]);
}

void removeCaracteresEspeciais(char *palavra)
{
    int i = 0, j = 0;

    while (palavra[i])
    {
        if (isalpha(palavra[i]))
            palavra[j++] = palavra[i];

        i++;
    }

    palavra[j] = '\0';
}

int buscaBinaria(char listaPalavras[][45], int tamanhoListaPalavras, char palavra[], int *pos)
{
    int inicio = 0;
    int fim = tamanhoListaPalavras - 1;
    int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        if (strcmp(palavra, listaPalavras[meio]) == 0)
        {
            return meio;
        }
        else if (strcmp(palavra, listaPalavras[meio]) < 0)
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    *pos = inicio;

    return -1;
}

void exibeDicionario()
{

    FILE *dicionario = fopen("dicionario.txt", "r");

    char linha[45];

    while (fgets(linha, sizeof(linha), dicionario) != NULL)
    {
        if (linha[0] != '\n')
        {
            printf("%s", linha);
        }
    }

    fclose(dicionario);
}