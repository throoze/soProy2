#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0
#endif

/*----------------------------------------------------------------------------*/

/* Definicion del tipo PilaString */

/**
 * Estructura de pila convencional. Almacena Strings mediante apuntadores.
 */

typedef struct stack StackString;

struct stack {
  char *palabra;
  StackString *sig;
};

typedef struct {
  StackString *head;
  int size;
} PilaString;

/* FIN tipo PilaString */

/* INICIO de operaciones referentes al tipo PilaString*/

/**
 * Crea un nuevo stack de Strings, reservando la memoria para ello
 * 
 * retorna: Un nuevo apuntador a StackString vacio. 
 */
StackString *newStackString();

/**
 * Crea una nueva pila vacia, reservando la memoria para ello
 * 
 * retorna: Un nuevo apuntador a PilaString vacia.
 */
PilaString *newPilaString();

/**
 * Inserta un nuevo elemento elem la PilaString pila.
 *
 * *pila: apuntador a la pila en donde se desea insertar el elemento.
 *
 * elem: String que se desea insertar en la pila.
 *
 * retorna: void.
 */
void pushPilaString(PilaString *pila, char* elem);

/**
 * Elimina el primer elemento de la PilaString pila.
 *
 * *pila: apuntador a la pila de la cual se desea obtener el elemento.
 *
 * retorna: el string almacenado en stack obtenido.
 */
char* popPilaString(PilaString *pila);

/**
 * Verifica si la PilaString pila esta vacia, es decir, no contiene elementos.
 *
 * *pila: apuntador a la pila en cuestion.
 *
 * retorna: 1 si la pila esta vacia 0 en caso contrario.
 */
int esVaciaPilaString(PilaString *pila);


/**
 *Imprime la pila mostrando cada uno de sus elementos y si tamano total.
 *
 **pila: pila a imprimir
 */
void imprimePilaString(PilaString *pila);

/**
 *Vacia la PilaString pila
 */
void cleanPila(PilaString *pila);

/*FIN de operaciones referentes al tipo PilaString */

/*Definición del tipo ListaInt.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores que almacena int.
 */
typedef struct cajitaInt CajitaInt;

struct cajitaInt {
  int data;
  int pos;
  CajitaInt *sig,*ant;
};

typedef struct {
  CajitaInt *head,*tail;
  int size;
} ListaInt;
/*FIN del tipo ListaInt.*/

/*INICIO Funciones y Procedimientos referentes al tipo ListaInt*/
/**
 * Crea una nueva Cajita, reservando la memoria necesaria para ello.
 * 
 * retorna: Un nuevo apuntador a Cajita vacía.
 */
CajitaInt *newCajitaInt();

/**
 * Crea una nueva lista vacía, reservando la memoria necesaria para ello.
 * 
 * retorna: un nuevo apuntador a una lista vacía.
 */
ListaInt *newListaInt();


/**
 * Inserta el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la inserción.
 * 
 * elem: elemento a insertar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la inserción; 0 si fue realizada 
 *          con éxito, 1 en caso contrario.
 */
int add(ListaInt *list, int elem);

/**
 * Elimina el elemento 'elem' en la Lista '*list'
 * 
 * *list: apuntador a la Lista donde se desea hacer la eliminación.
 * 
 * elem: elemento a eliminar de la Lista.
 */
void delete(ListaInt *list,  int elem);


/**
 * Devuelve el elemento en la posición pos.
 * retorna en la variable 'ans' el elemento almacenado en la posición 'posi'.
 * de no existir un elemento en esa posicion, asigna NULL a 'ans'.
 * list: lista a consultar.
 * posi: posición del elemento solicitado.
 * ans: apuntador a la salida de esta funcion.
 */
void get_li(ListaInt *list, int posi, int *ans);

/**
 * Dice si un elemento 'elem' está actualmente o no en la Lista '*list'.
 * 
 * *list: apuntador a la Lista donde se desea hacer la búsqueda.
 * 
 * elem: elemento a buscar en la Lista.
 * 
 * retorna: Un entero que indica el estado de la búsqueda; 1 si se encontró el
 *          elemento, 1 en caso contrario.
 */

int isIn(ListaInt *list, int elem);


/**
 * Imprime en la salida estándar la ListaInt 'lista'.
 * 
 * lista: ListaInt a imprimir.
 */
void li_print(ListaInt lista);


/**
 * Se encarga de devolver una ListaInt a su estado original vacía, liberando la
 * memoria consumida por ésta.
 * 
 * lote: Un apuntador a la ListaInt que se desea liberar.
 * 
 * retorna: 0 si se completó la limpieza con éxito, 1 en caso contrario.
 */
int li_liberar(ListaInt *lista);

/*FIN Funciones y Procedimientos referentes al tipo ListaInt*/

/*----------------------------------------------------------------------------*/


/*FIN DEL ARCHIVO (EOF)*/
