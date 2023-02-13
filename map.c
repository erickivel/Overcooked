#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int readMapFile(struct map *map) {
  FILE *file = fopen("map.txt", "r");

  if (!file) {
    printf("file can't be opened \n");
    fclose(file);
    return 0;
  }

  int err = fscanf(file, "%d %d", &map->maxX, &map->maxY);

  if (err == 1)
    return 0;

  fgetc(file); // remove new line

  int maxX = map->maxX;
  int maxY = map->maxY;

  map->matrix = (char **)malloc(maxY * sizeof(char *));
  if (map->matrix == 0)
    return 0;
  for (int lin = 0; lin < maxY; lin++) {
    map->matrix[lin] = (char *)malloc(maxX * sizeof(char));
    if (map->matrix[lin] == 0)
      return 0;
  }

  for (int line = 0; line < maxY; line++) {
    fgets(map->matrix[line], maxX + 1, file);
    fgetc(file); // remove new line
  }

  fclose(file);

  return 1;
}

struct map *createMap() {
  struct map *newMap = malloc(sizeof *newMap);

  int resReadMapFile = readMapFile(newMap);

  if (!resReadMapFile) {
    printf("Erro ao ler o arquivo do mapa\n");
    return NULL;
  }

  return newMap;
};

int endMap(struct map *map) { return 1; }
