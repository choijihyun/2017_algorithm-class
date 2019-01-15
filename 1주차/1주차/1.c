#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct Node {
	struct Node * prev;
	struct Node * next;
	char elem;
}Node;

Node * Header;
Node * Trailer;

void initNode() {
	Header = (Node *)malloc(sizeof(Node));
	Trailer = (Node *)malloc(sizeof(Node));
	Header->next = Trailer;
	Header->prev = NULL;
	Trailer->next = NULL;
	Trailer->prev = Header;
}

int search() {
	Node * tmp;
	int cnt=0;

	tmp = Header;
	while (tmp->next!=Trailer) {
		cnt++;
		tmp = tmp->next;
	}
	return cnt;
}

int check_point(int num) {
	int len;
	len = search();
	if (len < num)
		return 0;//invalid position
	else
		return 1;
}

Node * position(int num) {
	Node * tmp = Header;
	int cnt = 0;

	while (cnt != num) {
		cnt++;
		tmp = tmp->next;
	}

	return tmp;
}

void add_Node(int num, char item) {
	Node * add_node;
	Node * tmp;
	
	add_node = (Node *)malloc(sizeof(Node));
	add_node->elem = item;
	
	tmp = position(num);
	
	add_node->prev = tmp->prev;
	tmp->prev->next = add_node;
	add_node->next = tmp;
	tmp->prev = add_node;

}

void delete(int num) {
	Node * tmp ;

	if (!check_point(num)) {
		printf("invalid position\n");
	}
	else {
		tmp = position(num);
		//tmp가 지워야하는 노드 가리킴
		
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;

		free(tmp);
	}
}

char get_entry(int num) {
	int cnt = 0;
	Node * tmp = Header;

	if (!check_point(num)) {
		printf("invalid position\n");
		return 0;
	}
	else {
		while (cnt != num) {
			cnt++;
			tmp = tmp->next;
		}
		return tmp->elem;
	}
}

void print() {
	Node * tmp = Header;
	while (tmp != Trailer) {
		printf("%c", tmp->next->elem);
		tmp = tmp->next;
	}
	printf("\n");
}

int main() {
	int len,i,num;
	char func,elem;

	initNode();

	scanf("%d", &len);
	getchar();

	for (i = 0; i < len; i++) {
		scanf("%c", &func);
		switch (func) {
		case 'A':scanf("%d", &num);
			getchar();
			scanf("%c", &elem);
			getchar();
			add_Node(num, elem);break;
		case 'D':scanf("%d", &num);
			getchar();
			delete(num); break;
		case 'P':print(); 
			getchar(); break;
		case 'G':scanf("%d", &num);
			getchar();
			elem = get_entry(num);
			if (elem != 0) {
				printf("%c\n", elem);
			}
		}
	}
}