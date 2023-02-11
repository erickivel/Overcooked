#ifndef ORDER_H
#define ORDER_H

struct order {
  struct meal *meal;
  int clientId;
  struct order *prev;
  struct order *next;
};

struct orderQueue {
  struct order *firstOrder;
  struct order *lastOrder;
  int size;
};

struct orderQueue *createOrderQueue();

void populateOrderQueue(struct orderQueue *queue, int num);

void pushOrder(struct orderQueue *queue, struct order *order);

int popOrder(struct orderQueue *queue);

void deleteOrderQueue(struct orderQueue *queue);

#endif /* ORDER_H */
