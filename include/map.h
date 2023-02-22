#ifndef MAP_H
#define MAP_H

#include <stdio.h>

struct map {
  int maxX;
  int maxY;
  char **matrix;
};

struct map *createMap(char *mapPath);

int endMap(struct map *map);

#endif /* MAP_H */
