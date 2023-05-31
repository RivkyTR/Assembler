#include "utils.h"
#include "first_transition.h"

/*in first trans we get the lines of the source file and sorting them to a few types:
a instruction sentence that begins with a label
an instruction sentence that doesn'r begin with a label
a guide sentence
or extarenal or entry declare sentence
each type is send diffrently to continue the process*/
void first_trans(table * dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit,node **headIns,labelTable ** datLabel,FILE **fileRead,int * index)
{
	char line[MAX_LENGTH_SENTENCE+1];
	int typeSentence;
	
	/*reset the next values */
	(*headIns)=NULL;
	(index)[IC]=0;
	(index)[DC]=0;
	(index)[DATA_LABELS]=0;
	(index)[ENTRY_LABELS]=0;
	(index)[EXTERN_LABELS]=0;
	
	
	while(fgets(line,MAX_LENGTH_SENTENCE+1,*fileRead))/*RUN ON THE FILE*/
	{
		char first_word[MAX_LENGTH_SENTENCE];/*the first word of senece*/
		int i=0,j=0;
		int counter_comma=0,index_after_label,index_after_entry_or_exit;
		
		numLine++;
		
		/*check if comment line*/
		if(line[0]==';')
			continue;
		
		/*check if the sentence is more than 80 chars */
		if(strlen(line)>=MAX_LENGTH_SENTENCE )
		{
			if(line[(MAX_LENGTH_SENTENCE-1)]!='\n')
			{
				char next;
				int newline=0;
				printf("%s.am: In line %d: error - more then 80 chars in a line\n",file1,numLine);
				mistake=1;
				while ((next = (fgetc((*fileRead)))))
				{
					if((next=='\n') || (feof(*fileRead)))
					{
						newline=1;
						break;
					}
				}
				if(newline)
					continue;
			}
		}
		
		/*take of the line break character*/
		if(line[strlen(line)-2]=='\n')
			line[strlen(line)-2] = '\0';
		
		
		i=0;
		/*check if there is a comma at the beginning of a line*/
		CHECK_COMMAS
		if(counter_comma)
		{
			mistake=1;
			printf("%s.am: In line %d: error - %d comma before sentence\n",file1,numLine,counter_comma);
		}
		else if(line[i]=='\0' || feof(*fileRead)/*==EOF*/)/*empty sentence*/
			continue;
		
		/*the next loop enters the first sequence of characters excluding commas  into 'first_word'*/
		for(i=i; line[i]!='\0' && !isspace(line[i]) && line[i]!=','; i++)
			first_word[j++]=line[i];
		first_word[j]='\0';
		
		
		/*'index_after_label'  and  'index_after_entry_or_exit' holds the position of the character after the end of the first word*/
		index_after_label=i;
		index_after_entry_or_exit=i;
		
		
		/*the function 'typeLine' will return into typeSentence whitch type:
		 instruction label,entry or external ,data label or line without label*/
		typeSentence=typeLine(line,first_word,i);/* "typeLine" is in this file below*/
		
		if(typeSentence==DATA_LABEL)
			getData(dataTable,Entry,Exit, headIns,datLabel,line, first_word, index_after_label,index);/*"getData" in "guidanceSentence.c"*/
		
		else if(typeSentence==INSTRUCTION_LABEL)
		{
				addInstructionLabel(Exit, headIns,datLabel, first_word,index);/* "addInstructionLabel" is in "convert_to_binary.c"*/
				getInstructin(insTable,line,index_after_label,index);/*"getInstruction" in "instructionSentence.c"*/
		}
		
		else if(typeSentence==ENTRY_EXTERNAL)
			entry_exit(Entry,Exit,headIns,datLabel,line,first_word,index_after_entry_or_exit,index);/*"entry_exit" is "entry_exut.c"*/

		/*if it is an instruction sentence without a label in the beginning we send zero to the the function, because the operation is the first word of the sentence*/
		else if(typeSentence==INSTRUCTION)
			getInstructin(insTable, line, 0, index);/*"getInstruction" in "instructionSentence.c"*/
		
	}
	
	/*updates the addresses of the data labels and the data table, after we finished to enter all of the instruction data to the to the appropriate arrays, and we know what is the final value of IC */
	updateddresses(dataTable,datLabel,index);/* "updateddresses" is in "updateOrPrint.c"*/

}






/*this method gets the first word if the line and the location where the first word finished'
	it checks and sorts which type of treatment we should give her. treatments:
	entry or extern
	label of data
	label of instruction (after him there is an instruction)
	or just an instruction(without label)  */
int typeLine(char * line, char * firstWord, int indexAfterFirstWord)
{
	int lengthFirstWord=strlen(firstWord);
	int i= indexAfterFirstWord;
	/* the first char of the firstWord begins with point*/
	if(firstWord[0]=='.')
	{
		if(!strcmp(".entry",firstWord) || !strcmp(".extern",firstWord))
			return ENTRY_EXTERNAL;
		else if(!strcmp(".data",firstWord) || !strcmp(".struct",firstWord) || !strcmp(".string",firstWord))
			return DATA_LABEL;
	}
	
	/*if last char finishes with ':' --> label*/
	if(firstWord[lengthFirstWord-1]==':')
	{
			firstWord[lengthFirstWord-1]='\0';/*take of the ':' char*/
		
			/*checking if the label is legal*/
			if(!labelIsLagel(firstWord,"label",".am"))/*labelIsLagel" in "checking.c"*/
				mistake=1;
		
			/*we skip spaces and commas, (we'll handle quotation errors later)*/
			for(i=i;line[i]!='\0' && (isspace(line[i]) || line[i]==','); i++);
			
			/*if the first letter after the label is a point, than it like the first char of ".data" ".struct" ".string" ".entry" ".extern"*/
			if(line[i]=='.')
				return DATA_LABEL;
		
			/*else it an instruction lebel*/
			return INSTRUCTION_LABEL;
	}	
	/*if it is not ENTRY_EXTERNAL,	DATA_LABEL, INSTRUCTION_LABEL than it's an INSTRUCTION(without a label) */
	return INSTRUCTION;
}
