# i8080
Intel 8080 Emulator to run Altair Basic and Space Invaders

## Tests
To run the tests just build either

    make

or 

    make test

To run the tests:

    ./build/I8080

## Basic Interpreter
Runs Altair Basic for Altair 8800 4k edition. You can grab the rom here and place it in a rom directory in this project.

To build the Basic emulator build the following:

    make basic

To run the Basic emulator run:

    ./build/basic

To get up and running with Altair Basic the following can be inputted to start using the interpreter.

```
MEMORY SIZE? 4096
4096
TERMINAL WIDTH? 080
080
SIN? Y
Y
716 BYTES FREE
4K BASIC 4.0
COPYRIGHT MITS 1976
OK
```

## Space Invaders


To build the Space Invaders emulator build the following:

    make space

To run the Space Invaders emulator run:

    ./build/space-invaders