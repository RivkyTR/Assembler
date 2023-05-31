The main function is in the main.c

Assembler Files:
main: to start and end the running of the program, also responsible for freeing memory.
macro: responsible for the macro retirement, and returns the AM file after the macros are retired
first_transition: responsible for the first pass over the file.
second_transition: using the symbol values the first pass found, it finishes building the machine code.
checking: contains all the functions that should check if the code does not contain compilation errors.
instruction_sentence: handles instruction sentences.
guidance_sentence: handles guidance sentences.
prepares_to_conversion: contains all the functions that handle specific data, and prepare the data for conversion to binary.
convert_to_binary: contains all the functions that receive data and 'translate' it into binary and transfer it to the appropriate tables.
print_to_files: contains functions that receive the data tables in binary and open and print into the appropriate files (ob/ext/ent).
utils: contains definitions and types used in the program.
