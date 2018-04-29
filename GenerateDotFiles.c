/*
Name : Ipsita Singh
Roll No : 111601033
Task 1 : Generating Dot Files
*/

#include<stdio.h>

int readFile(char *inFileName,char (*am)[50]);	/* Function that reads file into a matrix return number of vertices*/

void generateDotFile(char *outFileName,char (*am)[50],int n);

/* Function to generate Dot file using above matrix*/


int main(){

char am[50][50];

char inFileName[20];

int n;

char outFileName[20];



	printf("Enter input file name\n");
	scanf("%s",inFileName);

	n = readFile(inFileName,am);
	
	printf("Enter output file name\n");	/* Take input name of output file*/
	scanf("%s",outFileName);


	generateDotFile(outFileName,am,n);	/* Calling to generate dot file*/


}

int readFile(char *inFileName,char (*am)[50]){

	int i,j;

	int n;				/* Number of vertices*/

	char number[10], type[10];	/* Initial two lines of file*/

	FILE *amfile;

	amfile = fopen(inFileName,"r");	/* Opens file in read mode*/

	if(amfile == 0){

	printf("Error in opening file\n");

	}

	fscanf(amfile,"%s\n%s\n%d\n",number,type,&n);

	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

			fscanf(amfile,"%c",&am[i][j]);	/* Scanning the matrix*/

		}

		fscanf(amfile,"\n");


	}

fclose(amfile);

return n;

}


void generateDotFile(char *outFileName,char (*am)[50],int n){


	int i,j;

	FILE *dotfile;

	dotfile = fopen(outFileName,"w");	/* Open file in write mode*/

	fprintf(dotfile,"graph {\n");

		for(i=0;i<n;i++){

			for(j=0;j<n;j++){

				if(am[i][j] == '1' && (i<j)){	

			/* i<j so not repeated values*/

				fprintf(dotfile,"%d -- %d;\n",i,j);
				}

			}

		

		}

	fprintf(dotfile,"}");	

	fclose(dotfile);	/* Close file*/

}







