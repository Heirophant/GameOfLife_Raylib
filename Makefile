
all:
	gcc game.c -o game -Wall -lraylib -lGL -lm

clean:
	rm game
