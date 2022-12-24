#include "scanner.h"
#include "AST.h"
#include "data.h"

/*
    C Interpreter
*/

//operators
static char *AST_op[] = { "+", "-", "*", "/" };

int interpretAST(struct AST_Node* n) {
    int leftval, rightval;

    if (n->left) {
        leftval = interpretAST(n->left);
    }
    if (n->right) {
        rightval = interpretAST(n->right);
    }

    if (n->op == A_INTLIT) {
        printf("int %d\n", n->intValue);
    }
    else {
        printf("%d %s %d\n", leftval, AST_op[n->op], rightval);
    }

    //interprets the code into c
    switch(n->op) {
        case A_ADD:
            return (leftval + rightval);
        case A_SUBTRACT:
            return (leftval - rightval);
        case A_MULTIPLY:
            return (leftval * rightval);
        case A_DIVIDE:  
            return (leftval / rightval);
        case A_INTLIT:
            return (n->intValue);
        default:
            fprintf(stderr, "ERROR: Unknown AST operator %d\n", n->op);
            exit(1);
    }
}