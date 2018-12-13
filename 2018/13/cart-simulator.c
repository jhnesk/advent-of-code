#include <stdlib.h>
#include <stdio.h>

#define LEFT_TURN 0
#define STRAIGHT 1 
#define RIGHT_TURN 2

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

typedef struct cart
{
	int x_coord;
	int y_coord;
	int direction;
	int last_turn;
	int move_count;
} cart_t;

char map_character(char c)
{
	switch (c) {
		case '>': 
		case '<': return '-';
		case 'v':
		case '^': return '|';
		default: return c;
	}
}

void populate_map(FILE* input, char map[150][150])
{
	int character;
	int carts = 0;
	int x=0;
	int y=0;

	while ((character = fgetc(input)) != EOF) {
		if (character == '\n') {
			y++;
			x = 0;
		} else {
			map[x][y] = map_character((char)character);
			x++;
		}
	}
}

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	char map[150][150];
	populate_map(fp, map);
	fclose(fp);
	int y;
	int x;

	for (y = 0; y < 150; y++) {
		for (x = 0; x < 150; x++) {
			printf("%c", map[x][y]);
		}
		printf("\n");
	}
}

