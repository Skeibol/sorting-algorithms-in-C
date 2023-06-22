#ifndef MYSTRING_H
#define MYSTRING_H
#include <stdio.h>

size_t stringLength(const char *a);
void mystrcmp(char *a, char *b);

size_t stringLength(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0')
    {
        length++;
    }
    return length;
}

void mystrcmp(char *str1, char *str2)
{
    size_t strLen = stringLength(str1);
    int isEqual = 1;
    if (strLen != stringLength(str2))
    {
        isEqual = 0;
    }

    for (size_t i = 0; i < strLen; i++)
    {
        if (*str1 != *str2)
        {
            isEqual = 0;
        }
        str2++;
        str1++;
    }
    if (isEqual)
    {
        printf("\nStrings are equal");
    }
    else
    {
        printf("\nStrings are not equal");
    };

}

#endif

