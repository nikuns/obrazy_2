#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"funkcje.h"

#define MAX 1024            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */


/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy       	       	       	       	    *
 *										    *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM			    *
 * \param[out] obraz_pgm tablica, do ktorej zostanie zapisany obraz		    *
 * \param[out] wymx szerokosc obrazka						    *
 * \param[out] wymy wysokosc obrazka						    *
 * \param[out] szarosci liczba odcieni szarosci					    *
 * \return liczba wczytanych pikseli						    *
 ************************************************************************************/

int czytaj(FILE *plik_we,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci) {
  char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;                /* zmienna pomocnicza do czytania komentarzy */
  int koniec=0;            /* czy napotkano koniec danych w pliku */
  int i,j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we==NULL) {
    fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");
    return(0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */
    koniec=1;                              /* Nie udalo sie? Koniec danych! */

  if ( (buf[0]!='P') || (buf[1]!='2') || koniec) {  /* Czy jest magiczne "P2"? */
    fprintf(stderr,"Blad: To nie jest plik PGM\n");
    return(0);
  }

  /* Pominiecie komentarzy */
  do {
    if ((znak=fgetc(plik_we))=='#') {         /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */
	koniec=1;                   /* Zapamietaj ewentualny koniec danych */
    }  else {
      ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */
    }                                         /* nie jest '#' zwroc go                 */
  } while (znak=='#' && !koniec);   /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we,"%d %d %d",wymx,wymy,szarosci)!=3) {
    fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return(0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i=0;i<*wymy;i++) {
    for (j=0;j<*wymx;j++) {
      if (fscanf(plik_we,"%d",&(obraz_pgm[i][j]))!=1) {
	fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");
	return(0);
      }
    }
  }
  return *wymx**wymy;   /* Czytanie zakonczone sukcesem    */
}                       /* Zwroc liczbe wczytanych pikseli */


/* Wyswietlenie obrazu o zadanej nazwie za pomoca programu "display"   */
void wyswietl(char *n_pliku) {
  char polecenie[DL_LINII];  /* bufor pomocniczy do zestawienia polecenia */
  

  strcpy(polecenie,"display ");  /* konstrukcja polecenia postaci */
  strcat(polecenie,n_pliku);     /* display "nazwa_pliku" &       */
  strcat(polecenie," &");
  printf("%s\n",polecenie);      /* wydruk kontrolny polecenia */
  system(polecenie);             /* wykonanie polecenia        */
}

/************************ZAPISYWANIE*******************************/
  void zapisz(FILE *plik_wy,int obraz_pgm[][MAX],int *wymx,int *wymy, int *szarosci){
    int i, j;

    if(plik_wy == NULL){
    fprintf(stderr,"Błąd: nie podano uchwytu do pliku w zapisz\n");
    exit(0);
  }
  fprintf(plik_wy, "P2\n");
  fprintf(plik_wy, "%d %d\n %d \n", *wymx, *wymy, *szarosci);   /*wypisywanie obrazu do pliku*/

  for(i=0;i<*wymy;i++){
    for(j=0;j<*wymx;j++){
      fprintf(plik_wy, "%d\n", obraz_pgm[i][j]);
   }
  }
 }
 /************************NEGATYW*********************/
void negatyw(int obraz[][MAX], int *wymx,int *wymy, int szarosci)
{
  for(int i=0; i<*wymy; i++)
    {
      for(int j=0; j<*wymx  ; j++)
        {
          obraz[i][j] = szarosci-obraz[i][j];
        }

    }
  printf("Wykonano negatyw \n");
}

/*********************PROGOWANIE********************/
void progowanie(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  int prog;
  int x;

  printf("stopien progowania w procentach: ");
  scanf("%d", &x);
  prog=x*szarosci*0.01;
 
  for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      if(obraz[i][j] <= prog)
      {
        obraz[i][j] = 0;
      }
     else
     {
       obraz[i][j] = szarosci;
     } 
    }
  }
  printf("wykonano progowanie\n");
}


/*******************POLPROGOWANIE CZERNI****************/
void  progowanie_czerni(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  int prog;
  int x;

  printf("stopien progowania w procentach: ");
  scanf("%d", &x);
  prog=x*szarosci*0.01;

  for(int i=0; i<*wymy; i++)
    {
      for(int j=0; j<*wymx; j++)
      { 
        if(obraz[i][j] <= prog)
        {
          obraz[i][j] = 0;
        }
      }
    } 
  printf("wykonano półprogowanie czerni\n");
}

/*******************POLPROGOWANIE BIELI****************/
void progowanie_bieli(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  int prog;
  int x;

  printf("stopien progowania w procentach: ");
  scanf("%d", &x);
  prog=x*szarosci*0.01;

  for(int i=0; i<*wymy; i++)
    {
      for(int j=0; j<*wymx; j++)
      { 
        if(obraz[i][j] >= prog)
        {
          obraz[i][j] = szarosci;
        }
      }
    } 
  printf("wykonano półprogowanie bieli\n");
}

/********************KOREKCJA GAMMA****************/
void korekcja_gamma(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  float gamma;
  

  printf("stopien gamma: ");
  scanf("%f", &gamma);

  for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      obraz[i][j]=pow(obraz[i][j],1/gamma)/pow(szarosci,(1-gamma)/gamma);
    }
  }
  printf("wykonano korekję gamma\n");
}
/******************ZMANA POZIOMOW**************/
void zmiana_poziomow(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  int czern, biel;

  printf("Podaj nowy poziom czerni i bieli w procentach: ");
  scanf("%d", &czern);
  scanf("%d", &biel);
	czern=czern*szarosci*0.01;
	biel=biel*szarosci*0.01;

 for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      if(obraz[i][j]<=czern)
      {
        obraz[i][j]=0;
      }
      if(obraz[i][j]>czern && obraz[i][j]<biel)
      {
        obraz[i][j]=(obraz[i][j]-czern)*szarosci/(biel-czern);
      }
      if(obraz[i][j]>=biel)
      {
        obraz[i][j]=szarosci;
      }
    }
  }
  printf("wykonano zmiane poziomów\n");
}

/*******************KONTUROWANIE*******************/
void konturowanie(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      obraz[i][j]=abs(obraz[i+1][j]-obraz[i][j])+abs(obraz[i][j+1]-obraz[i][j]);
    }
  }
  printf("wykonano konturowanie\n");
}

/*********************ROZMYWANIE POZIOM *****************/
void rozmywanie_poziom(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  for(int i=1; i<*wymy-1; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      obraz[i][j]=(obraz[i-1][j]+obraz[i][j]+obraz[i+1][j])/3;
    }
  }
  printf("rozmazano poziomo\n");
}

/*********************ROZMYWANIE PION*****************/
void rozmywanie_pion(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  for(int i=0; i<*wymy; i++)
  {
    for(int j=1; j<*wymx-1; j++)
    {
      obraz[i][j]=(obraz[i][j-1]+obraz[i][j]+obraz[i][j+1])/3;
    }
  }
  printf("rozmazano pionowo\n");
}

/********************ROZCIAGANIE HISTOGRAMU****************/
void rozciaganie_histogramu(int obraz[][MAX], int *wymx, int *wymy, int szarosci)
{
  int max=0;
  int min=szarosci;
  
  for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      if(max<obraz[i][j])
      {
        max=obraz[i][j];
      }
      if(min>obraz[i][j])
      {
        min=obraz[i][j];
      }
    }
  }
  for(int i=0; i<*wymy; i++)
  {
    for(int j=0; j<*wymx; j++)
    {
      obraz[i][j]=(obraz[i][j]-min)*(szarosci/(max-min));
    }
  }
  printf("wykonano rozciąganie histogramu\n");
}

/***********************MENU*****************/
void menu()
{
  printf("*************MENU*************\n");
  printf("* 1. Wczytaj plik            *\n");
  printf("* 2. Podgląd pliku           *\n");
  printf("* 3. Zapisz plik             *\n");
  printf("* 4. Wyjdź                   *\n");
  printf("* OPERACJE NA OBRAZACH       *\n");
  printf("* 5. Negatyw                 *\n");
  printf("* 6. Progowanie              *\n");
  printf("* 7. Półrogowanie czerni     *\n");
  printf("* 8. Półprogowanie bieli     *\n");
  printf("* 9. Zmiana poziomów         *\n");
  printf("* 10. Korekcja gamma         *\n");
  printf("* 11. Konturowanie           *\n");
  printf("* 12. Rozmywanie poziome     *\n");
  printf("* 13. Rozmywanie pionowe     *\n");
  printf("* 14. Rozciąganie histogramu *\n");
  printf("******************************\n");
}