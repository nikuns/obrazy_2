
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define MAX 1024            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci);
void wyswietl(char *n_pliku);
void zapisz(FILE *plik_wy,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci);
void negatyw(int obraz[][MAX], int *wymx,int *wymy, int szarosci);
void progowanie(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void  progowanie_czerni(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void progowanie_bieli(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void korekcja_gamma(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void zmiana_poziomow(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void konturowanie(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void rozmywanie_poziom(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void rozmywanie_pion(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void rozciaganie_histogramu(int obraz[][MAX], int *wymx, int *wymy, int szarosci);
void menu();
