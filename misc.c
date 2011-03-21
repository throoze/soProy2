/*
 * Universidad Simón Bolívar
 * Departamento de Computación y Tecnología de la Información
 * CI-3825  --  Sistemas Operativos I
 * Prof.: Yudith Cardinale
 * Proyecto 2: Comunicación entre procesos
 * Grupo 26
 * Autores: Victor De Ponte, 05-38087
 *	   	Isaac Lopez, 07-41120
 *
 * Archivo: misc.c
 * Descripción: Librería con funciones útiles miscelaneas.
 */

#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define FALSE 0
#define TRUE 1
#endif

#include "misc.h"

int strIsUL(char *str) {
  char *p = str;
  unsigned long integer = strtoul(str,&p,10);
  errno = 0;
  if (errno != 0) {
    // Falló la conversión, hay overflow.
    perror("Numero demasiado grande. Overflow.\n");
    return FALSE;
  } else if (str == p){
    // Falló la conversión, no se empezó a parsear el string.
    return FALSE;
  } else if (*p != 0) {
    // Falló la conversión, no todos los caracteres son números.
    return FALSE;
  }
  return TRUE;
}


void merge2(char **a, int a1, int a2){
	int tam = a2 - a1;
	char **nuevo; 
	int med = a1 + (tam/2);
	int aux = 0;
	int aux1 = a1;
	int aux2 = med + 1;
	while ((a1 + a2 - aux1 - aux2) > 0){
		if ((a1 - aux1) == 0){
				while((a2 - aux2) > 0){
					nuevo[aux] = a[aux2];
					aux++;
					aux2++;
				}
		} else if((a2 - aux2) == 0){
			while((a2 - aux2) > 0){
					nuevo[aux] = a[aux1];
					aux++;
					aux1++;
			}
		}
		else {
			if (strcmp(a[aux2],  a[aux1]) >= 0){
				nuevo[aux] = a[aux1];
				aux1++;
			} else {
				nuevo[aux] = a[aux2];
				aux2++;
			}
			aux++;
		}
	}
	aux = 0;
	while (aux < tam){
		a[a1 + aux] = nuevo[aux];
		aux++;
	}
	free(nuevo);
	return;
}


void mergeSort2(char **a, int a1, int a2){
	int tam = a2 - a1;
	if (tam <= 1) return;
	int med = a1 + (tam/2);
	mergeSort2(a, a1, med);
	mergeSort2(a, med + 1, a2);
	merge2(a, a1, a2);
}

void ordena(char **a){
	printf("tara\n");
	//mergeSort2(a, 0, (sizeof(a)/sizeof(char)));
}
