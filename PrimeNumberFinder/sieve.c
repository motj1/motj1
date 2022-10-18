//gcc SieveOEratostheles.c -O2 -oSieve
//.038 fastest for 1000000 27.552 for 1000000000
// O(N log (log N))
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char **ptr;
    if (argc > 1)
	    unsigned long long n = strtoull(argv[1], ptr, 0);
    else { printf("Please enter your desired length.\n"); exit(1) }
	_Bool *sieve = (_Bool *) malloc(n * sizeof(_Bool));
	
	for (unsigned long long x = 2; x <= n; x++) {
		if (sieve[x]) continue;
		for (unsigned long long u = x*2; u<=n; u+=x) sieve[u] = 1;
	}
	unsigned long long number = 0;
	FILE *out = fopen("out.txt", "w");
	for (unsigned long long x = 2; x <= n; x++) if (!sieve[x]) fprintf(out, "%llu\n",x);
	fclose(out);
	free(sieve);
}