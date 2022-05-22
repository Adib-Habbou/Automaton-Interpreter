## Description

The aim of this project is to implement a program that executes LR(1) automatons.
LR(1) automatons are used to recognize programming languages.
The program takes user input and tells if the string is accepted or rejected.


## Content

word.dot, word_bis.dot, dyck.dot, arith.dot <br />
stack.c, matrix.c, automaton.c <br />
stack.h, matrix.h <br />
Makefile <br />
README.MD <br />
rapport.pdf


## Usage

You need to call the program with the name of the AUT file in your terminal using the following command : ./automaton file.aut


## Examples

./automaton word.aut
./automaton word_bis.aut
./automaton dyck.aut
./automaton arith.aut


## DOT files

In order to generate the graph use the following command :
dot -Tpng file.dot > file.png (if you want to generate a png image)
dot -Tpdf file.dot > file.pdf (if you want to generate a pdf file)

