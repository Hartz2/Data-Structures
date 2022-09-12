#include <stdio.h>
#include <ctype.h>
#define MAXSIZE 5

int heap[MAXSIZE];

typedef struct huffmanNode{
  int frequency;
  struct huffmanNode* left;
  struct huffmanNode* right;
}huffNode;

void insert(int insertion) {  
  int temp=0;
  int i=0;
  int j=0; // recorrects the index i
  heap[++i]=insertion;
  j=i;
  while (i!=1){
  if (i%2==0){ //if its a left node
	if (heap[i/2]>heap[i]){
	  temp=heap[i/2];
	  heap[i/2]=heap[i];
	  heap[i]=temp;	  
	  i=i/2;
	}
  } else if (i%2!=0){ //if its a right node
	if (heap[(i-1)/2]>heap[i]){
	  temp=heap[(i-1)/2];
	  heap[(i-1)/2]=heap[i];
	  heap[i]=temp;
	  i=(i-1)/2;
	}
  }
  }
  i=j;
}

void userInterface(){
  int insertion;
  char loopCase;  
  printf("Enter a character (Enter a $ to quit entering characters): ");
  loopCase=getc(stdin);	
  loopCase=tolower(loopCase);
  while (loopCase!='$'){
	printf("Enter %c's frequency: ", loopCase);
	scanf("%d", &insertion);
	insert(insertion);
  	loopCase=getc(stdin);	
	printf("Enter a character (Enter a $ to quit entering characters): ");
	loopCase=getc(stdin);
	loopCase=tolower(loopCase);
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
  userInterface();
  return 0;
}
