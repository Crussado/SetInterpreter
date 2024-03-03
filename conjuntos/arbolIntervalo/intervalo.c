#include "intervalo.h"
#include <stdlib.h>
#include <stdio.h>
#include "limits.h"

//inter_crear crea un intervalo de enteros.
//inter_crear: Int->Int->Intervalo
Intervalo inter_crear(int x, int y) {
  Intervalo intervalo;
  intervalo.compx = x;
  intervalo.compy = y;
  return intervalo;
}

//inter_x toma un intervalo y devuelve su primer componente.
//inter_x Intervalo->Int
int inter_x(Intervalo intervalo) {
  return intervalo.compx;
}

//inter_y toma un intervalo y devuelve su segunda componente.
//inter_y Intervalo->Int
int inter_y(Intervalo intervalo) {
  return intervalo.compy;
}

//inter_eliminar se encarga de eliminar un intervalo dado.
//inter_eliminar: PIntervalo->NULL
void inter_eliminar(PIntervalo intervalo) {
  free(intervalo);
}

//inter_afectar se encargo de dado un intervalo y dos enteros, actualiza dicho intervalo.
//inter_afectar: PIntervalo->Int->Int->NULL
void inter_afectar(PIntervalo intervalo, int x, int y) {
  intervalo->compy = y;
  intervalo->compx = x;
}

//inter_restar toma dos intervalos que se intersectan y realiza la resta entre ellos, alamacena los intervalos
//resultantes y devuelve la cantidad intervalos que la resta producio.
//inter_restar: Intervalo->Intervalo->PIntervalo->PIntervalo->Int
int inter_restar(Intervalo intervalo1, Intervalo intervalo2, PIntervalo resta1,
                 PIntervalo resta2) {
  int a = inter_x(intervalo1), b = inter_y(intervalo1);
  int x = inter_x(intervalo2), y = inter_y(intervalo2);
  if (a < x && b >= x) {
    inter_afectar(resta1, a, x - 1);
    if (y >= b)
      return 1;
    else {
      inter_afectar(resta2, y + 1, b);
      return 2;
    }
  }
  if (a >= x && b > y) {
    inter_afectar(resta1, y + 1, b);
    return 1;
  }
  return 0;
}

//inter_intersectar se encarga de dado dos intervalos devuelve su interseccion.
//inter_intersectar: Intervalo->Intervalo->Intervalo
Intervalo inter_intersectar(Intervalo intervalo1, Intervalo intervalo2) {
  Intervalo interseccion;
  int a = inter_x(intervalo1), b = inter_y(intervalo1);
  int x = inter_x(intervalo2), y = inter_y(intervalo2);
  if (a <= x && b >= x) {
    if (y <= b)
      interseccion = intervalo2;
    else
      interseccion = inter_crear(x, b);
  }
  if (x <= a && y >= a) {
    if (b <= y)
      interseccion = intervalo1;
    else
      interseccion = inter_crear(a, y);
  }
  return interseccion;
}


//inter_intersectar se encarga de dados dos intervalos ver si los mismos se intersectan.
//inter_intersectar: Intervalo->Intervalo->Int
int inter_puede_intersectar(Intervalo intervalo1, Intervalo intervalo2) {
  int a = inter_x(intervalo1), b = inter_y(intervalo1);
  int x = inter_x(intervalo2), y = inter_y(intervalo2);
  if (a <= x && b >= x)
    return 1;
  if (x <= a && y >= a)
    return 1;
  return 0;
}

//inter_imprimir se encarga de imprimir un intervalo.
//inter_imprimir: Intervalo->NULL
void inter_imprimir(Intervalo intervalo) {
  int x = inter_x(intervalo), y = inter_y(intervalo);
  if (x == y)
    printf("%d", x);
  else
    printf("%d:%d", x, y);
}

//inter_comparar se encarga de dados dos intervalos, comparar sus respectivas componentes.
//inter_comparar: Intervalo->Intervalo->Int
int inter_comparar(Intervalo i1, Intervalo i2) {
  int a = inter_x(i1), b = inter_y(i1);
  int x = inter_x(i2), y = inter_y(i2);
  if (a == x && b == y)
    return 0;
  if (a == x) {
    if (b > y)
      return 1;                 //1 significa izquierda
    return 2;                   //2 significa derecha
  }
  if (a > x)
    return 1;
  return 2;
}

//inter_puedo_unir toma dos intervalos y verifica si se pueden "unir".
//inter_puedo_unir: Intervalo->Intervalo->Int
int inter_puedo_unir(Intervalo i1, Intervalo i2) {
  int a = inter_x(i1), b = inter_y(i1);
  int c = inter_x(i2), d = inter_y(i2);
  int puedo = 0;
  if (a <= c && b >= c)
    puedo = 1;
  else if (c <= a && d >= a)
    puedo = 1;
  else if (b != INT_MAX && (b + 1) == c)
    puedo = 1;
  else if (d != INT_MAX && (d + 1) == a)
    puedo = 1;
  return puedo;
}

//inter_union dados dos intervalos que pueden unirse y se encarga de unirlos.
//inter_union: Intervalo->Intervalo->Intervalo
Intervalo inter_union(Intervalo i1, Intervalo i2) {
  Intervalo unir;
  int a = inter_x(i1), b = inter_y(i1);
  int c = inter_x(i2), d = inter_y(i2);
  if (a <= c && b >= c) {
    if (d >= b)
      unir = inter_crear(a, d);
    else
      unir = i1;
  } else if (c <= a && d >= a) {
    if (b <= d)
      unir = i2;
    else
      unir = inter_crear(c, b);
  } else if (b != INT_MAX && (b + 1) == c)
    unir = inter_crear(a, d);
  else if (d != INT_MAX && (d + 1) == a)
    unir = inter_crear(c, b);
  else
    unir = i1;
  return unir;
}
