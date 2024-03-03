#include "arbolIntervalo/arbolIntervalo.h"
#include "arbolIntervalo/intervalo.h"
#include "hashSlist/tablahash.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "conjunto.h"
#include <ctype.h>

//iguales se encarga de comparar una clave con una casilla de tabla hash.
//iguales: Void*->Void*->Int.
int iguales(void *casilla, void *clave2) {
  char *c1 = casilla_obtener_clave((CasillaHash *) casilla);
  char *c2 = clave2;
  return strcmp(c1, c2);
}

//hash se encarga de "hashear" las claves para la tabla hash.
//hash: Void*->Unsigned
unsigned hash(void *clave) {
  unsigned primo = 97, h = 0, modulo = 10007;
  char *c = clave;
  for (unsigned i = 0; c[i] != '\0'; i++)
    h = (h * primo + c[i]) % modulo;
  return h;
}

//eliminar_dato se encarga de eliminar un cierto tipo de dato.
//eliminar_dato: Void*->NULL
void eliminar_dato(void *arbol) {
  Itree a = arbol;
  itree_destruir(a);
}

//eliminar_clave se encarga de eliniar un cierto tipo de clave.
//eliminar_clave: Void*->NULL
void eliminar_clave(void *clave) {
  free(clave);
}

//conjuntos_destruir se encarga de liberar un conjuntos de datos.
//conjuntos_destruir: Conjuntos*->NULL
void conjuntos_destruir(Conjuntos * conjunto) {
  tablahash_destruir(conjunto->tabla);
  free(conjunto);
}

//conjuntos_crear se encarga de crear un conjunto de conjuntos numericos.
//conjuntos_crear: Void->Conjuntos*
Conjuntos *conjuntos_crear() {
  Conjuntos *conjuntos = malloc(sizeof(Conjuntos));
  conjuntos->tabla =
      tablahash_crear(31, hash, iguales, eliminar_dato, eliminar_clave);
  return conjuntos;
}

//conjuntos_imprimir se encarga de dado un conjunto de conjuntos y un alias
//imprimir el conjunto con dicho alias.
//conjuntos_imprimir: Conjuntos*->Char*->NULL
void conjuntos_imprimir(Conjuntos * conjunto, char *alias) {
  CasillaHash *casillaBuscada = tablahash_buscar(conjunto->tabla, alias);
  if (!casilla_empty(casillaBuscada)) {
    Itree arbol = casilla_obtener_dato(casillaBuscada);
    itree_imprimir_hasta(arbol, compy_mayor(arbol));
    puts("");
  } else
    printf("No existe el conjunto\n");
}

//conjuntos_insertar se encarga de tomar un conjunto de conjuntos, un alias, un array numerico, su longitud
//y una forma del conjunto(comprension o extension) y de crear dicho conjunto con los elementos especificados.
//conjuntos_insertar: Conjuntos*->Char*->Int*->Int->Int->NULL
void conjuntos_insertar(Conjuntos * conjunto, char *alias, int *numeros,
                        int longitud, int forma) {
  Intervalo intervalo;
  Itree arbol = itree_crear();
  char *nombre = malloc(sizeof(char) * (strlen(alias) + 1));
  strcpy(nombre, alias);
  if (forma == 1) {             //comprension
    if (longitud != 0) {
      intervalo = inter_crear(numeros[0], numeros[1]);
      arbol = itree_insertar_avl(arbol, intervalo);
    }
  } else {                      //extension
    for (int i = 0; i < longitud; i++) {
      intervalo = inter_crear(numeros[i], numeros[i]);
      arbol = itree_insertar_avl(arbol, intervalo);
    }
  }
  tablahash_insertar(conjunto->tabla, nombre, arbol);
}

//verificar_conjuntos se encarga de tomar un conjunto de conjuntos, dos alias y dos conjuntos, luego
//verifica la existencia de dichos conjuntos con los respectivos alias y los almacena, retorna la cantidad
//de conjuntos existentes.
//verificar_conjuntos: Conjuntos*->Char*->Char*->CasillaHash**->CasillaHash**->Int
int verificar_conjuntos(Conjuntos * conjuntos, char *alias1, char *alias2,
                        CasillaHash ** c1, CasillaHash ** c2) {
  CasillaHash *casilla;
  int cantidad = 0;
  if (alias1 != NULL) {
    casilla = tablahash_buscar(conjuntos->tabla, alias1);
    if (!casilla_empty(casilla))
      cantidad++;
    *c1 = casilla;
  }
  if (alias2 != NULL) {
    casilla = tablahash_buscar(conjuntos->tabla, alias2);
    if (!casilla_empty(casilla))
      cantidad++;
    *c2 = casilla;
  }
  return cantidad;
}

//conjuntos_unir se encarga de dado un conjunto de conjuntos y tres alias, realizar la union entre ellos
//de la forma A1 = A2 U A3.
//conjuntos_unir: Conjuntos*->Char*->Char*->Char*->NULL
void conjuntos_unir(Conjuntos * conjunto, char *alias1, char *alias2,
                    char *alias3) {
  Itree arbol2, arbol3, arbol1;
  CasillaHash *casilla2, *casilla3;
  int cantidad =
      verificar_conjuntos(conjunto, alias2, alias3, &casilla2, &casilla3);
  if (cantidad != 2)
    printf("No existen los conjuntos\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol3 = casilla_obtener_dato(casilla3);
    if (arbol2 == arbol3) {
      if (strcmp(alias1, alias2) == 0)  // A = A U A
        return;
      else                      // B = A U A
        arbol1 = itree_copiar(arbol2);
    } else {                    // A = B U C
      arbol1 = itree_copiar(arbol3);
      arbol1 = itree_unir(arbol1, arbol2);
    }
    char *nombre = malloc(sizeof(char) * (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}

//conjuntos_intersectar se encarga de dado un conjunto de conjuntos y tres alias, realiza la operacion
//de interseccion entre los mismos, de la forma A1 = A2 n A3.
//conjuntos_intersectar: Conjuntos*->Char*->Char*->Char*->NULL
void conjuntos_intersectar(Conjuntos * conjunto, char *alias1, char *alias2,
                           char *alias3) {
  Itree arbol2, arbol3, arbol1;
  CasillaHash *casilla2, *casilla3;
  int cantidad =
      verificar_conjuntos(conjunto, alias2, alias3, &casilla2, &casilla3);
  if (cantidad != 2)
    printf("No existen los conjuntos\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol3 = casilla_obtener_dato(casilla3);
    if (arbol2 == arbol3) {
      if (strcmp(alias1, alias2) == 0)  // A = A n A
        return;
      else                      // B = A n A
        arbol1 = itree_copiar(arbol2);
    } else {
      arbol1 = itree_crear();
      arbol1 = itree_intersectar(arbol1, arbol2, arbol3);
    }
    char *nombre = malloc(sizeof(char) * (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}

//conjuntos_restar se encarga de dado un conjunto de conjuntos y tres alias, realiza la operacion de la resta
//de la forma A1 = A2 - A3.
//conjuntos_restar: Conjuntos*->Char*->Char*->Char*->NULL
void conjuntos_restar(Conjuntos * conjunto, char *alias1, char *alias2,
                      char *alias3) {
  Itree arbol2, arbol3, arbol1;
  CasillaHash *casilla2, *casilla3;
  int cantidad =
      verificar_conjuntos(conjunto, alias2, alias3, &casilla2, &casilla3);
  if (cantidad != 2)
    printf("No existen los conjuntos\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol3 = casilla_obtener_dato(casilla3);
    arbol1 = itree_crear();
    if (arbol2 != arbol3)
      arbol1 = itree_restar(arbol1, arbol2, arbol3);
    char *nombre = malloc(sizeof(char) * (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}

//conjuntos_complemento se encarga de tomar un conjunto de conjuntos y dos alias, realiza 
//la operacion del complemento de la forma A1 = complemento(A2).
//conjuntos_complemento: Conjuntos->Char*->Char*->NULL
void conjuntos_complemento(Conjuntos * conjunto, char *alias1, char *alias2) {
  Itree arbol1, arbol2;
  CasillaHash *casilla2;
  int cantidad = verificar_conjuntos(conjunto, alias2, NULL, &casilla2, NULL);
  if (cantidad != 1)
    printf("No existe el conjunto\n");
  else {
    arbol2 = casilla_obtener_dato(casilla2);
    arbol1 = itree_complemento(arbol2);
    char *nombre = malloc(sizeof(char) * (strlen(alias1) + 1));
    strcpy(nombre, alias1);
    tablahash_insertar(conjunto->tabla, nombre, arbol1);
  }
}
