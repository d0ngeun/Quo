#ifndef DATA_H
#define DATA_H

#ifndef extern_
    #define extern_ extern
#endif

#define TEXTLEN         512
#define NSYMBOLS        1024

extern_ int             Line;
extern_ int             Putback;
extern_ FILE            *Infile;
extern_ FILE            *Outfile;
extern_ struct Token    Token;
extern_ char            Text[TEXTLEN + 1];
extern_ struct symtable Gsym[NSYMBOLS];

#endif