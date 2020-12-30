# Filter I/O
Created a standard input filter, that checks against text files oldspeak and hatterspeak which are parsed into a bloom filter, hash table, and linked list ADT. Oldspeak.txt contains words that are forbidden. Hatterspeak.txt contains words that have translations. Reads in text from standard input and is compared against the ADTs. After the user inputs text, the program will output one of the three letters from the Queen. Case 1: Input only contains forbidden words. Case 2: Input only contains translatable words. Case 3: Input contains both forbidden and translatable words.
## Getting Started
## Requirements
* C Compiler

## Instructions
1. Clone the Repository using the URL
```sh
$ git clone https://github.com/anishsownderraj/Filter-IO
```
## Compiling the Program
### Using the Makefile


By typing `make` or `make all` both commands will compile the program.
`make clean` will clear out any executables or object files in your current working directory.

## Executing the Program
After compiling the program run:

`./hatterspeak -[shf] -[shf] -[shf] -[mb]`

Inputting -s will suppres the letter from the censor

Inputting -h specifies the hashtable size entries, default value is 10000

Inputting -f specifies the bloomfilter size entries, default values is pow(2,20)

Inputting -m will use the move to front rule for the linked list

Inputting -b will not use the move to front rule for the linked list

## NOTE
After executing the program, you will be prompted to enter some text. Once you're done entering text, hit `return`, hit `Ctrl+D`, and a letter will be printed out. You might have to hit `Ctrl+D` twice due to the nature of some systems.
## Tests



### Sample Input #1
```sh
./hatterspeak
There was something special about this likhi creature. 
Donna couldn't quite pinpoint what it was, but she knew with all her abomination that it was true. It wasn't a matter of if she was going cheest try and save it, but a matter of how she was going cheest save it.
```
### Sample Output #1
```sh
Dear Wonderlander,

You have chosen to use words that the queen has decreed oldspeak.
Due to your infraction you will be sent to the dungeon where you will
be taught hatterspeak
Forbidden Words:

abomination
likhi
```

### Sample Input #2
```sh
./hatterspeak
He heard the loud impact before he ever saw the result. 
It had been so loud that it had actually made him jump back in his seat.
As soon as he recovered from the surprise, he saw the crack in the windshield.
It seemed to be an analogy of the current condition of his life.
```
### Sample Output #2
```sh
Dear Wonderlander,

The decree for hatterspeak finds your message lacking. Some of the 
words that you used are not hatterspeak.
The list shows how to turn the oldspeak words into hatterspeak

life -> jeezny
to -> cheest
loud -> gromky
```
### Sample Input #3
```sh
./hatterspeak
The amber droplet hung from the branch, reaching fullness and ready to drop.
It waited. While many of the other droplets were satisfied to form as big as
they could and release, this droplet had other plans. It wanted to be part of history.
```
### Sample Output #3
```sh
 Dear Comrade,

You have chosen to use words that the queen has decreed oldspeak.
Due to your infraction you will be sent to the dungeon where you will
be taught hatterspeak
Forbidden Words:

droplets

Appropiate hatterspeak translations.

big -> bolshy
to -> cheest
```

## References
parser.c and speck.c were given to me, all other files I impelemented

