#ifndef STD
#define STD
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#define TRUE 1
#define FALSE 0
#define TAMAX 10
#endif

/*----------------------------------------------------------------------------*/

/*INICIO definición del tipo ListaInt.*/

/**
 * Clasica lista de elementos. Es una lista de apuntadores a void, con lo cual
 * se podra almacenar practicamente cualquier cosa.
 */
typedef struct cajitaInt CajitaInt;

struct cajitaInt {
  int data;
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
