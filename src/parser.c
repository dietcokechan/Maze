#include "../inc/maze.h"

/**
 * concat - concatenates two strings
 * @s1: destination string
 * @s2: source string to concatenate
 * Return: concatenated string
 */
char *concat(const char *s1, const char *s2)
{
	char *result = NULL;

	result = malloc(strlen(s1) + strlen(s2) + 1);
	if (!result)
		return (NULL);

	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

/**
 * free_map - frees map
 * @map: map instance
 */
void free_map(Map *map)
{
	int i;

	for (i = 0; i < map->x; i++)
		free(&map->map[i]);
	free(map->map);
}
