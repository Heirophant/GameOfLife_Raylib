# Conway's Game of Life

Game of Life was devised by John Conway in 70s. It is a type of cellular automata which from some inital conditions work on 4 rules and create intricate patterns. This is my attempt to render it using Raylib in C and in process learn a bit more about Raylib and rendering in general.

### RULES

**_RULE 1_** - Any live cell with fewer than two live neighbours dies

**_RULE 2_** - Any live cell with two or three live neighbours lives on to the next generation.



**_RULE 3_** - Any live cell with more than three live neighbours dies

**_RULE 4_** - Any dead cell with exactly three live neighbours becomes a live cell.


##


## Compiling

```shell
$ make
$ ./game
```

## Mechanics

The game has 2 modes

1. __Random__ : The Player can choose a random intial condition generated by ```rand()``` in C. This can be invoked by pressing ```r``` on title screen.
2. __Manual/Mouse__: In this mode player can set inital conditions manually using their mouse and left clicking on a cell to make it alive. Then press ENTER to start the game for their input initial condition. This mode can be invoked by pressing ```m``` on the title screen.

## Resources Used
- https://www.raylib.com/
- https://www.youtube.com/watch?v=CfeHFIP_xEI&t=1947s
- https://github.com/FrexG/ConwaysGOL/


