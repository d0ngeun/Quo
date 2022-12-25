#include "../headers/common.h"
/*
    PRATT Parser
*/

static int Op_Prec_Levels[] = { 0, 10, 10, 20, 20, 0 };
//                             EOF, +,  -, *,  /, INTLIT 

static int Op_Precedence(int tokenType) {
    int prec = Op_Prec_Levels[tokenType];
    if (prec == 0) {
        fprintf(stderr, "ERROR: Syntax error: %d Token: %d\n", Line, tokenType);
        exit(1);
    }

    return (prec);
}

static struct AST_Node* primary(void) {
    struct AST_Node* n;

    switch(Token.token) {
        case T_INTLIT:
            n = AST_CreateLeaf(A_INTLIT, Token.intValue);
            scan(&Token);
            return (n);
        default:
            fprintf(stderr, "ERROR: Incorrect Syntax: %d\n", Line);
            exit(1);
    }
}

int TokenToAST(int token) {
    switch(token) {
        case T_PLUS:
            return (A_ADD);
        case T_MINUS:
            return (A_SUBTRACT);
        case T_STAR:
            return (A_MULTIPLY);
        case T_SLASH:
            return (A_DIVIDE);
        default:
            fprintf(stderr, "ERROR: Unknown Token: TokenToAST : %d.\n", Line);
            exit(1);
    }
}

struct AST_Node* binary_expr(int prevTokPrec) {
    struct AST_Node* n, *left, *right;
    int tokenType;

    left = primary();

    tokenType = Token.token;
    if (tokenType == T_SEMI)
        return (left);

    while (Op_Precedence(tokenType) > prevTokPrec) {
        scan(&Token);
        right = binary_expr(Op_Prec_Levels[tokenType]);
        left = AST_CreateNode(TokenToAST(tokenType), left, right, 0);
        tokenType = Token.token;

        if (tokenType == T_SEMI)
            return (left);
    }

    return (left);
}