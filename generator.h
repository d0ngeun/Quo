#ifndef GENERATOR_H
#define GENERATOR_H

int AST_generateASM(struct AST_Node* n);
void generateCode(struct AST_Node *n);

void free_all_registers(void);
void cg_preamble();
void cg_postamble();
int cg_load(int value);
int cg_add(int r1, int r2);
int cg_subtract(int r1, int r2);
int cg_multiply(int r1, int r2);
int cg_divide(int r1, int r2);
void cg_printInt(int r);

#endif