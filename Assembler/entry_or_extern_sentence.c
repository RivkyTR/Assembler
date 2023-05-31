#include "utils.h"
#include "ent_ext.h"

/*This function gets a entry or extern sentence, type of data(entry or extern), and the index after the type data
end enters the label to the exit labels or entry labels  */

void entry_exit(ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable ** datLabel,char *line, char *type,int indexBeforeLabel,int * index)
{
	char  label[MAX_LENGTH_LABEL];
	int j=0,i=indexBeforeLabel;/* "j" is to enter the label from the sentence to the array "label", i is the current index of the sentence*/
	int counter_comma=0;


	/************begins checking mistakes-commas after .entry or .external************/
	CHECK_COMMAS
	if(counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the type data(.)\n",file1,numLine,counter_comma);
	}
	else if(line[i]=='\0'){
		mistake=1;
		printf("%s.am: In line %d: error - missing label\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	
	/* the loop inserts a sequence of numbers excluding commas into 'lebel'*/
	for (j=0,i=i; line[i]!='\0'&& !isspace(line[i]) && line[i]!=',' && j<(MAX_LENGTH_LABEL-1);i++)
		label[j++]=line[i];
	label[j]='\0';
	
	
	/************begins checking mistakes after the label************/
	CHECK_COMMAS
	if(line[i]=='\0' && counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the label\n",file1,numLine,counter_comma);
	}
	if(line[i]!='\0'){
		mistake=1;
		printf("%s.am: In line %d: error - extra data after the label\n",file1,numLine);
	}
	/************finished checking mistakes************/
	

	if(strcmp(label,""))/*if not empty label*/
	{
		/* the function "checkIfDeclared" is written in "checking.c" , and the function "addTo_Entry_External" is written in "convert_to_binary.c"*/
	
		/*if .entry than we check if the label was already defined as entry or extern, if not than we add the label to the entry labels*/
		if(!strcmp(type,".entry")){
			if(!checkIfDeclared(Entry,Exit,label,index))
				addTo_Entry_External(Entry,Exit,headIns,datLabel,Entry,label,&index[ENTRY_LABELS],index);
		}
	
		/*if .extern than we check if the label was already defined as entry or extern, if not than we add the label to the extern labels*/
		else if(!strcmp(type,".extern")){
			if(!checkIfDeclared(Entry,Exit,label,index))
				addTo_Entry_External(Entry,Exit,headIns,datLabel,Exit,label,&index[EXTERN_LABELS],index);
			
		}
	}
}


