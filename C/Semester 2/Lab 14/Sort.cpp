#include <math.h>
#include "Sort.h"

void SortStr(float* a, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && fabs(*(a + j - 1)) < fabs(*(a + j)); j--) {
			float c = *(a + j - 1);
			*(a + j - 1) = *(a + j);
			*(a + j) = c;
		}
	}
}