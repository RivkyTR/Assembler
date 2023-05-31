## Assembler project

The project included writing a 10-bit assembler which finds all the compilation errors in an assembly script.
In case no compilation errors were found, it "translates" the assembly files to machine code files.
returns object file and files for the enternal labels and for the external labels.
All numbers in the Object file are in unique base 32, two numbers in each row: 1. Address of the word in memory. 2. The content of the word.


## To run:
On Linux machine run:
- `make`
- `./assembler file_name1 file_name2`   <sub>(You can attach as many files as you want )</sub>





OS: Ubuntu-Linux. Programming languages: c
