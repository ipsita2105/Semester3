/*
Name : Ipsita Singh
Roll No : 111601033
Print components in a graph
*/

#include<stdio.h>
#include<stdlib.h>

//Isolated vertiecs are a single component

struct queue{

	int rear,front;          /* Keeps tack of rear and front*/
  
	int data[10];		/* Queue implemented as array*/
};

struct queue* newQueue();

void EnQueue(struct queue *q,int x);

int DeQueue(struct queue *q);

int IsEmpty(struct queue *q);

int readFile(char *inFileName,char (*am)[50]);	

void connected(char (*am)[50],int n);			// to count connected componentes

int main(){

char am[50][50];

char filename[20];

int n;

printf("Enter input file name\n");
scanf("%s",filename);

n = readFile(filename,am);

connected(am,n);


}

void connected(char (*am)[50],int n){

int i;

int visited[n];			        // To track visited vertices

	for(i=0;i<500;i++){

		visited[n] = 0;		// Initialising 

	}
	
int connected =0;		       // number of connected components

int v;

FILE *outfile;

char outFileName[20];

printf("Enter output file name\n");
scanf("%s",outFileName);

outfile = fopen(outFileName,"w");

fprintf(outfile,"graph {");



for(v=0;v<n;v++){		        // For every vertex

	if(visited[v] !=  1){		// If its not visited

		connected++;
		
		printf("Component %d : ",connected);	// Its a component

		struct queue *q;

		q = newQueue();

		EnQueue(q,v);
		
		
		visited[v] = 1;		// Mark it visited
		
			while(IsEmpty(q)){
		
			int w = DeQueue(q);	// Dequeue to explore it
			
			
			printf("%d ",w);	// this vertex part of component print it
			
			
		
				for(i=0;i<n;i++){
	
					if(am[w][i] == '1'){		// For adjacent vertices
					
							if(w < i){
					
							fprintf(outfile,"%d -- %d\n;",w,i);	// Add it to file
							}
		
			
							if(visited[i] != 1){		// If unvisited
			
							fprintf(outfile,"%d -- %d[color = red];\n",w,i); // add as red
							visited[i] = 1;		// Mark as visited
							EnQueue(q,i);		//Enqueue to explore later
			
							}
		
		
						}
	
	
	
				}
				
				
		
		
		
			}
			
			
		printf("end\n");	// End of a component	
			

	}

}

fprintf(outfile,"}");

if( connected == 1){

	printf("The graph is connected\n");

}

else{

	printf("There are %d connected components\n",connected);

}	




}

struct queue* newQueue(){

	struct queue *new = malloc(sizeof(struct queue));

	new->rear = -1;
	new->front = -1;

	return new;

}


void EnQueue(struct queue *q,int x){

		if( q->front == -1){

			q->front = q->rear = 0;             /* Adding first element */

			q->data[q->rear] = x;

		}


		else{

			q->rear = (q->rear) +1;	/* Otherwise rear increased and element added*/

			q->data[q->rear] = x;

		}

}


int DeQueue(struct queue *q){

int x;



		if(q->front == q->rear){   /* If only one element in queue*/
			
			
			x = q->data[q->front];
					
			q->front = q->rear =-1;
			
			return x;

		}

		else
		{
			
			x = q->data[q->front];
			q->front = (q->front)+1;	/* Otherwise front increased*/
			return x;

		}

}




int IsEmpty(struct queue *q){

		if( q-> front == -1){

			return 0;
		}

		else
			return 1;
			
}

int readFile(char *inFileName,char (*am)[50]){

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
























