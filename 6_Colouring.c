/*
Name : Ipsita Singh
Roll No : 111601033
Program : To colour a graph with maximum 6 colours
*/

//Colouring may not be optimal

#include<stdio.h>

int readFile(char *inFileName,char (*am)[500]);

void ColourGraph(char (*am)[500],int n);

void generateDotFile(char *outFileName,char (*am)[500],int result[],int n);

char* getColour(int i);


int main(){

	char filename[20];	
	
	char am[500][500];

	int n;

	printf("Enter file name\n");
	scanf("%s",filename);

	n = readFile(filename,am);

	ColourGraph(am,n);
	
	

}

void ColourGraph(char (*am)[500],int n){

int i,j;

int result[n];

result[0] = 0;				// Assign first vertex the first colour

	for(i = 1;i<n;i++){

		result[i] = -1;

	}

int palette[6];				// palette consists of 6 colours

	for(i=0;i<6;i++){

		palette[i] = 1;		// Make all colours available initially

	}

int u;

int v;

int colour;

for(u=1;u<n;u++){			// starting from next node onwards



	for(v=0;v<n;v++){
	
	
	
		if(am[u][v] == '1'){			// for every adjacent vertex
		
		printf("Next node of %d is %d\n",u,v);
		
			
			if(result[v] != -1){		// if it is coloured
			
			palette[result[v]] = 0;		// Make that colour unavailable in palette
			
			printf("Unavailable colour of %d is %d\n",v,result[v]);
			
			}
		
		
		
		}
	
	
	
	
	
	}

	

	for(colour=0;colour<n;colour++){
	
	
		if(palette[colour] == 1){	// Find first available colour
	
			break;
	
		}
	
	
	}


	result[u] = colour;			// assign it to u
	
	
	for(i=0;i<6;i++){
	
		palette[i] = 1;			// Again make all colours available for next loop
	
	
	}
	

}


for(u=0;u<n;u++)

printf("Vertex %d --> Colour %d\n",u,result[u]);

char outFileName[20];

	printf("Enter output file name\n");	/* Take input name of output file*/
	scanf("%s",outFileName);


	generateDotFile(outFileName,am,result,n);	/* Calling to generate dot file*/


}




int readFile(char *inFileName,char (*am)[500]){

	int i,j;

	int n;				/* Number of vertices*/

	char number[10], type[10];	/* Initial two lines od file*/

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

void generateDotFile(char *outFileName,char (*am)[500],int result[],int n){


	int i,j;

	FILE *dotfile;

	dotfile = fopen(outFileName,"w");	/* Open file in write mode*/

	fprintf(dotfile,"graph {\n");

		for(i=0;i<n;i++){

			for(j=0;j<n;j++){

				if(am[i][j] == '1' && (i<j)){

				fprintf(dotfile,"%d -- %d\n",i,j);
				}

			}

		

		}
		
	for(i=0;i<n;i++){
	
	fprintf(dotfile,"%d[color = %s,style = filled];\n",i,getColour(result[i]));
	
	}	

	fprintf(dotfile,"}");	

	fclose(dotfile);	/* Close file*/

}

char* getColour(int n){		// returns colour corresponding to colour number

switch(n){

case 0 : return "red";

	break;

case 1 : return "blue";

	break;

case 2 : return "green";

	break;

case 3 : return "yellow";

	break;

case 4 : return "pink";

	break;
	
case 5 : return "black";


}


}



















