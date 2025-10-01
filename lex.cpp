#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <string.h>

// Global Array of Keywords (Obsolete)
char keywords[][6] = {"begin", "call", "const", "do", "else", "end", "even", "fi", "if", "proc", "read", "then", "var", "while", "write"};


int a;

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

struct Lexeme {
    const char* Lexeme;
    TokenType Token;
}Lexeme;

// Tuple or dictionary like struct for comparing. Seperating all of the types of listed tokens and attaching their enums to them
struct Lexeme keywordTable[] = {
    {"begin", beginsym}, {"end", endsym}, {"if", ifsym},
    {"fi", fisym}, {"then", thensym}, {"while", whilesym},
    {"do", dosym}, {"call", callsym}, {"const", constsym},
    {"var", varsym}, {"procedure", procsym}, {"write", writesym},
    {"read", readsym}, {"else", elsesym}, {"even", evensym}
};

struct Lexeme operatorTable[] = {
    {"+", plussym}, {"-", minussym}, {"*", multsym}, {"/", slashsym}, {"=", eqsym}, {"<>", neqsym}, {"<", lessym}, {"<=", leqsym},
    {">", gtrsym}, {">=", geqsym}
};

struct Lexeme symbolTable[] = {
    {"(", lparentsym}, {")", rparentsym},{",", commasym}, {";", semicolonsym}, {".", periodsym}, {":=", becomessym}
};


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

int COMMENT_FLAG = 0; // Marks for comments and multilined comments

void addToTokenList(struct Lexeme lexemearray[], int* tokenCount, TokenType type, const char* value) {
    
    
    
    lexemearray[*tokenCount].Token = type;
    lexemearray[*tokenCount].Lexeme = value;
    *tokenCount++;
    return;
}

void parser(char* line, struct Lexeme *token_List){
    char c;
    // Reads through each character. Will need logic to address spaces, newlines, and return carraige. and to identify when it runs into a different type of token
    
    char token[30];
    int walker = 0;

    // Flag to identify which possibilites are left per check of a token. Will be used to identify what is possible for proper error checking
    int Identifier_flag = 0;
    int Keyword_flag = 0;
    int OP_flag = 0;
    int Punct_flag = 0;
    int Constant_flag = 0;

    // Length Limit
    int identifier_character_count = 0; // Identifiter names should not go past 11 characters
    int constant_check = 0; // Numbers should not go past 5 digits
    TokenType s;
    int i = 0, j = 0; // Will be used with the token array.
    
    int len = strlen(line);
	// Scans through the line character by character
    while (i < len) {

        char character = line[i];
        if (((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z')) && COMMENT_FLAG == 0) {
            char character = line[i];
            // Need to check if the previous was a number to seperate the tokens and flush the token array
            if (line[i - 1] >= '0' && line[i - 1] <= '9') {
                s = numbersym;
                printf("%-8.8s %d\n", token, numbersym);
                j = 0;
                token[j] = '\0';
                constant_check = 0;

                
            }

            token[j] = character;
            token[j + 1] = '\0';
            i++, j++;
            Identifier_flag = 1;
            identifier_character_count++; // Should not go past 11 characters
            if (token[0] != '\0' && i == len) {
                if (identifier_character_count < 11) {
                    s = identsym;
                    printf("%-8.8s %d\n", token, identsym);
                }
                else {
                    printf("%-8.8s identifier too long\n", token);
                }
            }
        }

        // Symbols Marks the end of a token and the start of a new one
        else if ((line[i] == ',' || line[i] == ' ' || line[i] == ';' || line[i] == '\n' || (line[i] == ':' && line[i+1] == '=') || line[i] == '.') && COMMENT_FLAG == 0) {
            
            
            // Start of symbol token, print the current token status and flush the token array.
            char character = line[i];

            // If the next symbol is an assignment operator
            if (line[i] == ':' && line[i + 1] == '=') {
                token[j] = ':';
                token[j + 1] = '=';
                token[j + 2] = '\0';
                i += 2;
                
            }

            // Check to see what symbol
            for (int k = 0; k < 6; k++) {
                if (strcmp(token, symbolTable[k].Lexeme) == 0) {
                    //If successful a keyword has been hit and we break at the end and we find out which keyword has been hit.
                    s = symbolTable[k].Token;
                    printf("%-8.8s %d\n", symbolTable[k].Lexeme, symbolTable[k].Token);
                    Keyword_flag = 1;
                    Identifier_flag = 0;
                    break;
                }
            }


            for (int k = 0; k < 15; k++) {
                if (strcmp(token, keywordTable[k].Lexeme) == 0) {
                    //If successful a keyword has been hit and we break at the end and we find out which keyword has been hit.
                    printf("%-8.8s %d\n", keywordTable[k].Lexeme, keywordTable[k].Token);
                    Keyword_flag = 1;
                    Identifier_flag = 0;
                    break;
                }
            }

            if (Identifier_flag == 1 && identifier_character_count < 11) {
                s = identsym;
                printf("%-8.8s %d\n", token, identsym);
            }
            else if (Identifier_flag == 1) {
                s = skipsym;
                printf("%-8.8s Identifier too long\n", token);
            }
            if (Constant_flag == 1 && constant_check < 6) {
                s = numbersym;
                printf("%-8.8s %d\n", token, numbersym);
            }
            else if (Constant_flag == 1) {
                s = skipsym;
                printf("%-8.8s Number too long\n", token);

            }

            j = 0;
            token[j] = line[i];
            token[j + 1] = '\0'; // Strcmp would not work properly without this at the end for comparing.
            
            
            
            // Check to see what symbol
            for (int k = 0; k < 6; k++) {
                if (strcmp(token, symbolTable[k].Lexeme) == 0) {
                    //If successful a keyword has been hit and we break at the end and we find out which keyword has been hit.
                    s = symbolTable[k].Token;
                    printf("%-8.8s %d\n", symbolTable[k].Lexeme, symbolTable[k].Token);
                    Punct_flag = 1;
                    Identifier_flag = 0;
                    break;
                }
            }

            

            // End of token. Count resets to 0 identifier and constant
            Identifier_flag = 0;
            Keyword_flag = 0;
            Punct_flag = 0;
            Constant_flag = 0;

            identifier_character_count = 0;
            constant_check = 0;

            token[0] = '\0';
            i++;
            j = 0;

            continue;
        }
        else if ((line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == '<' || line[i] == '>' || line[i] == '<=' || line[i] == '>=') || COMMENT_FLAG == 1) {
            
            // Operation to handle comments
            if ((line[i] == '/' && line[i + 1] == '*' && COMMENT_FLAG == 0) || COMMENT_FLAG == 1) {
                COMMENT_FLAG = 1;
                if (line[i] == '*' && line[i + 1] == '/') {
                    COMMENT_FLAG = 0; // Marks the end of the comment line
                    i++;
                }
                i++;
                continue;
            }

            // Start of operator token, print the current token status and flush the token array.
            j = 0;
            
            if (Identifier_flag == 1) {
                s = identsym;
                printf("%-8.8s %d\n", token, identsym);
            }
            else if (Identifier_flag == 1 && identifier_character_count > 11) {
                s = skipsym;
                printf("%-8.8s Identifier too long\n", token);
            }
            if (Constant_flag == 1 && constant_check < 6) {
                s = numbersym;
                printf("%-8.8s %d\n", token, numbersym);
            }
            else if (Constant_flag == 1) {
                s = skipsym;
                printf("'%-8.8s' Number too long\n", token);

            }

           
            token[j] = line[i];
            token[j + 1] = '\0'; // Strcmp would not work if we did not add this at the end.


            for (int k = 0; k < 10; k++) {
                if (strcmp(token, operatorTable[k].Lexeme) == 0) {
                    //If successful a operator has been hit and we break at the end and we find out which keyword has been hit.
                    printf("%-8.8s %d\n", operatorTable[k].Lexeme, operatorTable[k].Token);
                    break;
                }
            }

            // End of token. Count resets to 0 identifier and constant
            identifier_character_count = 0;
            constant_check = 0;
            token[0] = '\0';
            i++;
            j = 0;
        }
        
        else if ((line[i] >= '0' && line[i] <= '9') && constant_check < 6) {
             constant_check++;
             Constant_flag = 1;
             token[j] = line[i];
             token[j + 1] = '\0';
             i++, j++;
             if (token[0] != '\0' && i == len) {
               if (constant_check < 6) {
                  printf("%-8.8s %d\n", token, numbersym);
               }
               else {
                  printf("%-8.8s number too long\n", token);
                    }
             }
        }
        

        // If its not a symbol, identifier/keyword, operator, then its a constant
        else {
			// Invalid Symbol Found
            // If the token has not been cleaned before the invalid symbol print the token and flush the token array
            if (Identifier_flag == 1 && identifier_character_count < 11) {
                printf("%-8.8s %d\n", token, identsym);
            }
            else if (Identifier_flag == 1) {
                printf("%-8.8s Identifier too long\n", token);
			}
            if (Constant_flag == 1 && constant_check < 6) {
                printf("%-8.8s %d\n", token, numbersym);
            }
            else if (Constant_flag == 1) {
                printf("%-8.8s Number too long\n", token);
            }
            j = 0;
            token[j] = line[i];
            token[j + 1] = '\0'; // Strcmp would not work properly without this at the end for comparing.
            printf("%-8.8s Invalid symbol\n", token);
            i++;
            j = 0;
            // End of token. Count resets to 0 identifier and constant
            Identifier_flag = 0;
            Keyword_flag = 0;
            Punct_flag = 0;
            Constant_flag = 0;
            identifier_character_count = 0;
            constant_check = 0;
            token[0] = '\0';
			continue;
        }
        
		
        
        //addToTokenList(token_List, &walker, s, token);
    }
}

int main(int argc, char *argv[])
{

    // Opens the file
    FILE* fp = fopen("input3.txt", "r");

    // Stops if it could not find it
    if (fp == NULL) {
        printf("File could not be found\n");
        exit(0);
    }
    char line[30];

    printf("Source Program:\n\n");
    while (fgets(line, 30, fp) != NULL) {
        printf(line);
    }
    rewind(fp);

    printf("\n\nLexeme Table:\n\n");
    
    
    printf("lexeme   token type\n");
    struct Lexeme lexemearray[500];
    // fscanf reads through the file word by word. I can see it doing regular syntax well for our purpose. But, "a+b;begin;a,c,c,;" like this might falter
    // fgetc reads through the file by character. We can be able to circumvent the other issue above with it. but will have to find logic to ignore spaces, newlines, and return carriage. Update i couldnt think of a logic for fgetc that would handle comments
    // fgets reads through the file line by line but will have to seperate it by character. might be more work than its worth.
    
    // This is probably the dummest way we can do what i am thinking of in my head.
    while ((fgets(line, sizeof(line), fp) != NULL)) {
        parser(line, lexemearray);
    }
    

    

    return 0;
}

