#include <stdio.h>
#include <string.h>

int main(){
  char mensagem[100],aux;
  char bin[800];
  char manchester[1600];
  int i,j,k;
  printf("UTFPR\nTrabalho de Comunicação de dados\nCSR31-S71 2019.2\n\n");

  while(1){
    printf("Insira a mensagem ou pressione Ctrl + C para sair:\n");
    fgets(mensagem,sizeof(mensagem),stdin);

    /* Remove a nova linha (\n), caso ela tenha sido lida pelo fgets */
		int indiceUltimoCaractere = strlen(mensagem) - 1;
		if(mensagem[indiceUltimoCaractere] == '\n') {
			mensagem[indiceUltimoCaractere] = '\0';
		}

    printf("Texto inserido:\n%s\n",mensagem);
    printf("Criptografado...");

    //Criptografia faz o complemento de 2 de cada byte
    for(i=0;mensagem[i]!='\0';i++){
      mensagem[i] *= (char) -1;
    }

    printf("Mensagem criptografada:\n%s\n",mensagem);

    //Transforma em binário
    k=0;
    for(i=0;mensagem[i]!='\0';i++){
      aux = mensagem[i];
      for(j=0;j<8;j++){
        if(aux&0x80){
          bin[k] = '1';
        }
        else{
          bin[k] = '0';
        }
        aux = aux<<1;
        k++;
      }
    }
    bin[k] = '\0';
    printf("Binário:\n%s\n",bin);

    //Aplica algoritimo manchester
    k=0;
    for(i=0;bin[i]!='\0';i++){
      if(bin[i]=='0'){
        manchester[k] = '0';
        manchester[k+1] = '1';
      }
      else{
        manchester[k] = '1';
        manchester[k+1] = '0';
      }
      k += 2;
    }
    manchester[k-1] = '\0';

    printf("Manchester:\n%s\n",manchester);


  }

  return (0);
}
