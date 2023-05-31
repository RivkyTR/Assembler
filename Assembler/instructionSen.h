#define CHECK_COMMAS\
	counter_comma=0;\
		while(line[i]!='\0'){\
			for(i=i;line[i]!='\0' && isspace(line[i]);i++);\
			if(line[i]==',')\
				counter_comma++;\
			else\
				break;\
			i++;\
		}

#define NUM_OPERATIONS 16

/*This function gets a sentence, Decodes the line and then
enters the instruction sentence in the instruction table(insTable).
and enters the label(if there is) nto instruction labels.
gets a sentence and the index before the operation name*/

void getInstructin(table *insTable,char *line,int indexBeforeOperation,int * index);



/*this function handles wuth instruction sentences thet their operation is without operands
it code the operation.
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/
void withoutOperands(table *insTable, char *s,char *nameMethod,int k,int num_opcode,int * index);


/*this function handles with instruction sentences thet their operation handles with 1 operand
it code the operation.
send the operand to a another functions on order to code the operand
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/
void command1operand(table *insTable, char *s,char *nameMethod,int k,int num_opcode,int * index);


/*this function handles with instruction sentences that their operation handles with 2 operands
it code the operation.
send the operands to a another functions on order to code the operands
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/
void command2operands(table *insTable,  char *s,char *nameMethod,int k,int num_opcode,int * index);


/*This function gets data and enter it to the instruction table(insTable)
'numOfFields' is the number of the separate data we want to enter in the field of unsTable.typeword
(according to the kind of data is the type of union we will take by the field typeword)*/
void enterFullTableInstruction(table *insTable, int type,char * name,int * index,int numOfFields,...);

/*gets the operand and returns which type it is(register,immidiate,label,struct)*/
int findType(char * operand);

/*'putTable' gets the operand and which type it is and occording to this he send it to 'enterFullTableInstruction' to enter it in th instruction table*/
void putTable (table *insTable, char * operand,int type,int * index);


/*this function handles to code in 1 word both registers, and then send it to 'enterFullTableInstruction' to put it in the table*/
void bothRegisters(table *insTable, char * operand1,char * operand2,int * index);


/*this function gets a name of operation and returns his opcode
if undeined returns a number which is bigger than the biggest opcode*/
int typeOperation(char * command);




