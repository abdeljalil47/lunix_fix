#include "../minishell.h"

void error_exit(const char *str)
{
    printf(RED"%s"RESET, str);
    exit (EXIT_FAILURE);
}

void print_error(const char *str)
{
    printf(RED"%s"RESET, str);
}

void write_error(char *str, char *s, char *err)
{
    // printf("%s", str);
    // printf("%s", s);
    // printf("%s\n", err);
    write(2, RED, 5);
    if (str)
        write(2, str, ft_strlen(str));
    if (err)
        write(2, err, ft_strlen(err));
    if (s)
        write(2, s, ft_strlen(s));
    write(2, RESET, 5);
}