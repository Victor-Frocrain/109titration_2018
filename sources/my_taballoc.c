/*
** EPITECH PROJECT, 2019
** my_taballoc
** File description:
** my_taballoc
*/

#include "titration.h"

char **my_taballoc(char **tab)
{
    char **result = NULL;
    int len = 0;

    for (len = 0; tab && tab[len]; len++);
    if ((result = malloc(sizeof(char *) * (len + 2))) == NULL)
        return (NULL);
    for (int i = 0; tab && tab[i]; i++) {
        if ((result[i] = malloc(sizeof(char) * strlen(tab[i]))) == NULL)
            return (NULL);
        result[i] = strcpy(result[i], tab[i]);
    }
    result[len + 1] = NULL;
    return (result);
}
