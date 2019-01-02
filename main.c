#include <stdio.h>

const char T = 'T', underline = '_';
const int One = 1, one = -1;
char True[4];
char False[5], char_flag;
int int_flag;

int list[101], n;


void quicksort(int left, int right) {
    int i, j, t, temp, _temp, _con;
    if (left > right)
        return;
    temp = list[left];
    i = left;
    j = right;
    if (i != j)
        do {
            _con = 0;
            if (list[j] >= temp)
                if (i < j)
                    _con = 1;
            for (_temp = 0; _con; _temp = _temp + 1) {
                j = j - 1;
                _con = 0;
                if (list[j] >= temp)
                    if (i < j)
                        _con = 1;
            }
            _con = 0;
            if (list[i] <= temp)
                if (i < j)
                    _con = 1;
            for (_temp = 0; _con; _temp = _temp + 1) {
                i = i + 1;
                _con = 0;
                if (list[i] <= temp)
                    if (i < j)
                        _con = 1;
            }
            if (i < j) {
                t = list[i];
                list[i] = list[j];
                list[j] = t;
            }
        } while (i != j);
    list[left] = list[i];
    list[i] = temp;

    quicksort(left, i - 1);
    quicksort(i + 1, right);
}


int F(int no) {
    if (no == 0)
        return (1);
    if (no == 1)
        return (1);
    return (F(no - 1) + F(no - 2));
}

void bg(int a, int b) {
    int temp, i;
    if (a > b)
        temp = 3;
    else
        temp = 4;
    if (temp >= 3)
        if (temp != 4) {
            if ((True[temp]) != ('/'))
                printf("error10");
            else {
                return;
            }
        } else if ((False[temp]) != ('-'))
            printf("error11");
    True[2] = 'T';
}

void _printf() {
    printf(" T is %c", T);
    printf(" underline is %d", underline);
}

char _scanf() {
    char temp;
    scanf(" %c", &temp);
    return (temp);
}

char int2char(int no) {
    if (no == 43)
        return ('+');
    if (no == 45)
        return ('-');
    if (no == 42)
        return ('*');
    if (no == 47)
        return ('/');
    if (no <= 57)
        if (no >= 48)
            return ('1');
    if (no <= 90)
        if (no >= 65)
            return ('A');
    if (no <= 122)
        if (no >= 97)
            return ('a');
    return ('0');
}

int ascii2int(char chtemp) {
    return ((chtemp));
}

int sum(int a1, int a2, char a3, int a4, int a5,
        int a6) {//GrammarAnalysis main.cpp WordAnalysis.cpp WordAnalysis.h FileIO.cpp FileIO.h lib.cpp lib.h LexicalAnalysis.cpp LexicalAnalysis.h Exception.cpp Exception.h MipsGenerate.cpp MipsGenerate.h PCodeGenerate.cpp PCodeGenerate.h
    int temp;
    temp = a1 + a2 + a3 + a4 + a5 + a6;
    return (temp);
}

int conFun() {
    return (10);
}

void main() {
    const int con = 15;
    const char charcon = '1';
    char proc, iproc, chtemp;
    int a, b, array[3];
    int i, j, itemp;
    True[0] = 'T';
    True[1] = 'r';
    True[2] = '*';
    True[3] = '/';
    False[0] = 'F';
    False[1] = 'a';
    False[2] = 'l';
    False[3] = '+';
    False[4] = '-';

    scanf(" %c", &chtemp);
    a = ascii2int(chtemp);
    printf("'s ascii is ");
    printf("%d\n", a);
    chtemp = _scanf();
    printf(" again, is %c\n", chtemp);
    scanf("%d", &itemp);
    printf("%d\n", F(itemp));
    b = 20;
    b = F(b);
    if (b != 10946)
        printf(" error1 ");

    for (i = 0; i < 3; i = i + 1) {
        array[i] = i;
    }
    array[i - 3] = 10;
    b = 2;
    for (i = 1; i >= 0; i = i - 1)
        if (array[i] > array[b])
            b = i;
    if (array[b] != 10)
        printf(" error2 ");
    printf(" sum is ");
    printf("%d\n", -1 + (array[0] + array[1] + array[2]) * +3 / 3 + -10 / -10 + b - b);

    a = 13;
    bg(a, 12);

    _printf();
    chtemp = 'b';
    if ((chtemp)) {
        char_flag = 'a';
        itemp = 0;
        do {
            for (i = 1; i < 6; i = i + 1)
                itemp = itemp + i;
        } while (itemp <= (char_flag));
        if (itemp <= (char_flag))
            printf(" error4 ");
    } else {
        printf(" error5 ");
    }


    n = 10;
    list[10] = 9;
    list[1] = 8;
    list[2] = 6;
    list[3] = 4;
    list[4] = 7;
    list[5] = 3;
    list[6] = 2;
    list[7] = 1;
    list[8] = 0;
    list[9] = 5;
    quicksort(1, n);
    for (i = 1; i <= n; i = i + 1)
        if (list[i] != i - 1)
            printf(" error6 ");

    itemp = 99;
    chtemp = int2char(itemp);
    if ((chtemp) != ('a'))
        printf(" error7 ");
    if (ascii2int(int2char(itemp)) > 97)
        printf("error12");
    if (ascii2int(int2char(2)) > 60)
        printf("error13");
    bg(itemp, ascii2int(chtemp));

    if (sum(list[10], sum(1, 2, '1', 4, 5, 6), True[2], 20, con, conFun()) != 163) {
        printf(" error8 ");
    }

    printf(" empty string");
    printf("");
    printf("Yeah");
    //printf("!0#1$2%3&4'5(6)7*8+9,a-b.c/d~e:f;g<h=i>j?k@lm[n\o]p^q_r`st{y|u}v");
    printf("%c\n", charcon);
    printf("wxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ ");

}