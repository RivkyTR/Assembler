#include "utils.h"
#include "memory.h"

/*in this file we have methods who get data and enters them to the right place in the memory*/






/*This function receives values in a different number each time
And she insert the coded values into the instruction table.
There are many types of coding,
And each type of addressing method needs a different coding, by a different division of ten bits.
The method accepts in variable 'numOfFields' the number of parts into which the ten bits of "typeWord" should be divided.
And according to this it also receives a different number of values for income, a value for type, and the value for the name(if doesn't need a name will be entered "..").
If 'numOfFields'=SAVE_PLACE_FOR_ADDRESS=0 then the ten bits should be divided in 1
If 'numOfFields'=ENCODING_DATA=1 then the ten bits should be divided in 1
If 'numOfFields'=ENCODING_ADDRESS_OR_IMMIDIATE=2 then the ten bits should be divided in 2 (8,2 bytes)
If 'numOfFields'=ENCODING_REGISTER=3 then the ten bits should be divided in 3 (4,4,2 bytes)
If 'numOfFields'=ENCODING_INSTRUCTION=4 then the ten bits should be divided in 4 (4,2,2,2 bytes)
 */
void enterFullTableInstruction(table *insTable,int type,char * name,int *index,int numOfFields,...)
{
	va_list p;/*opening with p the values that are not written in the functions name */
	switch(numOfFields){
	
	case(SAVE_PLACE_FOR_ADDRESS):
		strcpy((insTable)[index[IC]].name,name);
		(insTable)[index[IC]].addr=index[IC]+100;
		(insTable)[index[IC]].typeWord.d.d1=0;
		(insTable)[index[IC]].typeLabel=type;
		(insTable)[index[IC]].linenumber=numLine;
		index[IC]+=1;
		break;
	
	case(ENCODING_DATA):
		va_start(p,numOfFields);
		strcpy((insTable)[index[IC]].name,name);
		(insTable)[index[IC]].addr=index[IC]+100;
		(insTable)[index[IC]].typeWord.d.d1=va_arg(p,int);
		(insTable)[index[IC]].typeLabel=type;
		(insTable)[index[IC]].linenumber=numLine;
		index[IC]+=1;
		va_end(p);
		break;
	
	case(ENCODING_ADDRESS_OR_IMMIDIATE):
		va_start(p,numOfFields);
		strcpy((insTable)[index[IC]].name,name);
		(insTable)[index[IC]].typeWord.c.c1=va_arg(p,int);
		(insTable)[index[IC]].typeWord.c.c2=va_arg(p,int);
		(insTable)[index[IC]].typeLabel=type;
		(insTable)[index[IC]].addr=index[IC]+100;
		(insTable)[index[IC]].linenumber=numLine;
		index[IC]+=1;
		va_end(p);
		break;
	
	case(ENCODING_REGISTER):
		va_start(p,numOfFields);
		strcpy((insTable)[index[IC]].name,name);
		(insTable)[index[IC]].typeWord.b.b1=va_arg(p,int);
		(insTable)[index[IC]].typeWord.b.b2=va_arg(p,int);
		(insTable)[index[IC]].typeWord.b.b3=va_arg(p,int);
		(insTable)[index[IC]].addr=index[IC]+100;
		(insTable)[index[IC]].linenumber=numLine;
		index[IC]+=1;
		va_end(p);
		break;
	
	case(ENCODING_INSTRUCTION):
		va_start(p,numOfFields);
		strcpy((insTable)[index[IC]].name,name);
		(insTable)[index[IC]].typeWord.a.a1=va_arg(p,int);
		(insTable)[index[IC]].typeWord.a.a2=va_arg(p,int);
		(insTable)[index[IC]].typeWord.a.a3=va_arg(p,int);
		(insTable)[index[IC]].typeWord.a.a4=va_arg(p,int);
		(insTable)[index[IC]].typeLabel=type;
		(insTable)[index[IC]].addr=index[IC]+100;
		(insTable)[index[IC]].linenumber=numLine;
		index[IC]+=1;
		va_end(p);
		break;
	}
}



/*This function gets a name of label-opcode (if it's not a call to a label, then put ".." )
and a numerical value and it  insert them into the data table*/
void enterFullTableData(table *dataTable,char * name,int number,int *index)
{
	strcpy((dataTable)[index[DC]].name,"..");
	(dataTable)[index[DC]].addr=index[DC];
	(dataTable)[index[DC]].typeWord.d.d1=number;
	index[DC]+=1;
}






/*this function creats a new place in the array which was send as a parameter to the function(the arrays would be Entry or Exit,)
and in this place it enters the label,
 it checks before entering the label: the label is legal,not definet,not declared
 if the array is Extern- checks if label is not already defined*/
void addTo_Entry_External(ex_en ** Entry, ex_en ** Exit,  node **headIns,labelTable **datLabel,ex_en ** labels, char * label, int *placeToPut,int * index)
{
	int k;/*the counter that will run in the Entry labels*/
	
	/*if the label is declared as entry*/
	for(k=0;k<index[ENTRY_LABELS];k++)
		if(!strcmp(label,(*Entry)[k].name))
			break;
	if(k!=index[ENTRY_LABELS])/*it means that we had to broke (break) the loop */
	{
		mistake=1;
		printf("%s.am: In line %d: error - the label is already declared as entry\n",file1,numLine);
	}
	/*if the label is illegal*/		
	else if(!labelIsLagel(label,"label",".am"))/* "labelIsLagel" from "checking.c"*/
	{
		mistake=1;
	}
	/*if the label is defined*/
	else if(Exit==labels && checkIfDefinedLabel(Exit,headIns, datLabel, label,index))/* "checkIfDefinedLabel" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error - tring to declare as external a label whitch is already defined\n",file1,numLine);
	}
	/*if the label is declared as extern*/
	else if(checkIfDefinedExtern(Exit,label,index))/* "checkIfDefinedExtern" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error - the label is already declared as external\n",file1,numLine);
	}
	else
	{
		if(*placeToPut)/*if we have more than 1 label already declared than we need to increase the array*/
		{
			ex_en *p;
			p=(ex_en*)realloc((*labels),(*placeToPut+1)*sizeof(ex_en));
			if(!p)
			{
				printf("%s.am: error the realloc failed",file1);
				exit(0);
			}
			(*labels)=p;
		}
			
			strcpy((*labels)[*placeToPut].name,label);
			(*labels)[*placeToPut].linenumber=numLine;
			(*placeToPut)++;
		
	}
}







/*this function creats a new place in the array of data labels
and in this place it enters the label, and the type of label(DATA,STRING or STRUCT)
checks before entered: if defined already or declared as extern*/
void addDataLabel(ex_en ** Exit,node ** headIns, labelTable ** datLabel, char * label,int kindOfData, int *numofdataLabels,int * index)
{
	/*if the label is defined*/
	if(checkIfDefinedLabel(Exit, headIns, datLabel, label,index))/* "checkIfDefinedLabel" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error- the label is already defined\n",file1,numLine);
	}
	/*if the label is declared as extern*/
	else if(checkIfDefinedExtern(Exit,label,index))/* "checkIfDefinedExtern" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error- tring to define a label which is already declared as external\n",file1,numLine);
	}
	else
	{
		if((*numofdataLabels))/*if we have already a label we need to increase by one*/
		{
			labelTable *p;
			p=(labelTable*)realloc((*datLabel),(*numofdataLabels+1)*sizeof(labelTable));
			if(!p)
			{
				printf("%s.am: error the realloc failed",file1);
				exit(0);
			}
			(*datLabel)=p;
		}
		
		strcpy((*datLabel)[*numofdataLabels].name,label);
		(*datLabel)[*numofdataLabels].address=index[DC];
		(*datLabel)[*numofdataLabels].typ=kindOfData;
		(*numofdataLabels)++;
		
	}
}








/*this function creats a new node in the list of instruction labels,
and in this place it enters the label
checks before entered: if defined already or declared as extern*/		
void addInstructionLabel(ex_en ** Exit, node **headIns,labelTable **datLabel, char * label,int *index)
{
	node * h=*headIns;/*h is to run on the instruction labels until  we find the last label to enter the new label*/
	node * new_node;/*the new label*/
	
	/*checking of the label was not already defined, running on the labels and if we find a label which is the same as the label we want to enter we stop, and then we check if we had to stop immidle*/
	
	if(checkIfDefinedLabel(Exit, headIns,datLabel, label,index))/* "checkIfDefinedLabel" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error- the label is already defined\n",file1,numLine);
	}
	else if(checkIfDefinedExtern(Exit,label,index))/* "checkIfDefinedExtern" from "checking.c"*/
	{
		mistake=1;
		printf("%s.am: In line %d: error- the label is already declared as extern\n",file1,numLine);
	}
	else
	{
		new_node= (node *)malloc(sizeof(node));
		if(!new_node)
		{
			printf("%s.am: error malloc failed",file1);
			exit(0);
		} 
		strcpy(new_node->name,label);
		new_node->address=index[IC]+100;
		new_node->next=NULL;
		
		h = *headIns;
		if((*headIns)==NULL)
		{
			(*headIns) = new_node;
		}
		else
		{
			while(h->next!=NULL)
				h=(node *)h->next;
			
			h->next = (ptr)new_node;
		}	
	}
}
