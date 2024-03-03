#include "tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "slist.h"

//casilla_obtener_clave se encarga de dada una casilla hash devolver su clave.
//casilla_obtener_clave: CasillaHash*->Void*
void *casilla_obtener_clave(CasillaHash * casilla) {
  return casilla->clave;
}

//casilla_obtener_dato se encarga de dada una casilla hash devolver su dato.
//casilla_obtener_dato: CasillaHash*->Void*
void *casilla_obtener_dato(CasillaHash * casilla) {
  return casilla->dato;
}

//casilla_empty se encarga de dada una casilla verificar si esta vacia.
//casilla_empty: CasillaHash*->Int
int casilla_empty(CasillaHash * casilla) {
  return casilla == NULL;
}

//casilla_eliminar se encarga de dada una casilla hash y su respectiva
//tabla hash de eliminar la casilla.
//casilla_eliminar: Void*->Void*->NULL
void casilla_eliminar(void *casilla, void *tabla) {
  CasillaHash *c = casilla;
  TablaHash *t = tabla;
  t->elimClave(c->clave);
  t->elimDato(c->dato);
  free(c);
}

//casilla_actualizar_dato se encarga de dada una casilla hash y un dato
//de asignarle ese nuevo dato a la casilla.
//casilla_actualizar_dato: CasillaHash*->Void*->NULL
void casilla_actualizar_dato(CasillaHash * casilla, void *dato) {
  casilla->dato = dato;
}

//crear_casilla se encarga de dado una clave y un dato crear una casilla con
//esa misma informacion.
//crear_casilla: Void*->Void*->CasillaHash*
CasillaHash *crear_casilla(void *clave, void *dato) {
  CasillaHash *casilla = malloc(sizeof(CasillaHash));
  casilla->dato = dato;
  casilla->clave = clave;
  return casilla;
}

//tablahash_crear se encarga de dada una longitud, una funcion para hashear, una para comparar
//claves, una para eliminar los datos y una para eliminar las claves, crea una tabla
//hash con esas caracteristicas.
//tablahash_crear: Unsigned->FuncionHash->FuncionIgualdad->FuncionElimDato->FuncionElimClave->TablaHash*
TablaHash *tablahash_crear(unsigned capacidad, FuncionHash hash,
                           FuncionIgualdad igual, FuncionElimDato elimDato,
                           FuncionElimClave elimClave) {
  TablaHash *tabla = malloc(sizeof(TablaHash));
  tabla->hash = hash;
  tabla->capacidad = capacidad;
  tabla->tabla = malloc(sizeof(SList) * capacidad);
  tabla->numElems = 0;
  tabla->igual = igual;
  tabla->elimClave = elimClave;
  tabla->elimDato = elimDato;

  for (unsigned idx = 0; idx < capacidad; ++idx)
    tabla->tabla[idx] = slist_crear();

  return tabla;
}

//tablahash_buscar se encarga de dada una tabla hash y una clave, devolver la 
//casilla con dicha clave o NULL en caso de que no exista.
//tablahash_buscar: TabkaHash*->Void*->Void*
void *tablahash_buscar(TablaHash * tabla, void *clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  CasillaHash *casillaBuscada =
      slist_contiene(tabla->tabla[idx], clave, tabla->igual);
  return casillaBuscada;
}

//tablahash_insertar se encarga dada una tabla hash una clave y un dato, de insertar
//los mismos en la tabla hash.
//tablahash_insertar: TablaHash*->Void*->Void*->NULL
void tablahash_insertar(TablaHash * tabla, void *clave, void *dato) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;
  CasillaHash *casilla = tablahash_buscar(tabla, clave);
  if (casilla_empty(casilla)) {
    casilla = crear_casilla(clave, dato);
    tabla->tabla[idx] = slist_agregar(tabla->tabla[idx], casilla);
    tabla->numElems++;
  } else {
    tabla->elimDato(casilla_obtener_dato(casilla));
    casilla_actualizar_dato(casilla, dato);
    tabla->elimClave(clave);
  }
}

//tablahash_eliminar se encarga de dada una tabla hash y una clave, de eliminar
//la casilla asociada a la clave.
//tablahash_eliminar: TablaHash*->Void*->NULL
void tablahash_eliminar(TablaHash * tabla, void *clave) {
  unsigned idx = tabla->hash(clave);
  idx = idx % tabla->capacidad;

  tabla->tabla[idx] =
      slist_eliminar(tabla->tabla[idx], clave, tabla->igual, casilla_eliminar,
                     tabla, &(tabla->numElems));
}

//tablahash_destruir se encarga de dada una tabla hash la elimina.
//tablahash_destruir: TablaHash*->NULL;
void tablahash_destruir(TablaHash * tabla) {
  for (unsigned i = 0; i < tabla->capacidad; i++)
    slist_destruir(tabla->tabla[i], casilla_eliminar, tabla);
  free(tabla->tabla);
  free(tabla);
}
