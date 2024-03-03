#ifndef __INTERPRETE_H__
#define __INTERPRETE_H__

#include <stddef.h>

#define MAX_BUFF 255

typedef enum {
  FALLO,
  IMPRIMIR,
  CREAR,
  INTERSECTAR,
  UNIR,
  RESTAR,
  COMPLEMENTO,
  SALIR
} Accion;

typedef enum {
  ERROR,
  COMPRESION,
  EXTENSION
} TipoConjunto;

TipoConjunto verificar_conjunto(char *conjunto, int *listaConjunto, int *largo);

Accion analizar_comando(char *ingreso, char *cadena1, char *cadena2,
                        char *cadena3);

#endif                          /* __INTERPRETE_H__ */
