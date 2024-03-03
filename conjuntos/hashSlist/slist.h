#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

#ifndef __FUNCIONIGUALDAD__
#define __FUNCIONIGUALDAD__
typedef int (*FuncionIgualdad) (void *, void *);
#endif

#ifndef __FUNCIONELIMINAR__
#define __FUNCIONELIMINAR__
typedef void (*FuncionEliminar) (void *, void *);
#endif

#ifndef __LISTA__
#define __LISTA__
typedef struct _SNodo {
  void *dato;
  struct _SNodo *sig;
} SNodo;

typedef SNodo *SList;
#endif

SList slist_crear();

void slist_destruir(SList lista, FuncionEliminar elim, void *extra);

int slist_vacia(SList lista);

SList slist_agregar(SList lista, void *dato);

SList slist_eliminar(SList lista, void *dato, FuncionIgualdad comparar,
                     FuncionEliminar elim, void *extra, unsigned *cantElem);

void *slist_contiene(SList lista, void *dato, FuncionIgualdad comparar);

#endif                          /* __SLIST_H__ */
