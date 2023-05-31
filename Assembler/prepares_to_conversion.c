#include "utils.h"
#include "prepares_to_conversion.h"






/*this file gets data and decode it and send it to methods who handle with the memory*/
/*'putTable' gets the operand and which type it is and occording to this he send it to 'enterFullTableInstruction' to enter it in th instruction table*/
void putTable (table *insTable,char * operand,int type,int * index)
{
	char number[MAX_LENGTH_SENTENCE];
	int i;

	switch(type)
	{
		case(IMMEDIATE_ADDRESS): 
		/*we begin from i=1 to skip the '#'*/
			for(i=1; operand[i]!='\0';i++)
			{
				if((operand[i]>'9' || operand[i]<'0') && !(i==1 &&(operand[i]=='-'  || operand[i]=='+')))
				{
					mistake=1;
					printf("%s.am: In line %d: error - the immidiate is not a number\n",file1,numLine);
					break;
				}
				else
					number[i-1]=operand[i];
			}
			number[i-1]='\0';
			enterFullTableInstruction(insTable,DATA,"..",index,ENCODING_ADDRESS_OR_IMMIDIATE,0,atoi(number));
			break;
		
		
		case(DIRECT_ADDRESS):
			enterFullTableInstruction(insTable,STRING,operand,index,SAVE_PLACE_FOR_ADDRESS);
			break;
		
		
		case(STRUCT_ADDRESS):{
			char *label,*number;
			
			label=strtok(operand,".");
			number=strtok(NULL,"\0");
			if(number==NULL)
			{
				mistake=1;
				break;
			}
			
			/*checking the legacy of the number*/
			if(atoi(number)!=1 && atoi(number)!=2)
			{
				mistake=1;
				printf("%s.am: In line %d: error - the operand is illegal - the immidiate is not 1 or 2\n",file1,numLine);
				break;
			}
			enterFullTableInstruction(insTable,STRUCT,label,index,SAVE_PLACE_FOR_ADDRESS);
			enterFullTableInstruction(insTable,DATA,"..",index,ENCODING_ADDRESS_OR_IMMIDIATE,ABSOLUTE,atoi(number));
			}break;
		
		case(DIRECT_REGISTER_ADDRESS):/*source register*/
			/*we begin from i=1 to skip the character 'r'  */
			for(i=1;operand[i]!='\0';i++)
				number[i-1]=operand[i];
			number[i-1]='\0';
			enterFullTableInstruction(insTable,REGISTER,"..",index,ENCODING_REGISTER,ABSOLUTE,0,atoi(number));
			break;
		
		
		case(TARGET_REGISTER):/*target register*/
		/*we begin from i=1 to skip the character 'r'  */
			for(i=1;operand[i]!='\0';i++)
				number[i-1]=operand[i];
			number[i-1]='\0';
			enterFullTableInstruction(insTable,REGISTER,"..",index,ENCODING_REGISTER,ABSOLUTE,atoi(number),0);
			break;
	}
}






/*this function handles to code in 1 word both registers, and then send it to 'enterFullTableInstruction' to put it in the table*/
void bothRegisters(table *insTable, char * operand1,char * operand2,int * index)
{
		int i=0,numFirstOperand,numSecondOperand;
		char number[MAX_LENGTH_SENTENCE];
	
		/*we begin from i=1 because we skip the 'r' from the registers*/
		/*the loop inserts operand1 excluding the first character into number*/
		for(i=1;operand1[i]!='\0';i++)
			number[i-1]=operand1[i];
			
		numFirstOperand=atoi(number);
		
		/*the loop inserts operand1 excluding the first character into number*/
		for(i=1;operand2[i]!='\0';i++)
			number[i-1]=operand2[i];
		number[i-1]='\0';
		numSecondOperand=atoi(number);
			
		enterFullTableInstruction(insTable,NO_STRUCT,"..",index,ENCODING_REGISTER,0,numSecondOperand,numFirstOperand);
}





/*the function get an operand,
it return which type is the operand:
0 - immidiate number(begins with '#')
1- label 
2- struct(if contains a '.')
3-register (if it equals one of the registers) */
int findType(char * operand)
{
	int i,count_point=0;

	if(operand[0]=='#')
		return IMMEDIATE_ADDRESS;
	
	/* "label_no_register" returns 0 if the operand equals one of the register, so we put also a '!'*/
	else if(!label_no_register(operand))
		return DIRECT_REGISTER_ADDRESS;
	
	/*in the end of the loop in 'count_point' will be the sum of the points from operand*/
	for(i=0; operand[i]!='\0' ;i++)
		count_point+=(operand[i]=='.'?1:0);

	if(count_point>=1)
	{
		char *label,copy_operand[MAX_LENGTH_LABEL];
		strcpy(copy_operand,operand);
		label=strtok(copy_operand,".");
		 /*if the first character is '.'*/
		if(operand[0]=='.')
		{
			mistake=1;
			printf("%s.am: In line %d: error - missing the label in the struct of operand\n",file1,numLine);
		}
		/*if the last character is '.'*/
		else if(operand[strlen(operand)-1]=='.')
		{
			mistake=1;
			printf("%s.am: In line %d: error - missing the number of field in the operand struct\n",file1,numLine);
		}
		else if(!labelIsLagel(label,"label-operand",".am"))
		{
				mistake=1;
		}
		return STRUCT_ADDRESS;
	}
	
	/*So far we haven't exited the function so the only thing left is just a label*/
	if(!labelIsLagel(operand,"label-operand",".am"))
	{
		mistake=1;
	}
	return DIRECT_ADDRESS;
	
}
