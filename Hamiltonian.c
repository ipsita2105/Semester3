#include <stdio.h>
#include<stdlib.h>


void findMaximal(char (*am)[500],int n);

int HasNeighbour(char (*am_temp)[500],int v,int n);

int NextNode(char (*am_temp)[500],int v,int n);

void DeleteColumn(char (*am_temp)[500],int current,int n);


struct node{

			int data;

			struct node *next;
			struct node *prev;
	};


struct node* createList();

void insert(struct node **head,int d);

void insertFront(struct node **head,int d);

void printList(struct node *head);

void printCycle(struct node *cycleHead);

int readFile(char *inFileName,char (*am)[500]);

int IncreaseLength(struct node **head,char (*am_temp)[500],int cycleSize,int n);

void generateRedDotFile(char (*am)[500],struct node *cycleHead,int n);

int AdjacentInCycle(struct node *cycleHead,int i,int j);

int formCycle(struct node **cycleHead,struct node *head,char (*am)[500],int last,int n);

int main(){

char filename[20];

char am[500][500];

int n;

printf("Enter file name\n");
scanf("%s",filename);

n = readFile(filename,am);

findMaximal(am,n);

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

void DeleteColumn(char (*am_temp)[500],int current,int n){

int i;

	for(i=0;i<n;i++){

	am_temp[i][current] = '0';

	}
}


void findMaximal(char (*am)[500],int n){

char am_temp[500][500];

int i,j;

	for(i=0;i<n;i++){

		for(j=0;j<n;j++){

			am_temp[i][j] = am[i][j];

		}

	}
	
int current =0;

int current_prev;
	

struct node *head ;

head = (struct node*)malloc(sizeof(struct node));
head ->next = NULL;
head->prev = NULL;
head->data = current;

int size = 1 ;

struct node *temp_head = head;


	while(HasNeighbour(am_temp,current,n)){

		current_prev = current;

		current = NextNode(am_temp,current,n);
		
		insert(&temp_head,current);
		
		size = size+1;
		
		temp_head = temp_head -> next;

		DeleteColumn(am_temp,current_prev,n);

	}
	
DeleteColumn(am_temp,current,n);

int last = temp_head->data;

	


current = 0;

if(HasNeighbour(am_temp,current,n)){

while(HasNeighbour(am_temp,current,n)){

		
		current_prev = current;

		current = NextNode(am_temp,current,n);

		insertFront(&head,current);
		
		size = size + 1;
		
		head = head ->prev;

		DeleteColumn(am_temp,current_prev,n);

	}
	
DeleteColumn(am_temp,current,n);

}




// Finding cycle



struct node *cycleHead = (struct node*)malloc(sizeof(struct node));

int cSize = 0;

printf("n = %d cycleSize = %d\n",n,cSize);

while(cSize != n){

cSize = formCycle(&cycleHead,head,am,last,n);

cSize = IncreaseLength(&cycleHead,am_temp,cSize,n);

}



printf("\nPrinting cycle\n");

printCycle(cycleHead);


generateRedDotFile(am,cycleHead,n);

}



void printCycle(struct node *cycleHead){

int d = cycleHead->data;
cycleHead = cycleHead->next;
printf("%d ,",d);

	while(cycleHead->data != d){

	printf("%d ,",cycleHead->data);
	cycleHead = cycleHead->next;

	}
	
printf("%d\n",d);	

}

int formCycle(struct node **cycleHead,struct node *head,char (*am)[500],int last,int n){

struct node *temp_head2 = head;

struct node *temp_iterator_prev;

struct node *iterator;

struct node *temp_cycleHead;

int cycleSize = 0;

int cycleFormed = 0;


	while(temp_head2->next != NULL){
	
 	iterator = temp_head2 -> next;

		while(iterator != NULL){


	if(am[temp_head2->data][iterator->data] == '1' && am[iterator->prev->data][last] == '1'){

			
			temp_iterator_prev = iterator->prev;

			 //******* form new cycle********
			 
			 printf("Forming cycle\n");
			 
			 cycleFormed = 1;
			 
			 (*cycleHead)->data = temp_head2->data;
			 temp_cycleHead = *cycleHead;
			 cycleSize = 1;

			 
			 while(iterator != NULL){
			 
			 temp_cycleHead->next = (struct node*)malloc(sizeof(struct node));
			 temp_cycleHead->next->data = iterator->data;
			 cycleSize = cycleSize + 1;
			 temp_cycleHead = temp_cycleHead -> next;
			 iterator = iterator ->next;
			 
			 }
			 
			

			while(temp_iterator_prev != temp_head2){
			
			temp_cycleHead->next = (struct node*)malloc(sizeof(struct node));
			temp_cycleHead->next->data = temp_iterator_prev->data;
			cycleSize = cycleSize + 1;
			temp_cycleHead = temp_cycleHead -> next;
			temp_iterator_prev = temp_iterator_prev-> prev;
			}
			
			temp_cycleHead->next = *cycleHead;
			
			//printCycle(cycleHead);//
			
			return cycleSize;


			}
			
	
			iterator = iterator->next;

		}
	

	temp_head2 = temp_head2 ->next;	


}

}

int IncreaseLength(struct node **head,char (*am_temp)[500],int cycleSize,int n){

struct node *tempHead = *head;

struct node *nextNode;

int d = tempHead ->data;

int i;

int current_prev;

tempHead = tempHead->next;

while(tempHead->data != d){//********

	for(i=0;i<n;i++){

		if(am_temp[tempHead->data][i] == '1'){

		int current  = tempHead->data;
		nextNode = tempHead->next;
		

				while(HasNeighbour(am_temp,current,n)){

						current_prev = current;

						current = NextNode(am_temp,current,n);
		
						tempHead -> next = (struct node *)malloc(sizeof(struct node));
						tempHead -> next -> data = i;	
						tempHead = tempHead -> next;
								
						cycleSize = cycleSize+1;

						DeleteColumn(am_temp,current_prev,n);

					}
					
					DeleteColumn(am_temp,current,n);
					
					tempHead->next = nextNode;
					
					return cycleSize;

		}



	}

tempHead = tempHead -> next;

}


return cycleSize;



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

void generateRedDotFile(char (*am)[500],struct node *cycleHead,int n){


char outFileName[20];

int i,j;

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
				
				
						if(AdjacentInCycle(cycleHead,i,j)){
					
						fprintf(reddotfile,"%d -- %d[color = red];\n",i,j);
					
						}	
				
				
					

						else {

						fprintf(reddotfile,"%d -- %d;\n",i,j);
				
						}
				}

			}

		

		}

fprintf(reddotfile,"}");
	
	
fclose(reddotfile);	


}

int AdjacentInCycle(struct node *cycleHead,int i,int j){

int d = cycleHead -> data;

//special check for first element

if(d == i){

if(cycleHead->next->data == j)
return 1;
}

if(d == j){

if(cycleHead->next->data == i)
return 1;

}

cycleHead = cycleHead -> next;

while(cycleHead->data != d){

	if(cycleHead->data == i){

		if(cycleHead->next->data == j)
		return 1;
	}
	
	
	if(cycleHead->data == j){
	
		if(cycleHead->next->data == i)
		return 1;
	
	}

cycleHead = cycleHead -> next;

}

return 0;



}








struct node* createList(){

struct node *head;
struct node *prev;

head = (struct node*)malloc(sizeof(struct node));
head ->next = NULL;
head->prev = NULL;

return head;

}

void insert(struct node **head,int d){
		
		struct node *newNode;
		struct node *p;

		p = *head;
		
		
		newNode = (struct node *)malloc(sizeof(struct node));
		newNode->data = d;	
		newNode -> prev = p;
		p->next = newNode;
		newNode->next =NULL;

}



void insertFront(struct node **head,int d){

struct node *newNode;
struct node *p;
p = *head;

		newNode = (struct node *)malloc(sizeof(struct node));
		newNode->data = d;	
		newNode -> prev = NULL;
		newNode->next =p;
		p->prev = newNode;
		
}



void printList(struct node *head){

		while(head != NULL){

			printf("%d, ",head->data);
			head=head->next;

		}

	}



































































