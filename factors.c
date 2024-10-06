#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/**
 * trial_division - Find factors using trial division
 * @num: String containing the number to factorize
 *
 * Description: This function attempts to factorize the given number
 * using trial division method.
 */
void trial_division(char *num)
{
	unsigned long long n;
	unsigned long long i;
	char *endptr;

	/* Convert string to number, checking for conversion errors */
	n = strtoull(num, &endptr, 10);

	/* If number is too large, print as is (handle in Python script) */
	if (*endptr != '\n' && *endptr != '\0')
	{
		printf("%s", num);
		return;
	}

	/* Check even numbers first */
	if (n % 2 == 0)
	{
		printf("%llu=%llu*2\n", n, n / 2);
		return;
	}

	/* Try odd numbers */
	for (i = 3; i <= sqrt(n); i += 2)
	{
		if (n % i == 0)
		{
			printf("%llu=%llu*%llu\n", n, n / i, i);
			return;
		}
	}

	/* If no factors found, print the number itself */
	printf("%llu=%llu*1\n", n, n);
}

/**
 * main - Entry point
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, 1 on failure
 *
 * Description: This function reads numbers from a file and factorizes them.
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char line[1024];
	clock_t start;

	/* Check for correct argument count */
	if (argc != 2)
		return (1);

	/* Open the file for reading */
	file = fopen(argv[1], "r");
	if (!file)
		return (1);

	/* Start the timer */
	start = clock();

	/* Process each line in the file */
	while (fgets(line, sizeof(line), file))
	{
		/* Check time limit (5 seconds) */
		if ((double)(clock() - start) / CLOCKS_PER_SEC > 4.5)
			break;

		/* Remove trailing newline if present */
		line[strcspn(line, "\n")] = 0;
		trial_division(line);
	}

	fclose(file);
	return (0);
}
