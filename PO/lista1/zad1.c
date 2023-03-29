/*
 * Wnuk Maksymilian
 * PO Lista 1 zadanie 1
 * gcc zad1.c z flagą -lm dla math.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "zad1.hpp"

#define M_PI 3.14159265358979323846
#define fig_malloc malloc(sizeof(Figura))
#define msg(fig) printf("%f\n", fig);

Figura *new_square(float x1, float y1, float bok)
{
    Figura *fig = fig_malloc;
    fig->typfig = SQUARE;

    fig->x1 = x1;
    fig->y1 = y1;

    fig->x2 = x1;
    fig->y2 = y1 + bok;

    fig->x3 = x1 + bok;
    fig->y3 = y1;

    fig->x4 = x1 + bok;
    fig->x4 = y1 + bok;

    return fig;
}

Figura *new_triangle(float x1, float y1, float bok1, float bok2)
{
    Figura *fig = fig_malloc;
    fig->typfig = TRIANGLE;

    fig->x1 = x1;
    fig->y1 = y1;

    fig->x2 = x1 + bok1; // bok wzdluz osi OX
    fig->y2 = y1;

    fig->x3 = x1; // bok wzdluz OY
    fig->y3 = y1 + bok2;

    return fig;
}

Figura *new_circle(float x1, float y1, float r)
{
    Figura *fig = fig_malloc;
    fig->typfig = CIRCLE;

    fig->x1 = x1;
    fig->y1 = y1;
    fig->r = r;

    return fig;
}

float pole(Figura *f)
{
    float res = -1;

    switch ((int)f->typfig)
    {
    case (SQUARE):
        res = pow(f->x3 - f->x1, 2.0);
        break;

    case (TRIANGLE):
        res = (1.0 / 2.0) * (f->x2 - f->x1) * (f->y3 - f->y1);
        break;

    case (CIRCLE):
        res = pow(f->r, 2.0) * M_PI;
        break;
    }

    return res;
}

float sumapol(Figura *f[], int size)
{
    float res = 0;
    for (int i = 0; i < size; i++)
    {
        res += pole(f[i]);
    }
    return res;
}

void przesun(Figura *f, float x, float y)
{
    switch ((int)f->typfig)
    {
    case (SQUARE):
        f->x4 += x;
        f->y4 += y;
        // FALLTHROUGH
    case (TRIANGLE):
        f->x2 += x;
        f->y2 += y;
        f->x3 += x;
        f->y3 += y;
        // FALLTHROUGH
    case (CIRCLE):
        f->x1 += x;
        f->y1 += y;
        break;
    }
}

void show(Figura *f){
    printf("Type: %s\nPoints:\n", str_table[f->typfig]);

    switch ((int)f->typfig){
        case(SQUARE):
            printf("(%f,%f)", f->x4,f->y4);
            // FALLTHROUGH
        case(TRIANGLE):
            printf("(%f,%f)", f->x3,f->y3);
            printf("(%f,%f)", f->x2,f->y2);
            // FALLTHROUGH
        case(CIRCLE):
            printf(" (%f,%f)\n", f->x1, f->y1);
            if (f->typfig == CIRCLE){
                printf("r = %f\n", f->r);
            }
            break;

    }
    printf("****\n");
}

int main()
{
    Figura *kwadrat = new_square(-1.0, 1.0, 3.0);
    msg(pole(kwadrat));
    Figura *trojkat = new_triangle(1.0, 1.0, 2.0, 3.0);
    msg(pole(trojkat));
    Figura *kolo = new_circle(1.0, 1.0, 5.0);
    msg(pole(kolo));

    Figura *f_arr[3] = {kolo, kwadrat, trojkat};

    show(kwadrat);
    show(trojkat);
    show(kolo);

    przesun(kwadrat, 10, 10);
    show(kwadrat);

    printf("%f\n", sumapol(f_arr, 3));

    return 0;
}