#include "utils.h"
#include "instructionSen.h"

/*This function gets a sentence, Decodes the line and then
enters the instruction sentence in the instruction table(insTable).
and enters the label(if there is) nto instruction labels.
gets a sentence and the index before the operation name*/

void getInstructin(table *insTable,char *line,int indexBeforeOperation,int * index)
{
	/*"j" is to enter to "nameofins"from the sentence, "i" is the current index,t is to cunt tht the operation name is not more than 3 charecters, "operation" holds the opcode of the operation*/
	int j=0,i=indexBeforeOperation,counter_comma=0,t=0,index_after_instruction_name,operation;
	char nameofins[OPERATION_LENGTH+1];
	
	/************begins checking mistakes-commas before command************/
	CHECK_COMMAS
	if(counter_comma && indexBeforeOperation!=0){/*it means that we had a lebel before so "indexBeforeOperation"is zero*/
		mistake=1;
		printf("%s.am: In line %d: error - %d comma before the operation name\n",file1,numLine,counter_comma);
	}
	if(line[i]=='\0')
	{
		mistake=1;
		printf("%s.am: In line %d: error - empty label\n",file1,numLine);
	}
	/************finished checking comma mistakes************/
	else/*if the line didnt finish ==> the label is not empty*/
	{
		/*enter into nameofins the sequence of numbers until 3 charecters(the operations names are 3 charcters long) */
		for(i=i;line[i]!='\0' && line[i]!=',' && t++<OPERATION_LENGTH;i++)
			nameofins[j++]=line[i];
		nameofins[j]='\0';
	
		/* "index_after_instruction_name"  holds the position of the character after the end of the command*/
		index_after_instruction_name=i;
	
		/*if the char after instruction is not space or comma --> instruction is more then 3 chars -->There is no such command*/
		if(!isspace(line[index_after_instruction_name]) && line[index_after_instruction_name]!=',' && line[index_after_instruction_name]!='\0')
		{
			printf("%s.am: In line %d: error - no such operation\n",file1,numLine);
			mistake=1;
		}
	
		else
		{
			operation=typeOperation(nameofins);/*"typeoperation" is in this file below*/
			if((14<=operation && operation<=15) )
				withoutOperands(insTable,line,nameofins,index_after_instruction_name,operation,index);/*"withoutOperands" is in this file below*/
			
			else if((4<=operation && operation<=13) && operation!=6)
				command1operand(insTable,line,nameofins,index_after_instruction_name,operation,index);/*"command1operand" is in this file below*/
			
			else if((0<=operation && operation<=3) || operation==6)
				command2operands(insTable,line,nameofins,index_after_instruction_name,operation,index);/*"command2operands" is in this file below*/
			
			else
			{
				mistake=1;
				printf("%s.am: In line %d: error - no such operation\n",file1,numLine);
			}
		}
	}	
}




/*this function gets a name of operation and returns his opcode
if undeined returns a number which is bigger than the biggest opcode*/
int typeOperation(char * command)
{
	int numOp;
	char operations[NUM_OPERATIONS][4]={"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt"};

	for(numOp=0; numOp<NUM_OPERATIONS; numOp++)
		if(!strcmp(command,operations[numOp]))
			return numOp;
	return numOp+1;
}
	


	

/*this function handles wuth instruction sentences thet their operation is without operands
it code the operation.
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/

void withoutOperands(table *insTable,char *line,char *nameMethod,int index_after_instruction_name,int num_opcode,int * index)
{
	int i,counter_comma;

	i=index_after_instruction_name;
	
	/************begins checking mistakes-commas or data  after instruction************/
	CHECK_COMMAS
	if(line[i]=='\0' && counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the operation name\n",file1,numLine,counter_comma);
	}
	if(line[i]!='\0'){
		mistake=1;
		printf("%s.am: In line %d: error - extra data after the operation name\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	enterFullTableInstruction(insTable,NO_STRUCT,"..",index,ENCODING_INSTRUCTION,ABSOLUTE,0,0,num_opcode);/* "enterFullTableInstruction"is in "convert_to_binary.c"*/
}






/*this function handles with instruction sentences thet their operation handles with 1 operand
it code the operation.
send the operand to a another functions on order to code the operand
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/

void command1operand(table *insTable,char *line,char *nameMethod,int index_after_instruction_name,int num_opcode,int * index)
{
	/*"oprnd" is the operand, "typeaddress"-is which type of operand is this*/
	char oprnd[MAX_LENGTH_SENTENCE];
	int i,typeAddress,j=0,counter_comma=0;
	
	
	i=index_after_instruction_name;
	
	/************begins checking mistakes-commas after command************/
	CHECK_COMMAS
	if(counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the operation name\n",file1,numLine,counter_comma);
	}
	/************finished checking mistakes************/
	
	/* the loop inserts a sequence of charecters excluding commas into oprnd*/
	for(i=i;line[i]!='\0' && line[i]!=',' && !isspace(line[i]);i++)
		oprnd[j++]=line[i];
	oprnd[j]='\0';
	
	/************begins checking mistakes-more than 1 comma or missing a comma after first operand************/
	CHECK_COMMAS
	if(line[i]=='\0' && counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the operand\n",file1,numLine,counter_comma);
	}
	if(line[i]!='\0'){
		mistake=1;
		printf("%s.am: In line %d: error - extra data after the operand\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	/* function "findType" will put in "typeAddress" the type of operand: 0-immidiate, 1-label, 2-struct, 3-register */
	typeAddress=findType(oprnd);/*"findType" is in "prepares_to_conversion.c"*/
	
	/*coding the first line*/
	enterFullTableInstruction(insTable,NO_STRUCT,"..",index,ENCODING_INSTRUCTION,ABSOLUTE,typeAddress,0,num_opcode);/* "enterFullTableInstruction" is in "convert_to_binary.c"*/

	/*Checking whether the addressing method is valid for the target operand of the various instructions*/
	if(typeAddress!=IMMEDIATE_ADDRESS || (typeAddress==IMMEDIATE_ADDRESS && !strcmp(nameMethod,"prn")))
	{
		if(typeAddress==DIRECT_REGISTER_ADDRESS)
			/*"putTable" gets data from this function and code it to the instruction table, it is in "prepares_to_conversion.c"*/
			putTable(insTable,oprnd,TARGET_REGISTER,index);/*we send to the function TARGET_REGISTER because it is a target register and we encode it differently from source register*/
		else
			putTable(insTable,oprnd,typeAddress,index);
	}
	else
	{
		mistake=1;
		printf("%s.am: In line %d: error-  the addressing method is illegal\n",file1,numLine);
	}
}








/*this function handles with instruction sentences that their operation handles with 2 operands
it code the operation.
send the operands to a another functions on order to code the operands
gets the instruction sentence, the operation's name , the index after the operation, and the opcode of the operation*/

void command2operands(table *insTable, char *line,char *nameMethod,int index_after_instruction_name,int num_opcode,int *index)
{
	/*typeFirstOp", "typeSecondOp" is the type of the 2 operands, "firstOp" "secondOp" is the operands*/
	int i,j,counter_comma,typeFirstOp,typeSecondOp;
	char firstOp[MAX_LENGTH_SENTENCE],secondOp[MAX_LENGTH_SENTENCE];
		
	i=index_after_instruction_name;
	
	
	/************begins checking mistakes-commas before first operand************/
	CHECK_COMMAS
	if(counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the operation name\n",file1,numLine,counter_comma);}
	/************finished checking mistakes************/
	
	/* the loop inserts a sequence of charecters excluding commas into firstOp*/
	for(j=0,i=i; line[i]!='\0' && !isspace(line[i]) && line[i]!=',';i++)
		firstOp[j++]=line[i];
	firstOp[j]='\0';


	/************begins checking mistakes-more than 1 comma or missing a comma after first operand************/
	CHECK_COMMAS
	if(counter_comma==0 && line[i]=='\0'){
		mistake=1;
		printf("%s.am: In line %d: error - missing a comma after the first operand and the second operand\n",file1,numLine);
	}
	else if(counter_comma==0){
		mistake=1;
		printf("%s.am: In line %d: error - missing a comma after the first operand\n",file1,numLine);
	}
	else if(counter_comma!=1){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the first operand\n",file1,numLine,counter_comma);
	}
	/************finished checking mistakes************/	
		
	/* the loop inserts a sequence of charecters excluding commas into secondOp*/
	for(j=0,i=i; line[i]!='\0' && !isspace(line[i]) && line[i]!=',' ;i++)
		secondOp[j++]=line[i];
	secondOp[j]='\0';
	
	
	/************begins checking mistakes-commas or data after instruction************/
	CHECK_COMMAS
	if(line[i]=='\0' && counter_comma)
	{
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the second operand\n",file1,numLine,counter_comma);
	}
	if(line[i]!='\0')
	{
		mistake=1;
		printf("%s.am: In line %d: error - extra data after the second operand\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	
	/* function "findType" will put in "typeAddress" the type of the operands: 0-immidiate, 1-label, 2-struct, 3-register */
	typeFirstOp=findType(firstOp);/*"findType" in "prepares_to_conversion.c"*/
	typeSecondOp=findType(secondOp);/*"findType" in "prepares_to_conversion.c"*/
	
	/*coding the first word*/
	enterFullTableInstruction(insTable,NO_STRUCT,"..",index,ENCODING_INSTRUCTION,ABSOLUTE,typeSecondOp,typeFirstOp,num_opcode);/*"enterFullTableInstruction" is in "convert_to_binary.c"*/
	
	/*Checking whether the addressing method is valid for the source operand and the target operand of the various instructions*/
	if( ( typeSecondOp!=IMMEDIATE_ADDRESS ||  	(typeSecondOp==IMMEDIATE_ADDRESS && (!strcmp(nameMethod,"cmp") || !strcmp(nameMethod,"prn") ))) 
		&& (strcmp(nameMethod,"lea") || (!strcmp(nameMethod,"lea") && typeFirstOp!=IMMEDIATE_ADDRESS && typeFirstOp!=DIRECT_REGISTER_ADDRESS)))
	{
		/*if both operands are registers we will encode them in 1 word instead of 2, so we need a specific treatment for this option*/
		if(typeFirstOp==DIRECT_REGISTER_ADDRESS && typeSecondOp==DIRECT_REGISTER_ADDRESS)
		{
			bothRegisters(insTable,firstOp,secondOp,index); /*"bothRegisters" is in "prepares_to_conversion.c"*/
		}
		else
		{
			/*"putTable" gets data from this function and code it to the instruction table. it is in "prepares_to_conversion.c"*/
			putTable(insTable,firstOp,typeFirstOp,index);
			/*we send to the function TARGET_REGISTER because it is a target register and we encode it differently from source register*/
			if(typeSecondOp==DIRECT_REGISTER_ADDRESS)
				putTable(insTable,secondOp,TARGET_REGISTER,index);
			else
				putTable(insTable,secondOp,typeSecondOp,index);
		}
	}
	else/*if the addressing method is not valid for the source operand or the target operand of the various instructions*/
	{
		mistake=1;
		printf("%s.am: In line %d: error - the addressing method is illegal\n",file1,numLine);
	}
}
