

/*this function go through the tables and updates tha addresses of the operand labels
checks if all labels which were declared as entry were defined*/
void second_trans(table *dataTable,table *insTable,ex_en ** Entry,ex_en ** Exit,node ** headIns,labelTable **datLabel,char * nameFile,int *index);

/*This function gets a label and checks if the label was already defined in the instruction ar data lebels or maybe was declares as external label*/ 
int checkIfDefinedLabel(ex_en ** Exit,node **headIns, labelTable ** datLabel, char *label, int * index);



/*this function gets a label and the place who we need to put the address of the label
 looks for the address of the label by the external labels.
 prints to file of externals the name of the label and which address used it.
returns 1(EXTERNL) if ssuceed find the address of the label, otherwise 0*/
int updateAdressAcordingExternal(table *insTable, ex_en ** Exit,char *name,int i, int * index);


/*this function gets a label and the place who we need to put the address of the label
and looks for the address of the label by the instruction labels and data lebels.
returns 2(RELOCATABLE) if ssuceed find the adress of the label, otherwise 0*/
int updateAdressAcordingLabels( table *insTable, node **headIns, labelTable **datLabel, char *name, int i, int * index);



/*gets name of files and prints to the files*/
void printToFiles(table *dataTable,table *insTable ,ex_en ** Entry,ex_en ** Exit, char *nameOB , char *nameENT , char * nameEX, int * index);



