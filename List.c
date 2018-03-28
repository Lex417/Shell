#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int index;   //indice de los comandos
    struct Node * next;
    struct Node * prev;
    char *value; //el comando a guardar
} node_t; //instancia

node_t *head = NULL; //primer nodo de la lista
node_t *tail = NULL; //ultimo nodo de la lista


void push(int val, char *comm) //metodo ingresar
{
    node_t * newNode = malloc (sizeof(node_t)); //Se crea un nuevo nodo

    newNode->next = NULL;
    newNode->prev = NULL;  //Se le asignan los punteros a nulo

    newNode->value = malloc(strlen(comm)+1); //Se crea memoria dinamica del tamanno del comando +1
    strcpy(newNode->value,comm); //Se igualan o copian los valores del comando al puntero value de la lista
    newNode->index = val; //se le asigna su numero de index

    node_t * tmp = head;
    if(head == NULL)  //si la lista esta vacia
    {
      head = newNode;
      tail = head;
    }
    else //si no, se agrega al final y se ajusta el previo
    {
        tail->next = newNode; //SIguiente es nuevo
        tail->next->prev = tail; //Se ajustan los punteros
        tail = tail->next; //Se mueve al ultimo
    }
}

int numberOfNodes(){ //Cuenta cuantos nodos tiene la lista
    node_t * tmp = head;
    int cont = 0;
    while (tmp)
    {
        cont++;
        tmp = tmp->next;
    }
  return cont;
}

void showHistory() //Para ver el historial
{
    node_t * tmp = head; //Nodo tmp que apunta a la lista
    int cont = 10; //Limite de historial
    int i;

    if(tmp==NULL) //Validacion, si la lista esta vacia, no hay comandos
    {
      printf("You haven't entered any command \n");
      return;
    }
    else if(numberOfNodes()<cont) //Si la cantidad de nodos es menor a 10
    {
      tmp = tail;                      //Se necesita saber el numero desde el cual empezar a contar
      for(i=numberOfNodes(); i>0; i--) //i = al tamanno de la lista, mientras i sea mayor que 0, va a imprimir los valores
      {
        printf ("%d: %s\n", i, tmp->value); //Se imprime el valor del comando y el valor de i, si la lista es de 3, imprime 3comando,2comando,1comando
        printf("\n");
        tmp = tmp->prev; //Para moverse hacia atras
      }
    }
    else
    {
      tmp = tail;
      while(cont != 0) //De ser el caso que hayan muchos comandos en la lista o mas de 10
      {                               //Se utiliza la variable cont para contar en reversa solo los ultimos 10 ingresados
        printf ("%d: %s\n", tmp->index, tmp->value); //Se imprime el contador del 10 al 1 y el comando
        printf("\n");
        tmp = tmp->prev; //Se muestra para atras
        cont --;
      }
    }
}
char * getPos(int pos) // retorna el nodo de la lista segun el index
{                      //para desde el main traer el comando
    int size = numberOfNodes();
    node_t * tmp = head;

    if(pos > size) //Validacion si no hay comandos
      return NULL;

    else
    {
      for (int i = 1; i < pos; i++) //Busca la posicion del index
      {
          if (tmp == NULL)
              break;
          tmp = tmp->next;
      }
    }
  return tmp->value;
}


void deleteList()//Para borrar la lista
{
    node_t * tmp = head;
    while (tmp)
    {
        head = head->next;
        free (tmp);
        tmp = head;
    }
}
