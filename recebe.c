#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "plotg.h"

#define BUFFER_LENGTH 1600

int main(){
  struct sockaddr_in client,server;
  int serverfd, clientfd;
  char manchester[BUFFER_LENGTH];
  int serv_port;
  int yes = 1;
  int msg_len;
  socklen_t client_len = sizeof(client);
  int i,k;
  char bin[800];
  char mensagem[100];
  unsigned char caracter;

  printf("UTFPR\nTrabalho de Comunicação de dados\nCSR31-S71 2019.2\nServidor\n\n");

  printf("Insira a porta do servidor\n");
  scanf("%d",&serv_port);

  //Inicia socket
  if((serverfd=socket(AF_INET,SOCK_STREAM,0))==-1){
    printf("Erro ao criar socket\n");
    return(-1);
  }
  //Configura parametros do socket
  server.sin_family = AF_INET;
  server.sin_port = htons(serv_port);
  memset(server.sin_zero, 0x0, 8);

  //Seta porta
  if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1){
    printf("Erro ao setar porta\n");
    return(-1);
  }

  if(bind(serverfd, (struct sockaddr*)&server, sizeof(server)) == -1 ){
    printf("Erro ao setar porta\n");
    return(-1);
  }

  printf("Aguardando conexão\n");

  //Espera conexões
  if(listen(serverfd, 1) == -1){
    printf("Erro\n");
    return(-1);
  }

  if ((clientfd=accept(serverfd,(struct sockaddr *) &client, &client_len )) == -1){
    printf("Erro\n");
    return(-1);
  }

  while(1){
    //Zera buffer
    memset(manchester,0x0,BUFFER_LENGTH);

    printf("Aguardando mensagem...\n");

    //Recebe msg
    if((msg_len = recv(clientfd, manchester, BUFFER_LENGTH, 0)) > 0) {
      manchester[msg_len] = '\0';
      //Condição de saída
      if(strcmp(manchester,"**")==0){
        break;
      }
      printf("Manchester: \n%s\n", manchester);


      //Gera Gráfico
      if(plotg(manchester)==-1){
        return(-1);
      }

      //Converte para binário
      i=0;
      k=0;
      while (manchester[i]!='\0'){
        if(manchester[i]=='0' && manchester[i+1] == '1'){
          bin[k] = '0';
        }
        else{
          bin[k] = '1';
        }
        k++;
        i += 2;
      }
      bin[k] = '\0';
      printf("Binário:\n%s\n", bin);

      //Converte para msg criptografada
      i=0;
      k=0;
      while(bin[i]!='\0'){
        caracter = 0;
        if(bin[i]=='1'){
          caracter += 0x80;
        }
        if(bin[i+1]=='1'){
          caracter += 0x40;
        }
        if(bin[i+2]=='1'){
          caracter += 0x20;
        }
        if(bin[i+3]=='1'){
          caracter += 0x10;
        }
        if(bin[i+4]=='1'){
          caracter += 0x08;
        }
        if(bin[i+5]=='1'){
          caracter += 0x04;
        }
        if(bin[i+6]=='1'){
          caracter += 0x02;
        }
        if(bin[i+7]=='1'){
          caracter += 0x01;
        }
        i += 8;
        mensagem[k] = caracter;
        k++;
      }
      mensagem[k]='\0';

      printf("Mensagem criptografada:\n%s\n", mensagem);


      //Descriptografa
      for(i=0;mensagem[i]!='\0';i++){
        mensagem[i] *= (char) -1;
      }

      printf("Mensagem descriptografada:\n%s\n", mensagem);

    }
  }
  printf("Saindo...\n");
  close(clientfd);
  close(serverfd);
  return (0);
}
