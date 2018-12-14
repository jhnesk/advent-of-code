#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define LEFT_TURN 0
#define STRAIGHT 1 
#define RIGHT_TURN 2

typedef struct cart
{
	int x;
	int y;
	char direction;
	int last_turn;
	bool crashed;
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
	cart->crashed = false;
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

void populate_map(char* fileName, tile_t* map[150][150])
{
	FILE* input = fopen(fileName, "r");
	int character;
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
	fclose(input);
}

int count_carts(char* fileName)
{
	FILE* input = fopen(fileName, "r");
	int carts = 0;
	int ch;

	while ((ch = fgetc(input)) != EOF) {
		if (ch == '>' || ch == '<' || ch == 'v' || ch == '^') {
			carts++;
		}
	}
	fclose(input);
	return carts;
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

int first_collision = true;

// return true on crash
bool move(tile_t* map[150][150], cart_t* cart)
{
	if (cart == NULL) {
		return false;
	}
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
		if (first_collision) {
			printf("13.1: %d,%d\n", x, y);
			first_collision = false;
		}
		map[x][y]->cart->crashed = true;
		cart->crashed = true;
		map[x][y]->cart = NULL;
		return true;
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
	return false;
}

void populate_cart_order(tile_t* map[150][150], cart_t** carts)
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
	tile_t* map[150][150];
	populate_map(argv[1], map);

	int cart_count = count_carts(argv[1]);
	cart_t* carts[cart_count];
	int new_cart_count = cart_count;
	populate_cart_order(map, carts);
	while (cart_count > 1) {
		for (int c = 0 ; c < cart_count ; c++) {
			if (!carts[c]->crashed) {
				if (move(map, carts[c])) {
					new_cart_count-=2;
				}
			}
		}
		cart_count = new_cart_count;
		populate_cart_order(map, carts);
	}
	printf("13.2: %d,%d\n", carts[0]->x, carts[0]->y);
}
