#ifndef MEAL_H
#define MEAL_H

struct ingredient {
	char val;
	struct ingredient* next;
};

struct meal {
	int size;
	struct ingredient* top;
};

struct meal* newMeal();

int addIngredient(struct meal* meal, char val);

struct ingredient* removeIngredient(struct meal* meal);

int deleteMeal(struct meal* meal);

#endif /* MEAL_H */
