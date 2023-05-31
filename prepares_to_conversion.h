/*this file codes values and send them to the methods tha, will enter them to their place*/



#define NUM_REGISTERS 8
#define LENGRH_REGISTERS 3
#define NUMBER_OPERATIONS 16
#define LENGTH_OPRATION 4

/*this file gets data and decode it and send it to methods who handle with the memory*/
/*'putTable' gets the operand and which type it is and occording to this he send it to 'enterFullTableInstruction' to enter it in th instruction table*/
void putTable (table *insTable,char * operand,int type,int * index);


/*this function handles to code in 1 word both registers, and then send it to 'enterFullTableInstruction' to put it in the table*/
void bothRegisters(table *insTable, char * operand1,char * operand2,int * index);



/*the function get an operand,
it return which type is the operand:
0 - immidiate number(begins with '#')
1- label 
2- struct(if contains a '.')
3-register (if it equals one of the registers) */
int findType(char * operand);


/*This function gets data and enter it to the instruction table(insTable)
'numOfFields' is the number of the separate data we want to enter in the field of unsTable.typeword
(according to the kind of data is the type of union we will take by the field typeword)*/
void enterFullTableInstruction(table *insTable,int type,char * name,int * index,int numOfFields,...);

/*This function returns 1 if the 'nameLabel is not a register, but if it is a register - returns 0*/
int label_no_register(char * nameLabel);


/*this function checks if the label is not the same as saved elements of assembly or not valid name*/
int labelIsLagel(char * label,char * kind, char * ending);
