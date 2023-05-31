
#include "utils.h"
#include "main.h"


int main(int argc, char * argv[]){
	int j=0;
	while(++j<argc)
	{
		char nameAS[MAX_LENGTH_SENTENCE];/* here will be the name of the file we want to open to spread macros*/
		char nameAM[MAX_LENGTH_SENTENCE];/* here will be the name of the file we want to open to make first and second transition */

		/*this will be the pointer to the file we go to read from*/
		FILE *fileRead;
		
		/*This array contains the encoded data segment */
		table dataTable[MAX_LINES_IN_PROGRAM];
		
		/*This array contains the encoded instructions segment */
		table  insTable[MAX_LINES_IN_PROGRAM];
		
		/*This array contains the labels defined as entry*/
		ex_en * Entry;
		
		/*This array contains the labels defined as external*/
		ex_en *Exit;
		
		/*This node contains the head of the linked list of information labels*/
		node * headIns=NULL;
		
		/*the array that holds the data labels*/
		labelTable * datLabel;
		
		node * h=headIns;/* h is to run later on a loop to free the dinamic  memory*/
		
		/*this array contains the number of nodes or members in the different arrays.
		the first place is for IC- uncoded instruction lines
		the second place is for DC - uncoded data lines
		the second place is for DATA_LABELS - it is the number of data labels
		the second place is for ENTRY_LABELS - it is the number of labels which were declared as entry
		the second place is for EXTERN_LABELS - it is the number of labels which were declared as external
		enum index{IC,DC,DATA_LABELS,ENTRY_LABELS,EXTERN_LABELS};*/
		int  index[]={0,0,0,0,0};/*we reset then into zero*/
		
	/*file1 is the current file*/
		strcpy(file1,argv[j]);
		
	/*we create for every one 1 member, in order to dint have problems by free it, if we will not use it*/
		datLabel=(labelTable*)malloc(sizeof(labelTable));
		if(!datLabel)
		{
			printf("%s.am: error the malloc failed",file1);
			exit(0);
		}
		
		Entry=(ex_en*)malloc(sizeof(ex_en));
		if(!Entry)
		{
			printf("%s.am: error the malloc failed",file1);
			exit(0);
		}
		
		Exit=(ex_en*)malloc(sizeof(ex_en));
		if(!Exit)
		{
			printf("%s.am: error the malloc failed",file1);
			exit(0);
		}
		
	/*At the beginning of the processing of each file, everything will be reset */
		mistake=numLine=0;
	
	/*open the source file*/
		fileRead=fopen(strcat(strcpy(nameAS,argv[j]),".as"),"r");
		if(!fileRead)
		{
			printf("ERROR - not exist %s.as",file1);
			continue;
		}
		
	/*spreading macros*/
		enter_macro(argv[j],&fileRead);
		
	/*open the filw eithout macros*/
		fileRead=fopen(strcat(strcpy(nameAM,argv[j]),".am"),"r");
		if(!fileRead)
		{
			printf("ERROR - not exist %s.am",file1);
			continue;
		}
	/*we go to a new file so we reset the linenumber*/
		numLine=0;
		
	/*the first transition gets in "first_transition.c" the sentences from the file and sort them:
	if get a guide sentence send the  sentence to a function in "guidanceSentence.c"
	if get a instruction sentence send the sentence to a function in "instructioSentence.c"
	if get an enter or extern sentence send the sentence to a fiunction in "entry_or_extern_sentence.c"
	each from "guidanceSentence.c",  instructioSentence.c","entry_or_extern_sentence.c" is responsible to code the sentence he got
	he could use the "convert_to_binary.c" "updateOrPrint.c" "checking.c" and "sentToMemory.c"*/
		if(!mistake)
			first_trans(dataTable,insTable,&Entry,&Exit,&headIns,&datLabel,&fileRead,index);
		fclose(fileRead);
	
	/*the second transition "trans.c" goes over the tables and uopdates the opperand-labels
	he use the "updateOrPrint.c""*/
		if(!mistake)
			second_trans(dataTable,insTable,&Entry,&Exit,&headIns,&datLabel,argv[j],index);
		
		
	/*freeing memory*/	
			free(Entry);
			free(Exit);
			free(datLabel);
		while(h!=NULL){
			node * p=h;
			h=(node *)h->next;
			free(p);
		}
		
	}
	
	return 0;
}

