#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define LEFT_TURN 0
#define STRAIGHT 1 
#define RIGHT_TURN 2

#define CART_COUNT 17

typedef struct cart
{
	int x;
	int y;
	char direction;
	int last_turn;
	int move_count;
} cart_t;

typedef struct tile
{
	char track;
	cart_t* cart;
} tile_t;

char map_track(char c)
{
	switch (c) {
		case '>': 
		case '<': return '-';
		case 'v':
		case '^': return '|';
		default: return c;
	}
}

cart_t* create_cart(int x, int y, char direction) {
	cart_t* cart = malloc(sizeof(cart_t));
	cart->x = x;
	cart->y = y;
	cart->direction = direction;
	cart->last_turn = RIGHT_TURN;
	cart->move_count = 0;
	return cart;
}

cart_t* map_cart(int x, int y, char c)
{
	switch (c) {
		case '>':
		case '<':
		case 'v':
		case '^':
			return create_cart(x, y, c);
		default:
			return NULL;
	}
}

void populate_map(FILE* input, tile_t* map[150][150])
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
			map[x][y] = malloc(sizeof(tile_t));
			map[x][y]->track = map_track((char)character);
			map[x][y]->cart = map_cart(x, y, (char)character);
			x++;
		}
	}
}

void print(tile_t* map[150][150])
{
	int y;
	int x;
	for (y = 0; y < 150; y++) {
		for (x = 0; x < 150; x++) {
			if (map[x][y]->cart == NULL) {
				printf("%c", map[x][y]->track);
			} else {
				printf("%c", map[x][y]->cart->direction);
			}
		}
		printf("\n");
	}
}

void intersection_turn(cart_t* cart) {
	switch (cart->direction) {
		case '>':
			if (cart->last_turn == LEFT_TURN) {
				cart->last_turn = STRAIGHT;
			} else if (cart->last_turn == STRAIGHT) {
				cart->last_turn = RIGHT_TURN;
				cart->direction = 'v';
			} else {
				cart->last_turn = LEFT_TURN;
				cart->direction = '^';
			}
			break;
		case 'v':
			if (cart->last_turn == LEFT_TURN) {
				cart->last_turn = STRAIGHT;
			} else if (cart->last_turn == STRAIGHT) {
				cart->last_turn = RIGHT_TURN;
				cart->direction = '<';
			} else {
				cart->last_turn = LEFT_TURN;
				cart->direction = '>';
			}
			break;
		case '<':
			if (cart->last_turn == LEFT_TURN) {
				cart->last_turn = STRAIGHT;
			} else if (cart->last_turn == STRAIGHT) {
				cart->last_turn = RIGHT_TURN;
				cart->direction = '^';
			} else {
				cart->last_turn = LEFT_TURN;
				cart->direction = 'v';
			}
			break;
		case '^':
			if (cart->last_turn == LEFT_TURN) {
				cart->last_turn = STRAIGHT;
			} else if (cart->last_turn == STRAIGHT) {
				cart->last_turn = RIGHT_TURN;
				cart->direction = '>';
			} else {
				cart->last_turn = LEFT_TURN;
				cart->direction = '<';
			}
			break;
	}
}

void move(tile_t* map[150][150], cart_t* cart)
{
	int x = cart->x;
	int y = cart->y;
	map[x][y]->cart = NULL;
	switch (cart->direction) {
		case '>': x++; break;
		case '<': x--; break;
		case '^': y--; break;
		case 'v': y++; break;
	}
	if (map[x][y]->cart != NULL) {
		printf("COLLISION AT %d,%d\n", x, y);
		raise(SIGTERM);
	}
	cart->x = x;
	cart->y = y;
	map[x][y]->cart = cart;

	switch (map[x][y]->track) {
		case '/':
			if (cart->direction == '>') {
				cart->direction = '^';
			} else if (cart->direction == 'v') {
				cart->direction = '<';
			} else if (cart->direction == '<') {
				cart->direction = 'v';
			} else if (cart->direction == '^') {
				cart->direction = '>';
			}
			break;
		case '\\':
			if (cart->direction == '>') {
				cart->direction = 'v';
			} else if (cart->direction == 'v') {
				cart->direction = '>';
			} else if (cart->direction == '<') {
				cart->direction = '^';
			} else if (cart->direction == '^') {
				cart->direction = '<';
			}
			break;
		case '+':
			intersection_turn(cart);
			break;
	}
}

void populate_cart_order(tile_t* map[150][150], cart_t* carts[CART_COUNT])
{
	int i = 0;
	for (int y = 0; y < 150; y++) {
		for (int x = 0; x < 150; x++) {
			if (map[x][y]->cart != NULL) {
				carts[i] = map[x][y]->cart;
				i++;
			}
		}
	}
}

int main(int argc, char** argv)
{
	FILE* fp = fopen(argv[1], "r");
	tile_t* map[150][150];
	populate_map(fp, map);
	fclose(fp);

	cart_t* carts[CART_COUNT];

	while (1) {
		populate_cart_order(map, carts);
		for (int c = 0 ; c < CART_COUNT ; c++) {
			move(map, carts[c]);
		}
		//print(map);
		//fflush(stdout);
	}
}
