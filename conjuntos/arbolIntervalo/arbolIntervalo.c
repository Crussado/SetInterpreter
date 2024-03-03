#include <stdio.h>
#include <stdlib.h>
#include "arbolIntervalo.h"
#include "intervalo.h"
#include "limits.h"

//Itree se encarga de crear un arbol de intervalo vacio.
//itree_crear: NULL->Itree
Itree itree_crear() {
  return NULL;
}

//itree_empty se encarga de de verificar si el arbol es vacio.
//itree_empty: Itree->Int
int itree_empty(Itree arbol) {
  return arbol == NULL;
}

//itree_destruir se encarga de destruir un arbol de intervalo.
//itree_destruir: Itree->NULL
void itree_destruir(Itree arbol) {
  if (!itree_empty(arbol)) {
    itree_destruir(arbol->left);
    itree_destruir(arbol->right);
    free(arbol);
  }
}


//maximo se encarga de elegir el numero mas grande entre dos.
//maximo: Int->Int->Int
int maximo(int a, int b) {
  return a > b ? a : b;
}

//itree_recorrer_dfs se encarga de llevar a cabo el recorrido por profundidad del árbol.
//itree_recorrer_dfs: Itree->BTRecorrido->NULL
void itree_recorrer_dfs(Itree arbol, BTRecorrido orden) {
  if (itree_empty(arbol))
    return;
  if (orden == ITREE_RECORRIDO_PRE) {
    inter_imprimir(arbol->intervalo);
    itree_recorrer_dfs(arbol->left, orden);
    itree_recorrer_dfs(arbol->right, orden);
  } else if (orden == ITREE_RECORRIDO_IN) {
    itree_recorrer_dfs(arbol->left, orden);
    inter_imprimir(arbol->intervalo);
    itree_recorrer_dfs(arbol->right, orden);
  } else {
    itree_recorrer_dfs(arbol->left, orden);
    itree_recorrer_dfs(arbol->right, orden);
    inter_imprimir(arbol->intervalo);
  }
}

//itree_altura se encarga de obtener la altura de un arbol.
//itree_altura: Itree->Int
int itree_altura(Itree arbol) {
  if (itree_empty(arbol))
    return -1;
  return arbol->altura;
}

//actualizar_altura se encarga de actualizar la altura de un arbol.
//actualizar_altura: Itree->NULL
void actualizar_altura(Itree arbol) {
  if (!itree_empty(arbol))
    arbol->altura =
        maximo(itree_altura(arbol->left), itree_altura(arbol->right)) + 1;
}

//compy_mayor se encarga de obtener la mayor de las segundas componentes de un intervalo en el arbol.
//compy_mayor: Itree->Int
int compy_mayor(Itree arbol) {
  if (itree_empty(arbol))
    return 0;
  return arbol->maxDerecha;
}

//actualizar_compy_mayor se encarga de obtener la mayor de las segundas componentes de un arbol de intervalo actualizada.
//actualizar_compy_mayor: Itree->NULL
void actualizar_compy_mayor(Itree arbol) {
  if (!itree_empty(arbol)) {
    if (itree_empty(arbol->left) && itree_empty(arbol->right))
      arbol->maxDerecha = inter_y(arbol->intervalo);
    else if (itree_empty(arbol->left) && !itree_empty(arbol->right))
      arbol->maxDerecha =
          maximo(compy_mayor(arbol->right), inter_y(arbol->intervalo));
    else if (!itree_empty(arbol->left) && itree_empty(arbol->right))
      arbol->maxDerecha =
          maximo(compy_mayor(arbol->left), inter_y(arbol->intervalo));
    else
      arbol->maxDerecha =
          maximo(maximo(compy_mayor(arbol->left), compy_mayor(arbol->right)),
                 inter_y(arbol->intervalo));
  }
}

//dif_altura se encarga de hacer la diferencia entre la altura del arbol derecho y la del arbol izquierdo.
//dif_altura: Itree->Int
int dif_altura(Itree arbol) {
  return itree_altura(arbol->right) - itree_altura(arbol->left);
}

//itree_rotacion_izq se encarga de hacer la rotación simple izquierda a un arbol, cambiando así de lugar los nodos del mismo.
//itree_rotacion_izq: Itree->Itree
Itree itree_rotacion_izq(Itree arbol) {
  Itree arbolN = arbol->right;
  arbol->right = arbolN->left;
  arbolN->left = arbol;
  actualizar_altura(arbol);
  actualizar_altura(arbolN);
  actualizar_compy_mayor(arbol);
  actualizar_compy_mayor(arbolN);
  return arbolN;
}

//itree_rotacion_der se encarga de hacer la rotación simple derecha a un arbol, cambiando así de lugar los nodos del mismo.
//itree_rotacion_der: Itree->Itree
Itree itree_rotacion_der(Itree arbol) {
  Itree arbolN = arbol->left;
  arbol->left = arbolN->right;
  arbolN->right = arbol;
  actualizar_altura(arbol);
  actualizar_altura(arbolN);
  actualizar_compy_mayor(arbol);
  actualizar_compy_mayor(arbolN);
  return arbolN;
}

//balancear se encarga de balancear un arbol.
//balancear: Itree->Itree
Itree balancear(Itree arbol) {
  int dif = dif_altura(arbol);
  if (abs(dif) <= 1)
    return arbol;
  if (dif < 0) {
    if (dif_altura(arbol->left) == 1) {
      arbol->left = itree_rotacion_izq(arbol->left);
      arbol = itree_rotacion_der(arbol);
    } else
      arbol = itree_rotacion_der(arbol);
  } else {
    if (dif_altura(arbol->right) == -1) {
      arbol->right = itree_rotacion_der(arbol->right);
      arbol = itree_rotacion_izq(arbol);
    } else
      arbol = itree_rotacion_izq(arbol);
  }
  return arbol;
}

//elim_minimo se encarga de: 1) obtener el minimo intervalo y 2) eliminarlo posteriormente.
//elim_minimo: Itree->Int*->Int*->Itree
Itree elim_minimo(Itree arbol, int *a, int *b) {
  if (!itree_empty(arbol)) {
    if (itree_empty(arbol->left)) {
      *a = inter_x(arbol->intervalo);
      *b = inter_y(arbol->intervalo);
      Itree aux = arbol;
      arbol = arbol->right;
      free(aux);
    } else {
      arbol->left = elim_minimo(arbol->left, a, b);
      actualizar_compy_mayor(arbol);
      actualizar_altura(arbol);
      arbol = balancear(arbol);
    }
  }
  return arbol;
}

//Itree_eliminar se encarga de eliminar un intervalo de un arbol de intervalos.
//itree_eliminar: Itree->Intervalo->Itree
Itree itree_eliminar(Itree arbol, Intervalo intervalo, Itree * remplazo) {
  if (itree_empty(arbol)) {
    *remplazo = NULL;
    return arbol;
  }
  int bandera = inter_comparar(arbol->intervalo, intervalo);
  if (bandera == 0) {
    Itree aux;
    if (itree_empty(arbol->left) || itree_empty(arbol->right)) {
      aux = arbol;
      if (itree_empty(arbol->left))
        arbol = arbol->right;
      else
        arbol = arbol->left;
      free(aux);
    } else {
      int a, b;
      arbol->right = elim_minimo(arbol->right, &a, &b);
      arbol->intervalo = inter_crear(a, b);
      actualizar_compy_mayor(arbol);
      actualizar_altura(arbol);
      arbol = balancear(arbol);
    }
    *remplazo = arbol;
    return arbol;
  }
  if (bandera == 1)
    arbol->left = itree_eliminar(arbol->left, intervalo, remplazo);
  else
    arbol->right = itree_eliminar(arbol->right, intervalo, remplazo);

  actualizar_compy_mayor(arbol);
  actualizar_altura(arbol);
  arbol = balancear(arbol);
  return arbol;
}

//itree_insertar_avl se encarga de insertar un elemento en el arbol de intervalo.
//itree_insertar_avl: Itree->Intervalo->Itree
Itree itree_insertar_base(Itree arbol, Intervalo intervalo) {
  if (itree_empty(arbol)) {
    arbol = malloc(sizeof(BTIntervalo));
    arbol->left = itree_crear();
    arbol->right = itree_crear();
    arbol->altura = 0;
    arbol->intervalo = intervalo;
    arbol->maxDerecha = inter_y(intervalo);
    return arbol;
  }
  int bandera = inter_comparar(arbol->intervalo, intervalo);
  if (bandera == 1)
    arbol->left = itree_insertar_avl(arbol->left, intervalo);
  else
    arbol->right = itree_insertar_avl(arbol->right, intervalo);

  actualizar_compy_mayor(arbol);
  actualizar_altura(arbol);
  arbol = balancear(arbol);
  return arbol;
}

//itree_copiar_nodo se le pasa un nodo de un arbol de intervalo y crea una copia del mismo.
//itree_copiar_nodo: Itree->Itree
Itree itree_copiar_nodo(Itree nodo) {
  if (itree_empty(nodo))
    return itree_crear();
  Itree copia = malloc(sizeof(BTIntervalo));
  copia->intervalo = nodo->intervalo;
  copia->maxDerecha = nodo->maxDerecha;
  copia->altura = nodo->altura;
  return copia;
}

//itree_copiar se le pasa un arbol de intervalo y se encarga de crear una copia del mismo.
//itree_copiar: Itree->Itree
Itree itree_copiar(Itree arbol) {
  if (itree_empty(arbol))
    return itree_crear();
  Itree nuevoArbol = itree_copiar_nodo(arbol);
  nuevoArbol->right = itree_copiar(arbol->right);
  nuevoArbol->left = itree_copiar(arbol->left);
  return nuevoArbol;
}

//itree_insertar_aux toma un cierto nodo de un arbol para recorrerlo, el arbol en cuestion, 
//y un puntero a intervalo, se encarga de eliminar todos los intervalos del arbol que se "unan",
//con el intervalo extra, para luego insertarlos todos juntos.
//itree_insetar_aux: Itree->Itree->PIntervalo->Itree
Itree itree_insertar_aux(Itree recorro, Itree arbol, PIntervalo intervalo) {
  if (itree_empty(recorro))
    return arbol;
  int puedoUnir = inter_puedo_unir(recorro->intervalo, *intervalo);
  if (puedoUnir) {
    *intervalo = inter_union(recorro->intervalo, *intervalo);
    arbol = itree_eliminar(arbol, recorro->intervalo, &recorro);
    return itree_insertar_aux(recorro, arbol, intervalo);
  }
  if (inter_x(*intervalo) < inter_x(recorro->intervalo))
    arbol = itree_insertar_aux(recorro->left, arbol, intervalo);
  if (inter_y(*intervalo) > inter_y(recorro->intervalo))
    arbol = itree_insertar_aux(recorro->right, arbol, intervalo);
  return arbol;
}

//itree_insertar_avl toma un arbol de intervalo y un intervalo para insertarlo realizando,
//la union entre los elementos del arbol y el mismo intervalo.
//itree_insertar_avl: Itree->Intervalo->Itree
Itree itree_insertar_avl(Itree arbol, Intervalo intervalo) {
  arbol = itree_insertar_aux(arbol, arbol, &intervalo);
  arbol = itree_insertar_base(arbol, intervalo);
  return arbol;
}

//itree_unir dados dos arboles de intervalo se encarga de realizar la union entre ellos.
//sobreescribiendo el primero.
//itree_unir: Itree->Itree->Itree
Itree itree_unir(Itree arbol1, Itree arbol2) {
  if (itree_empty(arbol2))
    return arbol1;
  Intervalo intervalo = arbol2->intervalo;
  arbol1 = itree_insertar_avl(arbol1, intervalo);
  arbol1 = itree_unir(arbol1, arbol2->left);
  arbol1 = itree_unir(arbol1, arbol2->right);
  return arbol1;
}

//hay_posibilidad toma un arbol de intervalo y un intervalo y se encarga de corroborar si existe
//la posibilidad de que el intervalo intersecte al arbol.
//hay_posibilidad: Itree->Intervalo->Int
int hay_posibilidad(Itree arbol, Intervalo intervalo) {
  if (itree_empty(arbol))
    return 0;
  if (arbol->maxDerecha >= inter_x(intervalo))
    return 1;
  return 0;
}

//itree_intersectar_base toma dos arboles de intervalo y un intervalo e inserta todas las intersecciones del 
//intervalo con el segundo arbol en el primero.
//itree_intersectar_base: Itree->Itree->Intervalo->Itree
Itree itree_intersectar_base(Itree arbol, Itree arbol1, Intervalo intervalo) {
  if (!hay_posibilidad(arbol1, intervalo))
    return arbol;
  if (inter_puede_intersectar(arbol1->intervalo, intervalo)) {
    Intervalo interseccion = inter_intersectar(arbol1->intervalo, intervalo);
    arbol = itree_insertar_avl(arbol, interseccion);
  }
  if (inter_y(intervalo) > inter_y(arbol1->intervalo)
      && hay_posibilidad(arbol1->right, intervalo))
    arbol = itree_intersectar_base(arbol, arbol1->right, intervalo);
  if (inter_x(intervalo) < inter_x(arbol1->intervalo)
      && hay_posibilidad(arbol1->left, intervalo))
    arbol = itree_intersectar_base(arbol, arbol1->left, intervalo);
  return arbol;
}

//itree_intersectar toma tres arboles de intervalos(siendo el primero nulo) y se encarga de realizar la interseccion entre ellos
//de la forma A1 = A2 n A3.
//itree_intersectar: Itree->Itree->Itree->Itree
Itree itree_intersectar(Itree arbol, Itree arbol1, Itree arbol2) {
  if (itree_empty(arbol1) || itree_empty(arbol2))
    return arbol;
  arbol = itree_intersectar_base(arbol, arbol1, arbol2->intervalo);
  arbol = itree_intersectar(arbol, arbol1, arbol2->left);
  arbol = itree_intersectar(arbol, arbol1, arbol2->right);
  return arbol;
}

//itree_restar_base dos arboles de intervalo y un intervalo, y se encarga de realizar la resta
//entre el intervalo y el segundo arbol, para el resultado insertarlo en el primero.
//itree_restar_base: Itree->Intervalo->Itree
Itree itree_restar_base(Itree arbol, Intervalo intervalo, Itree arbol1) {
  if (!hay_posibilidad(arbol1, intervalo)) {
    arbol = itree_insertar_avl(arbol, intervalo);
    return arbol;
  }
  if (inter_puede_intersectar(intervalo, arbol1->intervalo)) {
    Intervalo resta1, resta2;
    int caso = inter_restar(intervalo, arbol1->intervalo, &resta1, &resta2);
    if (caso == 0)
      return arbol;
    if (caso == 2) {
      arbol = itree_restar_base(arbol, resta1, arbol1->left);
      arbol = itree_restar_base(arbol, resta2, arbol1->right);
    } else if (inter_x(intervalo) == inter_x(resta1))
      arbol = itree_restar_base(arbol, resta1, arbol1->left);
    else
      arbol = itree_restar_base(arbol, resta1, arbol1->right);
    return arbol;
  }
  if (inter_y(intervalo) > inter_y(arbol1->intervalo))
    arbol = itree_restar_base(arbol, intervalo, arbol1->right);
  else
    arbol = itree_restar_base(arbol, intervalo, arbol1->left);
  return arbol;
}

//itree_restar toma tres arboles de intervalo(primero vacio) y se encarga de realizar la operacion
//de la resta de la forma A1 = A2 - A3.
//itree_restar: Itree->Itree->Itree->Itree
Itree itree_restar(Itree arbol, Itree arbol1, Itree arbol2) {
  if (itree_empty(arbol1))
    return arbol;
  arbol = itree_restar_base(arbol, arbol1->intervalo, arbol2);
  arbol = itree_restar(arbol, arbol1->left, arbol2);
  arbol = itree_restar(arbol, arbol1->right, arbol2);
  return arbol;
}

//itree_complemento se encarga de dado un arbol de intervalos devolver su complemento.
//itree_complemento: Itree->Itree
Itree itree_complemento(Itree arbol) {
  Intervalo universo = inter_crear(INT_MIN, INT_MAX);
  Itree complemento = itree_crear();
  complemento = itree_restar_base(complemento, universo, arbol);
  return complemento;
}

//itree_imprimir_hasta toma un arbol de intervalos y un limite e imprime en secuencia
//todos los intervalos [x, y] del arbol cuyos valores y no superen el limite.
//itree_imprimir_hasta: Itree->Int
void itree_imprimir_hasta(Itree arbol, int limite) {
  if (itree_empty(arbol))
    return;
  if (inter_y(arbol->intervalo) > limite)
    return;
  else {
    itree_imprimir_hasta(arbol->left, limite);
    inter_imprimir(arbol->intervalo);
    if (inter_y(arbol->intervalo) != limite)
      printf(", ");
    itree_imprimir_hasta(arbol->right, limite);
  }
}
