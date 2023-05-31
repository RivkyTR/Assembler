

typedef struct{
	char name[MAX_LENGTH_LABEL];/*name of macro*/
	char mac[MAX_LENGTH_SENTENCE*10];/*The contents of the macro 10*81(written maximum 10 lines)*/
} mcr;


/*this function gets a pointer to a file and spread itsmacros into a new file with an ending am*/
void enter_macro(char create[],FILE ** fileRead);


/*this function gets a macro name and creates a new place for the new macro
checks if the macro name is legal and if it is not already exist an the macro's array*/
int add_macro(mcr ** macr,int * numOfMacros,char *nameMacro);


/*this function checks if the label is not the same as saved elements of assembly or not valid name*/
int labelIsLagel(char * label,char * kind, char * ending);
