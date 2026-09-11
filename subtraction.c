/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include <stdlib.h>

#include "apc.h"

int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR) {
	/* Definition goes here */
	// skipping leading zeros
	Dlist *sig1 = *head1;
	while (sig1->data =='0'&& sig1->next!=NULL) sig1=sig1->next;
	Dlist *sig2 = *head2;
	while (sig2->data =='0'&& sig2->next!=NULL) sig2=sig2->next;

	// calculating length
	int len1 =0;
	for (Dlist *p = sig1;p!=NULL;p=p->next) len1++;
	int len2 =0;
	for (Dlist *p = sig2;p!=NULL;p=p->next) len2++;

	int list2_bigger=0;

	if (len1<len2) {
		list2_bigger =1;
	}else if (len1==len2) {
		Dlist *p1 = sig1,*p2 = sig2;
		while (p1!=NULL){
			if (p1->data>p2->data) {list2_bigger=0;break;}
			if (p1->data<p2->data) {list2_bigger=1;break;}
			p1=p1->next;
			p2=p2->next;
		}
	}
	Dlist *temp1 =list2_bigger? *tail2: *tail1;
	Dlist *temp2 =list2_bigger? *tail1: *tail2;
	Dlist *tempR = NULL;
	int flag = 0;


	while (temp1!=NULL || temp2!=NULL) {
		int d1 = (temp1!=NULL)?(temp1)->data -'0':0;
		int d2 = (temp2!=NULL)?(temp2)->data -'0':0;

		if (flag==1) {
			d1=d1-1;
			flag=0;
		}
		int sub;
		if (d1<d2) {
			flag = 1;
			sub = (d1+10)-d2;
		}else {
			sub = d1-d2;
		}

		// result storing
		Dlist *new_node=(Dlist *)malloc(sizeof(Dlist));
		if (new_node==NULL) {
			return FAILURE;
		}
		new_node->data=sub+'0';
		new_node->prev=NULL;
		new_node->next=tempR;
		if (tempR!=NULL) {
			tempR->prev = new_node;
		}
		tempR= new_node;

		//  move
		if (temp1!=NULL)temp1 = temp1->prev;
		if (temp2!=NULL)temp2 = temp2->prev;
	}



	while (tempR->data=='0'&&tempR->next!=NULL) {
		Dlist *tofree = tempR;
		tempR=tempR->next;
		tempR->prev= NULL;
		free(tofree);
	}

	//////////need to checks/////////////
	if (list2_bigger&& tempR->data!='0') {
		Dlist *sign_node=(Dlist *)malloc(sizeof(Dlist));
		if (sign_node==NULL) {
			return FAILURE;
		}
		sign_node->data= '-';
		sign_node->prev=NULL;
		sign_node->next=tempR;
		tempR->prev=sign_node;
		tempR=sign_node;

	}
	*headR=tempR;
	return SUCCESS;
}