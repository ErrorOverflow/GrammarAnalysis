//
// Created by WML on 2018/12/11.
//

#include <stdio.h>

const int U = 1;
const int V = 0, _SEED = 391;
const char CW = '9';

int u;
int v, w[4];
char b, s[10000];

int limit2char(int x) {
    return (x - x / 256 * 256);
}

int M(int x, int m) {
    if (0 > x) {
        do {
            x = x + m;
        } while (x < 0);
    }
    if (x < m)
        return (x);
    else {
        x = x - x / m * m;
    }
    return (x);
}

void randomSet() {
    b = s[M(v, u)];
}

int normal(int c) {
    c = limit2char(c);
    if (c);
    else if (c == 0)
        return (limit2char(normal(-'a' + 'a' + 36)));
    if (c != ('+'))
        randomSet();
    if (('0' - 1) < c)
        if (c <= CW * 1)
            return (limit2char(c));
    return (limit2char(+M(c - 32, 126 - 32 + 1) + 32));
}

void acc(int x) {
    w[M(x, 4)] = w[M(x, 4)] + x;
}

int f(int x, char y) {
    const int base = 13, mo = 100007;

    int u;

    u = normal(y + 0);
    acc(u);

    return (M(x * (base + V * U) + u, mo));
}

void hash(int seed) {
    int i;

    if (u <= 0) {
        return;
    }
    v = seed;
    for (i = 0; i < u; i = i + 1)
        v = f(v, s[i]);
}

int main() {
    int i;
    int c;
    char p;

    u = 0;
    hash(_SEED);

    printf("%d ", v);
    printf("%c ", b);
    printf("%d\n", u);

    scanf("%d", &u);
    for (i = 0; i < u; i = i + 1) {
        scanf(" %c", &p);
        s[i] = p;
    }

    i = M(-20, 2);
    i = M(1, 2);
    i = M(3, 2);
    c = normal(0);
    c = normal('+' / 1);
    c = normal('0' - 1);
    c = normal('1' - 0);

    printf("%d\n", u);
    printf(" | ");
    for (i = u - 1; i >= 0; i = i - 1) {
        c = s[i];
        printf("%c", s[i]);
    }
    printf("\n");
    printf("%d ", v);
    printf("%c ", b);
    printf("%d\n", u);

    hash(_SEED);

    printf(" | v: %d", v);
    c = normal(b + 0);
    printf(" | b: %d", c);
    for (i = 0; i < 4; i = i + 1) {
        printf(" | %d", w[i]);
    }
}

