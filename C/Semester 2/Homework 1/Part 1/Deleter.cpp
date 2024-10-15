#include "Deleter.h"
#include <iostream>

void deleteZeros(int** a, int &n, int m) {
	int newSize = n;
	for (int i = 0; i < n; i++) {
		bool hasZero = false;
		do {
			hasZero = false;
			for (int j = 0; j < m; j++) {
				if (*(*(a + i) + j) == 0) {
					hasZero = true;
				}
 			}
			if (hasZero) {
				for (int k = i; k < n - 1; k++) {
					for (int j = 0; j < m; j++) {
						*(*(a + k) + j) = *(*(a + k + 1) + j);
					}
				}
				for (int j = 0; j < m; j++) {
					*(*(a + n - 1) + j) = -1;
				}
				newSize--;
			}
		} while (hasZero);
	}
	if (newSize == n) puts("Нет строк, содержащих как минимум один 0.");
	else printf("Удалены все строки, содержащие как минимум один 0.\nИх количество: %d\n", n - newSize);
	n = newSize;
}