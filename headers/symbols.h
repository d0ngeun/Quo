#ifndef SYMBOLS_H
#define SYMBOLS_H

struct symbtable {
    char* name;
};

int findGlob(char* s);
int addGlob(char* name);

#endif