/*
** EPITECH PROJECT, 2019
** compute_values
** File description:
** compute_values
*/

#include "titration.h"

double **my_new_alloc(double **tab)
{
    int len = 0;
    double **copy = NULL;

    for (len = 0; tab && tab[len]; len++);
    if ((copy = malloc(sizeof(double *) * (len + 2))) == NULL)
        return (NULL);
    for (int i = 0; tab && tab[i]; i++) {
        if ((copy[i] = malloc(sizeof(double) * 4)) == NULL)
            return (NULL);
        for (int j = 0; tab && tab[i] && tab[i][j]; j++) {
            copy[i][j] = tab[i][j];
        }
        copy[i][2] = 0;
        copy[i][3] = 0;
    }
    if ((copy[len] = malloc(sizeof(double) * 4)) == NULL)
        return (NULL);
    for (int i = 0; i < 4; i++)
        copy[len][i] = 0;
    copy[len + 1] = NULL;
    return (copy);
}

char *cut_string(char *str, int nb)
{
    int i = 0;
    char *result = malloc(sizeof(char) * strlen(str));

    if (result == NULL)
        return (NULL);
    if (nb == 2)
        for (i = 0; str && str[i] && str[i] != ';'; i++);
    if (str[i] == ';')
        i++;
    for (int j = 0; str && str[i] && str[i] != ';'; i++) {
        result[j] = str[i];
        j++;
    }
    return (result);
}

void reorder_values(titration_t *values)
{
    double temp1 = 0;
    double temp2 = 0;

    for (int i = 0; values->values && values->values[i] && values->values[i][0] &&
    values->values[i][1]; i++) {
        temp1 = values->values[i][0];
        temp2 = values->values[i][1];
        for (int k = 0; values->values && values->values[k] && values->values[k][0] &&
        values->values[k][1]; k++) {
            if (temp1 > values->values[k][0] && k > i) {
                values->values[i][0] = values->values[k][0];
                values->values[i][1] = values->values[k][1];
                values->values[k][0] = temp1;
                values->values[k][1] = temp2;
                i = 0;
                break;
            }
        }
    }
}

bool compute_values(char **tab)
{
    titration_t *values;

    if ((values = malloc(sizeof(titration_t))) == NULL)
        return (false);
    for (int i = 0; tab && tab[i]; i++) {
        if ((values->values = my_new_alloc(values->values)) == NULL)
            return (false);
        values->values[i][0] = strtod(cut_string(tab[i], 1), NULL);
        values->values[i][1] = strtod(cut_string(tab[i], 2), NULL);
    }
    reorder_values(values);
    compute_derivative(values);
    return (true);
}
