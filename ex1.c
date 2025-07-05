#include <stdio.h>
#include <stdlib.h>

void coverterBinario(int numero, char *binario){
   int i = 0;
   int temp[32];
   
    if(numero == 0){
        binario [1] = '0';
        binario [0] ='\0';
        return;
    }

    while (numero > 0){
        temp[i++] = numero%2;
        numero = numero/2;
    }

    int j =0;
    for(i = i -1;i >= 0;i--){
        binario[j++] = temp[i]+'0';
    }
    binario[j]='\0';
}

int main(){
    int numero;
    char binario[32];
    FILE *arquivoBinarios;

    arquivoBinarios = fopen("listaBinarios.txt","w");
    if(arquivoBinarios == NULL){
        puts("Falha na ao abrir o arquivo!!");
        exit(1);
    }

    while (1)
    {
       puts("Digite numero para converter para binario:");
       scanf("%d",&numero);

       if(numero<0)
       break;

       coverterBinario(numero,binario);
       fprintf(arquivoBinarios, "%s\n",binario);

    }

    puts("Arquivo salvo !!");

    fclose(arquivoBinarios);
    return 0;
}