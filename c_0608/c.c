#include <stdio.h>
#include <stdlib.h>

#define MAX_string 20
typedef char* element;
typedef struct DListNode {	// ���߿��� ��� Ÿ��
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;
// ���� ���� ����Ʈ�� �ʱ�ȭ
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
		
		printf("�޴�\n n) ���� ����\n p) ���� ����\n d) ���� ���� ����\n i) ���� ���� ������ ���� �߰�\n o) ���� ����Ʈ ���(���� ���õ� ���Ͽ��� ��������[O] ���)\n e) ���α׷� ���� : ");
		char choice;
		scanf_s("%c", &choice);

		switch (choice) {
		case 'n':
			choice_node = choice_node->rlink;
			if (head->rlink == head) {
				printf("������ ������. \n");
				break;
			}
			else if(choice_node == head) 
				choice_node = choice_node->rlink;
			
			printf("���������� �̵�\n");
			break;
		case 'p':
			choice_node = choice_node->llink;
			if (head->llink == head) {
				printf("������ �����ϴ�. \n");
				break;
			}
			else if (choice_node == head)
				choice_node = choice_node->llink;
			

			printf("�������� �̵�\n");
			break;
		case 'd':
			if (choice_node == head) {
				printf("������ �ٽ� �����Ͽ� �ֽʽÿ�\n");
			}else {
				printf("������ �����մϴ�.\n ");
				choice_node = head;
				head = ddelete(choice_node, choice_node->rlink);
			}break;
		case 'i':
			printf("�߰��� ������ �Է��� �ֽʽÿ� : ");
			scanf_s("%s", fruit, MAX_string);
			dinsert(head, fruit);
			break;
		case 'o':
			print_dlist(head, choice_node);
			break;

		case 'e': printf("���α׷��� �����մϴ�. ");
			free(fruit);
			free(head);
			return 0;
		default: printf("�߸��� �Է��Դϴ�. \n");

		}
		choice = getchar();
	}
}
