#include "scanner.h"
#include "AST.h"
#include "generator.h"
#include "statements.h"
#include "data.h"

void match(int t, char* what) {
    if (Token.token == t) {
        scan(&Token);
    }
    else {
        printf("ERROR: %s expected on line %d\n", what, Line);
        exit(1);
    }
}

void semi(void) {
    match(T_SEMI, ";");
}

void statements(void) {
    struct AST_Node* tree;
    int reg;

    while (1) {
        match(T_PRINT, "write");
        tree = binary_expr(0);
        reg = AST_generateASM(tree);
        cg_printInt(reg);
        free_all_registers();

        semi();
        if (Token.token == T_EOF)
            return;
    }
}