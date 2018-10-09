#include <stdio.h>
#include <stdlib.h>
struct polynomial {
	int coefficient;
	int index;
	struct polynomial *next;
};
typedef struct polynomial poly;

poly *make(int n){
	poly *a = malloc(sizeof(poly));
	a->coefficient = 0;
	a->index = 0;
	poly *head = a;
	int i;
	for(i = 0; i < n; i++) {
		poly *node = malloc(sizeof(poly));
		scanf("%d %d",&node->coefficient, &node->index);
		a->next = node;
		a = node;
	}
	a->next = malloc(sizeof(poly));
	a->next->next = NULL;
	return head;
}
void print(poly *head){
	poly *b;
	for(b = head->next; b->next != NULL; b = b->next) {
		printf("(%d)*x^(%d) + ",b->coefficient,b->index);
	}
	printf("\b\b\b\n");
}
poly *plus(poly *A,poly *B){
	poly *a = A;
	poly *b = B;
	while(a->next->next!=NULL && b->next->next!=NULL) {
		if(a->next->index == b->next->index) {
		a->next->coefficient += b->next->coefficient;
		poly *t = b->next;
		b->next = t->next;
		free(t);
		a = a->next;
		}else if(a->next->index < b->next->index) {
			poly *t = b->next;
			b->next = t->next;
			t->next = a->next;
			a->next = t;
			a = a->next;
		}else a = a->next;
	}
	if(a->next->next == NULL) {
		free(a->next);
		a->next = b->next;
	}
	return A;
}
void delete(poly *arr){
	poly *a = arr->next;
	free(arr);
	while (a->next != NULL) {
	poly *t = a;
	a = a->next;
	free(t);
	}
	free(a);
}
int main(){
	int polyNum;
	scanf("%d",&polyNum);
	poly *a = make(polyNum);
	scanf("%d",&polyNum);
	poly *b = make(polyNum);
	print(a);
	print(b);
	poly *c = plus(a,b);
	print(c);
	delete(a);
	delete(b);
	return 0;
}
