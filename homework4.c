#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXSIZE 10

typedef struct huffmanNode{
  int frequency;
  char character;
  struct huffmanNode* left;
  struct huffmanNode* right;
}huffNode;

huffNode* heap[MAXSIZE];


typedef struct stackNode {
  huffNode* bstNode;
  struct stackNode *below;	
} stackNode;


int stackEmpty(stackNode* tTop){
  if (tTop==NULL){
	return 1;
  } else {
	return 0;
  }
}

void push(huffNode** pushNode, stackNode* newNode, stackNode** top) {
  newNode=malloc(sizeof(stackNode));
  newNode->bstNode=(*pushNode);
  newNode->below=(*top);
  (*top)=newNode;
}

huffNode* pop(stackNode** tTop){
  stackNode* tTemp=(*tTop);
  (*tTop)=(*tTop)->below;
  return tTemp->bstNode;
}

//uses top and new
void prOrTr(huffNode* tRoot, stackNode* new, stackNode** top){
  int done=0;
  huffNode* trvPtr=tRoot;
  printf("Pre-Order Traversal Visited: ");
  while (!done){
	while (trvPtr!=NULL){
	  printf("%d ", trvPtr->frequency); // visited
	  if (trvPtr->left!=NULL){
		push(&trvPtr, new, &(*top));
		trvPtr=trvPtr->left;
	  }else {
		trvPtr=trvPtr->right;
	  }
	}
	if (stackEmpty((*top))){
		done=1;
	} else {
		trvPtr=pop(&(*top));
		trvPtr=trvPtr->right;
	}	  	
  }
}

// uses top and new
void inOrTr(huffNode* tRoot, stackNode* new, stackNode** top){
  int done=0;
  huffNode* currentNode=tRoot;
  printf("In-Order Traversal Visited: ");
  while (!done){
	while (currentNode!=NULL){
	  if (currentNode->left!=NULL){
		push(&currentNode, new, &(*top));
		currentNode=currentNode->left;
	  } else {
		printf("%c ", currentNode->character);
		currentNode=currentNode->right;
	  }
	}
	if (stackEmpty((*top))){
	  done=1;
	} else {
	  currentNode=pop(&(*top));
	  printf("%c ", currentNode->character);
	  currentNode=currentNode->right;
	}	
  }
}


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
  
  heap[++i]=malloc(sizeof(huffNode));
  heap[i]=insertion;

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
  int lowest;
  heap[i]=heap[count];
  // dont forget to subtract one from count (Done)
  heap[count]=NULL;
  int loopCase=1;
  while (loopCase!=0){ // currently the seg fault
	if (i*2+1<count){
	if (heap[i]->frequency>heap[i*2]->frequency) {
	  lowest=i*2;
	}
	if (heap[lowest]->frequency>heap[(i*2)+1]->frequency){
	  lowest=(i*2)+1;
	}
	temp=heap[lowest];
	heap[lowest]=heap[i];
	heap[i]=temp;
	i=lowest;		
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

  
  while (count!=1){	
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
  stackNode *new=NULL;
  stackNode *top=NULL;
  huffNode* root=heap[1];
  userInterface();
  prOrTr(root, new, &top);
  printf("\n");
  inOrTr(root, new, &top);
  printf("\n");
  return 0;
}
