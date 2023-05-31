assembler: main.o convert_to_binary.o checking.o instructionSentence.o guidanceSentence.o macro.o second_transition.o prepares_to_conversion.o first_transition.o print_to_files.o entry_or_extern_sentence.o
	gcc -ansi -pedantic -Wall -g main.o instructionSentence.o convert_to_binary.o guidanceSentence.o macro.o second_transition.o prepares_to_conversion.o print_to_files.o first_transition.o entry_or_extern_sentence.o checking.o -o assembler 
main.o: main.c main.h utils.h
	gcc -c -ansi -pedantic -Wall  main.c -o main.o
entry_or_extern_sentence.o: entry_or_extern_sentence.c ent_ext.h utils.h
	gcc -c -ansi -pedantic -Wall  entry_or_extern_sentence.c -o entry_or_extern_sentence.o	
print_to_files.o: print_to_files.c memory.h utils.h
	gcc -c -ansi -pedantic -Wall  print_to_files.c -o print_to_files.o	
prepares_to_conversion.o: prepares_to_conversion.c utils.h prepares_to_conversion.h
	gcc -c -ansi -pedantic -Wall  prepares_to_conversion.c -o prepares_to_conversion.o
first_transition.o: first_transition.c first_transition.h utils.h
	gcc -c -ansi -pedantic -Wall  first_transition.c -o first_transition.o
second_transition.o: second_transition.c utils.h second_transition.h memory.h
	gcc -c -ansi -pedantic -Wall  second_transition.c -o second_transition.o
instructionSentence.o: instructionSentence.c utils.h instructionSen.h
	gcc -c -ansi -pedantic -Wall  instructionSentence.c -o instructionSentence.o
guidanceSentence.o: guidanceSentence.c guideSen.h utils.h
	gcc -c -ansi -pedantic -Wall guidanceSentence.c -o guidanceSentence.o
macro.o: macro.c utils.h macro.h
	gcc -c -ansi -pedantic -Wall macro.c -o macro.o
convert_to_binary.o: convert_to_binary.c utils.h memory.h
	gcc -c -ansi -pedantic -Wall convert_to_binary.c -o convert_to_binary.o
checking.o: checking.c utils.h check.h
	gcc -c -ansi -pedantic -Wall checking.c -o checking.o

	
