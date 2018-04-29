/*
Name : Ipsita Singh
Roll No : 111601033
Task 4: Finding diameter in a graph
*/

#include<stdio.h>
#include<stdlib.h>

struct queue{

	int rear,front;          /* Keeps tack of rear and front*/

	int data[10];		/* Queue implemented as array*/
};

struct queue* newQueue();

void EnQueue(struct queue *q,int x);

int DeQueue(struct queue *q);

int IsEmpty(struct queue *q);

int readFile(char *inFileName,char (*am)[50]);

int shortestPath(char (*am)[50],int root,int goal,int n);	// Returns shortest path between teo vertices

int notInChecked(int checked[],int x);

int IsConnected(char (*am)[50],int n);				// To check if input graph is connected or not

void diameter(char (*am)[50],int n);

void generateRedDotFile(char (*am)[50],int root,int goal,int n);	// To mark the one of the diameter red


int main(){

char am[50][50];

char filename[20];

int n;

	printf("Enter input filename\n");
	scanf("%s",filename);

	n = readFile(filename,am);
	
	
	if(IsConnected(am,n)){

	diameter(am,n);
	
	}
	
	else{
	
	printf("Graph is not connected !\n");
	
	}
	

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

int notInChecked(int checked[],int x){


		if(checked[x] == 1)

		return 0;


		else

		return 1;

}

void diameter(char (*am)[50],int n){

int l;

int distance[n][n];	// Stores distance between any vertices

int i,j;

	for(i=0;i<n;i++){

		for(j=0;j<n;j++){
		
		
			if(i<j){
			
			l = shortestPath(am,i,j,n);	// returns shortest path between them
			distance[i][j] = l;		// store it
			
			}



		}


	}
	
	
int start,end,dia=0;

	for(i=0;i<n;i++){


		for(j=0;j<n;j++){
		
			if(i<j){
			
				if(distance[i][j] >= dia){
				
				dia = distance[i][j];	// Find largest of these shortest paths
				start = i;		// Store the vertices
				end = j;
				
				}
		
		
			}


		}

	}
	
printf("Diameter of graph is %d\n",dia);	

generateRedDotFile(am,start,end,n);	// Colour red these two vertices


}

int shortestPath(char (*am)[50],int root,int goal,int n){	// Taken from previous program

int checked[500];

int distance[500];

int i,current;


	for(i=0;i<500;i++){

		checked[i] = 0;
		distance[i] = 99999;

	}
	

checked[root] = 1;

distance[root] = 0;
		
	
struct queue *q;

q = newQueue();

EnQueue(q,root);


while(IsEmpty(q)){

current = DeQueue(q);
	
	
	for(i=0;i<n;i++){
	
		if(am[current][i] == '1'){
		
			
			if(notInChecked(checked,i)){
			
			
			checked[i] = 1;
			distance[i] = distance[current] + 1;
			EnQueue(q,i);
			
			}
		
		
		}
	
	
	
	}




}

return distance[goal];

}	

void generateRedDotFile(char (*am)[50],int root,int goal,int n){

// Finds shortest path again and colours them red

int checked[500];

int prev[500];

int distance[500];

int i,current,j;


	for(i=0;i<500;i++){

		checked[i] = 0;
		prev[i] = -1;
		distance[i] = 99999;

	}
	

checked[root] = 1;

distance[root] = 0;
		
	
struct queue *q;

q = newQueue();

EnQueue(q,root);


while(IsEmpty(q)){

current = DeQueue(q);

	
	for(i=0;i<n;i++){
	
		if(am[current][i] == '1'){
		
			
			if(notInChecked(checked,i)){
			
			
			checked[i] = 1;
			prev[i] = current;
			distance[i] = distance[current] + 1;
			EnQueue(q,i);
			
			}
		
		
		}
	
	
	
	}




}

int v;


int array[500];

for(i=0;i<500;i++){

array[i] = -1;
}

int k =0;

v = goal;


	while(prev[v] != -1){

		array[k] = v;
		k++;
		v = prev[v];
	}


array[k] = root;



char outFileName[20];

k=1;

	printf("Enter out file name\n");
	scanf("%s",outFileName);
	
	// Generate Red Dot File
	
	FILE *reddotfile;
	
	reddotfile = fopen(outFileName,"w");
	
	fprintf(reddotfile,"graph {\n");

		for(i=0;i<n;i++){

			for(j=0;j<n;j++){
			
					int flag = 0;
			
			

				if(am[i][j] == '1' && (i<j)){	
				
				
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

					else if(flag == 0){

						fprintf(reddotfile,"%d -- %d;\n",i,j);
				
					}
				
				}

			}

		

		}

fprintf(reddotfile,"}");
	
	
fclose(reddotfile);	


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

int IsConnected(char (*am)[50],int n){

int i;

int visited[n];

	for(i=0;i<500;i++){

		visited[n] = 0;

	}
	
int connected =0;

int v;


for(v=0;v<n;v++){

	if(visited[v] !=  1){

		connected++;

		struct queue *q;

		q = newQueue();

		EnQueue(q,v);
		
		visited[v] = 1;
		
			while(IsEmpty(q)){
		
			int w = DeQueue(q);
			
						
		
				for(i=0;i<n;i++){
	
					if(am[w][i] == '1'){
					
			
							if(visited[i] != 1){
			
							visited[i] = 1;
							EnQueue(q,i);
			
							}
		
		
						}
	
	
	
				}
				
				
		
		
		
			}
				
			

	}

}


if( connected == 1){

	return 1;

}

else

return 0;


}




