/*
 * Archivo: almacenamiento.c
 * Desarrollado por: Victor De Ponte
 *                   Isaac Lopez
 */

#include "almacenamiento.h"

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define FALSE 0
#define TRUE 1
#endif


/*INICIO funciones y Procedimientos referentes al tipo PilaString*/
StackString *newStackString() {
  StackString *nueva = (StackString *) malloc(sizeof(StackString));
  if (nueva != NULL) {
    nueva->sig = NULL;
    return nueva;
  }  else {
    fprintf(stderr, "newStackString: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

PilaString *newPilaString() {
  PilaString *nueva = (PilaString *) malloc(sizeof(PilaString));
  if (nueva != NULL) {
    nueva->head = NULL;
    nueva->size = 0;
    return nueva;
  }  else {
    fprintf(stderr, "newPilaString: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

void pushPilaString(PilaString *pila, char* elem) {
  StackString *nueva  = newStackString();
  strcpy(nueva->palabra , elem);
  nueva->sig = pila->head;
  pila->head = nueva;
  pila->size++;  
  return;
}

char* popPilaString(PilaString *pila) {
  if (esVaciaPilaString(pila)) {
    fprintf(stderr, "popPilaString: Error al sacar un elemento de la pila: pila vacia!!!\n");
    return;
  } else {
    StackString *salida = pila->head;
    pila->head = pila->head->sig;
    pila->size--;
    char *aux = salida->palabra;
    free(salida);
    return ;
  }
}

int esVaciaPilaString(PilaString *pila) {
  if (pila->size == 0) {
    return 1;
  } else {
    return 0;
  }
}

void imprimePilaString(PilaString *pila) {
  if (esVaciaPilaString(pila) == 1) {
    printf("\n --LA PILA ESTA VACIA--\n");
  } else {
    printf("\n --TAMAÑO = %d --\n", pila->size);
    printf("--------------------\n");
    printf("   %s\n", pila->head->palabra);
    int tam = pila->size - 1;
    StackString *itera = newStackString();
    itera->sig = pila->head;
    while (tam > 0) {
      itera->sig = itera->sig->sig;
      tam--;
      printf("   %s   \n", itera->sig->palabra);
    }
    printf("--------------------\n");
  }
  return;
}

void cleanPila(PilaString *pila) {
  while (esVaciaPilaString(pila) == 0) {
    popPilaString(pila);
  }
}

/*FIN funciones y Procedimientos referentes al tipo PilaString*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/
CajitaInt *newCajitaInt() {
  CajitaInt *nueva = (CajitaInt *) malloc(sizeof(CajitaInt));
  if (nueva != NULL) {
    nueva->sig = nueva->ant = NULL;
    nueva->pos = 0;
    return nueva;
  } else {
    fprintf(stderr, "newCajitaInt: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

ListaInt *newListaInt() {
  ListaInt *nueva = (ListaInt *) malloc(sizeof(ListaInt));
  if (nueva != NULL) {
    nueva->head = nueva->tail = NULL;
    nueva->size = 0;
    return nueva;
  } else {
    fprintf(stderr, "newListaInt: Error al hacer la reserva de memoria!!!\n");
    exit(1);
  }
}

int add(ListaInt *list, int elem) {
  CajitaInt *nueva = newCajitaInt();
  nueva->data = elem;
  if (list->head != NULL && list->tail != NULL) {
    list->tail->sig = nueva;
    nueva->ant = list->tail;
    nueva->sig = NULL;
    list->tail = nueva;
    nueva->pos = nueva->ant->pos + 1;
  } else {
    list->head = list->tail = nueva;
    nueva->pos = 0;
  }
  list->size++;
  nueva = NULL;
  return 0;
}

void delete(ListaInt *list, int elem){
  CajitaInt *aux = list->head;
  while (aux) {
    if (aux->data == elem) {
      if (list->size == 1) {
	free(aux);
	aux = list->head = list->tail = NULL;
	return;
      }
      if (aux->ant) {
	aux->ant->sig = aux->sig;
      } else {
	list->head = aux->sig;
      }
      if (aux->sig) {
	aux->sig->ant = aux->ant;
      } else {
	list->tail = aux->ant;
      }
      aux->ant = aux->sig = NULL;
      free(aux);
      aux = NULL;
      list->size--;
      return;
    }
    aux = aux->sig;
  }
  return;
}

void get_li(ListaInt *list, int posi, int *ans){
  CajitaInt *aux = list->head;
  while (aux->pos != posi && aux && aux->sig) {
    aux = aux->sig;
  }
  if (aux) {
    if (aux->pos == posi) {
      *ans = aux->data;
    } else {
      ans = NULL;
    }
  }
}

int isIn(ListaInt *lista, int elem){
  CajitaInt *aux = lista->head;
  while (aux) {
    if (aux->data == elem) {
      return TRUE;
    }
    aux = aux->sig;
  }
  return FALSE;
}

void li_print(ListaInt lista){
  CajitaInt *aux = lista.head;
  printf("|-------|\n");
  while (aux) {
    printf("|%d\t|\n", aux->data);
    aux = aux->sig;
  }
  printf("|_______|\n");
}

int li_liberar(ListaInt *list){
  CajitaInt *aux = list->head;
  CajitaInt *siguiente;
  while (aux) {
    if (list->size == 1) {
      free(aux);
      aux = list->head = list->tail = NULL;
      return;
    }
    if (aux->ant) {
      aux->ant->sig = aux->sig;
    } else {
      list->head = aux->sig;
    }
    if (aux->sig) {
      aux->sig->ant = aux->ant;
    } else {
      list->tail = aux->ant;
    }
    siguiente = aux->sig;
    aux->ant = aux->sig = NULL;
    free(aux);
    aux = NULL;
    list->size--;
    aux = siguiente;
    siguiente = NULL;
  }
  aux = siguiente = NULL;
  return;
}

/*FIN Funciones y Procedimientos referentes al tipo ListaInt*/

/*FIN DEL ARCHIVO (EOF)*/
