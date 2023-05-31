
#define NUM_REGISTERS 8
#define LENGRH_REGISTERS 3
#define NUMBER_OPERATIONS 16
#define LENGTH_OPRATION 4

/*this function gets a label and checkes if it is not already defined as entry or external
running on tha extern and entry labels,it stop when we find a lebal that is the same as the label we want to enter,
	and then we check if we had to stop imiddle, if yes than the label is already defined
	returns 1 if already defined, otherwise 0*/
int checkIfDeclared(ex_en ** Entry,ex_en ** Exit,char *label,int * index);


/*this function gets a string(char *)
and checkes if it is not the same as one of the registers.
return 1 if it is not the same as one of the registers' otherwise 0 */
int label_no_register(char * nameLabel);


/*this function checks if the label is not the same as saved elements of assembly or not valid name or more than 30 characters*/
int labelIsLagel(char * label,char * kind, char * ending);

/*this function is running on the labels, we stop when we find a lebal that is the same as the label we got from user,
	and then we check if we had to stop in middle, if yes than the label is already defined in the labels
	returns zero if not fefined this label. */ 
int checkIfDefinedLabel(ex_en ** Exit,node **headIns, labelTable ** datLabel, char *label, int * index);


/*if the label was declared as external return 1, otherwise zero*/	
int checkIfDefinedExtern(ex_en ** Exit,char *label,int *index);


