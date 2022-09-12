#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define maxStrLen 10


typedef struct treeNode {
  char key;
  char data[maxStrLen];
  struct treeNode *left;
  struct treeNode *right;
}treeNode;


typedef struct stackNode {
  treeNode* bstNode;
  struct stackNode *below;	
} stackNode;


int stackEmpty(stackNode* tTop){
  if (tTop==NULL){
	return 1;
  } else {
	return 0;
  }
}

void push(treeNode** pushNode, stackNode* newNode, stackNode** top) {
  newNode=malloc(sizeof(stackNode));
  newNode->bstNode=(*pushNode);
  newNode->below=(*top);
  (*top)=newNode;
}

treeNode* pop(stackNode** tTop){
  stackNode* tTemp=(*tTop);
  (*tTop)=(*tTop)->below;
  return tTemp->bstNode;
}

void getStr(treeNode* tTemp, char newKey){  
  printf("Enter the string of up to 10 characters for ");
  printf("%c", newKey);
  printf("'s data: ");
  scanf("%s", (tTemp)->data);
} 


void addNode1(treeNode** absRoot, treeNode** tRoot, treeNode* newGuy, char tKey) { //Finds the place for a node via recursion and places the node
  if((*tRoot)==NULL) {
	(*tRoot)=malloc(sizeof(treeNode));
	(*tRoot)->key=tKey;		
	getStr((*tRoot), tKey);
	(*tRoot)->left=NULL;
	(*tRoot)->right=NULL;
	(*absRoot)=(*tRoot);
  } else if (tKey<(*tRoot)->key) {
	if ((*tRoot)->left==NULL){	    	  
	  newGuy->key=tKey;
	  getStr(newGuy, tKey);
	  newGuy->left=NULL;
	  newGuy->right=NULL;
	  (*tRoot)->left=newGuy;  	  
  	} else {
  	  (*tRoot)=(*tRoot)->left;
    	  addNode1(absRoot, tRoot, newGuy, tKey);
  	}	
  } else {
	if ((*tRoot)->right==NULL){
    	  newGuy->key=tKey;
	  getStr(newGuy, tKey);
	  newGuy->left=NULL;
	  newGuy->right=NULL;
	  (*tRoot)->right=newGuy;  	  
	} else {
    	  (*tRoot)=(*tRoot)->right;
    	  addNode1(absRoot, tRoot, newGuy, tKey);
	}
  }
}


void addNode(treeNode** absRoot, treeNode** tRoot, treeNode* newGuy, char tKey) {
  newGuy=malloc(sizeof(treeNode));
  addNode1(absRoot, tRoot, newGuy, tKey);
  (*tRoot)=(*absRoot); //New addition, not yet tested
}


void getKey(char** newKey){
  char tKey[20];
  printf("Enter the key: ");
  scanf("%s", tKey);
  tKey[0]=toupper(tKey[0]);
  (*newKey)=&tKey[0];
}

//uses top and new
void prOrTr(treeNode* tRoot, stackNode* new, stackNode** top){
  int done=0;
  treeNode* trvPtr=tRoot;
  printf("Pre-Order Traversal Visited: ");
  while (!done){
	while (trvPtr!=NULL){
	  printf("%c ", trvPtr->key); // visited
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
void inOrTr(treeNode* tRoot, stackNode* new, stackNode** top){
  int done=0;
  treeNode* currentNode=tRoot;
  printf("In-Order Traversal Visited: ");
  while (!done){
	while (currentNode!=NULL){
	  if (currentNode->left!=NULL){
		push(&currentNode, new, &(*top));
		currentNode=currentNode->left;
	  } else {
		printf("%c ", currentNode->key);
		currentNode=currentNode->right;
	  }
	}
	if (stackEmpty((*top))){
	  done=1;
	} else {
	  currentNode=pop(&(*top));
	  printf("%c ", currentNode->key);
	  currentNode=currentNode->right;
	}	
  }
}


void find(treeNode* tRoot){
  char tKey;
  char scChar[20];
  int done=0;
  treeNode* trvPtr=tRoot;
  printf("Enter the search key: ");
  scanf("%s", scChar);
  scChar[0]=toupper(scChar[0]);
  tKey=scChar[0];
  while(!done){  
    if (trvPtr==NULL){
	  printf("%c ", tKey);
	  printf("is not in the tree\n");
	  done=1;
    } else if (tKey<trvPtr->key) {
	  trvPtr=trvPtr->left;
    } else if (tKey>trvPtr->key) {
	  trvPtr=trvPtr->right;
    } else if (tKey==trvPtr->key){
	  printf("Found the string ");
	  printf("%s ", trvPtr->data);
	  printf("there\n");
	  done=1;
    }	
  }
}


void userInterface(treeNode** Root) {
  treeNode *root=NULL, *temp=NULL, *theRoot=NULL;
  char menuInterfaceString[20];
  char menuInterface;
  char *newKey; 
  printf("Enter choice (I)nsert, (F)ind, (Q)uit: ");
  scanf("%s", menuInterfaceString);
  menuInterfaceString[0]=toupper(menuInterfaceString[0]);	
  menuInterface=menuInterfaceString[0];
  if (menuInterface=='I'){
	getKey(&newKey);
	addNode(&theRoot, &root, temp, *newKey);	
  }
  if (menuInterface=='F'){
	printf("The binary search tree is empty.\n");
  }
  while (menuInterface!='Q'){
	printf("Enter choice (I)nsert, (F)ind, (Q)uit: ");
 	scanf("%s", menuInterfaceString);
	menuInterfaceString[0]=toupper(menuInterfaceString[0]);	
	menuInterface=menuInterfaceString[0];
	if (menuInterface=='I'){
	  getKey(&newKey);
	  addNode(&theRoot, &root, temp, *newKey);	  
	}
	if (menuInterface=='F'){
	  find(root);
	}
  }
  (*Root)=root;
}

int main() {  
  stackNode *new=NULL;
  stackNode *top=NULL;
  treeNode* root;
  userInterface(&root);
  prOrTr(root, new, &top);
  printf("\n");
  inOrTr(root, new, &top);
  printf("\n");
  return 0;
}



