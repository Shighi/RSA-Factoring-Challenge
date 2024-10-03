#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * factorize - Factorize a number and print the result
 * @n: The number to factorize
 *
 * This function finds the smallest factor of n and prints the factorization.
 */
void factorize(unsigned long long n)
{
	unsigned long long i;

	for (i = 2; i * i <= n; i++)
	{
		if (n % i == 0)
		{
			printf("%llu=%llu*%llu\n", n, n / i, i);
			return;
		}
	}
	printf("%llu=%llu*1\n", n, n);
}

/**
 * process_file - Process each line from the input file
 * @file: Pointer to the input file
 *
 * This function reads each line from the file, converts it to a number,
 * and calls the factorize function if the number is greater than 1.
 */
void process_file(FILE *file)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned long long n;

	while ((read = getline(&line, &len, file)) != -1)
	{
		n = strtoull(line, NULL, 10);
		if (n > 1)
			factorize(n);
	}

	free(line);
}

/**
 * main - Entry point of the program
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 *
 * Return: 0 on success, 1 on failure
 *
 * This function checks the command-line arguments, opens the input file,
 * calls process_file to handle the file contents, and then closes the file.
 */
int main(int argc, char *argv[])
{
	FILE *file;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return (1);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		return (1);
	}

	process_file(file);

	fclose(file);
	return (0);
}
