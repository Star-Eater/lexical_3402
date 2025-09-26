#define _CRT_SECURE_NO_WARNINGS


#include <iostream>

typedef enum {
    skipsym = 1, // Skip / ignore token
    identsym, // Identifier
    numbersym, // Number
    plussym, // +
    minussym, // -
    multsym, // *
    slashsym, // /
    eqsym, // =
    neqsym, // <>
    lessym, // <
    leqsym, // <=
    gtrsym, // >
    geqsym, // >=
    lparentsym, // (
    rparentsym, // )
    commasym, // ,
    semicolonsym, // ;
    periodsym, // .
    becomessym, // :=
    beginsym, // begin
    endsym, // end
    ifsym, // if
    fisym, // fi
    thensym, // then
    whilesym, // while
    dosym, // do
    callsym, // call
    constsym, // const
    varsym, // var
    procsym, // procedure
    writesym, // write
    readsym, // read
    elsesym, // else
    evensym // even
} TokenType;

/*
Lexical Error Reporting
The lexical analyzer must detect and report lexical errors, but does not need to report
grammar errors, syntax errors, or semantic errors. Your program should scan through the
entire input program and report all lexical errors encountered. The following three types of
lexical errors must be detected:
    1. Identifier too long: Identifiers exceeding 11 characters
    2. Number too long: Numbers exceeding 5 digits
    3. Invalid symbols: Characters that are not part of the PL/0 language specification
    
    Error Reporting Strategy: Your program should continue scanning through the entire
                              source program even after encountering lexical errors, collecting all errors before reporting
                              them. This allows the user to see all lexical issues in a single run rather than having to fix
                              errors one at a time.
                              For examples of lexical error detection and reporting, see Appendix B which demonstrates
                              input files containing lexical errors and their corresponding error output.
*/


/*
    Possible Procedure(s):
        Scan through all at once:
            As we go through the input file. We make a lexeme table at the start whether that be a 2D, 1D array, none at all.

            Array Method: 

            No Array Method:
                We scan through the input file. Create a function to check each symbol and print the following lexeme associated with its token type in the list above. Any errors with the lexeme will have an appropriate 
                error name in the token type column (shown below). For how it runs it...

                Error Example:

                    Source Program :
                        begin
                        x := 123456;
                        end .

                    Lexeme Table :

                        lexeme | token type
                               |
                        begin  | 20
                               |
                        x      | 2
                               |
                        :=     | 19
                               |
                        123456 | Number too long
                               |
                        ;      | 17
                               |
                        end    | 21
                               |
                        .      | 18

                        Token List :

                            20 2 x 19 1 17 21 18
*/

/*
    Character Description
        Space Space character (ignored)
        Tab Horizontal tab (ignored)
        Newline Line feed character (ignored)
        Carriage Return Carriage return character (ignored)
*/


/*
    Psuedocode:
        
        Begin:
            While scannning file:
                Check its char up until space or punctuation:
                    If the end is a punctuation:
                        ',' = the following have to be either an identifer or a constant
                        ';' = the following can be a keyword
                        check to see if any enums are triggered
                    If space is encountered:
                        Check to see if any enums are triggered.
                    Keywords "begin" and "end" do not need identifers following
                    
                    


*/

void parser() {

}

int main(int argc, char *argv[])
{

    // Opens the file
    FILE* fp = fopen("input.txt", "r");

    // Stops if it could not find it
    if (fp == NULL) {
        printf("File could not be found\n");
        exit(0);
    }
    char line[30];

    while (fgets(line, 30, fp) != NULL) {
        printf(line);
    }
    
    


    return 0;
}

