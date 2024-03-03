#ifndef __ARBOLINTERVALO_H__
#define __ARBOLINTERVALO_H__

#include <stddef.h>
#include "intervalo.h"

typedef enum {
  ITREE_RECORRIDO_IN,
  ITREE_RECORRIDO_PRE,
  ITREE_RECORRIDO_POST
} BTRecorrido;

typedef struct _BTIntervalo {
  int maxDerecha;
  int altura;
  struct _BTIntervalo *left;
  struct _BTIntervalo *right;
  Intervalo intervalo;
} BTIntervalo;

typedef BTIntervalo *Itree;

Itree itree_crear();

void itree_destruir(Itree arbol);

Itree itree_insertar_avl(Itree arbol, Intervalo dato);

Itree itree_eliminar(Itree arbol, Intervalo dato, Itree * sobra);

Itree itree_intersectar_base(Itree arbol, Itree arbol1, Intervalo intervalo);

Itree itree_intersectar(Itree arbol, Itree arbol1, Itree arbol2);

void itree_recorrer_dfs(Itree arbol, BTRecorrido orden);

int itree_altura(Itree arbol);

Itree itree_copiar(Itree arbol);

Itree itree_unir(Itree arbol1, Itree arbol2);

Itree itree_restar(Itree arbol, Itree arbol1, Itree arbol2);

Itree itree_complemento(Itree arbol);

void itree_imprimir_hasta(Itree arbol, int limite);

int compy_mayor(Itree arbol);

#endif                          /* __ARBOLINTERVALO_H__ */
