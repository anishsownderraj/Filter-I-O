Directions to use my program:

To compile the program run `clang -Wall -Wpedantic -Wextra -Werror hatterspeak.c -o hatterspeak`
To run the program run `./hatterspeak -[shf] -[shf] -[shf] -[mb]`

Inputting -s will suppres the letter from the censor
Inputting -h specifies the hashtable size entries, default value is 10000
Inputting -f specifies the bloomfilter size entries, default values is pow(2,20)
Inputting -m will use the move to front rule
Inputting -b will not use the move to front rule

Using Makefile to run the program:

By typing make or make all both commands `clang -Wall -Wpedantic -Wextra -Werror hatterspeak.c -o hatterspeak`and `./hatterspeak -[shf] -[shf] -[shf] -[mb]` will compile and run the program.
`make clean` will clear out any executables or object files in your current working directory.
'make infer' runs infer on the program.

No Make Infer Errors