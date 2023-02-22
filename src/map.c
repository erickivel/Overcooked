#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int readMapFile(struct map *map, char *mapPath) {
  FILE *file = fopen(mapPath, "r");

  if (!file) {
    printf("file can't be opened \n");
    fclose(file);
    return 0;
  }

  int err = fscanf(file, "%d %d", &map->maxX, &map->maxY);

  if (err == 1)
    return 0;

  (void)fgetc(file); // remove new line

  int maxX = map->maxX;
  int maxY = map->maxY;

  map->matrix = malloc(maxY * sizeof(char *));
  if (map->matrix == 0)
    return 0;
  for (int lin = 0; lin < maxY; lin++) {
    map->matrix[lin] = malloc(maxX * sizeof(char) + 1);
    if (map->matrix[lin] == 0)
      return 0;
  }

  for (int line = 0; line < maxY; line++) {
    (void)fgets(map->matrix[line], maxX + 1, file);
    (void)fgetc(file); // remove new line
  }

  fclose(file);

  return 1;
}

struct map *createMap(char *mapPath) {
  struct map *newMap = malloc(sizeof *newMap);

  int resReadMapFile = readMapFile(newMap, mapPath);

  if (!resReadMapFile) {
    printf("Erro ao ler o arquivo do mapa\n");
    return NULL;
  }

  return newMap;
}

int endMap(struct map *map) {
  for (int i = 0; i < map->maxY; i++) {
    free(map->matrix[i]);
  }

  free(map->matrix);
  free(map);

  return 1;
}
