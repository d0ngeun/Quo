#include "scanner.h"
#include "AST.h"
#include "generator.h"
#include "statements.h"
#define extern_
    #include "data.h"
#undef extern_
#include <errno.h>

static void init() {
    Line = 1;
    Putback = '\n';
}

static void usage(char* prog) {
    fprintf(stderr, "Usage: %s infile\n", prog);
    exit(1);
}

void main(int argc, char* argv[]) {
    if (argc != 2) {
        usage(argv[0]);
    }

    init();
    struct AST_Node* n;

    if ((Infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }
    if ((Outfile = fopen("out.s", "w")) == NULL) {
        fprintf(stderr, "Unable to create out.s %s\n", strerror(errno));
        exit(1);
    }

    scan(&Token);
    cg_preamble();
    statements();
    cg_postamble();

    fclose(Outfile);

    system("cc -o out out.s");
    system("./out");

    exit(0);
}