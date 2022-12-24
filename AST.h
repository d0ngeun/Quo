#ifndef AST_H
#define AST_H

enum NodeType {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INTLIT
};

struct AST_Node {
    int op;
    struct AST_Node* left;
    struct AST_Node* right;
    int intValue;
};

//AST.c
struct AST_Node* AST_CreateNode(int op, struct AST_Node* left, struct AST_Node* right, int intValue);
struct AST_Node* AST_CreateLeaf(int op, int intValue);
struct AST_Node* AST_CreateUnary(int op, struct AST_Node* left, int intValue);

//parser.c
struct AST_Node* binary_expr(int tokenType);

//interpreter.c
int interpretAST(struct AST_Node* n);

#endif