// Name: Zachary Hart
// Course: CS315
// Assignment: homework2
// Queues and dequeues from a circular queue

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode {
  char c;
  struct listNode *next;
} listNode;

listNode *front = NULL;
listNode *newNode = NULL;
// Note that the trail is unnecessary, as it is simply equal to start->next from
// the previous call of queue

void queue(char m_letter) {
  if (newNode == NULL) {
    newNode = malloc(sizeof(listNode));
    newNode->next = newNode;
    newNode->c = m_letter;
    front = newNode;
  } else {
    newNode->next = malloc(sizeof(listNode));
    newNode->next->next = front;
    newNode = newNode->next;
    newNode->c = m_letter;
  }
}

void dequeue() {
  listNode *delPtr = NULL;
  if (newNode == NULL) {
    // do nothing
    printf("Nothing to remove; the queue is empty. \n");
  } else if (front->next == front) {
    delPtr = front;
    front = NULL;
    newNode = NULL;
    printf("The character removed was a(n) %c \n", delPtr->c);
    free(delPtr);
  } else {
    delPtr = front;
    front = front->next;
    printf("The character removed was a(n) %c \n", delPtr->c);
    free(delPtr);
  }
}

int main() {
  char c;
  char letter;
  char gobbledygook;
  while (c != 'q' && c != 'Q') {
    printf("Enter 'i' to queue, 'r' to dequeue, or 'q' to quit: ");
    scanf("%c", &c);
    scanf("%c", &gobbledygook);
    if (c == 'i' || c == 'I') {
      printf("Enter a letter to queue: ");
      scanf("%c", &letter);
      scanf("%c", &gobbledygook);
      letter = toupper(letter);
      queue(letter);
    }
    if (c == 'r' || c == 'R') {
      dequeue();
    }
  }
  return 0;
}
