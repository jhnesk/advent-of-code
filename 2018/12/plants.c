#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct pot
{
	bool plant;
	bool nextPlant;
	int value;
	struct pot* previous;
	struct pot* next;
} pot_t;

int sum(pot_t* head) {
	int sum = 0;
	pot_t* current = head;
	while (current != NULL) {
		if (current->plant) {
			sum += current->value;
		}
		current = current->next;
	}
	return sum;
}

pot_t* append(bool plant, pot_t* previous) {
	pot_t* pot = malloc(sizeof(pot_t));
	pot->plant = plant;
	pot->nextPlant = false;
	pot->previous = previous;
	pot->next = NULL;

	if (previous != NULL) {
		previous->next = pot;
		pot->value = previous->value + 1;
	} else {
		pot->value = 0;
	}
	return pot;
}

pot_t* prepend(bool plant, pot_t* next) {
	pot_t* pot = malloc(sizeof(pot_t));
	pot->plant = plant;
	pot->nextPlant = false;
	pot->previous = NULL;
	pot->next = next;
	if (next != NULL) {
		next->previous = pot;
		pot->value = next->value - 1;
	} else {
		pot->value = 0;
	}
	return pot;
}

void grow(pot_t* current) {
	while (current != NULL) {
		current->plant = current->nextPlant;
		current = current->next;
	}
}

int calculateRuleIndex(pot_t* current) {
	int index = 0;
	if (current->previous != NULL) {
		if (current->previous->previous != NULL && current->previous->previous->plant) {
			index += 1 << 4;
		}
		if (current->previous->plant) {
			index += 1 << 3;
		}
	}
	if (current->plant) {
		index += 1 << 2;
	}
	if (current->next != NULL) {
		if (current->next->plant) {
			index += 1 << 1;
		}
		if (current->next->next != NULL && current->next->next->plant) {
			index += 1 << 0;
		}
	}
	return index;
}

void print(pot_t* current) {
	while (current != NULL) {
		if (current->plant) {
			putc('#', stdout);
		} else {
			putc('.', stdout);
		}
		current = current->next;
	}
	putc('\n', stdout);
}

pot_t* addEmptyLast(pot_t* tail) {
	if (tail->plant) {
		tail = append(false, tail);
	}
	if (tail->previous->plant) {
		tail = append(false, tail);
	}
	return tail;
}

pot_t* addEmptyFirst(pot_t* head) {
	if (head->plant) {
		head = prepend(false, head);
	}
	if (head->next->plant) {
		head = prepend(false, head);
	}
	return head;
}

pot_t* removeEmptyLast(pot_t* tail) {
	while (!tail->plant) {
		pot_t* previous = tail->previous;
		previous->next = NULL;
		free(tail);
		tail = previous;
	}
	return tail;
}

pot_t* removeEmptyFirst(pot_t* head) {
	while (!head->plant) {
		pot_t* next = head->next;
		next->previous = NULL;
		free(head);
		head = next;
	}
	return head;
}

int main(int argc, char **argv)
{
	FILE* fp = fopen(argv[1], "r");

	pot_t* head = NULL;
	pot_t* tail = NULL;
	pot_t* current = NULL;

	fscanf(fp, "initial state: ");

	int ch;
	while ((ch = fgetc(fp)) != '\n') {
		current = append((char)ch == '#', tail);
		if (head == NULL) {
			head = current;
		}
		tail = current;
	}

	// translated from input.txt manually with vim tricks.
	// index in the array is binary from the rules where # is 1 and . is 0.
	bool rules[32] = {0,0,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,1,0,1,1,0,0,1,1,1,1,1,1,1,1,1};

	for (int i = 0; i < 20; i++) {
		head = addEmptyFirst(head);
		tail = addEmptyLast(tail);
		current = head;

		while (current != NULL) {
			int rule = calculateRuleIndex(current);
			current->nextPlant = rules[rule];
			current = current->next;
		}
		grow(head);
		head = removeEmptyFirst(head);
		tail = removeEmptyLast(tail);
	}
	printf("%d\n", sum(head));
}
