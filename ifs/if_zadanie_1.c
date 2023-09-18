#include <limits.h>
#include <math.h>
#include <stdio.h>

int x = 0, y = 0;

int main() {
    scanf("%d", &x); 
    scanf("%d", &y); 
    printf("%d + %d = %d\n", x, y, x + y);
    printf("++%d = %d\n", x, x + 1);
    printf("%d - %d = %d\n", x, y, x - y);
    printf("%d * %d = %d\n", x, y, x * y);
    if (y == 0) {
        printf("exception: 0 division\n");
    } else {
        printf("%d / %d = %d\n", x, y, x / y);
        printf("%d %% %d = %d\n", x, y, x % y);
    }
    printf("%d == %d = %d\n",x, y, x == y);
    printf("%d != %d = %d\n",x, y, x != y);
    printf("%d > %d = %d\n",x, y, x > y);
    printf("%d >= %d = %d\n",x, y, x >= y);
    printf("%d < %d = %d\n",x, y, x < y);
    printf("%d <= %d = %d\n",x, y, x <= y);
    printf("%d && %d = %d\n",x, y, x && y);
    printf("%d || %d = %d\n",x, y, x || y);
    printf("%d ^^ %d = %d\n",x, y, !x != !y);
    printf("!%d = %d\n", x, !x);
    printf("%d & %d = %d\n",x, y, x & y);
    printf("%d | %d = %d\n",x, y, x | y);
    printf("%d ^ %d = %d\n",x, y, x ^ y);
    int overflow = INT_MAX + 1;
    long long check =  (~((long long)pow(2, 31))) + 1;
    printf("%d == %lld = %d\n", overflow, check, overflow == check);
}
