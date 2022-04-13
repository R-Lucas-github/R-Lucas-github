#include<stdio.h>

#include<stdio.h>


                  /*Tableau 1D avec une valeur*/
void initArray1D(int size,int iArray[size], int value)
{
	for(int i = 0; i < size; i++)
	{
		iArray[i] = value;
	}
}

                  /*Tableau 2D avec une valeur**/
void initArray(int nbLin, int nbCol, int iArray[nbLin][nbCol], int value) 
{
	int i,j;
	for ( i = 0; i < nbLin; i++)
	{
		for ( j = 0; j < nbCol; j++)
		{
			iArray[i][j] = value;
		}
	}
}

                  /*Affichage tableau 2D*/
void showArray(int nbLin, int nbCol, int iArray[nbLin][nbCol]) 
{
	int i,j;
	for(i = 0; i < nbLin; i++)
	{
		for(j = 0; j < nbCol; j++)
			printw("%3d ", iArray[i][j]);
		printw("\n");
	}
}
