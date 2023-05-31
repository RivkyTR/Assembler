#include "utils.h"
#include "guideSen.h"

/*This function gets a guide sentence.
 Decodes the line,
 enters the guide sentence into the data table(dataTable) .
gets a sentence, the label of the data,and the index after the label name*/

void getData(table * dataTable,ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable **datLabel, char * line,char * firstWord,int indexAfterFirstWord,int *index)
{
	int j=0, i=indexAfterFirstWord,indexBeforeData; /* j ia a counter to copy to "typeData" the label, "i" is the current index, "indexBeforeData" is the index after the type data before the data begins*/
	char  typeData[MAX_LENGTH_LABEL];
	int counter_comma=0;
	
	if(!strcmp(".data",firstWord) || !strcmp(".string",firstWord) || !strcmp(".struct",firstWord))
	{
		/************begins checking mistakes-commas after the label ************/
		CHECK_COMMAS
		if(counter_comma){
			mistake=1;
			printf("%s.am: In line %d: error - %d comma after name of the type data\n",file1,numLine,counter_comma);}
		/************finished checking mistakes************/
		
		/*we sent to each function the type of data: '.data' , ',string', 'struct*/
		indexBeforeData=i;
		if(!strcmp(".data",firstWord))
			getInt(dataTable,line,indexBeforeData,index);/* "getInt " is written in this file below*/
		else if(!strcmp(".string",firstWord))
			getString(dataTable,line,indexBeforeData,index);/* "getString " is written in this file below*/
		else if(!strcmp(".struct",firstWord))
			getStruct(dataTable,line,indexBeforeData,index);/* "getStruct " is written in this file below*/
		
	}
	
	/*if we have a label before the type data --> is the 'firstWord' a label*/
	else
	{
		/************begins checking mistakes-commas after the label ************/
		CHECK_COMMAS
		if(counter_comma){
			mistake=1;
			printf("%s.am: In line %d: error - %d comma after label\n",file1,numLine,counter_comma);
		}
		/************finished checking mistakes************/
		
		
		/*the loop enters the second word which is the type data(beacause the first word ia a label) into */	
		for(i=i;line[i]!='\0' && !isspace(line[i]) && line[i]!=',' && j<(MAX_LENGTH_LABEL-1);i++)
			typeData[j++]=line[i];
		typeData[j]='\0';
	
	
		/************begins checking mistakes-commas before the data ************/
		CHECK_COMMAS
		if(counter_comma){
			mistake=1;
			printf("%s.am: In line %d: error - %d comma after name of the type data\n",file1,numLine,counter_comma);
		}
		/***********finished checking mistakes************/
		
		
		/*if the word after the label was entry or extern than we ignore the label that was before*/
		if(!strcmp(".entry",typeData) || !strcmp(".extern",typeData))
		{
			printf("%s.am: In line %d: warning - label before entry or extern definition\n",file1,numLine);
			entry_exit(Entry,Exit,headIns,datLabel,line,typeData,i,index);/* "entry_exit" is written in file "entry_exit.c"*/
		}
		
		else
		{
			if(checkIfDefinedLabel(Exit,headIns,datLabel,firstWord,index))/* "checkIfDefinedLabel" is written in "checking.c"*/
			{
				mistake=1;
				printf("%s.am: In line %d: error- the label is already defined\n",file1,numLine);
			}
			else
			{
			/*we send to addDataLabel with appropriate type(DATA,STRING,STRUCT)
			and each one to his appropriate function*/
			
			/*"addDataLabel" is in convert_to_binary.c" getInt,getString,getStruct is in this file below*/
				indexBeforeData=i;
				if(!strcmp(".data",typeData))
				{
					addDataLabel(Exit,headIns,datLabel,firstWord,DATA,&index[DATA_LABELS],index);
					getInt(dataTable,line,indexBeforeData,index);
				}
				else if(!strcmp(".string",typeData)){
					addDataLabel(Exit,headIns,datLabel,firstWord,STRING,&index[DATA_LABELS],index);
					getString(dataTable,line,indexBeforeData,index);
				}
				else if(!strcmp(".struct",typeData)){
					addDataLabel(Exit,headIns,datLabel,firstWord,STRUCT,&index[DATA_LABELS],index);
					getStruct(dataTable,line,indexBeforeData,index);
				}
				else
				{
					mistake=1;
					printf("%s.am: In line %d: error- there isn't such type of data or operation\n",file1,numLine);
				}
			}
		}
	}
}






/*This function handles with .data
it gets a guide sentence and the index after the type of data(in thus casv the index after '.date' )
and enters the numerical values to the data table*/

void getInt(table * dataTable,char * line,int indexBeforeData,int * index)
{
	int counter_comma,j=0,number=0,comma=0,space=0,i=indexBeforeData;
	char num[MAX_LENGTH_SENTENCE];

	/************begins checking mistakes-commasbefore the number ************/
	CHECK_COMMAS
	if(counter_comma)
	{
		mistake=1;
		printf("%s.am: In line %d: error- %d comma before any number\n",file1,numLine,counter_comma);
	}
	else if(line[i]=='\0')
	{
		mistake=1;
		printf("%s.am: In line %d: error- missing a number after data.\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	while(line[i]!='\0')
	{
		if(line[i]=='.')
		{
			mistake=1;
			printf("%s.am: In line %d: error- illegal number-we accept just integers\n",file1,numLine);
			comma=0;
			break;
		}
		
		counter_comma=0;
		while(line[i]!='\0')
		{
			if(line[i]==',')
				counter_comma++;
			else
				break;
			i++;
		}
		
		if(line[i]=='\0')/*if end of line*/
		{
			comma=counter_comma?1:0;
			break;
		}
		/*if we got a comma it means that a number finished..*/
		else if(counter_comma==1)
		{
			num[j]='\0';
			j=0;
			/*sent to the 'enterFullTableData' which will enter to the data table the appropriate values*/
			enterFullTableData(dataTable,"..",atoi(num),index);/*"enterFullTableData" is in "convert_to_binary.c"*/
			number=space=!(comma=1);
		}
		/*if more than 1 comma*/
		else if(counter_comma!=0)/*it means more than 1 comma*/
		{
			mistake=1;
			printf("%s.am: In line %d: error- %d commas\n",file1,numLine,counter_comma);
			number=space=!(comma=1);
		}
		
			
			
		/*if we got space when the flag 'number' is on..*/	
		if(number && isspace(line[i]))
			space=1;
			
		else if(number)  /*if we are immidle a number: */
		{
		
			if(space)/*if we are immidle a number and 'space' is on and we got one more charecter*/
			{
				mistake=1;
				printf("%s.am: In line %d: error - missing comma\n",file1,numLine);
				space=0;
			}
			else if(('0'<=line[i] && line[i]<='9')/*/line[i]!='-' && line[i]!='+'*/)/*if it's an number we just had him to num*/
			{
				num[j++]=line[i];
			}
			else/*if not a number*/
			{
				mistake=1;
				printf("%s.am: In line %d: error-illgal number\n",file1,numLine);
				for(i=i;line[i]!='\0' && !isspace(line[i]) && line[i]!=','; i++);
				comma =number=0;
				continue;
			}
		}
		else/*flag 'number' is turn off -->we are not immidle a number. it's a new number */
		{
			if(('0'<=line[i] && line[i]<='9')  || line[i]=='-' || line[i]=='+' )/*the first char of a number could be also minus or plus*/
			{
				num[j++]=line[i];
				comma=!(number=1);
			}
			else if(!isspace(line[i]))/*but if it is not a number,minus,plus or white space*/
			{
				mistake=1;
				printf("%s.am: In line %d: error - not a number\n",file1,numLine);
				comma=0;
			}
		}
		i++;
	}/*end of loop while not end of line*/
		
	if(!comma)/*if does not finish with comma,we will enter the last number into the data table*/
	{
		num[j]='\0';
		enterFullTableData(dataTable,"..",atoi(num),index);/*"enterFullTableData" is in "convert_to_binary.c"*/
	}	
	else/*finish with comma*/
	{
		mistake=1;
		printf("%s.am: In line %d: error- finish with comma\n",file1,numLine);
	}
}






/*This function handles with .string
it gets a guide sentence and the index after the type of data(in this case the index after '.string' )
and enters the character values to the data table*/

void getString(table *dataTable, char * line,int indexBeforeData, int * index)
{
	int counter_comma=0,i=indexBeforeData;
	
	/*skip all white spaces until the \"*/
	for(i=i;line[i]!='\0' && isspace(line[i]) && line[i] !='"'; i++);
	
	/*if we came to the end- it means that there was not \"(quotation marks) -->missing string*/
	if(line[i]=='\0')
	{
		mistake=1;
		printf("%s.am: In line %d: error - missing the string\n",file1,numLine);
	}
	/*if the first charecter after the spaces was not \"(quotation marks) --> missing the quotation mark of beginning of the string*/
	else
	{	
		if(line[i]!='"')
		{
			mistake=1;
			printf("%s.am: In line %d: error -  missing a \" in the begining\n",file1,numLine);
		}
		/* index - 'i' is now on the \" place, for that we increase him by 1 is now he is in the first letter of the string*/
		i++;	
	
		/*enter the string to the data table. we enter the charecters to the data table until we come to the end of the sentence or to \" */
		while(line[i]!='\0' && line[i]!='"')
		{
			enterFullTableData(dataTable,"..",line[i],index);/*"enterFullTableData" is in "convert_to_binary.c"*/
			i++;
		}
	
		/*if we exit the loop because we came to the end of line --> missing the closing  \"(quotation marks) in the end  */
		if(line[i]=='\0')
		{
			mistake=1;
			printf("%s.am: In line %d: error- missing tha \" in the end!!\n",file1,numLine);
		}
	
		/* if we exit the loop because \" then we increase the index 'i' to point to the next character*/
		line[i]=='"'?i++:1;
	
	
		/************begins checking mistakes-commas or extra data after the string ************/
		CHECK_COMMAS
		if(line[i]=='\0' && counter_comma){
			mistake=1;
			printf("%s.am: In line %d: error - %d comma after the string\n",file1,numLine,counter_comma);
		}
		else if(line[i]!='\0' || counter_comma){
			mistake=1;
			printf("%s.am: In line %d: error - extra data after the string\n",file1,numLine);
		}
		/************finished checking mistakes************/
	
	}
	/*we enter to the data table zero for the end of the string*/	
	enterFullTableData(dataTable,"..",0,index);/*"enterFullTableData" is in "convert_to_binary.c"*/
}





/*This function handles with .struct
it gets a guide sentence and the index after the type of data(in this case the index after '.struct' )
and enters the numeric and character values to the data table*/

void getStruct(table *dataTable, char * line,int indexBeforeData,int * index)
{
	char num[MAX_LENGTH_SENTENCE];/*the first fiels of struct is a number , and "num" holds it*/
	int j=0,i=indexBeforeData;
	int counter_comma=0;
	
	/************begins checking mistakes-commas  after ".struct" ************/
	CHECK_COMMAS
	if(counter_comma){
		mistake=1;
		printf("%s.am: In line %d: error - %d comma after the type struct(.)\n",file1,numLine,counter_comma);
	}
	if(line[i]=='\0')
	{
		mistake=1;
		printf("%s.am: In line %d: error - missing number and string after struct\n",file1,numLine);
	}
	/************finished checking mistakes************/
	
	else/* didnt finish the line*/
	{
		/*if the number begins with '-' or '+' */
		if(line[i]=='-' || line[i]=='+')
			num[j++]=line[i++];
	
	/*the loop enters the sequence of numbers into num*/
		while(line[i]!='\0' && '0'<=line[i] && line[i]<='9' )
			num[j++]=line[i++];
		num[j]='\0';
	
	/*if the first charecter after the number is not comma or space than it means that immidle the nnber we have a charecter which is not number*/
		if(line[i]!=',' && !isspace(line[i]) && line[i]!='\0')
		{
			for(i=i;line[i]!='\0' && !isspace(line[i]) && line[i]!=',';i++); /*skipping the whole illegal number*/
			mistake=1;
			printf("%s.am: In line %d: error - not a legal number\n",file1,numLine);
		}
	
	
		/************begins checking mistakes-more than 1 comma or missing commas after the number************/
		CHECK_COMMAS
		if(counter_comma==0){
			mistake=1;
			printf("%s.am: In line %d: error - no comma after the number\n",file1,numLine);
		}
		else if(counter_comma!=1){
			mistake=1;
			printf("%s.am: In line %d: error - more than 1 comma after the number of the struct\n",file1,numLine);
		}
		/************finished checking mistakes************/
	
	
		enterFullTableData(dataTable,"..",atoi(num),index);/*"enterFullTableData" is in "convert_to_binary.c"*/
	
		/*we call the function "getString" to get the string of the struct*/
		getString(dataTable,line,i,index);/*"getString" is in this file above"*/
	}
}
