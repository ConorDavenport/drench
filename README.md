# drench
The aim of this project is to write a program that can solve a game of
Drench. The game can be played [here](http://flashbynight.com/drench/),
and below is a picture of what it looks like.

![alt text](https://github.com/ConorDavenport/drench/blob/master/media/move1.png)

## How to play
The aim of the game is to fill the board with a single colour. The board is
a 14x14 grid filled with a random selection of coloured squares. The
squares can be one of six colours; green, pink, purple, light cyan, red, and yellow.

The player starts as the top left tile and, with the six coloured buttons, 
they can change the colour of their tile. If the player tile changes to the
colour of an adjacent tile (a tile that shares and edge with the player
tile), the player object extends to encompass the original tile and the 
tiles of this new colour. To understand this better, have a look at the 
figure above. The player starts as the purple tile in the top left corner. 
The player then selects pink and the player object then becomes the
original tile plus the two pink tiles beside it.

![alt text](https://github.com/ConorDavenport/drench/blob/master/media/move2.png)

There are two red sections adjacent to the player object, and by changing
to red, the player object now includes these two red sections.

![alt text](https://github.com/ConorDavenport/drench/blob/master/media/move3.png)

The player then selects green, and the two green sections adjacent to the
player object are now included in the player object.

![alt text](https://github.com/ConorDavenport/drench/blob/master/media/move4.png)