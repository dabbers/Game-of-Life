#include "life2.h"
#include <windows.h>
#include <winbase.h>

int main() {
  int nrow, ncol, ngen, count=0, sleep;
  float percent, tmp;

  printf("Enter number of rows and columns: ");
  scanf("%d %d", &nrow, &ncol);

  printf("\nThere are a total of %d cells.\n"
	 "Enter percent of cells initially alive: ", nrow * ncol);
  scanf("%f", &percent);

  printf("\nEnter desired number of generations [-1='infinite loop']: ");
  scanf("%d", &ngen);

  printf("\nYou can specify an amount of 'sleep', in seconds or fractions of a second,\n"
	 "between generations.  Enter amount of sleep [0=none]: ");
  scanf("%f", &tmp);
  sleep = (int)(tmp * 1000);

  lifeInit(nrow, ncol);
  lifePopulateRandom(percent);

  while (1) {
	  printf("Generation number: %d, Alive: %d\n", count, lifeNumAlive());
    lifeStep();
    lifePrint();
    // lifePrintNeighbors(); // could display neighbor count instead!

    if (sleep != 0)
     Sleep( sleep );


    if (lifeNumAlive() == 0 || count == ngen)
      break;
    else
      system("cls");

    count++;
  }

  return 0;
}
    