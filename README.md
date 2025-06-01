# wordle-starting-word-analyzer
Goes through a word list and checks, if the word were used as a starting word for Wordle and all letters were gray, how many words would still be leftover valid guesses.

This is not really a good metric to judge how good of a starter the word is. This project is mainly an optimization exercise.

Build with `g++ -std=c++23 main.cpp -o out/bin -O3`
