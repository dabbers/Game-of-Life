#include "life2.h"
#include <string.h>
void print_help(void);

int main1() {
  int nrow, ncol, choice;
  float percent;

  print_help();
  printf("\nEnter choice: ");

  while ((choice = getchar()) != 'q' &&
	 choice != EOF) {
    switch (choice) {

    case 'A':
    case 'a':
      printf("Number of alive cells: %d\n", lifeNumAlive());
      break;

    case 'I':
    case 'i':
      printf("Enter the number of rows and columns: ");
      scanf("%d %d", &nrow, &ncol);
      lifeInit(nrow, ncol);
      break;

    case 'D':
    case 'd':
      lifeDestroy();
      break;

    case 'N':
    case 'n':
      lifePrintNeighbors();
      break;

    case 'P':
    case 'p':
      lifePrint();
      break;

    case 'R':
    case 'r':
      printf("Enter percent [0.0 to 100.0]: ");
      scanf("%f", &percent);
      lifePopulateRandom(percent);
      break;

    case 'S':
    case 's':
      lifeStep();
      break;

    case 'Z':
    case 'z':
      lifeShiftLeft();
      break;

    case 'X':
    case 'x':
		lifeShiftUp();
      break;

    case 'C':
    case 'c':
      lifeShiftDown();
      break;

    case 'V':
    case 'v':
      lifeShiftRight();
      break;

    case 'H':
    case 'h':
      print_help();
      break;

    case '\n': /* ignore whitespace */
    case '\t':
    case ' ':
      printf("\nEnter choice: ");
      break;

    default:
      printf("Not a valid choice.\n");
      break; 
    } // end switch
    
  } // end while

  return 0;
} // main()

void print_help(void) {
    printf("Choices:\n"
	 "  a = lifeNumAlive()        [number of alive cells]\n"
	 "  i = lifeInit()            [initialize game]\n"
	 "  p = lifePrint()           [print the board]\n"
	 "  n = lifePrintNeighbors()  [print neighbor counts]\n"
	 "  r = lifePopulateRandom()  [populate the board randomly]\n"
	 "  s = lifeStep()            [step one generation]\n"
	 "  z = lifeShiftLeft()       [shift board left]\n"
	 "  x = lifeShiftUp()         [shift board \"up\"]\n"
	 "  c = lifeShiftDown()       [shift board \"down\"]\n"
	 "  v = lifeShiftRight()      [shift board right]\n"
         "  d = lifeDestroy()         [free all cells]\n"
	 "  h = [help -- this menu]\n"
	 "  Q = [quit]\n");
    return;
} // print_help()