

#include "utils.h"
#include "macro.h"

	

/*this function gets a pointer to a file and spread itsmacros into a new file with an ending am*/
void enter_macro(char create[],FILE ** fileRead)
{
	FILE* fileWrite;/*the pointer to the file we write After spreading macros*/
	int flag_immidle_macro=0;/*flag which is 1 if we are immidle a macro*/
	char  line[MAX_LENGTH_SENTENCE],firstWord[MAX_LENGTH_SENTENCE],name_macro[MAX_LENGTH_LABEL+1],nameOfFile[MAX_LENGTH_SENTENCE];
	
	/*the number of macros*/
	int numOfMacros=0;
	
	/* "macr"the array that hold the macro-name and his content*/
	mcr * macr;
	macr=(mcr*)malloc(sizeof(mcr));
	if(!macr)
	{
		printf("%s.as: error the malloc failed",file1);
		exit(0);
	}
	
	/*open a file to write after spreading macros*/
	fileWrite=fopen(strcat(strcpy(nameOfFile,create),".am"),"w");
	
	while(fgets(line,MAX_LENGTH_SENTENCE,(*fileRead)))
	{
		int  i=0,j=0,number_macro=0;/*number_macro" holds the number of macro we want to writh to the file*/
		
		numLine++;
		
		/*skip the white spaces of the begining*/	
		for(i=0;line[i]!='\0' && isspace(line[i]) ; i++);
		
		
		/*the next loop put the first word into firstWord*/
		while(line[i]!='\0' && !isspace(line[i]))
			firstWord[j++]=line[i++];
		firstWord[j]='\0';
		
		
		/*we look if the firstWord is not a call to a macro*/
		for(j=0; j<numOfMacros; j++)
			if(!strcmp((macr)[j].name,firstWord))
			{
				number_macro=j+1;/*if we find the macro-name, put into number_macro the the macro's number */
				break;
			}
		
		if(number_macro)/*if the firstword was a macro*/{
		 	fputs((macr)[number_macro-1].mac,fileWrite);
		 	number_macro=0;
		 	}
		
		else if(!strcmp("macro",firstWord))/*if it is a beining of a macro-->*/
		{
			j=0;
			
			/*skip all the white spaces*/
			for(i=i;line[i]!='\0' && isspace(line[i]) ; i++);
			
			/*if the next charecter after the nacro-name is '\0'--> came to the end -->. missing name of macro*/
			if(line[i]=='\0')
			{
				mistake=1;
			}
			
			/*the next loop put the name of the macro into name_macro*/	
			while(line[i]!='\0' && !isspace(line[i]) && j<(MAX_LENGTH_LABEL))
				name_macro[j++]=line[i++];
			name_macro[j]='\0';
			
			/*call for add_macro to enter the new macro to tha array of macros */
			if(add_macro(&macr,&numOfMacros,name_macro))
				/*turn on flag*/
				flag_immidle_macro=1;
		}
		
		else if(!strcmp("endmacro",firstWord))
			flag_immidle_macro=0;/*turn off flag*/
		
		/*if immidle of the macro copy the line into the content of the last macro*/
		else if(flag_immidle_macro)
			strcat((macr)[numOfMacros-1].mac,line);
			
		/*if not immidle a macro we print the entire line to fileWrite*/
		else
			fprintf(fileWrite,"%s",line);
		
	}

	free(macr);
	fclose(*fileRead);
	fclose(fileWrite);
}







/*this function gets a macro name and creates a new place for the new macro
checks if the macro name is legal and if it is not already exist an the macro's array*/
int add_macro(mcr ** macr,int *numOfMacros,char *nameMacro)
{
	mcr* p;
	int i;
	int flag_macro_isDefined=0;/*flag who will be 1 if the nameMacro is already defined*/
	
	/*the next loop enters to 'flag_macro_isDefined' 1 if the name of macro already exist in the macro array*/
	for (i=0; i<(*numOfMacros) ; i++)
		if(!strcmp(nameMacro,(*macr)[i].name))
		{
			flag_macro_isDefined=1;
			break;
		}
		
	if(flag_macro_isDefined)
	{
		mistake=1;
		printf("%s.as: In line %d: error - the macro is already defined\n",file1,numLine);
	}
	else if(!labelIsLagel(nameMacro,"macro-name",".as"))
	{
		mistake=1;
	}
	else
	{
		if(!(*numOfMacros))
		{
			*macr=(mcr*)malloc(sizeof(mcr));
			if(!macr)
			{  
			printf("%s.as: error the calloc failed",file1);
				exit(0);
			}
		}
		else/*if not the first macro we need to increase the macro array*/
		{	
			p=(mcr*)realloc(*macr,(*numOfMacros+1)*(sizeof(mcr)));
			if(!p)
			{  
			printf("%s.as: error the realloc failed",file1);
				exit(0);
			}
			*macr=p;
		}
		
		strcpy((*macr)[*numOfMacros].name,nameMacro);
		(*numOfMacros)++;
		return 1;
	}
	return 0;
}
