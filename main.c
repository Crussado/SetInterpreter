#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "conjuntos/conjunto.h"
#include "interprete.h"

//main es aquella que lleva a cabo la estructura del programa.
int main() {
  Accion comando = CREAR;
  Conjuntos *conjuntos = conjuntos_crear();
  TipoConjunto conjuntoPor;
  int numeros[MAX_BUFF], largo;
  char ingreso[MAX_BUFF], cadena1[MAX_BUFF], cadena2[MAX_BUFF],
      cadena3[MAX_BUFF];
  while (comando != SALIR) {
    printf("Introduzca el comando: ");
    fgets(ingreso, MAX_BUFF, stdin);
    comando = analizar_comando(ingreso, cadena1, cadena2, cadena3);
    switch (comando) {
    case CREAR:
      conjuntoPor = verificar_conjunto(cadena2, numeros, &largo);
      switch (conjuntoPor) {
      case COMPRESION:
        conjuntos_insertar(conjuntos, cadena1, numeros, largo, 1);
        break;
      case EXTENSION:
        conjuntos_insertar(conjuntos, cadena1, numeros, largo, 0);
        break;
      default:
        printf("Fallo en el conjunto\n");
        break;
      }
      break;
    case IMPRIMIR:
      conjuntos_imprimir(conjuntos, cadena1);
      break;
    case UNIR:
      conjuntos_unir(conjuntos, cadena1, cadena2, cadena3);
      break;
    case INTERSECTAR:
      conjuntos_intersectar(conjuntos, cadena1, cadena2, cadena3);
      break;
    case RESTAR:
      conjuntos_restar(conjuntos, cadena1, cadena2, cadena3);
      break;
    case COMPLEMENTO:
      conjuntos_complemento(conjuntos, cadena1, cadena2);
      break;
    case FALLO:
      printf("Error en el comando\n");
      break;
    default:
      break;
    }
  }
  conjuntos_destruir(conjuntos);
  return 0;
}
