#include"screenshot.h"

int main()
{
	clock_t t1 = clock();
	int i;
	int iterations = 10;
	for (i = 0; i < iterations; i++)
	{
		giscreen();
	}
	clock_t t2 = clock();
	printf("%d iteration: %0.0f fps\n", iterations, iterations / ((double)(t2 - t1) / CLOCKS_PER_SEC));
	return 0;
}