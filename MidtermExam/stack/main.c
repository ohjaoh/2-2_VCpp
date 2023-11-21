#include <stdio.h>
#include "stack.h"

int main() {
	struct Data* Content = (struct Data*)malloc(sizeof(struct Data));
	Content->contentID = 1;
	push(Content);

	Content = (void *)0;
	struct Data* Content = (struct Data*)malloc(sizeof(struct Data));
	Content->contentID = 2;

	push(Content); 
	Content = pop();
	printf("Content ID: %d", Content->)
	Content = pop();



	free(Content);

	return 0;
}