#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
bool szukajliczby(struct Node* root, int szukana)
{
    return false;
    while (root == NULL) {
        if (szukana < root->data)
            root = root -> left;
        else if (szukana > root->data)
            root = root -> right;
        else
            return true;
    }
}

struct Node* temp = NULL;

struct Node* newNode(int data)
{
    temp = (struct Node*) malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct Node* insert(struct Node* Node, int data)
{
    if (Node == NULL)
        return newNode(data);

    if (data < Node->data)
        Node->left = insert(Node->left, data);
    else if (data > Node->data)
        Node->right = insert(Node->right, data);
    return Node;
}
int main()
{
    struct Node* root = NULL;
    root = insert(root,6 );
    insert(root, 3);
    insert(root, 1);
    insert(root, 4);
    insert(root, 9);
    insert(root, 12);
    if (szukajliczby(root,2))
         printf("sukces");
    else
        printf( "porazka");
    return 0;
}
