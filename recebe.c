#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

  printf("UTFPR\nTrabalho de Comunicação de dados\nCSR31-S71 2019.2\nServidor\n\n");


  //Inicia socket
  printf("Insira a porta do servidor\n");
  scanf("%d",&serv_port);

  server.sin_family = AF_INET;
  server.sin_port = htons(serv_port);
  memset(server.sin_zero, 0x0, 8);

  if((serverfd=socket(AF_INET,SOCK_STREAM,0))==-1){
    printf("Erro ao criar socket\n");
    return(-1);
  }

  if(setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))==-1){
    printf("Erro ao setar porta\n");
    return(-1);
  }

  if(bind(serverfd, (struct sockaddr*)&server, sizeof(server)) == -1 ){
    printf("Erro ao setar porta\n");
    return(-1);
  }

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

    //Recebe msg
    if((msg_len = recv(clientfd, manchester, BUFFER_LENGTH, 0)) > 0) {
      manchester[msg_len] = '\0';
      if(strcmp(manchester,"**")==0){
        break;
      }
      printf("Manchester: %s\n", manchester);

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
      printf("%s\n", bin);


    }
  }

  close(clientfd);
  close(serverfd);
  return (0);
}
