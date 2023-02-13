#include <stdlib.h>

#include "meal.h"
#include "order.h"

int clientId = 1;

struct orderQueue *createOrderQueue() {
  struct orderQueue *newOrderQueue = malloc(sizeof(struct orderQueue));

  newOrderQueue->lastOrder = NULL;
  newOrderQueue->firstOrder = NULL;
  newOrderQueue->size = 0;

  return newOrderQueue;
}

struct order *createOrder(struct meal *meal) {
  struct order *newOrder = malloc(sizeof(struct order));

  newOrder->meal = meal;
  newOrder->clientId = clientId;
  clientId++;
  newOrder->next = NULL;
  newOrder->prev = NULL;

  return newOrder;
}

void pushOrder(struct orderQueue *queue, struct order *order) {
  if (queue->size == 0) {
    queue->firstOrder = order;
    queue->lastOrder = order;
    queue->size = 1;

    return;
  }

  if (queue->size == 1) {
    queue->firstOrder->next = order;
    order->prev = queue->firstOrder;
    queue->lastOrder = order;
    queue->size = 2;

    return;
  }

  order->prev = queue->lastOrder;
  queue->lastOrder->next = order;
  queue->lastOrder = order;
  queue->size += 1;

  return;
}

int popOrder(struct orderQueue *queue) {
  if (queue->size == 0)
    return 0;

  struct order *oldFirstOrder = queue->firstOrder;

  if (queue->size == 1) {
    queue->size = 0;
    queue->firstOrder = NULL;
    queue->lastOrder = NULL;
  } else {
    queue->firstOrder = oldFirstOrder->next;
    queue->size -= 1;
  }

  deleteMeal(oldFirstOrder->meal);
  free(oldFirstOrder);

  return 1;
}

void populateOrderQueue(struct orderQueue *queue, int num) {
  for (int i = 0; i < num; i++) {
    struct meal *meal = createRandomMeal();
    struct order *order = createOrder(meal);

    pushOrder(queue, order);
  }
}

void deleteOrderQueue(struct orderQueue *queue) { free(queue); }
