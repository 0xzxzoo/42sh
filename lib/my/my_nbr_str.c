/*
** EPITECH PROJECT, 2025
** my_nbr_str
** File description:
** Implementation of integer-to-string helpers
*/

static void my_rev_str(char *str)
{
    int len = 0;
    char temp;

    while (str[len] != '\0')
        len++;
    for (int i = 0; i < len / 2; i++) {
        temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

static int write_digits(int nbr, char *buffer, int i)
{
    while (nbr > 0) {
        buffer[i] = (nbr % 10) + '0';
        nbr /= 10;
        i++;
    }
    return i;
}

static int handle_zero(char *buffer, int i)
{
    buffer[i] = '0';
    buffer[i + 1] = '\0';
    return i + 1;
}

int my_put_nbr_in_str(int nbr, char *buffer, int start)
{
    int i = start;
    int sign = 0;

    if (nbr == 0)
        return handle_zero(buffer, i);
    if (nbr < 0) {
        sign = 1;
        nbr = -nbr;
    }
    i = write_digits(nbr, buffer, i);
    if (sign) {
        buffer[i] = '-';
        i++;
    }
    buffer[i] = '\0';
    my_rev_str(buffer + start);
    return i;
}
