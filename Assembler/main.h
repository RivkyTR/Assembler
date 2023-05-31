
/*send pointer to a file to spread the macros, and create a new file with an ending of .am
gets the name of the file to create the new file with .am ending*/
void enter_macro(char create[],FILE ** f);

/*first trans go through the file with ending of am and codes what he can, and creates arrays of the labels*/
void first_trans(table * dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit,node ** head, labelTable ** datLabel, FILE **f22,int * index);


/*second trans-go throgh the instuction table and updates the addresses of the labels we disn't know until know.
it alse checks if all the labels which was declared as entry were defined,
and that all labels which were declared as extern are not defined
gets fil's nae n order to create files which end with .ob .ext .ent*/
void second_trans(table *dataTable,table * insTable,ex_en ** Entry,ex_en ** Exit, node ** head,labelTable **datLabel, char *nameFile, int * index);

