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
		
		
		
		
/*This function gets a guide sentence.
 Decodes the line,
 enters the guide sentence into the data table(dataTable) .
gets a sentence, the label of the data,and the index after the label name*/

void getData(table * dataTable,ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable **datLabel, char * line,char * firstWord,int indexAfterFirstWord,int *index);




/*This function handles with .data
it gets a guide sentence and the index after the type of data(in thus casv the index after '.date' )
and enters the numerical values to the data table*/
void getInt(table *dataTable,char * s,int i,int * index);

/*This function handles with .string
it gets a guide sentence and the index after the type of data(in this case the index after '.string' )
and enters the character values to the data table*/
void getString(table *dataTable,char * s,int i,int * index);

/*This function handles with .struct
it gets a guide sentence and the index after the type of data(in this case the index after '.struct' )
and enters the numeric and character values to the data table*/
void getStruct(table *dataTable,char * s,int i,int * index);

/*This function gets a label and checks if the label was already defined in the instruction ar data lebels or maybe was declares as external label*/ 
int checkIfDefinedLabel(ex_en ** Exit,node ** headIns,labelTable ** datLabel,char *label,int * index);

/*This function handles with '.entry or' '.extern',
it gets a guide sentence, type of label and the  and the index after the type of data(in this case the index after '.entry' or '.extern')
and enters the label to the appropriate labels.*/
void entry_exit(ex_en ** Entry,ex_en ** Exit,node **headIns,labelTable ** datLabel,char *s, char *c,int k,int * index);

/*This function enters a new data lebel to the data labels*/
void addDataLabel(ex_en ** Exit,node ** headIns,labelTable ** datLabel,char * label,int kindOfData,int * numofdataLabels,int * index);

/*This function enters values of type data( '.data', '.string'.'.struct') to the data table
gets the label name and the numeric value to enter,( ehen we have a strung we put the ascii code)*/
void enterFullTableData(table *dataTable,char * name,int numOfField,int * index);
