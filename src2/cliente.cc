#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include<time.h>
int main(int argc, char **argv){
  if(argc<2)
  {
    printf("<host> <puerto>\n");
    return 1;
  }
  struct sockaddr_in cliente; //Se declara la conexion
  struct hostent *servidor; //se declara la informacion del host
  servidor = gethostbyname(argv[1]); 
  if(servidor == NULL)
  { // Se comprueba que exista conexion
    printf("Host erróneo\n");
    return 1;
  }
  int puerto, conexion;
  char buffer[100];
  conexion = socket(AF_INET, SOCK_STREAM, 0); //Asignación del socket
  puerto=(atoi(argv[2])); //Conversion del argumento
  bzero((char *)&cliente, sizeof((char *)&cliente));
  cliente.sin_family = AF_INET;
  cliente.sin_port = htons(puerto); 
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)
  { //Se conecta con el host
    printf("Error conectando con el host\n");
    close(conexion);
    return 1;
  }
  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  char respuesta[100];
  printf("1.recibir un consejo\n");
  fgets(respuesta,100,stdin);
  if (strcmp(respuesta, "1")){
    string hola = "consejo";
    strcpy(buffer,hola.c_str());
  }
  send(conexion, buffer, 100, 0); //Se envia
  bzero(buffer, 100);
  recv(conexion, buffer, 100, 0); //Se recepciona
  printf("%s\n", buffer);
return 0;
}
