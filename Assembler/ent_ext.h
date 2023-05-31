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
		
		/*This function gets a entry or extern sentence, type of data(entry or extern), and the index after the type data
end enters to the exit or entry labels  */
void entry_exit(ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable ** datLabel,char *line, char *type,int indexBeforeLabel,int * index);



/*This function enters a label to entry or extern labels by the 'placeToPut' index(it is dependent on the pointer we send by labels*/
void addTo_Entry_External(ex_en ** Entry, ex_en ** Exit,node ** headIns,labelTable ** datLabel,ex_en ** labels,char * label,int *placeToPut,int *index);


/*this function gets a label and checkes if it is not already defined as entry or external
running on tha extern and entry labels,it stop when we find a lebal that is the same as the label we want to enter,
	and then we check if we had to stop imiddle, if yes than the label is already defined
	returns 1 if already defined, otherwise 0*/
int checkIfDeclared(ex_en ** Entry,ex_en ** Exit,char *label,int * index);


