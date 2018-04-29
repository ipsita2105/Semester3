/*
Name : Ipsita Singh
Roll No : 111601033
Task 2 : Genrate dot file showing  bfs traversal
*/

#include<stdio.h>
#include<stdlib.h>

struct queue{

	int rear,front;          /* Keeps tack of rear and front*/
  
	//int size;		/*Keeps track of size*/

	int data[10];		/* Queue implemented as array*/
};

struct queue* newQueue();

void EnQueue(struct queue *q,int x);

int DeQueue(struct queue *q);

int IsEmpty(struct queue *q);

int readFile(char *inFileName,char (*am)[50]);

void bfs(char (*am)[50],int root,int goal,int n);	




int main(){

char am[50][50];

char filename[20];

int n,root,goal;

	printf("Enter input filename\n");
	scanf("%s",filename);

	n = readFile(filename,am);
	
	printf("Enter value of root vertex\n");
	scanf("%d",&root);
	
	printf("Enter value of goal vertex\n");
	scanf("%d",&goal);
	
	bfs(am,root,goal,n);
	

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



void bfs(char (*am)[50],int root,int goal,int n){

int checked[500];		// To keep account of visited nodes

int prev[500];			// Keeps account of prev of each node

int distance[500];		// Keeps distance of each node from root

int path=0;			// Flag to see if connected or not

int i,current,j;


	for(i=0;i<500;i++){		// Initializing values

		checked[i] = 0;
		prev[i] = -1;
		distance[i] = 99999;

	}
	

checked[root] = 1;		// Mark root as visited

distance[root] = 0;		// Distance of root from root = 0
		
	
struct queue *q;

q = newQueue();

EnQueue(q,root);		// Enqueue root


while(IsEmpty(q)){

current = DeQueue(q);		// Dequeue first queue element 

	if( current == goal){		// If its the goal then path found
	

		printf("Path exists\n");
		path = 1;

	}
	
	
	
	for(i=0;i<n;i++){		// Otherwise check for each adjacent node
	
		if(am[current][i] == '1'){
		
			
			if(!checked[i]){		// If it not visited
			
			
			checked[i] = 1;				// Mark as visited
			prev[i] = current;			
			distance[i] = distance[current] + 1;	// distance is diastence till prev node + 1
			EnQueue(q,i);				// Now enqueue to explore this node	
			}
		
		
		}
		
	}

}

int v;

if(path == 1){

int array[500];		// Array stores vertices name that are in path

for(i=0;i<500;i++){

array[i] = -1;
}

int k =0;

v = goal;

printf("The shortest path is (Printed in reverse order)-\n");

	while(prev[v] != -1){

		printf("%d ->",v );
		array[k] = v;
		k++;
		v = prev[v];
	}

printf("%d\n",root);

array[k] = root;

printf("Length of path %d\n",distance[goal]);		// Prints distance of goal from root

char outFileName[20];

k=1;

	printf("Enter out file name\n");
	scanf("%s",outFileName);
	
	// Generate Red Dot File
	
	FILE *reddotfile;
	
	reddotfile = fopen(outFileName,"w");
	
	fprintf(reddotfile,"graph {\n");

		for(i=0;i<n;i++){			// Check for each vertex in graph

			for(j=0;j<n;j++){
			
					int flag = 0;
			
			

				if(am[i][j] == '1' && (i<j)){		// See adjacent vertex
				
				
					for(k=1;k<500;k++){
				
						if( array[k] == i){
				
							if(array[k-1] == j || array[k+1] == j){
				
							fprintf(reddotfile,"%d -- %d[color = red];\n",i,j);
							flag =1;
				
							}
				
				
						}
				
				
					}
					
					if(array[0] == i && array[1] == j ){
				
					fprintf(reddotfile,"%d -- %d[color = red];\n",i,j);
					flag =1;
				
					}
					
					// If they are adjacent in array then print them red
					
					// Otherwise print non coloured edge

					else if(flag == 0){

						fprintf(reddotfile,"%d -- %d;\n",i,j);
				
					}
				
				}

			}

		

		}

fprintf(reddotfile,"}");
	
	
fclose(reddotfile);	



}

else{
	printf("Path doesn't exist\n");
	return;
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





























