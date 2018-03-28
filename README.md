# SHELL
Created by Enzo Quesada & Leonardo Hidalgo.
All rights reserved ®

##Programa
* Se abre la terminal con ctrl+alt+t.
* Se dirige a la carpeta donde se encuentra el proyecto, comando "cd"

## Forma1
* El ejecutable se encuentra en una carpeta oculta (.out)
* cd/ .out
* Digitar el comando ./Shell
## Forma2
* cd /code
* Se puede compilar realizando la sentencia: gcc Shell.c -o Shell
* Seguido de ./Shell
## Forma3  (Necesario Python)
* Las sentencias anteriores ya se encuentran dentro del archivo Compile.py
* Por lo que solo se necesita digitar el comando python Compile.py

## Para agregar Shell por default
* Agregar el path del ejecutable a /etc/shells, cat /etc/shells para checkear
* Para asignar el Shell seleccionado como actual, cualquiera de los siguientes comandos:
		chsh -s "$(command -v Shell)"
		chsh -s /bin/Shell NombreUsuario
		chsh -s /bin/Shell



