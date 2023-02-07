#include"stdlib.h"

#include"meal.h"

struct ingredient* createIngredient(char val) {
	struct ingredient* newIngredient = malloc(sizeof(struct ingredient));

	newIngredient->val = val;
	newIngredient->next = NULL;

	return newIngredient;
};

struct meal* newMeal() {
	struct meal* newMeal = malloc(sizeof(struct meal));

	newMeal->size = 0;
	newMeal->top = NULL;

	return newMeal;
}

int push(struct meal* meal, struct ingredient* ingredient) {};

struct meal* pop(struct meal* meal) {};

int deleteMeal(struct meal* meal) {
	struct ingredient* lastIngredient = meal->top;
	struct ingredient* currentIngredient = meal->top;

	while (lastIngredient != NULL) {
		free(lastIngredient):
		lastIngredient
	}
};
