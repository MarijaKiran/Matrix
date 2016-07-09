#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 5


//function that takes a dynamic array of integers in parameter of size 5x5 and prints out in contents in a square
//the function works
void printMatrix (int **matrix)
{
	//declare two variables for counting rows and columns respectively
    int i,j;
    printf("Print Matrix:\n");
    //2 for loops for printing a 2D matrix of size NxN or 5x5 because N is defined as 5
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
        	//print elt on [i][j]th position in the matrix
            printf("%d ",matrix[i][j]);
        }
        //start printing in new lines once first N numbers are printed out
        printf("\n");
    }
}

//function that replaces the elements of a 2D dynamic array of size 5x5 with random generated integers from 0-9 and returns the same array
//the function works
int **fillMatrix (int **matrix)
{
	//declare int variables-counters for rows and columns respectively
	int i,j;
	srand(time(NULL));
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			//generates a random number from 0-9
			int r = rand()%10;
			//each elt on [i][j]th position is set to a random number
			matrix[i][j]=r;
		}
	}
	//return of the 2D array
	return matrix;
}

//function that returns the number of occurrences of "number" in the 2D dynamic array "matrix" of size 5x5
//the function works
int numberOccurrences (int number, int **matrix)
{
	//declare variables i, j for rows and columns respectively
	int i,j;
	//declare an int variable count initialized to 0 for counting number of occurrences
	int count=0;
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			//if elt of [i][j]th position of the matrix matches "number" then
			if(matrix[i][j]==number)
			{
				//increment counter
				count++;
			}
		}
	}
	//return counter
	return count;
}

//function that prints out the elements appearing n times in the 2D array "matrix"
void PrintEltPresentNtimes (int **matrix, int n)
{
	//declare a int variable for storing the number appearing n times in the 2D array "matrix"
    int temp;

    //declare counters i,j for rows and columns respectively
	int i,j;
	for(i=0;i<N;i++)
	{
		//temp!=matrix[i][j] to avoid printing same numbers that appeared n times in the array "matrix"
		//bug: does not work with the following case matrix:
		/*
			1 2 3 4 5
			2 3 4 8 4
			0 2 1 1 9
			6 6 7 6 6
			8 8 8 1 0
		 */
		//because
		//setting n=3
		//we have to print out elts that appeared 3 times in the matrix
		//which are: 2 4
		//noting temp=2, but after temp=4, for it after to become temp=2 again
		//without being able to compare the previous value of temp
		//need to add condition
		for(j=0;j<N && temp!=matrix[i][j];j++)
		{
			//calling the function numberOccurrences which returns the nb of occ of the elt on [i][j]th position in the matrix
			//checks if the number of occ is equal to the entered number of occurrences by the user
			if((numberOccurrences(matrix[i][j],matrix))==n)
			{
				//if true temp gets value from elt on [i][j]th position in "matrix"
			    temp=matrix[i][j];
			    //print out this elt
				printf("%d ",matrix[i][j]);

			}
		}
	}
}

int main()
{

    //declare int variable "number1" to store a number entered by a user on which number of occurrences will be calculated in the matrix
	//declare an int variable numberofOcc entered by the user whose value is later compared with value of the number of occ of each elt in array "matrix"
	int number1,numberofOcc;

	//declare an int counter to store number of occ of the number1
	int counter;

	//declare int counters to count rows and columns respectively
    int i,j;

    //initialize matrix to NULL
    int **matrix=NULL;

    //allocating 2D matrix using malloc
    matrix=(int**)malloc(N*sizeof(int*));

    //if after allocating the 2D array, "matrix" is still NULL, malloc did not work
    if(matrix==NULL)
    {
    	//exit the program returning -1
        exit(-1);
    }

    for(i=0;i<N;i++)
    {
        //allocate all rows of the matrix of size 5
        matrix[i]=(int*)malloc(N*sizeof(int));

        //fill in the matrix by numbers entered by the user
        for(j=0;j<N;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
    //print out the filled in matrix by the user
   printMatrix(matrix);

   //fill the matrix with random numbers
   matrix=fillMatrix(matrix);

   //print this random filled matrix
   printMatrix(matrix);

   //enter a number by the user on which number of occurrences will be calculated
   printf("Number=");
   scanf("%d",&number1);

   //store the number of occcurrences of the entered number1 by the user in the matrix  (preconditions: number is in the matrix)
   counter=numberOccurrences(number1,matrix);

   //print out counter
   printf("%d",counter);

   //add a number of occ entered by the user wished to compare to the number of occurrences of each elt in the array "matrix"
   printf("Number of occurrences:");
   scanf("%d",&numberofOcc);

   //calling of the function PrintEltPresentNtimes which will print out elts appearing numberofOcc/N times in the "matrix" array
   PrintEltPresentNtimes(matrix, numberofOcc);
   return 0;
}
