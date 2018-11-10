#include <stdio.h>
#include <stdlib.h>

// Abre o arquivo e mostrar as siglas dos partidos de cada candidato.
// Al�m disso, mostra o n�mero da menor e da maior sigla.

int main (int argc, char *argv[])
{
    FILE *fp;
    char c;

    if (argc!=2) {
        printf("Numero de parametros diferente de dois.\n");
        exit(1);
    }

    fp=fopen(argv[1], "r");

    if(fp==NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        exit(2);
    }

     // Faz a leitura do cabe�alho, descartando a informa��o
     // L� at� encontrar a primeira quebra de linha.
     fscanf (fp, "%c", &c);
     while (c != '\n') {
            fscanf (fp, "%c", &c);
     }

    // Conta a quantidade de ponto e v�rgulas
    int contpv = 0;

    int min = 10000, max = -1;

    // Utilizado para converter string de dois caracteres em um inteiro de dois d�gitos: sigla do partido
    int sigla[2], i = 1;

    // Faz a leitura do primeiro caracter
    fscanf (fp, "%c", &c);

    while (!feof(fp)) {

        // Caso encontre um ponto-e-v�rgula, conta.
        if (c == ';') contpv++;

        // Ap�s ler o vig�simo-s�timo ponto e virgula
        if (contpv == 27 && c!=';' && c!='\"'){

            // Realiza um deslocamento baseado na tabela ASCII
            sigla[i] = c-'0';

            i--;
        }

        // Ao se chegar no final do registro de um candidato...
        if(c == '\n') {

            //...o contador de pontos-e-v�rgulas � reiniciado.
            contpv = 0;

            // Inicia-se tamb�m o �ndice para o vetor que armazena os dois caracteres do n�mero do partido
            i = 1;

            // Converte-se a sigla do partido em um n�mero inteiro
            int partNum = sigla[1]*10 + sigla[0];

            // Se a �ltima leitura n�o tiver gerado um final de arquivo mostra o n�mero do partido
            if(!feof(fp))
                printf("%d\n", partNum);

            // Verifica qual � o maior n�mero de partido
            if (partNum>max)
                max = partNum;
            else if(partNum<min)
                min = partNum;
        }

        // Faz a leitura do pr�ximo caracter
        fscanf(fp, "%c", &c);

    }

    printf("MAX: %d \n", max);
    printf("MIN: %d \n", min);

    fclose(fp);

    return 0;
}


