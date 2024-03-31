#include "../inc/maze.h"

/**
 * close_file - close file
 * @fp: file ptr
 */
void close_file(FILE *fp)
{
	if (fp)
		fclose(fp);
}

/**
 * open_file - open file
 * @filename: file name
 * Return: file ptr
 */
FILE *open_file(char *filename)
{
	FILE *fp = NULL;

	fp = fopen(filename, "r");
	if (!fp)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	return (fp);
}

/**
 * read_file - reads content of file and parses it
 * @fp: file
 * Return: map struct
 */
Map read_file(FILE *fp)
{
	Map map = {0, 0, 0, NULL};
	int i = 0;
	int capacity = 100;
	int *integers = (int *)malloc(capacity * sizeof(int));
	int count = 0;
	int number;
	int size = 0;

	while (fscanf(fp, "%d", &number) == 1)
	{
		if (count == capacity)
		{
			capacity *= 2;
			integers = (int *)realloc(integers, capacity * sizeof(int));
		}
		integers[count] = number;
		count++;
	}

	size = count;

	map.size = size;
	map.x = map.y = sqrt(size);

	map.map = integers;

	return (map);
}

/**
 * handle_file - call functions to handle file
 * @filename: file name
 * Return: map
 */
Map handle_file(char *filename)
{
	FILE *fp = NULL;

	fp = open_file(filename);
	Map map = read_file(fp);
	
	close_file(fp);

	return (map);
}
