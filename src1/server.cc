#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include<time.h>

string consejoaleatorio(){
    ifstream ficheroEntrada;
string frase;
ficheroEntrada.open ("consejos.txt");// Se abre el archivo de los consejos
getline(ficheroEntrada,frase);
srand(time(NULL));
std::vector<std::string> data;
int cont=0;
int num;
while (frase!=""){
    data.push_back(frase);//se guardan los caracteres de cada linea del archivo
    getline(ficheroEntrada,frase);
    cont++;
}
ficheroEntrada.close();
num = rand()%cont;//se genera un numero al azar

    return data[num];//linea al azar que se muestra

}

int main(int argc, char **argv){
    

  if(argc<2)
  { //Se piden los argumentos
    printf("%s <puerto>\n",argv[0]);
    return 1;
  }
  int c_servidor, c_cliente, puerto; //Se declaran las variables a trabajar
  socklen_t longc; //variable que guarda la longitud 
  struct sockaddr_in servidor, cliente;
  char buffer[100]; //Variable que guarda los mensajes recibidos
  puerto = atoi(argv[1]);
  c_servidor = socket(AF_INET, SOCK_STREAM, 0); //Creacion del socket
  bzero((char *)&servidor, sizeof(servidor));
  servidor.sin_family = AF_INET; 
  servidor.sin_port = htons(puerto);
  servidor.sin_addr.s_addr = INADDR_ANY; //Especifica la direccion
  if(bind(c_servidor, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
  { //Se asigna el puerto
    printf("Error del puerto con la conexion");
    close(c_servidor);// se cierra la conexion con el servidor
    return 1;
  }
  listen(c_servidor, 3); //Se espera el mensaje o peticion
  printf("A la escucha en el puerto %d\n", ntohs(servidor.sin_port));
  longc = sizeof(cliente); //Se asigna el tamño de la variable
  c_cliente = accept(c_servidor, (struct sockaddr *)&cliente, &longc); //Se espera una conexion con el servidor
  if(c_cliente<0)
  {
    printf("Error al recepccionar el mensaje\n");
    close(c_servidor);//Se cierra el servidor
    return 1;
  }
  printf("Conectando con %s:%d\n", inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
  if(recv(c_cliente, buffer, 100, 0) < 0)
  { 
    printf("Error al recibir los datos\n");
    close(c_servidor);
    return 1;
  }
  else
  {
    string var=buffer;
    if (var=="consejo"){
        char consejito[100];
        strcpy(consejito,consejoaleatorio().c_str());
        printf("se envio el consejo %s\n",consejito);//Se muestra el consejo que envia el servidor
        send(c_cliente,consejito, 100, 0);//Se encia el consejo
    }
    
  }
  close(c_servidor);
  return 0;
}
