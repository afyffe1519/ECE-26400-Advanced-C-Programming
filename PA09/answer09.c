#include "answer09.h"

bool isCircular(const node_t * head)
{
	const node_t * slow = head;
	const node_t * fast = head;

	while(slow && fast && fast -> next)
	{
		slow = slow -> next;
		fast = fast -> next -> next;
		if(slow == fast)
		{
			return true;
		}
	}
	return false;
}
