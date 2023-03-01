#include"../types.h"

#include<stdlib.h>
#include<string.h>

const char superscripts[10][20] = {
    "\u2070",
    "\u00B9",
    "\u00B2",
    "\u00B3",
    "\u2074",
    "\u2075",
    "\u2076",
    "\u2076",
    "\u2078",
    "\u2079",
};

char *superscript_convert(uint value)
{
    uint digit[10];
    uint count_digit = 0;

    while (value >= 1)
    {
        digit[count_digit++] = value % 10;
        value /= 10;
    }

    char *new_value = malloc((6 * count_digit + 1) * sizeof(char));

    while (count_digit--)
    {
        strcat(new_value, superscripts[digit[count_digit]]);
    }

    return new_value;
}
