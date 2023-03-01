#include<stdio.h>

typedef unsigned int uint;

#define P 0b00000001
#define R 0b00000010
#define L 0b00000100
#define W 0b00001000

#define PW 0b00010000
#define RW 0b00100000

void draw(uint obj)
{
    if (obj == 0)
    {
        printf("                            ");
    }

    if (obj == W)
        printf("                           |");

    if (obj & R)
        printf(" 0/0⁰ 0/0⁰ 0/0⁰ 0/0⁰ 0/0⁰  %c", (obj & W) ?'|' :' ');

    if (obj & P)
    {
        printf(" [Player]                  %c", (obj & W) ?'|' :' ');
    }

    if (obj & L)
        printf("----------------------------");
}

uint amount_rounds_get(uint field)
{
    uint rounds = 0;
    while (field > 1)
    {
        field /= 2;
        rounds++;
    }

    return rounds + 1;
}

int main(int argc, char **argv)
{
    uint field = 128;
    uint amount_rounds = amount_rounds_get(field);
    uint width = 28;

    /* shown range */
    uint range_shown = 2;
    uint range_offset = 3;

    /* amount_rounds */
    char wall = '|';
    char *player = "[Player]";
    char line = '-';

    uint row, col, round = 0;
    for (row = 0; row < field * 2; row++)
    {
        round = 0;
        uint offset = 0;
        uint modulo = 2;
        for (col = 0; col < amount_rounds; col++, offset = 2 * offset + 1, modulo *= 2)
        {
            if (col >= range_offset && col < range_offset + range_shown)
            {
                uint obj = 0, i;

                if (row % modulo == offset)
                    obj |= P;
                if (row % modulo == offset + 1)
                    obj |= L;
                if (col > 0 && row % modulo == offset + 2)
                    obj |= R;
                if (col < amount_rounds - 1)
                    for (i = 0; i < 2 * offset + 1; i++)
                        if (row % (modulo * 2) == offset + 2 + i)
                            obj |= W;

                draw(obj);
            }
        }

        putchar('\n');
    }


    return 0;
}
