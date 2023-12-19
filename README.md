# Chess

Command line based C++17 implementation of chess.

Used Object Oriented Programming techniques, including the use of design patterns, specifically vistor and factory as well as the use of polymorphic clas design, and for Chess piece design. In order to maintain memory safe development, smart pointers and RAII were used.

All chess rules were implemented including promotions and en passant, and enforcement of legal moves. The undo functionality was also available. Four different levels of computer were also programmed, that could be played against, or played against each other

Dependencies were managed using the use of a Makefile, and interface and implementation seperation using header files.

To run the given project, first to create the executable, use the make file,

```shell
make
```

And then use the executable to begin

```shell
./chess
```

Example games are shown in the testcase folder, to initiate a game, first input 'game', before specifying if the two players should be either 'player', or 'computer1', 'computer2', 'computer3', 'computer4'. Here is an example of the game being played.

The UML of this program is as shown below
