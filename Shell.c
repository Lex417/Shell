/*
Created by Enzo Dario Quesada R. & Leonardo Hidalgo F.
13th March, 2018.
All rights reserved.
*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "List.c"
//https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
// colores para la funcion username
#define ANSI_COLOR_LIGHT_CYAN  "\e[96m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define  size  200
#define LSH_TOK_DELIM " \t\r\n\a" // espacio y parametros
#define tamComando 2097152
//definicion de booleanos
typedef int bool;
#define true 1
#define false 0
//instancia de los metodos
char *read_input();
char **parse_input(char *);
int shell(char **, char *, int);
void username (char *,char *);
//***Funcion Main***
int main(int argc, char const *argv[]) {
  //variables
  int index = 1;
  char *cmd;
  char **args;

  // punteros para el username
  char *user = malloc(100 * sizeof(char));
  char *pc = malloc(100 * sizeof(char));

  // loop para mantener el shell, se termina cuando se ingresa exit
  do {
    username (user, pc);
    cmd = read_input();
    args = parse_input(cmd);
    shell(args, cmd, index);
    index++;

  }while (strcmp(cmd,"exit")); //condicion de salida (funcion exit)

  return 0;
}

char *read_input() { // guarda el comando en input para después pasarlo al parse_input

  char *input = NULL;
  size_t bufsize = 0; // tamaño del buffer
  getline(&input, &bufsize, stdin);

  return input;
}
/*
 * https://brennan.io/2015/01/16/write-a-shell-in-c/
    Metodo parse_input basado en el link adjunto
 */
char **parse_input(char *input) { // parsea el comando para su lectura en el execvp

  int bufsize = size;
  int position = 0;

  char **cmd_array = malloc(bufsize * sizeof(char*)); // array donde se almacena el comando
  char *token;

  if (!cmd_array) {
    fprintf(stderr, "lsh: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(input, LSH_TOK_DELIM);// separa el comando cuando hay un espacio o hay un parametro

  while (token != NULL) {// gerena un loop siempre y cuando token no sea un null
    cmd_array[position] = token;
    position++;
    if (position >= bufsize) { // en caso de que la posición sea mayor al tamaño del array
      bufsize += 20;
      cmd_array = realloc(cmd_array, bufsize * sizeof(char*)); // realloc: resize the memory block pointed to
      if (!cmd_array) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
    token = strtok(NULL, LSH_TOK_DELIM);
  }

  cmd_array[position] = NULL;

  return cmd_array;// retorna el array para el execvp
}

int shell(char **cmd, char *input,int index ) { // funcion del shell, contiene el fork y el excevp


  if (strcmp(input, "") != 0)
      push (index, input); // guarda el comando ingresado

  if(input[0]=='!') // imprime el comando segun su numero
  {
    int j;
    char number[7]; //vector para reconocer solo el numero ingresado (tamaño de un int)
    bool flag = true;
    for(j=1; input[j] && j<9; j++)
    { //Probar que el input solo tenga numeros
      if(input[j] == '1' || input[j] == '2' || input[j] == '3' ||
      input[j] == '4' || input[j] == '5' || input[j] == '6' || input[j] == '7'
      || input[j] == '8' || input[j] == '9' || input[j] == '0') {
        number[j-1] = input[j];
      }
      else {//Validacion
        flag = false;
        printf("No ingreso un numero valido de comando");
        break;
      }
    }
    if(flag) {
      int num = atoi(number); //Parsea el valor

      if(getPos(num)==NULL) //Se trae el comando de la lista segun su index
        printf ("Error, comando no existe");
      else
        printf ("%s\n", getPos(num)); //Imprime en pantalla el comando
    }
  }

   // strcmp compara el comando ingresado, con la palabra clave y retorna 0 si son iguales

  if(strcmp(input,"history") == 0)
      showHistory(); // muestra el historial de comandos

  else if(strcmp(input,"exit") == 0)
    printf("\n");

  else {

    pid_t pid;
    pid = fork();

    if (pid < 0) {
      perror("lsh");
      exit(0);
    }

    else if (pid == 0) {
      if (execvp(cmd[0], cmd) == -1) // ejecuta el comando digitado, si retorna -1 el comando no existe
        perror("lsh");
      exit(EXIT_FAILURE);
    }
    else
      wait(NULL);
    return 1;
  }
}

void username (char * user,char * pc){ // imprime el nombre de usuario y de la pc

  getlogin_r(user,tamComando); //getlogin_r retorna el usuario de la maquina
  gethostname (pc, tamComando);// gethostname retorna el nombre de la pc

  printf(ANSI_COLOR_LIGHT_CYAN"%s@%s>>"ANSI_COLOR_RESET, user, pc);

}
