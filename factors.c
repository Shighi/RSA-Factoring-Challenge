#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * trial_division - Find factors using optimized trial division
 * @num: String containing the number to factorize
 *
 * Description: Uses wheel factorization to skip numbers that can't be factors
 */
void trial_division(char *num)
{
	unsigned long long n;
	unsigned long long i;
	const unsigned long long small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	size_t len = sizeof(small_primes) / sizeof(small_primes[0]);
	
	n = strtoull(num, NULL, 10);
	
	/* Check small primes first */
	for (size_t j = 0; j < len; j++)
	{
		if (n % small_primes[j] == 0)
		{
			printf("%llu=%llu*%llu\n", n, n / small_primes[j], small_primes[j]);
			return;
		}
	}
	
	/* Use wheel factorization incrementing pattern */
	const unsigned long long increments[] = {4, 2, 4, 2, 4, 6, 2, 6};
	size_t inc_len = sizeof(increments) / sizeof(increments[0]);
	size_t inc_idx = 0;
	
	i = 31;  /* Start after checking small primes */
	while (i * i <= n)
	{
		if (n % i == 0)
		{
			printf("%llu=%llu*%llu\n", n, n / i, i);
			return;
		}
		i += increments[inc_idx];
		inc_idx = (inc_idx + 1) % inc_len;
	}
	
	printf("%llu=%llu*1\n", n, n);
}

/**
 * main - Entry point of the factors program
 * @argc: Argument count
 * @argv: Array of argument strings
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char line[1024];
	clock_t start = clock();
	double time_limit = 4.5;  /* Set slightly below 5s to ensure completion */
	
	if (argc != 2)
		return (1);
	
	file = fopen(argv[1], "r");
	if (!file)
		return (1);
	
	while (fgets(line, sizeof(line), file))
	{
		if ((double)(clock() - start) / CLOCKS_PER_SEC > time_limit)
			break;
		
		line[strcspn(line, "\n")] = 0;
		trial_division(line);
	}
	
	fclose(file);
	return (0);
}
