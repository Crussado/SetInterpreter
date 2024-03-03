#include "slist.h"
#include <stdlib.h>
#include <stdio.h>

//slist_crear se encarga de crear una lista vacia.
//slist_crear: Void->SList
SList slist_crear() {
  return NULL;
}

//slist_destruir se encarga de dada una lista, una funcion elim, y un dato extra que junto
//a la funcion se encargan de eliminar los datos de la lista, eliminana la lista.
//slist_destruir: SList->FuncionEliminar->Void*->NULL
void slist_destruir(SList lista, FuncionEliminar elim, void *extra) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    elim(nodoAEliminar->dato, extra);
    free(nodoAEliminar);
  }
}

//slist_vacia se encarga de dada una lista corroborar si es vacia.
//slist_vacia: SList->Int
int slist_vacia(SList lista) {
  return lista == NULL;
}

//slist_agregar se encarga de dada una lista y un dato, agrega el dato a la lista.
//slist_agregar: SList->Void*->SList
SList slist_agregar(SList lista, void *dato) {
  SList nodoNuevo = malloc(sizeof(SNodo));
  nodoNuevo->dato = dato;
  nodoNuevo->sig = lista;
  return nodoNuevo;
}

//slist_eliminar dada una lista, un dato a buscar, una funcion para que los compare, una para que junto a un 
//dato extra eliminen el dato buscado y un entero representando la cantidad, buscan y eliminan un dato de la lista.
//slist_eliminar: SList->Void*->FuncionIgualdad->FuncionEliminar->Void*->Int*->Slist
SList slist_eliminar(SList lista, void *clave, FuncionIgualdad comparar,
                     FuncionEliminar elim, void *extra, unsigned *cant) {
  if (lista == NULL)
    return NULL;

  if (comparar(lista->dato, clave) == 0) {
    SList aux = lista->sig;
    elim(lista->dato, extra);
    free(lista);
    *cant = *cant - 1;
    return aux;
  }

  SList padre = lista, hijo = padre->sig;
  int encontrado = 0;

  while (hijo != NULL && !encontrado) {
    if (comparar(hijo->dato, clave) == 0)
      encontrado = 1;
    else {
      hijo = hijo->sig;
      padre = padre->sig;
    }
  }
  if (encontrado) {
    padre->sig = hijo->sig;
    elim(hijo->dato, extra);
    free(hijo);
    *cant = *cant - 1;
  }
  return lista;
}

//slist_contiene dada una lista, un dato a comparar, y una funcion para comparar, se encarga de
//devolver el dato buscado, devuelve NULL en caso de no encontrarlo.
//slist_contiene: SList->Void*->FuncionIgualdad
void *slist_contiene(SList lista, void *clave, FuncionIgualdad comparar) {
  void *aux = NULL;

  for (; lista != NULL && aux == NULL; lista = lista->sig)
    if (comparar(lista->dato, clave) == 0)
      aux = lista->dato;
  return aux;
}
