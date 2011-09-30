// life.c
/* Functions to implement various aspects of Conway's Game of Life.
 * 
 * See CptS 122, Fall 2011, HW 1, Problem 2.
 * 
 * Author: John B. Schneider
 * Date: 9/10/2011
 */

#include "life2.h"


typedef struct cell* CellPtr;
typedef struct cell {
	//Stores each generation. That way we only do 
	// 1 set of calculations to modify next and current
	char s[2]; // status: alive or dead
	int x, y;
	CellPtr top, bottom, left, right; // above, below, left, right
} Cell;


// number of rows, columns, and total cells in entire grid
static int nrow_t, ncol_t, ntot_t, iGenerationIndex = 0; 

// number of alive cells in the current grid
static int alive_in_grid=0;

/* The following pointer point to memory where the complete
 * "grid" is stored.
 */
static CellPtr g0=NULL;


//int countAliveNeighbors(int row, int col);



void lifeInit(int the_nrow, int the_ncol) 
{
	int i = 0,j = 0, k = 0;
	CellPtr tmp = NULL, LeftCell = NULL, TopCell;

	nrow_t = the_nrow;
	ncol_t = the_ncol;
	ntot_t = nrow_t * ncol_t;

	// Free memory if previously initialized.
	if (g0 != NULL)
	{
		free(g0);
	}

	g0 = (CellPtr) malloc( sizeof( Cell ) );

	if ( g0 == NULL ) 
	{
		printf( "Initialization memory allocation failed.  Terminating...\n" );
		exit( -1 );
	}


	j = 0;
	LeftCell = tmp = g0;
	TopCell = NULL;

	for ( i = 1; i < ntot_t; i++ )
	{

		tmp->right = (CellPtr)malloc( sizeof( Cell ) );

		tmp->top = TopCell;
		tmp->s[0] = ' ';
		tmp->s[1] = ' ';
		tmp->x = k;
		tmp->y = j;

		if ( TopCell != NULL )
		{
			tmp->top->bottom = tmp;
			TopCell = TopCell->right;
		}

		tmp->right->left = tmp;
		tmp = tmp->right;



		j++;
		if ( j >= (ncol_t-1) && k < nrow_t )
		{
			LeftCell->left = tmp->left;
			tmp->left->right = LeftCell;
			tmp->top = LeftCell;

			TopCell = LeftCell;
			LeftCell = tmp;
			k++;
			j = 0;
		}
	}

	
	tmp = g0;
	LeftCell = LeftCell->left;
	/**
	 Reiterate through the top row assigning the bottom to top
	 and top to bottom. This is becuse the bottom didn't exist when
	 we created the top and we didn't have instant access to the top
	 row when we created the bottom, but now we have free varis to do
	 this with.
	 **/
	for( i = 0; i < ncol_t; i++ )
	{
		tmp->top = LeftCell;
		LeftCell->bottom = tmp;

		LeftCell = LeftCell->right;
		tmp = tmp->right;
	}
	
	return;
} // lifeInit()


void lifePrint(void) 
{
	int i = 0,j = 0, k = 1;
	CellPtr tmp = NULL, LeftCell = NULL, TopCell;

	j = 0;
	LeftCell = tmp = g0;
	TopCell = NULL;
	printf(" \t");
	for( i = 0; i < ncol_t; i++ )
		printf("%d ", i );
	printf("\n0\t");
	for ( i = 1; i < ntot_t; i++ )
	{
		
		printf("%c ", tmp->s[iGenerationIndex] );
		j++;
		tmp = tmp->right;

		if ( j >= (ncol_t) )
		{
			
			printf("\n");
			printf("%d\t", k );
			LeftCell = LeftCell->bottom;
			tmp = LeftCell;
			k++;
			j = 0;
		}
	}



  return;
} // lifePrint()


void lifePrintNeighbors(void) 
{
	int i = 0,j = 0, k = 1, neighbors = 0;

	CellPtr tmp = NULL, LeftCell = NULL, TopCell;

	j = 0;
	LeftCell = tmp = g0;
	TopCell = NULL;
	printf(" \t");
	for( i = 0; i < ncol_t; i++ )
		printf("%d ", i );
	printf("\n0\t");
	for ( i = 1; i <= ntot_t; i++ )
	{

		if ( tmp->left->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->bottom->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->left->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->left->bottom->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->bottom->s[iGenerationIndex] == '*' )
			neighbors++;

		printf("%i ", neighbors );
		neighbors=0;
		j++;
		tmp = tmp->right;

		if ( j >= (ncol_t) )
		{
			
			printf("\n");
			printf("%d\t", k );
			LeftCell = LeftCell->bottom;
			tmp = LeftCell;
			k++;
			j = 0;
		}
	}

	return;
} // lifePrintNeighbors()


void lifePopulateRandom(float percent) 
{

	int i = 0,j = 0, k = 0, num_to_insert = 0, tmpb = 0;
	
	CellPtr tmp = NULL, LeftCell = NULL, TopCell;

	if (percent < 0.0 || percent > 100.0) 
	{
		printf("Invalid percentage: %f.\n", percent);
		return;
	}
	percent /= 100.0;


	// rows
	j = 0;

	alive_in_grid = 0;

	srand(time(NULL));

	num_to_insert = (int) (percent * ntot_t);

	j = 0;
	LeftCell = tmp = g0;
	TopCell = NULL;
	for ( i = 1; i < ntot_t; i++ )
	{
		tmp->s[iGenerationIndex] = ' ';
		tmp = tmp->right;
		j++;
		if ( j >= (ncol_t) && k < nrow_t )
		{
			LeftCell = LeftCell->bottom;
			tmp = LeftCell;
			k++;
			j = 0;
		}
	}
	while (alive_in_grid < num_to_insert) 
	{
		
		j = 0;
		LeftCell = tmp = g0;
		TopCell = NULL;
		tmpb = (rand() % ntot_t);
		for ( i = 1; i < tmpb; i++ )
		{
			tmp = tmp->right;
			j++;
			if ( j >= (ncol_t) )
			{
				LeftCell = LeftCell->bottom;
				tmp = LeftCell;
				j = 0;
			}
		}

		if ( tmp->s[iGenerationIndex] == ' ' )
		{
			alive_in_grid++;

		}

		tmp->s[iGenerationIndex] = '*';

	}


	printf("\n");


  return;
} // lifePopulateRandom()


void lifeStep() {
	int i = 0,j = 0, k = 1, neighbors = 0;
	int iAlive = 0;

	CellPtr tmp = NULL, LeftCell = NULL, TopCell;

	j = 0;
	LeftCell = tmp = g0;
	TopCell = NULL;
	for ( i = 1; i <= ntot_t; i++ )
	{

		if ( tmp->left->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->bottom->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->left->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->top->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->left->bottom->s[iGenerationIndex] == '*' )
			neighbors++;

		if ( tmp->right->bottom->s[iGenerationIndex] == '*' )
			neighbors++;
	/**
	 If alive:
		D if Neighbors < 2
		A if 2 <= N <= 3
		D if 3 < N <= 8
	else if dead:
		A if N = 3
		D if N != 3
	end
	*/
		if ( tmp->s[iGenerationIndex] == '*' )
		{
			if ( neighbors < 2 || neighbors > 3 )
			{
				tmp->s[iGenerationIndex^1] = ' ';
			}
			else
			{
				iAlive++;
				tmp->s[iGenerationIndex^1] = '*';
			}
		}
		else
		{
			if ( neighbors != 3 )
			{
				tmp->s[iGenerationIndex^1] = ' ';
			}
			else
			{
				iAlive++;
				tmp->s[iGenerationIndex^1] = '*';
			}
		}
		neighbors=0;
		j++;
		tmp = tmp->right;

		if ( j >= (ncol_t) )
		{
			LeftCell = LeftCell->bottom;
			tmp = LeftCell;
			j = 0;
		}
	}
	iGenerationIndex ^= 1;
	alive_in_grid = iAlive;
	return;
} // lifeStep()


int lifeNumAlive(void) {
  return alive_in_grid;
} // lifeNumAlive()

void lifeShiftLeft( )
{
	
	g0 = g0->right;

}

void lifeShiftUp( )
{
	printf("Old g0 %p\n", g0);
	printf("g0->top %p\ (%d,%d)n", g0->top, g0->top->x, g0->top->y );
	printf("g0->top->right (%d,%d)\n", g0->top->right->x, g0->top->right->y );
	g0 = g0->bottom;
	printf("new g0 %p\n", g0);
	printf("g0->top %p\n", g0->top );
	printf("g0->top->right (%d,%d)\n", g0->top->right->x, g0->top->right->y );
}

void lifeShiftDown( )
{
	g0 = g0->top;
}
void lifeShiftRight( )
{
	g0 = g0->left;
}


void lifeDestroy()
{	int i = 0,j = 0, k = 1;
	CellPtr tmp = NULL, LeftCell = NULL;

	j = 0;
	tmp = g0;
	LeftCell = g0->bottom;


	for ( i = 1; i < ntot_t; i++ )
	{
		tmp = tmp->right;
		
		// This like.. doesn't work... EVER!
		// http://dab.biz/images/screenie/2011-09-22_2007.png
		// That's ^ the error I'm getting :(
		free(tmp->left);
		
		
		if ( j >= (ncol_t) )
		{
			LeftCell = LeftCell->bottom;
			tmp = LeftCell;
			k++;
			j = 0;
		}
	}
	nrow_t = 0;
	ncol_t = 0;
	ntot_t = 0;

}