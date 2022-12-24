#include "scanner.h"
#include "AST.h"
#include "generator.h"
#include "data.h"

/*
    ASM Compiler
*/

static int free_registers[4];
static char *register_list[4] = { "%r8", "%r9", "%r10", "%r11" };

void free_all_registers(void) {
    free_registers[0] = free_registers[1] = free_registers[2] = free_registers[3] = 1; 
}

static int alloc_register(void) {
    for (int i = 0; i < 4; i++) {
        if (free_registers[i]) {
            free_registers[i] = 0;
            return (i);
        }
    }

    fprintf(stderr, "ERROR: Out of registers\n");
    exit(1);
}

static void free_register(int reg) {
    if (free_registers[reg] != 0) {
        fprintf(stderr, "ERROR: Can't free register %d\n", reg);
        exit(1);
    }

    free_registers[reg] = 1;
}

void cg_preamble() {
    free_all_registers();
    fputs(
        "\t.text\n"
        ".LC0:\n"
        "\t.string\t\"%d\\n\"\n"
        "printint:\n"
        "\tpushq\t%rbp\n"
        "\tmovq\t%rsp, %rbp\n"
        "\tsubq\t$16, %rsp\n"
        "\tmovl\t%edi, -4(%rbp)\n"
        "\tmovl\t-4(%rbp), %eax\n"
        "\tmovl\t%eax, %esi\n"
        "\tleaq	.LC0(%rip), %rdi\n"
        "\tmovl	$0, %eax\n"
        "\tcall	printf@PLT\n"
        "\tnop\n"
        "\tleave\n"
        "\tret\n"
        "\n"
        "\t.globl\tmain\n"
        "\t.type\tmain, @function\n"
        "main:\n"
        "\tpushq\t%rbp\n"
        "\tmovq	%rsp, %rbp\n",
        Outfile
    );
}

void cg_postamble() {
    fputs(
	    "\tmovl	$0, %eax\n"
	    "\tpopq	%rbp\n"
	    "\tret\n",
        Outfile
    );
}

int cg_load(int value) {
    int r = alloc_register();
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, register_list[r]);

    return (r);
}

int cg_add(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", register_list[r1], register_list[r2]);
    free_register(r1);
    
    return (r2);
}

int cg_subtract(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", register_list[r2], register_list[r1]);
    free_register(r2);

    return (r1);
}

int cg_multiply(int r1, int r2) {
    fprintf(Outfile, "\timulq\t%s, %s\n", register_list[r1], register_list[r2]);
    free_register(r1);

    return (r2);
}

int cg_divide(int r1, int r2) {
    fprintf(Outfile, "\tmovq\t%s,%%rax\n", register_list[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", register_list[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", register_list[r1]);
    free_register(r2);

    return (r1);
}

void cg_printInt(int r) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", register_list[r]);
    fprintf(Outfile, "\tcall\tprintint\n");

    free_register(r);
}

int AST_generateASM(struct AST_Node* n) {
    int left_register, right_register;

    if (n->left) left_register = AST_generateASM(n->left);
    if (n->right) right_register = AST_generateASM(n->right);

    switch (n->op) {
        case A_ADD:
            return (cg_add(left_register, right_register));
        case A_SUBTRACT:
            return (cg_subtract(left_register, right_register));
        case A_MULTIPLY:
            return (cg_multiply(left_register, right_register));
        case A_DIVIDE:
            return (cg_divide(left_register, right_register));
        case A_INTLIT:
            return (cg_load(n->intValue));
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}

void generateCode(struct AST_Node* n) {
    int curr_register;

    cg_preamble();
    curr_register = AST_generateASM(n);
    cg_printInt(curr_register);
    cg_postamble();
}