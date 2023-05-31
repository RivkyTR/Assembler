#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>



#define MAX_LENGTH_SENTENCE 81
#define MAX_LENGTH_LABEL 31
#define OPERATION_LENGTH 3
#define MAX_LINES_IN_PROGRAM 1000
#define BASE 32


typedef union {
	struct {
			unsigned int a1:2;
			unsigned int a2:2;
			unsigned int a3:2;
			unsigned int a4:4;
		}a;/*lekoded pkuda*/
		struct {
			unsigned int b1:2;
			unsigned int b2:4;
			unsigned int b3:4;
		}b;/*lekoded operand 1 or 2 toghether (each one need 4 bits) */
		
		struct {
			unsigned int c1:2;
			unsigned int c2:8;
		}c;/*lekoded address or immidiate number*/
		struct{
		unsigned int d1:10;
		}d;/*lekoded numbers of .data .struct .string*/
}word;


typedef struct{
	int addr;
	word  typeWord;
	char name[MAX_LENGTH_LABEL];
	int typeLabel;
	int linenumber;
}table  ;/* oraot - the table for the coded instructions and data*/



typedef struct{
	char name[MAX_LENGTH_LABEL];
	int address;
	int typ;
}labelTable;/*taviyot - the labels of type with daye .data .struct .string*/


typedef struct {
	char name[MAX_LENGTH_LABEL];
	int address;
	int linenumber;
} ex_en;/*labels of type external or entry*/


typedef struct node * ptr;
typedef struct {
	char name[MAX_LENGTH_LABEL];
	int address;
	ptr next;
}node;/*for labels of instructions*/


int mistake;/*flag if we find a mistake*/
int numLine;/*current line*/
char file1[MAX_LENGTH_SENTENCE];/*the name of the current file without ending*/

/*type of sentences*/
enum type1{INSTRUCTION,DATA_LABEL,INSTRUCTION_LABEL,ENTRY_EXTERNAL};
/*type of address*/
enum typecode{ABSOLUTE,EXTERNL,RELOCATABLE};
/*type of data*/
enum typeData{DATA,STRING,STRUCT,REGISTER,NO_STRUCT};
/*types if addresses to code*/
enum typeAddress{IMMEDIATE_ADDRESS,DIRECT_ADDRESS,STRUCT_ADDRESS,DIRECT_REGISTER_ADDRESS,TARGET_REGISTER};
/*number of fields in which devides the ten bits */
enum numOfFields{SAVE_PLACE_FOR_ADDRESS=0,ENCODING_DATA=1,ENCODING_ADDRESS_OR_IMMIDIATE=2,ENCODING_REGISTER=3,ENCODING_INSTRUCTION=4};
/*holds the place in the array wehere the value they represents. for example in the array  in place IC is saved the number of real IC*/
enum index{IC,DC,DATA_LABELS,ENTRY_LABELS,EXTERN_LABELS};

