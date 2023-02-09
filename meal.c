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

// Push
int addIngredient(struct meal* meal, char value) {
	struct ingredient* ing = createIngredient(value);
	
	if (meal->size == 0)	{
		meal->top = ing;
		meal->size = 1;
		return 1;
	}

	struct ingredient* oldTop = meal->top;
	meal->top = ing;
	ing->next = oldTop;
	meal->size += 1;

	return 1;
};

// Pop
struct ingredient* removeIngredient(struct meal* meal) {
	if (meal->size == 0) 
		return NULL;

	struct ingredient* ing = meal->top;
	meal->top = meal->top->next;
	meal->size -= 1;

	return ing;
};

int deliverMeal(struct meal* meal) {
	
}

int deleteMeal(struct meal* meal) {
	struct ingredient* lastIngredient = meal->top;
	struct ingredient* currentIngredient = meal->top;

	while (lastIngredient != NULL) {
		free(lastIngredient);
		lastIngredient
	}
};
