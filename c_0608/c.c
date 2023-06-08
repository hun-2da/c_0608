#include <stdio.h>
#include <stdlib.h>

#define MAX_string 20
typedef char* element;
typedef struct DListNode {	// 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;
// 이중 연결 리스트를 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
void print_dlist(DListNode* phead,DListNode* choice)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		if(p==choice)
			printf("<-| O |%s| O |-> ", p->data);
		else printf("<-| |%s| |-> ", p->data);
	}
	printf("\n");
}
void dinsert(DListNode* before, char* data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode -> data = malloc(MAX_string * sizeof(char));
	strcpy(newnode->data, data);
	//newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
DListNode* ddelete(DListNode* head, DListNode* removed)
{
	if (removed != head) {
		removed->llink->rlink = removed->rlink;
		removed->rlink->llink = removed->llink;
		free(removed->data);
		free(removed);
	}
	return head;
}
int main(void)
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	DListNode* choice_node = head;
	char* fruit = malloc(MAX_string * sizeof(char));

	while (1) {
		
		printf("메뉴\n n) 다음 과일\n p) 이전 과일\n d) 현재 과일 삭제\n i) 현재 과일 다음에 과일 추가\n o) 과일 리스트 출력(현재 선택된 과일에는 마지막에[O] 출력)\n e) 프로그램 종료 : ");
		char choice;
		scanf_s("%c", &choice);

		switch (choice) {
		case 'n':
			choice_node = choice_node->rlink;
			if (head->rlink == head) {
				printf("과일이 없지요. \n");
				break;
			}
			else if(choice_node == head) 
				choice_node = choice_node->rlink;
			
			printf("오른쪽으로 이동\n");
			break;
		case 'p':
			choice_node = choice_node->llink;
			if (head->llink == head) {
				printf("과일이 없습니다. \n");
				break;
			}
			else if (choice_node == head)
				choice_node = choice_node->llink;
			

			printf("왼쪽으로 이동\n");
			break;
		case 'd':
			if (choice_node == head) {
				printf("과일을 다시 선택하여 주십시오\n");
			}else {
				printf("과일을 삭제합니다.\n ");
				choice_node = head;
				head = ddelete(choice_node, choice_node->rlink);
			}break;
		case 'i':
			printf("추가할 과일을 입력해 주십시오 : ");
			scanf_s("%s", fruit, MAX_string);
			dinsert(head, fruit);
			break;
		case 'o':
			print_dlist(head, choice_node);
			break;

		case 'e': printf("프로그램을 종료합니다. ");
			free(fruit);
			free(head);
			return 0;
		default: printf("잘못된 입력입니다. \n");

		}
		choice = getchar();
	}
}
