#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(){
  char mensagem[100],aux;
  char bin[800];
  char manchester[1600];
  char serv_addr[16];
  int serv_port;
  int i,j,k;
  struct sockaddr_in server;
  int sockfd;
  int len = sizeof(server);


  printf("UTFPR\nTrabalho de Comunicação de dados\nCSR31-S71 2019.2\nCliente\n\n");

  printf("Insira o IP do servidor\n");
  scanf("%s",serv_addr);

  printf("Insira a porta do servidor\n");
  scanf("%d",&serv_port);

  //Inicia socket cliente
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    printf("Erro na criação do socket\n");
    return(-1);
  }

  //Define propriedades da conexão
  server.sin_family = AF_INET;
  server.sin_port = htons(serv_port);
  server.sin_addr.s_addr = inet_addr(serv_addr);
  memset(server.sin_zero, 0x0, 8);

  //Tenta conectar ao servidor
  if(connect(sockfd, (struct sockaddr*) &server, len) == -1){
    printf("Erro na conexão\n");
    return(-1);
  }

  while(1){
    printf("Insira a mensagem ou digite ** para sair:\n");
    fgets(mensagem,sizeof(mensagem),stdin);

    /* Remove a nova linha (\n), caso ela tenha sido lida pelo fgets */
		int indiceUltimoCaractere = strlen(mensagem) - 1;
		if(mensagem[indiceUltimoCaractere] == '\n') {
			mensagem[indiceUltimoCaractere] = '\0';
		}

    if(strcmp(mensagem, "**") == 0){
      break;
    }

    printf("Texto inserido:\n%s\n",mensagem);
    printf("Criptografado...");

    //Criptografia faz o complemento de 2 de cada byte
    for(i=0;mensagem[i]!='\0';i++){
      mensagem[i] *= (char) -1;
    }

    printf("Mensagem criptografada:\n%s\n",mensagem);

    for(i=0;mensagem[i]!='\0';i++){
      printf("%d\n",mensagem[i]);
    }

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
    manchester[k] = '\0';

    printf("Manchester:\n%s\n",manchester);

    //Imprime linha superior do grafico
    for(i=0;manchester[i]!='\0';i++){
      if(manchester[i]=='0'){
        printf(" ");
      }
      else{
        printf("_");
      }
    }
    printf("\n\n");

    //Imprime linha inferior do grafico
    for(i=0;manchester[i]!='\0';i++){
      if(manchester[i]=='0'){
        printf("_");
      }
      else{
        printf(" ");
      }
    }
    printf("\n\n");

    //Envia mensagem
    send(sockfd, manchester, strlen(manchester), 0);

  }

  //Encerra Comunicação
  send(sockfd, "**", strlen("**"), 0);
  close(sockfd);

  return (0);
}
