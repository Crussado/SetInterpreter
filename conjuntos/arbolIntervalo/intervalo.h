#ifndef __INTERVALO_H__
#define __INTERVALO_H__

#include <stddef.h>

typedef struct {
  int compx;
  int compy;
} Intervalo;

typedef Intervalo *PIntervalo;

Intervalo inter_crear(int x, int y);

void inter_eliminar(PIntervalo intervalo);

int inter_puede_intersectar(Intervalo intervalo, Intervalo nuevo);

Intervalo inter_intersectar(Intervalo intervalo1, Intervalo intervalo2);

void inter_imprimir(Intervalo intervalo);

int inter_comparar(Intervalo i1, Intervalo i2);

int inter_y(Intervalo intervalo);

int inter_x(Intervalo intervalo);

int inter_puedo_unir(Intervalo i1, Intervalo i2);

Intervalo inter_union(Intervalo i1, Intervalo i2);

int inter_restar(Intervalo intervalo1, Intervalo intervalo2, PIntervalo resta1,
                 PIntervalo resta2);

#endif                          /* __INTERVALO_H__ */
