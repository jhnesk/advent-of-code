#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <limits.h>

typedef struct polymer
{
	char c;
	struct polymer* next;
	struct polymer* previous;
} polymer_t;

void parseFile(polymer_t* head, char* file)
{
	polymer_t* current = head;
	FILE* fp = fopen(file, "r");
	int character;

	while ((character = fgetc(fp)) != '\n') {
		current->c = (char)character;
		current->next = malloc(sizeof(polymer_t));
		current->next->previous = current;
		current = current->next;
		current->next = NULL;
	}
	// oups, last one is garbage. w/e, just clean up :)
	current->previous->next = NULL;
	free(current);
	fclose(fp);
}

void print(polymer_t* head)
{
	polymer_t* current = head;
	while (current) {
		printf("%c", current->c);
		current = current->next;
	}
}

int count(polymer_t* head) {
	int count = 0;
	polymer_t* current = head;
	while (current) {
		current = current->next;
		count++;
	}
	return count;
}

polymer_t* react(polymer_t* head)
{
	int caseDiff = 'a'-'A';
	polymer_t* current = head;
	polymer_t* before = NULL;
	polymer_t* after = NULL;
	do {
		int diff = abs(current->c - current->next->c);
		if (diff == caseDiff) {
			after = current->next->next;
			before = current->previous;
			if (after != NULL) {
				after->previous = before;
			}
			if (before != NULL) {
				before->next = after;
			}
			free(current->next);
			free(current);
			current = before ? before : after;
			if (current->previous == NULL) {
				head = current;
			}
		} else {
			current = current->next;
		}
	} while (current && current->next);
	return head;
}

polymer_t* removeChar(polymer_t* head, char character)
{
	polymer_t* current = head;
	polymer_t* before = NULL;
	polymer_t* after = NULL;

	do {
		if (tolower(current->c) == character) {
			after = current->next;
			before = current->previous;
			if (after != NULL) {
				after->previous = before;
			}
			if (before != NULL) {
				before->next = after;
			}
			free(current);
			current = before ? before : after;
			if (current->previous == NULL) {
				head = current;
			}
		}
		current = current->next;
	} while (current->next);
	return head;
}

int main(int argc, char **argv)
{
	polymer_t* head;

	if (argc < 2) {
		printf("Missing file argument.\n");
		exit(1);
	}

	head = malloc(sizeof(polymer_t)); 
	parseFile(head, argv[1]);
	head = react(head);

	printf("5.1: %d\n", count(head));

	int min = INT_MAX;

	for (int i = 0; i < 26; i++) {
		parseFile(head, argv[1]);
		head = removeChar(head, 'a' + i);
		head = react(head);
		int length = count(head);

		if(length < min) {
			min = length;
		}
	}
	printf("5.2: %d\n", min);

	return 0;
}
