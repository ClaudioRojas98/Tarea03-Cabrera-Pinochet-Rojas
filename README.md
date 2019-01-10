# Integrantes

-  Augusto Pinochet correo: augusto.pinochet@alumnos.uv.cl
-  Claudio Rojas  correo : claudio.rojasc@alumnos.uv.cl
-  Sebastian Cabrera correo: sebastian.cabrera@alumnos.uv.cl

# Descripción
Sofware de intereaccion de cliente con servidor
## Compilar
``` 
make clear
make
./servidor <puerto>
./cliente <host> <puerto>
``` 

## Ejemplos de uso
Una vez levantado el servidor web,en otra pestaña se ejecuta al cliente y ahi para solicitar el consejo al azar, se ingresa 1 y el servidor responde con un consejo
ej: ./cliente 127.0.0.1 6000
	1. recibir consejo\n
	1\n
	consejo....
