#include <stdio.h>
#include <stdlib.h>

typedef struct listItem{
  int n;
  struct listItem *next;
}listItem;

listItem *start=NULL;
listItem *temp;
listItem *pptr;
listItem *nptr;


void addItem(){    
  if (start==NULL){	
  	temp=malloc(sizeof(listItem));
	printf("Enter a number: ");
	scanf("%d", &temp->n);
	temp->next=NULL;
	start=temp;
  } else {
	temp->next=malloc(sizeof(listItem));
	temp=temp->next;
	temp->next=NULL;
	printf("Enter a number: ");
	scanf("%d", &(temp->n));
  }
}

void printList(){    
  printf("OK, heres your list in numeric order: ");    
  while(pptr!=NULL){			
	if (pptr->n!=0)
	  printf("%d", pptr->n);
	if (pptr->next!=NULL&&pptr->n!=0){
	  printf(" -> ");
	}
	pptr=pptr->next;
  }
  printf("\n");
  pptr=start;
}

int checkNum(int x){
  listItem *cptr=start;
  int numCheck=0; //0 is for false
  while (cptr!=NULL){	
	if (cptr->n==x){
	  numCheck=1; //1 is for true
	}
	cptr=cptr->next;
  }
  return numCheck;
}

int deleteItem(){
  listItem *dptr=NULL;
  listItem *rm=NULL;  
  int numCheck=0;
  dptr=start;
  printf("What number do you want to delete?  ");
  int x;
  scanf("%d", &x);  
  numCheck=checkNum(x);
  if (dptr->next!=NULL&&numCheck==1){
	if (x==start->n){	  		  	  
	  temp=start;
	  start=start->next;
	  free(temp);
	  pptr=start;
	}
	else{
  	while(dptr->next->n!=x){
	  dptr=dptr->next;
  	}  	
  	rm=dptr->next;  
	dptr->next=dptr->next->next;
	free(rm);
	}
  }
  else {
  if (x!=0){
    printf("Can't delete, ");
    printf("%d", x);
    printf(" is not in the list\n");
  }
  }
  return x;
}

void orderList(){  
//  listItem *temporaryStart;
  listItem *i;
  listItem *j;
  int num;
  /*
  if (start->next->n!=0||start->next!=NULL){
    temporaryStart=malloc(sizeof(listItem));
    temporaryStart->next=start;
    start=temporaryStart;
    trail=temporaryStart;
    temp=start->next; //dont touch the start when ordering until last;
  }
  */
  
  for (i=start;i->next!=NULL;i=i->next)
  {
    for(j=i->next;j!=NULL;j=j->next)
    {
      if (i->n>j->n){
        num=i->n;
        i->n=j->n;
        j->n=num;
      }    
    }
  }
  
  //temp=temporaryStart;
  //start=temporaryStart->next;
  //free(temporaryStart);
}

int main(){
  int x; 
  temp=malloc(sizeof(listItem));
  temp->next=NULL;
  temp->n=-1; //initialize temp. Will be overwritten with addItem();  
  while (temp->n!=0){	
	addItem();  
  }
  nptr=start;
  if (nptr->n==0){
	printf("Your list is empty\n");
  } else {
  orderList();
  pptr=start;
  printList();  
  
  x=deleteItem();
  printList();
  while (x!=0){	
  	x=deleteItem();  
  	printList();
  }  
  printf("Bye\n");  
  }
  return 0;
}
