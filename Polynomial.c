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
	printf("\b\b\b   \n");
}
poly *plus(poly *A,poly *B){
	poly *a = A;
	poly *b = B;
	while(a->next->next!=NULL && b->next->next!=NULL) {
		if(a->next->index == b->next->index) {
			a->next->coefficient += b->next->coefficient;
			poly *t = b->next;
			b->next = t->next;
			// printf("删除%d\n",t);
			free(t);
			t = a->next;
			if(t->coefficient == 0){
				a->next = t->next;
				// printf("删除%d\n",t);
				free(t);
			}else a = a->next;
		}else if(a->next->index < b->next->index) {
			poly *t = b->next;
			b->next = t->next;
			t->next = a->next;
			a->next = t;
			a = a->next;
		}else a = a->next;
	}
	if(a->next->next == NULL) {
		poly *t = a->next;
		a->next = b->next;
		b->next = t;
	}
	return A;
}
void delete(poly *arr){
	poly *a = arr->next;
	// printf("删除%d\n",arr);
	free(arr);
	while (a->next != NULL) {
		poly *t = a;
		a = a->next;
		// printf("删除%d\n",t);
		free(t);
	}
	// printf("删除%d",a);
	free(a);
}
int main(){
	int polyNum;
	scanf("%d",&polyNum);
	poly *a = make(polyNum);
	poly *t;
	// for(t = a; t->next!=NULL;t = t->next){
	// 	printf("%d\n",t);
	// }
	// printf("%d\n---------多项式a\n",t);
	scanf("%d",&polyNum);
	poly *b = make(polyNum);
	// for(t = b; t->next!=NULL;t = t->next){
	// 	printf("%d\n",t);
	// }
	// printf("%d\n---------多项式b\n",t);
	print(a);
	print(b);
	poly *c = plus(a,b);
	print(c);
	// printf("-------正常print\n");
	// for(;c->next != NULL;c = c->next){
	// 	printf("%d\n",c);
	// }
	// printf("%d\n",c);
	delete(a);
	// printf("-------正常删除a\n");
	// for(c = b;c->next != NULL;c = c->next){
	// 	printf("%d\n",c);
	// }
	// printf("%d\n",c);
	delete(b);
	// printf("-------正常删除b\n");
	return 0;
}
