#include "utils.h"
#include "memory.h"


/*this file handles with printing memory accordung to the request*/
char abc[]="!@#$%^&*<>abcdefghijklmnopqrstuv";




/*this function creates and prints the files : object, entry,external*/
void printToFiles(table *dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit,char *nameOB , char *nameENT , char * nameEXT,int * index)
{
	FILE *fEXT;/*a pointer to the external file*/
	FILE * fENT;/*a pointer to the entry file*/
	FILE *fOB;/*a pointer to the object file*/
	int i,j,openFileEX=0;
	
	fOB=fopen(nameOB,"w");/*open the object file to write*/
	
	/*printing to file object the values of IC and DC*/
	pr1(index[IC],&fOB);
	fprintf(fOB," ");
	pr1(index[DC],&fOB);
	fprintf(fOB,"\n");
	
	/*printing to file object the instruction segment*/
	for(i=0;i<index[IC];i++)
	{
			pr1((insTable)[i].addr,&fOB);
			fprintf(fOB,"\t");
			pr1((insTable)[i].typeWord.d.d1,&fOB);
			fprintf(fOB,"\t\n");
	}
	
	/*printing to file object the data segment*/
	for(i=0;i<index[DC];i++)
	{
			pr1((dataTable)[i].addr,&fOB);
			fprintf(fOB,"\t");
			pr1((dataTable)[i].typeWord.d.d1,&fOB);
			fprintf(fOB,"\t\n");
	}
	fclose(fOB);
/*printg to file of entries just if exist at least 1 label entry, that is, when "index[ENTRY_LABELS]!=0 " */
	if(index[ENTRY_LABELS] )
	{
		fENT=fopen(nameENT,"w");/*open the entry file to write*/
		for(i=0;i<index[ENTRY_LABELS];i++)
		{
			fprintf(fENT,"%s\t",(*Entry)[i].name);
			pr1((*Entry)[i].address,&fENT);
			fprintf(fENT,"\n");
		}
		fclose(fENT);
	}
	
	/*printing to file external*/
	/* openFileEX is tha flag who showes if we opened the file of externals*/
	for(j=0 ; j<index[IC] ;j++)
		for(i=0; i<index[EXTERN_LABELS]; i++)
			if(!strcmp((*Exit)[i].name,(insTable)[j].name))/*if we find a label in instruction segment which is external*/
			{
				if(openFileEX)/*if the flag of open file is on==> the file is created already*/
				{
					fprintf(fEXT,"%s\t",(*Exit)[i].name);
					pr1((insTable)[j].addr,&fEXT);
					fprintf(fEXT,"\n");
				}
				else
				{
					openFileEX=1;
					fEXT=fopen(nameEXT,"w");/*open the extern file to write*/
					fprintf(fEXT,"%s\t",(*Exit)[i].name);
					pr1((insTable)[j].addr,&fEXT);
					fprintf(fEXT,"\n");
				}
			}
	if(openFileEX)/*if the flag of open file is on==> we need to close the file*/
		fclose(fEXT);
}





/*this function gets a number and a pointer to a file and prints the number it got in 32-base by 2 digits*/
void pr1( int num,FILE **f)
{
	fprintf(*f,"%c",abc[num/BASE%BASE]);
	fprintf(*f,"%c",abc[num%BASE]);
}
	
	
	
