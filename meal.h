#ifndef MEAL_H
#define MEAL_H

struct ingredient {
	char val;
	struct ingredient* next;
}

struct meal {
	int size;
	struct ingredient* top;
}

int push(struct meal* meal, struct ingredient* ingredient);

struct meal* pop(struct meal* meal);

#endif /* MEAL_H */
