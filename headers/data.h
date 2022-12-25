#ifndef DATA_H
#define DATA_H

#ifndef extern_
    #define extern_ extern
#endif

#define TEXTLEN         512

extern_ int             Line;
extern_ int             Putback;
extern_ FILE            *Infile;
extern_ FILE            *Outfile;
extern_ struct Token    Token;
extern_ char            Text[TEXTLEN + 1];

#endif