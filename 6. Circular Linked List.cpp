#include <stdio.h>
#include <stdlib.h>

typedef struct CNode {
    int data;
    struct CNode *next;
} CNode;

CNode* push_front(CNode* head, int val){
    CNode* n=(CNode*)malloc(sizeof(CNode)); n->data=val;
    if (!head){ n->next=n; return n; }
    CNode* tail=head; while (tail->next!=head) tail=tail->next;
    n->next=head; tail->next=n; return n;
}
void traverse(CNode* head){
    if (!head){ printf("\n"); return; }
    CNode* p=head;
    do { printf("%d ", p->data); p=p->next; } while (p!=head);
    printf("\n");
}
CNode* insert_after(CNode* head, CNode* pos, int val){
    if (!pos) return head;
    CNode* n=(CNode*)malloc(sizeof(CNode)); n->data=val;
    n->next=pos->next; pos->next=n; return head;
}
CNode* delete_node(CNode* head, CNode* target){
    if (!head || !target) return head;
    if (head==target && head->next==head){ free(target); return NULL; }
    CNode* prev=head; while (prev->next!=target && prev->next!=head) prev=prev->next;
    if (prev->next==target){
        prev->next=target->next;
        if (target==head) head=target->next;
        free(target);
    }
    return head;
}

int main(){
    CNode* head=NULL;
    head=push_front(head,3);
    head=push_front(head,2);
    head=push_front(head,1);
    traverse(head);
    insert_after(head, head->next, 99);
    traverse(head);
    head=delete_node(head, head->next);
    traverse(head);

    // free all
    while (head){
        CNode* next=head->next;
        head=delete_node(head, head);
        if (head && head==next) break;
    }
    return 0;
}
