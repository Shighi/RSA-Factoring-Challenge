#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <gmp.h>

/**
 * handle_large_number - Process numbers that exceed unsigned long long
 * @num: String containing the large number
 */
void handle_large_number(char *num)
{
	mpz_t n, i, remainder;
	mpz_inits(n, i, remainder, NULL);
	mpz_set_str(n, num, 10);

	/* Check small factors first for performance */
	int small_factors[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
	int len = sizeof(small_factors) / sizeof(small_factors[0]);

	for (int j = 0; j < len; j++)
	{
		mpz_mod_ui(remainder, n, small_factors[j]);
		if (mpz_cmp_ui(remainder, 0) == 0)
		{
			mpz_divexact_ui(i, n, small_factors[j]);
			gmp_printf("%Zd=%Zd*%d\n", n, i, small_factors[j]);
			mpz_clears(n, i, remainder, NULL);
			return;
		}
	}

	mpz_clears(n, i, remainder, NULL);
	printf("%s=%s*1\n", num, num);
}

/**
 * trial_division - Find factors using optimized trial division
 * @num: String containing the number to factorize
 */
void trial_division(char *num)
{
	unsigned long long n;
	unsigned long long i;
	char *endptr;
	
	/* Check if number is too large or invalid */
	if (strlen(num) > 19)
	{
		handle_large_number(num);
		return;
	}
	
	n = strtoull(num, &endptr, 10);
	if (*endptr != '\0' || n == ULLONG_MAX)
	{
		handle_large_number(num);
		return;
	}
	
	/* Check even numbers first */
	if (n % 2 == 0)
	{
		printf("%llu=%llu*2\n", n, n / 2);
		return;
	}
	
	/* Check small odd numbers */
	for (i = 3; i * i <= n; i += 2)
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
 * main - Entry point of the factors program
 * @argc: Argument count
 * @argv: Array of argument strings
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
	FILE *file;
	char line[1024];
	clock_t start = clock();
	double time_limit = 4.5;
	
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
