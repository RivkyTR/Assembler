#include "utils.h"
#include "second_transition.h"
#include "memory.h"



/*this function go through the tables and updates tha addresses of the operand labels
checks if all labels which were declared as entry were defined*/
void second_trans(table *dataTable,table *insTable,ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable **datLabel,char * nameFile,int *index)
{
	int i=0,j;
	char nameEXT[MAX_LENGTH_SENTENCE];/*name for file externals*/
	char nameENT[MAX_LENGTH_SENTENCE];/*name for file entries*/
	char nameOB[MAX_LENGTH_SENTENCE];/*name for object file*/

	
	/*preparing names for the files*/
	strcat(strcpy(nameEXT,nameFile),".ext");
	strcat(strcpy(nameENT,nameFile),".ent");
	strcat(strcpy(nameOB,nameFile),".ob");
	


/*checking if the labels which were declared as entry labels are defined in the labels*/
	for(j=0; j<index[ENTRY_LABELS]; j++)
	{
		int addressOfLabel=checkIfDefinedLabel(Exit,headIns, datLabel, (*Entry)[j].name, index);/* "checkIfDefinedLabel" is from "checking.c" - returns address of label if find*/
		if(addressOfLabel)
		{
			(*Entry)[j].address=addressOfLabel;
		}
		else
		{
						
			mistake=1;
			printf("%s.am: In line %d: error - the label was declared as entry but not defined\n",file1,(*Entry)[j].linenumber);
			break;
		}
	}
	
	/*we run over the table to update the addresses that we know just now after the first transition */                                 
	for(i=0;i<index[IC];i++)
	{
		if(strcmp((insTable)[i].name,".."))/*if it not compare to ".."-->it's a label*/
			/* "updateAdressAcordingLabels" returns RELOCATABLE if it finds the label and updated it in "print_to_files.c"*/
			if(updateAdressAcordingLabels(insTable,headIns,datLabel,(insTable)[i].name,i,index)!=RELOCATABLE)
				/*if the label we search was not in the labels we look for it in the externals it in "print_to_files.c"*/
				if( updateAdressAcordingExternal(insTable,Exit,(insTable)[i].name,i,index)!=EXTERNL)
				{
					mistake=1;
					printf("%s.am: In line %d: error - the label-operand is not defined\n",file1,insTable[i].linenumber);
				}
	}

	
	if(!mistake)
		printToFiles(dataTable,insTable,Entry,Exit,nameOB,nameENT,nameEXT,index); /* "printTofiles" is in "print_to_files.c"*/
}



/*this function gets a label and the place who we need to put the address of the label
and looks for the address of the label by the instruction labels and data lebels.
checks if the struct operand label is not defined as instruction label
returns 2(RELOCATABLE) if ssuceed find the adress of the label, otherwise 0*/
int updateAdressAcordingLabels(table * insTable,node **headIns,labelTable ** datLabel, char *label, int locationToPutAddress,int * index)
{
	int k=0;/*k to run on the data labels*/
	node * h=*headIns;/*h to run on the instruction labels*/
	
	/*going through the instructions labels*/
	while(h!=NULL){
		if(!strcmp(label,h->name))
		{
			/* if we called the operand like a struct but his label is an instruction label (and not data) it's Obviously not a struct*/
			if ((insTable)[locationToPutAddress].typeLabel==STRUCT)
			{
				mistake=1;
				printf("%s.am: In line %d: error - the operand-struct-label is not a declared as a struct\n",file1,(insTable)[locationToPutAddress].linenumber);
			}
			(insTable)[locationToPutAddress].typeWord.c.c1=RELOCATABLE;
			(insTable)[locationToPutAddress].typeWord.c.c2=h->address;
			return RELOCATABLE;
		}
		h=(node *)h->next;
	}
	/*going through the data labels*/	
	for(k=0;k<index[DATA_LABELS];k++)
	{
		if(!strcmp(label,(*datLabel)[k].name))
		{
		/*if the operand is a struct bot is label us not declared as a strucr-error*/
			if((insTable)[locationToPutAddress].typeLabel==STRUCT)
				if((*datLabel)[k].typ!=STRUCT)
				{
					mistake=1;
					printf("%s.am: In line %d: error - the operand-struct-label is not a declared as a struct\n",file1,(insTable)[locationToPutAddress].linenumber);
				}
			(insTable)[locationToPutAddress].typeWord.c.c1=RELOCATABLE;
			(insTable)[locationToPutAddress].typeWord.c.c2= (*datLabel)[k].address;
			return RELOCATABLE;
		}
	}
	return 0;
}




/*this function gets a label and the place who we need to put the address of the label
 looks for the address of the label by the external labels.
 prints to file of externals the name of the label and which address used it.
returns 1(EXTERNL) if ssuceed find the address of the label, otherwise 0*/
int updateAdressAcordingExternal(table *insTable,ex_en ** Exit,char *label,int locationToPutAddress,int *index)
{
	int k=0;
	for(k=0 ; k<index[EXTERN_LABELS] ; k++)
		if(!strcmp(label,(*Exit)[k].name)){
			(insTable)[locationToPutAddress].typeWord.c.c1=EXTERNL;
			(insTable)[locationToPutAddress].typeWord.c.c2=0;
			return EXTERNL;
		}
	return 0;
}




/*this function updates the addresses of the data labels and data table,
after the first transition when we know what is the final value of IC*/
void updateddresses(table *dataTable,labelTable **datLabel,int * index)
{
	int i;
	
	/*we increase every one by the counter of instructions(IC) and 100 because the addresses begin from 100*/
	for(i=0;i<index[DATA_LABELS];i++)
		(*datLabel)[i].address+=index[IC]+100;
	for(i=0;i<index[DC];i++)
		(dataTable)[i].addr+=index[IC]+100;
}