#include <cinttypes>
#include <iostream>

using namespace std;

#define LIMIT 1000000

int64_t primesCumSums[80000];
int primesList[80000];
int numprimes;

uint64_t iscompound[1 + ((1 + LIMIT)>>6)];
#define baisset(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) != 0
#define baisclear(ba, i) ((ba)[(i)>>6] & (1ull << ((i) & 63))) == 0
#define baset(ba, i) (ba)[(i)>>6] |= (1ull << ((i) & 63))

void fillprimes(int upperBound);

int main()
{
    fillprimes(LIMIT);
    for(int i = 0; i < numprimes; i++){
        primesCumSums[i+1] = primesList[i]+primesCumSums[i];
    }

    int found = 0;
    for(int len = numprimes-1; !found && len >0; len--){
        for(int bot = 0, top = len; !found && top<=numprimes; top++, bot++){
            int64_t primsum = primesCumSums[top] - primesCumSums[bot];
            if(primsum > LIMIT) break;
            if(baisclear(iscompound, primsum)){
                found = 1;
                printf("len: %d, sum: %d\n", len, primsum);
            }
        }
    }
    
}


void fillprimes(int upperBound) {
	int i, j;

	baset(iscompound, 0);
	baset(iscompound, 1);
	for (i = 2; i*i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
			for (j = i*i; j <= upperBound; j += i) {
				baset(iscompound, j);
			}
		}
	}

	for (; i <= upperBound; i++) {
		if (baisclear(iscompound, i)) {
			primesList[numprimes++] = i;
		}
	}

}