#include "../headers/common.h"

/*
    Abstract Syntax Tree
*/

//General Node
struct AST_Node* AST_CreateNode(int op, struct AST_Node* left, struct AST_Node* right, int intValue) {
    struct AST_Node* n;

    n = (struct AST_Node*) malloc(sizeof(struct AST_Node));
    if (n == NULL) {
        fprintf(stderr, "ERROR: No Memory Space: AST_CreateNode.\n");
        exit(1);
    }

    n->op = op;
    n->left = left;
    n->right = right;
    n->intValue = intValue;

    return (n);
}

//Leaf Node
struct AST_Node* AST_CreateLeaf(int op, int intValue) {
    return (AST_CreateNode(op, NULL, NULL, intValue));
}

//One child Node
struct AST_Node* AST_CreateUnary(int op, struct AST_Node* left, int intValue) {
    return (AST_CreateNode(op, left, NULL, intValue));
}