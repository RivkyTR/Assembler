#include "utils.h"
#include "check.h"



/*this function gets a label and checkes if it is not already defined as entry or external
running on tha extern and entry labels,it stop when we find a lebal that is the same as the label we want to enter,
	and then we check if we had to stop imiddle, if yes than the label is already defined
	returns 1 if already defined, otherwise 0*/
int checkIfDeclared(ex_en ** Entry,ex_en ** Exit,char *label,int *index)
{
	int i_for_entry,i_for_exit;/* "i_for_entry" is the counter to run on the Entry loops, "i_for_exit" is to run on the external loops*/
	
	/*running on tha extern and entry labels, we stop when we find a lebal that is the same as the label we want to enter,
	and then we check if we had to stop imiddle, if yes than the label us already declared*/
	
	/*running the extern and entry labels*/
	for(i_for_entry=0 ; i_for_entry<index[ENTRY_LABELS]; i_for_entry++)
		if(!strcmp(label,(*Entry)[i_for_entry].name))
		{
			mistake=1;
			printf("%s.am: In line %d: error - The label has already been defined as entry\n",file1,numLine);
			return 1;
		}

	for(i_for_exit=0; i_for_exit<index[EXTERN_LABELS]; i_for_exit++)
		if(!strcmp(label,(*Exit)[i_for_exit].name))
		{
			mistake=1;
			printf("%s.am: In line %d: error - The label has already been defined as extern\n",file1,numLine);
			return 1;
		}
	return 0;
}





/*this function gets a string(char *)
and checkes if it is not the same as one of the registers.
return 1 if it is not the same as one of the registers' otherwise 0 */
int label_no_register(char * nameLabel)
{
	int i;/*counter to run on the registers array*/
	char rgstr[NUM_REGISTERS][LENGRH_REGISTERS]={"r0","r1","r2","r3","r4","r5","r6","r7"};
	
	for(i=0; i<NUM_REGISTERS; i++)
		if(!strcmp(rgstr[i],nameLabel))
			return 0;
	return 1;
}




/*this function checks if the label is not the same as saved elements of assembly or not valid name or more than 30 characters*/
int labelIsLagel(char * label,char * kind, char * ending)
{
	int i=0;/*counter to run on the operatins array and after that a counter to run an tha labels charecters*/
	char operations[NUMBER_OPERATIONS][LENGTH_OPRATION]={"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rts","hlt"};

	
	for(i=0; i<NUMBER_OPERATIONS;i++)
		if(!strcmp(operations[i],label))
		{
			printf("%s%s: In line %d: error - illegel %s - the %s is a operation name\n",file1,ending,numLine,kind,kind);
			return 0;
		}
	if(!strcmp(label,""))
	{
		printf("%s%s: In line %d: error - a %s is missing\n",file1,ending,numLine,kind);
		return 0;
	}
	
	if(strlen(label)>=MAX_LENGTH_LABEL)
	{
		printf("%s%s: In line %d: error - illegel %s - the %s is more then 30 charecters\n",file1,ending,numLine,kind,kind);
		return 0;
	}
	if(!label_no_register(label))/*"label_no_register" is written in this file "checking.c"*/
	{
		printf("%s%s: In line %d: error - illegel %s - the %s is a register\n",file1,ending,numLine,kind,kind);
		return 0;
	}
	
	if(!(('a'<=label[0] && label[0]<='z' ) || ('A'<=label[0] && label[0]<='Z')))
	{
		printf("%s%s: In line %d: error - illegel %s - the %s does not start with a letter\n",file1,ending,numLine,kind,kind);
		return 0;
	}
	for(i=0; label[i]!='\0';i++)
		if(!(('a'<=label[i] && label[i]<='z' )||('A'<=label[i] && label[i]<='Z')) && !('0'<=label[i] && label[i]<='9'))
		{
			printf("%s%s: In line %d: error - illegel %s - the %s contains charecter that are not letters or numbers\n", file1, ending,numLine, kind, kind);
			return 0;
		}
	if(!strcmp("data",label) || !strcmp("string",label) || !strcmp("struct",label) || !strcmp("entry",label) || !strcmp("extern",label))
	{
		printf("%s%s: In line %d: error - illegel %s - the %s is a seved element of c\n",file1,ending,numLine,kind,kind);
		return 0;
	}
	return 1;
}





/*if the label was declared as external return 1, otherwise zero*/	
int checkIfDefinedExtern(ex_en ** Exit,char *label,int *index)
{
	int k;
	for(k=0;k<index[EXTERN_LABELS];k++)
		if(!strcmp(label,(*Exit)[k].name))
			return 1;
	return 0;
}





/*this function is running on the labels, we stop when we find a lebal that is the same as the label we got from user,
	and then we check if we had to stop in middle, if yes than the label is already defined in the labels
	returns zero if not fefined this label. */
int checkIfDefinedLabel(ex_en ** Exit,node **headIns, labelTable ** datLabel, char *label, int *index){
	node * h=*headIns;
	int k;
	
	/*running on the instruction labels, if find the label return his address */
	while(h!=NULL){
			if(!strcmp(label,h->name))
			{
				if( h->address)
					return  h->address;
				else
					return 1;
			}
			h=(node *)h->next;
	}
	
	/*running on the data labels, if find the label return his address */	
	for(k=0;k<index[DATA_LABELS];k++)
		if(!strcmp(label,(*datLabel)[k].name))
		{
			if( (*datLabel)[k].address)/*if the adddress is not zero return address*/
				return (*datLabel)[k].address;
			else
				return 1;
		}
	
	/*if didnt find the label return zero*/	
	return 0;
}

