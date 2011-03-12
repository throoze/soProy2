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
#define TAMAX 10
#endif

/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/
CajitaInt *newCajitaInt() {
  CajitaInt *nueva = (CajitaInt *) malloc(sizeof(CajitaInt));
  if (nueva != NULL) {
    nueva->sig = nueva->ant = NULL;
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
  } else {
    list->head = list->tail = nueva;
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

int isIn(ListaInt *list, int elem){
  CajitaInt *aux = list->head;
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
