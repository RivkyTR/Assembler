/*this file holds the methods to handle with the memory: enter memery, update, or print*/



/*this function gets a label and the place who we need to put the address of the label
and looks for the address of the label by the instruction labels and data lebels.
checks if the struct operand label is not defined as instruction label
returns 2(RELOCATABLE) if ssuceed find the adress of the label, otherwise 0*/
int updateAdressAcordingLabels(table * insTable,node **headIns,labelTable ** datLabel, char *label, int locationToPutAddress,int * index);



/*this function gets a label and the place who we need to put the address of the label
 looks for the address of the label by the external labels.
 prints to file of externals the name of the label and which address used it.
returns 1(EXTERNL) if ssuceed find the address of the label, otherwise 0*/
int updateAdressAcordingExternal(table *insTable,ex_en ** Exit,char *label,int locationToPutAddress,int *index);



/*this function updates the addresses of the data labels and data table,
after the first transition when we know what is the final value of IC*/
void updateddresses(table *dataTable,labelTable **datLabel,int * index);

/*this function creates and prints the files : object, entry,external*/
void printToFiles(table *dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit,char *nameOB , char *nameENT , char * nameEXT,int * index);




/*This function receives values in a different number each time
And she insert the coded values into the instruction table.
There are many types of coding,
And each type of addressing method needs a different coding, by a different division of ten bits.
The method accepts in variable 'numOfFields' the number of parts into which the ten bits of "typeWord" should be divided.
And according to this it also receives a different number of values for income, a value for type, and the value for the name(if doesn't need a name will be entered "..").
If 'numOfFields'=SAVE_PLACE_FOR_ADDRESS=0 then the ten bits should be divided in 1
If 'numOfFields'=ENCODING_DATA=1 then the ten bits should be divided in 1
If 'numOfFields'=ENCODING_ADDRESS_OR_IMMIDIATE=2 then the ten bits should be divided in 2 (8,2 bytes)
If 'numOfFields'=ENCODING_REGISTER=3 then the ten bits should be divided in 3 (4,4,2 bytes)
If 'numOfFields'=ENCODING_INSTRUCTION=4 then the ten bits should be divided in 4 (4,2,2,2 bytes)
 */
void enterFullTableInstruction(table *insTable,int type,char * name,int *index,int numOfFields,...);




/*This function gets a name of label-opcode (if it's not a call to a label, then put ".." )
and a numerical value and it  insert them into the data table*/
void enterFullTableData(table *dataTable,char * name,int number,int *index);


/*this function creats a new place in the array which was send as a parameter to the function(the arrays would be Entry or Exit,)
and in this place it enters the label,
 it checks before entering the label: the label is legal,not definet,not declared
 if the array is Extern- checks if label is not already defined*/
void addTo_Entry_External(ex_en ** Entry, ex_en ** Exit,  node **headIns,labelTable **datLabel,ex_en ** labels, char * label, int *placeToPut,int * index);


/*this function creats a new place in the array of data labels
and in this place it enters the label, and the type of label(DATA,STRING or STRUCT)
checks before entered: if defined already or declared as extern*/
void addDataLabel(ex_en ** Exit,node ** headIns, labelTable ** datLabel, char * label,int kindOfData, int *numofdataLabels,int * index);


/*this function creats a new node in the list of instruction labels,
and in this place it enters the label
checks before entered: if defined already or declared as extern*/		
void addInstructionLabel(ex_en ** Exit, node **headIns,labelTable **datLabel, char * label,int *index);







/*this function is running on the labels, we stop when we find a lebal that is the same as the label we got from user,
	and then we check if we had to stop in middle, if yes than the label is already defined in the labels.
returns 0 if not defined*/
int checkIfDefinedLabel(ex_en ** Exit,node ** headInstructionLabels,labelTable ** datLabel,char *label,int * index);


/*this function is running on the extern labels, we stop when we find a lebal that is the same as the label we got from user,
	and then we check if we had to stop imiddle, if yes than the label is already defined in the labels 
	returns 0 just if not defined*/
int checkIfDefinedExtern(ex_en ** Exit,char *label,int * index);

/*this function gets a number anf a pointer to a file and prints the number it got in 32-base by 2 digits*/
void pr1( int num,FILE **f);


/*this function checks if the label is not the same as saved elements of assembly or not valid name*/
int labelIsLagel(char * label,char * kind, char * ending);


