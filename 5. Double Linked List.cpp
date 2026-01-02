#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev, *next;
} Node;

Node* push_front(Node* head, int val){
    Node* n=(Node*)malloc(sizeof(Node)); n->data=val; n->prev=NULL; n->next=head;
    if (head) head->prev=n;
    return n;
}
Node* insert_after(Node* head, Node* pos, int val){
    if (!pos) return head;
    Node* n=(Node*)malloc(sizeof(Node)); n->data=val;
    n->next=pos->next; n->prev=pos;
    if (pos->next) pos->next->prev=n;
    pos->next=n;
    return head;
}
Node* delete_node(Node* head, Node* target){
    if (!target) return head;
    if (target->prev) target->prev->next=target->next;
    else head=target->next;
    if (target->next) target->next->prev=target->prev;
    free(target);
    return head;
}
void traverse_forward(Node* head){
    for (Node* p=head;p;p=p->next) printf("%d ", p->data);
    printf("\n");
}
void traverse_backward(Node* head){
    Node* tail=head; while (tail && tail->next) tail=tail->next;
    for (Node* p=tail;p;p=p->prev) printf("%d ", p->data);
    printf("\n");
}

int main(){
    Node* head=NULL;
    head=push_front(head,3);
    head=push_front(head,2);
    head=push_front(head,1); // list: 1 2 3
    traverse_forward(head);

    insert_after(head, head->next, 99); // after 2 -> 99
    traverse_forward(head);

    head=delete_node(head, head->next); // delete node 2
    traverse_forward(head);
    traverse_backward(head);

    // free all
    while (head) head=delete_node(head, head);
    return 0;
}
