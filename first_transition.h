#define CHECK_COMMAS\
	counter_comma=0;\
		while(line[i]!='\0' && line[i]!=EOF){\
			for(i=i; line[i]!='\0' && isspace(line[i]) && line[i]!=EOF;i++);\
			if(line[i]==',')\
				counter_comma++;\
			else\
				break;\
			i++;\
		}
		
		
		/*in first trans we get the lines of the source file and sorting them to a few types:
a instruction sentence that begins with a label
an instruction sentence that doesn'r begin with a label
a guide sentence
or extarenal or entry declare sentence
each type is send diffrently to continue the process*/
void first_trans(table * dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit,node **headIns,labelTable ** datLabel,FILE **fileRead,int * index);


/*this functiom returns if it is a guide sentence, entry or external sentence, or instruction sentence that begins wih a label or without,
gets a sentence, the first word in the sentence and the index after the end of the first word
returns which type of sentence*/
int typeLine(char * s,char*c,int i);


/*This function enters the instruction sentence in the instruction table(insTable).
gets a sentence and the index before the operation name*/
void getInstructin(table *insTable, char *s,int ,int * index);


/*This function gets a label, checks if it is legal and enters it into the instruction labels
gets the label*/
void addInstructionLabel(ex_en ** Exit,node ** headIns,labelTable **datLabel,char * label,int * index);


/*This function enters the guide sentence into the data table(dataTable) 
gets a sentence, the label of the data,and the index after the label name*/
void getData(table *dataTable,ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable ** datLabel,char * s,char *c,int i,int * index);


/*by the end of the first transition after we know what is IC it updates the address of data labels and the addresses of the data table. */
void updateddresses(table *dataTable, labelTable **datLabel, int * index);


/*This function gets a entry or extern sentence, type of label(entry or extern), and the index after the type data
end enters to the exit or entry labels  */
void entry_exit(ex_en ** Entry,ex_en ** Exit,node **headIns,labelTable ** datLabel,char *s, char *c,int k,int * index);


/*this function checks if the label is not the same as saved elements of assembly or not valid name*/
int labelIsLagel(char * label,char * kind, char * ending);
