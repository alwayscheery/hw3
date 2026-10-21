#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node*& head, Node*& smaller, Node*& larger, int pivot)
{
    // Base case: empty list
    if (head == NULL)
    {
        smaller = NULL;
        larger = NULL;
        return;
    }

    // Remove the first node from head
    Node* current = head;
    head = head->next;

    // Recursively split the remaining list
    Node* restSmaller;
    Node* restLarger;
    llpivot(head, restSmaller, restLarger, pivot);

    // Put the current node at the front of the correct list
    if (current->val <= pivot)
    {
        current->next = restSmaller;
        smaller = current;
        larger = restLarger;
    }
    else
    {
        current->next = restLarger;
        larger = current;
        smaller = restSmaller;
    }
}

