/*
Name : Ipsita Singh
Roll No : 111601033
Program : Finds an eulerian tour if it exists, from a given root vertex
*/


#include<stdio.h>
#include<stdlib.h>

struct queue{

	int rear,front;          /* Keeps tack of rear and front*/

	int data[500];		/* Queue implemented as array*/
};

struct queue* newQueue();

void EnQueue(struct queue *q,int x);

int DeQueue(struct queue *q);

int IsEmpty(struct queue *q);

struct stack{

	int data[500];

	int top;

	//int size;

};

struct stack* newStack();

void stackPush(struct stack *s,int x);

int stackPop(struct stack *s);

int stackEmpty(struct stack *s);

int IsConnected(char (*am)[500],int n);

int readFile(char *inFileName,char (*am)[500]);

int AllEvenDegree(char (*am)[500],int n);

int IsIsolated(char (*am)[500],int v,int n);

void Euler(char (*am)[500],int root,int n);

int NextNode(char (*am_temp)[500],int v,int n);

void MarkEdge(char (*am_temp)[500],int v,int u,int n);

int HasNeighbour(char (*am_temp)[500],int v,int n);


int main(){

char am[500][500];

char filename[20];

int n;

int root;

int connected,EvenDegree;

	printf("Enter input filename\n");
	scanf("%s",filename);

	n = readFile(filename,am);

	connected = IsConnected(am,n);		// Check if input graph is connected

	EvenDegree = AllEvenDegree(am,n);	// Check if input graph has all vertices even degree

	if(connected == 1 && EvenDegree == 1){
		
		printf("Eulerian circuit exisits\n");	// If above conditions satisfied, it exists

		printf("Enter root vertex\n");
		scanf("%d",&root);

		Euler(am,root,n);			// Find eulerian tour

	}

	else{

		printf("Eulerain circuit doesn't exist\n");	// Otherwise dosen't exists
	}


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

int IsConnected(char (*am)[500],int n){		

int i;

int visited[n];

	for(i=0;i<n;i++){

		if(IsIsolated(am,i,n)){

		visited[i] = 1;

		}

		else

		visited[i] = 0;

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

int AllEvenDegree(char (*am)[500],int n){

int i,j;


	for(i=0;i<n;i++){

	int d = 0;

		for(j=0;j<n;j++){

				if(am[i][j] == '1'){
					
					d++;

				}


		}

		if(d%2 != 0)	// If degree of any vertex not even then return 0
		return 0;


	}

return 1;

}

int IsIsolated(char (*am)[500],int v,int n){	// To ignore isolated vertices for checking connectivity

int j;

int zeros=0;


		for(j=0;j<n;j++){
			
			if(am[v][j] == '0'){
				
				zeros= zeros +1;

			}


		}


		if(zeros == n){
			
			return 1;		// If isolated it will marked as visited in IsConnected
			
			
		}


return 0;



}


void Euler(char (*am)[500],int root,int n){

int i,j;

int c=0;

int circuit[500];

char am_temp[500][500];

	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

		  am_temp[i][j] = am[i][j];	// temp copy of am


		}

	}


int current;

int current_prev;

struct stack *s;

s = newStack();

current = root;		// start with given root value



while(HasNeighbour(am_temp,current,n)){		// While it has a neighbour

current_prev = current;

current = NextNode(am_temp,current,n);		// get the neighbour

stackPush(s,current_prev);			// add it to stack

MarkEdge(am_temp,current_prev,current,n);	// mark as visited in temp am


}

circuit[c] = current;				// add last vertex with no neighbours in circuit
c++;

while(!stackEmpty(s)){


 	current = stackPop(s);				// Check if other pushed vertices still have neighbours
	
	if(HasNeighbour(am_temp,current,n)){		// if neighbour exusts
	
				stackPush(s,current);	// push current in stack

		while(HasNeighbour(am_temp,current,n)){

			current_prev = current;

			current = NextNode(am_temp,current,n);

			stackPush(s,current);			// push the neighbour in stack

			MarkEdge(am_temp,current_prev,current,n);


			}
				

	}
	
	else{
	
		circuit[c] = current;		// if no neighbour add it to circuit
		c++;
	
	}


}


printf("The path is -\n");

for(i=c-1;i>=0;i--){

printf("%d -> ",circuit[i]);	// path stored in reverse, so print reversed

}

printf("\n");


}

int HasNeighbour(char (*am_temp)[500],int v,int n){		// To check if neighbour exists

int j;


		for(j=0;j<n;j++){

				if(am_temp[v][j] == '1'){
				
					return 1;	

				}


			}


return 0; // reach here if no neighbour left


}


int NextNode(char (*am_temp)[500],int v,int n){		// to return next node

int j;

		for(j=0;j<n;j++){

			if(am_temp[v][j] == '1'){
				
				return j;

			}


		}


}


void MarkEdge(char (*am_temp)[500],int v,int u,int n){	// edge marked 

am_temp[v][u] = '0';

am_temp[u][v] = '0';

}



struct stack* newStack(){


	struct stack *new = malloc(sizeof( struct stack));

	new -> top = -1;

	return new;

}


void stackPush(struct stack *s,int x){


		if(s->top == -1){

		s->top =0;

		s->data[s->top] = x;

		}

		else{

		s->top = s->top+1;
		s->data[s->top] = x;
		}

}

int stackEmpty(struct stack *s){

	if(s->top == -1){
	
	return 1;
	
	}

	else{
	return 0;

	}

}

int stackPop(struct stack *s){

	int x = s->data[s->top];
	s->top = s->top -1;

	return x;

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




