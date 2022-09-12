#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 5

typedef struct huffmanNode{
  int frequency;
  char character;
  struct huffmanNode* left;
  struct huffmanNode* right;
}huffNode;

huffNode* heap[MAXSIZE];


void insert(int insertion, char key, int count) {  
  char cTemp;
  int temp=0;
  int i=count;

  //insert an almost perfect new node//
  heap[++i]=malloc(sizeof(huffNode));
  heap[i]->frequency=insertion;
  heap[i]->character=key;
    
  while (i!=1){
  if (i%2==0){ //if its a left node
	if (heap[i/2]->frequency>heap[i]->frequency){
	  temp=heap[i/2]->frequency;
	  cTemp=heap[i/2]->character;
	  heap[i/2]->frequency=heap[i]->frequency;
	  heap[i/2]->character=heap[i]->character;
	  heap[i]->frequency=temp;	  
	  heap[i]->character=cTemp;	  
	}
	i=i/2;
  } else if (i%2!=0){ //if its a right node
	if (heap[(i-1)/2]->frequency>heap[i]->frequency){
	  temp=heap[(i-1)/2]->frequency;
	  cTemp=heap[(i-1)/2]->character;
	  heap[(i-1)/2]->frequency=heap[i]->frequency;
	  heap[(i-1)/2]->character=heap[i]->character;
	  heap[i]->frequency=temp;
	  heap[i]->character=cTemp;	  
	}
	i=(i-1)/2;
  }
  }
  
}

void insertPtr(huffNode* insertion, int count) {  
  
  
  huffNode* temp;
  int i=count;

  //insert an almost perfect new node//
  
  heap[++i]=insertion;

  while (i!=1){
  if (i%2==0){ //if its a left node
	if (heap[i/2]->frequency>heap[i]->frequency){
	  temp=heap[i/2];
	  heap[i/2]=heap[i];
	  heap[i]=temp;	  	  
	}
	i=i/2;
  } else if (i%2!=0){ //if its a right node
	if (heap[(i-1)/2]->frequency>heap[i]->frequency){
	  temp=heap[(i-1)/2];
	  heap[(i-1)/2]=heap[i];
	  heap[i]=temp;	  
	}
	i=(i-1)/2;
  }
  }
  
}

huffNode* claim(int count) { 
  int i=1;
  huffNode* returnNode = heap[i];  
  huffNode* temp;  
  heap[i]=heap[count];
  // dont forget to subtract one from count (Done)
  heap[count]=NULL;
  int loopCase=1;
  while (loopCase!=0){ // currently the seg fault
	if (i*2<count){
	if (heap[i]->frequency>heap[i*2]->frequency){
	  temp=heap[i*2];
	  heap[i*2]=heap[i];
	  heap[i]=temp;	  
	  if (i*2<count){
	  	i=i*2;
	  } else {
		loopCase=0;
	  }
	} else if (heap[i]->frequency>heap[(i*2)+1]->frequency){
	  temp=heap[(i*2)+1];
	  heap[(i*2)+1]=heap[i];
	  heap[i]=temp;	  
	  if ((i*2)+1<count){
	  	i=(i*2)+1;
	  } else {
		loopCase=0;
	  }
	}
	} else {
	  loopCase=0;
	}
  } 
  return returnNode;
}

void userInterface(){    
  int count=0;
  int insertion;
  char loopCase;  
  printf("Enter a character (Enter a $ to quit entering characters): ");
  loopCase=getc(stdin);	
  loopCase=tolower(loopCase);  
  while (loopCase!='$'){
	printf("Enter %c's frequency: ", loopCase);
	scanf("%d", &insertion);		
	insert(insertion, loopCase, count);	
  	loopCase=getc(stdin); // taking the garbage
	printf("Enter a character (Enter a $ to quit entering characters): ");
	loopCase=getc(stdin);
	loopCase=tolower(loopCase);
	if (loopCase!='$'){
		count++;
	}
  }
  
  
  //Build and display the huffman tree//
  
  huffNode* temp;
  huffNode* first;
  huffNode* second;  
  
  /* Testing Block
  int t=0;

  while (t<=count){
	t++;
	printf("%d, ", heap[t]->frequency);
  }
  */

  
  while (heap[2]!=NULL){
	temp=malloc(sizeof(huffNode));
	temp->character='-';
	
	
	
	first=claim(count--);	
	second=claim(count--);
	temp->left=first;
	temp->right=second;
	
	temp->frequency=(temp->left->frequency)+(temp->right->frequency);
	
	insertPtr(temp, count); //Recall that this function orders the heap as well
	count++;
	
  }
  
  // Testing Line printf("Top: %c \n", heap[1]->character);
  
}

int leftNode(int index){
  index=index*2;
  return index;
}

int rightNode(int index){
  index=(index*2)+1;
  return index;
}

int main() {
  userInterface();
  return 0;
}
