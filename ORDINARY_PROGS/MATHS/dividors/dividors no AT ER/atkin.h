#include <cmath>
#include "unsgnlong.h"

ULONG atkin(ULONG N,ULONG P[]) {

ULONG limit = N;
ULONG sqr_lim;
bool is_prime[N];
ULONG x2, y2;
ULONG i, j;
ULONG n;
ULONG y = 3;
 
// Инициализация решета
sqr_lim = (unsigned long)sqrt((long double)limit);
for (i = 0; i <= limit; i++) is_prime[i] = false;
is_prime[2] = true;
is_prime[3] = true;
 
// Предположительно простые - это целые с нечетным числом
// представлений в данных квадратных формах.
// x2 и y2 - это квадраты i и j (оптимизация).
x2 = 0;
for (i = 1; i <= sqr_lim; i++) {
    x2 += 2 * i - 1;
    y2 = 0;
    for (j = 1; j <= sqr_lim; j++) {
        y2 += 2 * j - 1;
 
        n = 4 * x2 + y2;
        if ((n <= limit) && (n % 12 == 1 || n % 12 == 5))
            is_prime[n] = !is_prime[n];
 
        // n = 3 * x2 + y2; 
        n -= x2; // Оптимизация
        if ((n <= limit) && (n % 12 == 7))
            is_prime[n] = !is_prime[n];
 
        // n = 3 * x2 - y2;
        n -= 2 * y2; // Оптимизация
        if ((i > j) && (n <= limit) && (n % 12 == 11))
            is_prime[n] = !is_prime[n];
    }
}
 
// Отсеиваем кратные квадратам простых чисел в интервале [5, sqrt(limit)].
// (основной этап не может их отсеять)
for (i = 5; i <= sqr_lim; i++) {
    if (is_prime[i]) {
        n = i * i;
        for (j = n; j <= limit; j += n) {
            is_prime[j] = false;
        }
    }
}
 
// Вывод списка простых чисел в консоль.
//printf("2, 3, 5"); 
P[0] = 2; P[1] = 3; P[2] = 5;
for (i = 6; i <= limit; i++) {  // добавлена проверка делимости на 3 и 5. В оригинальной версии алгоритма потребности в ней нет.
    if ((is_prime[i]) && (i % 3 != 0) && (i % 5 !=  0)){
       //printf(", %d", i);
	   P[y++] = i;
    }
}

return y; 
} //O(N/loglogN);