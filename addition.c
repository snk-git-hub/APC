    /*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function perform addition (Dlist** head1, Dlist** tail1, Dlist** head2, Dlist** tail2, Dlist** headR) -> intforms addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include <stdlib.h>

#include "apc.h"

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR)
{
	/* Definition goes here */
    int carry=0;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	Dlist *tempR = *headR;

	while (temp1!=NULL || temp2!=NULL) {
		int d1 =(temp1!=NULL) ? (temp1)->data -'0': 0;
		int d2 =(temp2!=NULL) ? (temp2)->data -'0': 0;
		int sum = d1 +d2+carry;
		int ans = sum%10;
		carry = sum/10;

		Dlist *new_node = (Dlist *) malloc(sizeof(Dlist));
		if (new_node == NULL) {
			return FAILURE;
		}

		new_node->data = ans+'0';
		new_node->prev = NULL;
		new_node->next = tempR;

		if (tempR!=NULL) {
			tempR->prev = new_node;
		}
		tempR=new_node;



		if (temp1 != NULL) temp1 =  temp1->prev;
		if (temp2 != NULL) temp2 =  temp2->prev;

	}
	if (carry>0) {

		Dlist *new_node = (Dlist *) malloc(sizeof(Dlist));
		if (new_node == NULL) {
			return FAILURE;
		}
		new_node->data = carry+'0';
		new_node->prev = NULL;
		new_node->next = tempR;
		if (tempR!=NULL) {
			tempR->prev = new_node;
		}
		tempR=new_node;
	}
	*headR = tempR;
	return 0;

}
