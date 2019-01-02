#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"funkcje.h"

#define MAX 1024            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */



int main() 
{
  int obraz[MAX][MAX];
  int wymx,wymy,odcieni;
  int odczytano = 0;
  FILE *plik, *plik_wy, *temp_plik;
  char nazwa[100];
  int opcja, szarosci;
  char nazwa_wy[100];

  while (opcja != 4)
{
  menu();
  scanf("%d", &opcja);
  switch(opcja)
  {
    case 1:
      printf("Podaj nazwe pliku:\n");
      scanf("%s",nazwa);
      plik=fopen(nazwa,"r");
      if (plik != NULL)
      {
      odczytano = czytaj(plik,obraz,&wymx,&wymy,&odcieni);
      fclose(plik);
      }
    break;

    case 2:
	temp_plik=fopen("aaa", "w");
	zapisz(temp_plik,obraz,&wymx,&wymy,&odcieni);               /*zapisanie obrazu do pliku aaa w celu podglądu obrazu od razu po wykonaniu operacji*/
	fclose(temp_plik);
	temp_plik=fopen("aaa", "r");
	if(temp_plik != NULL)
	{
	  odczytano=czytaj(temp_plik, obraz,&wymx,&wymy,&odcieni);
	  fclose(temp_plik);
	}
      if (odczytano != 0)
      wyswietl("aaa");
    break;

    case 3:
      printf("zapisz jako:\n");
      scanf("%s", nazwa_wy);
      plik_wy = fopen(nazwa_wy,"w");
      zapisz(plik_wy,obraz,&wymx,&wymy,&odcieni);
      fclose(plik_wy);
    break;
    case 5:
      negatyw(obraz, &wymx, &wymy, odcieni);
    break;

    case 6:
      progowanie(obraz, &wymx, &wymy, odcieni);
    break;

    case 7:
      progowanie_czerni(obraz, &wymx, &wymy, odcieni);
    break;

    case 8:
      progowanie_bieli(obraz, &wymx, &wymy, odcieni);
    break;

    case 9:
      zmiana_poziomow(obraz, &wymx, &wymy, odcieni);
    break;
    case 10:
	    korekcja_gamma(obraz, &wymx, &wymy, odcieni);
    break;
    case 11:
      konturowanie(obraz, &wymx, &wymy, odcieni);
    break;
    case 12:
      rozmywanie_poziom(obraz, &wymx, &wymy, odcieni);
    break;
    case 13:
      rozmywanie_pion(obraz, &wymx, &wymy, odcieni);
    break;
    case 14:
      rozciaganie_histogramu(obraz, &wymx, &wymy, odcieni);
    break;
    default:
    break;
  }
}
  return odczytano;
}