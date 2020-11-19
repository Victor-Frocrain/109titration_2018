/*
** EPITECH PROJECT, 2019
** titration
** File description:
** titration
*/

#include "titration.h"

void display_usage(void)
{
    char *str = NULL;
    int fd = open("README", O_RDONLY);

    if (fd < 0)
        return;
    str = get_next_line(fd);
    while (str) {
        printf("%s\n", str);
        free(str);
        str = get_next_line(fd);
    }
    close(fd);
    exit(MY_EXIT_SUCCESS);
}

bool parse_line(char *str)
{
    int i = 0;

    for (i = 0; str && str[i] && str[i] != ';'; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
            return (false);
    }
    if (str[i] != ';')
        return (false);
    for (i++; str && str[i]; i++) {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
            return (false);
    }
    if (i < 3)
        return (false);
    return (true);
}

char **check_values(char *path, char **tab)
{
    int fd = open(path, O_RDONLY);
    char *str = NULL;

    if (fd < 0)
        return (NULL);
    str = get_next_line(fd);
    for (int i = 0; str; i++) {
        if ((tab = my_taballoc(tab)) == NULL)
            return (NULL);
        if ((tab[i] = malloc(sizeof(char) * strlen(str))) == NULL)
            return (NULL);
        tab[i] = strcpy(tab[i], str);
        if (parse_line(tab[i]) == false)
            return (NULL);
        free(str);
        str = get_next_line(fd);
    }
    return (tab);
}

char **parser(int ac, char **av, char **tab)
{
    if (ac != 2)
        return (NULL);
    if (strcmp(av[1], "-h") == 0)
        display_usage();
    tab = check_values(av[1], tab);
    return (tab);
}

int titration(int ac, char **av)
{
    char **tab = NULL;

    if ((tab = parser(ac, av, tab)) == NULL)
        return (MY_EXIT_ERROR);
    compute_values(tab);
    return (MY_EXIT_SUCCESS);
}
