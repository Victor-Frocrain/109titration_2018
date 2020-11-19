/*
** EPITECH PROJECT, 2019
** compute_all
** File description:
** compute_all
*/

#include "titration.h"

bool detect_equivalent(double nb, double eq)
{
    if (nb < 0 && nb > eq)
        return (true);
    if (nb >= 0 && nb < eq)
        return (true);
    return (false);
}

void second_estimated(titration_t *values, int mem)
{
    double a = 0;
    double b = 0;
    double result = 0;
    double end = values->values[mem + 1][0];
    double eq = 0;

    if (mem == 0 || !values->values[mem + 1])
        return;
    printf("\nSecond derivative estimated:\n");
    for (double step = values->values[mem - 1][0]; step <= end;
    step += 0.1) {
        if (step >= values->values[mem][0])
            mem++;
        a = (values->values[mem][3] - values->values[mem - 1][3]) /
        (values->values[mem][0] - values->values[mem - 1][0]);
        b = values->values[mem - 1][3] - a * values->values[mem - 1][0];
        result = a * step + b;
        if (detect_equivalent(result, eq) || step == values->values[mem - 1][0])
            eq = step;
        printf("%.1f ml -> %.2f\n", step, result);
    }
    printf("\nEquivalent point at %.1f ml\n", eq);
}

void second_derivative(titration_t *values, int mem)
{
    printf("\nSecond derivative:\n");
    for (int i = 2; i > 1 && values->values[i] && values->values[i - 1] &&
    values->values[i + 1]; i++) {
        if (values->values[i + 1][0] - values->values[i - 1][0] == 0)
            exit(MY_EXIT_ERROR);
        values->values[i][3] = (values->values[i + 1][2] - values->values[i - 1][2]) /
        (values->values[i + 1][0] - values->values[i - 1][0]);
    }
    for (int i = 2; values->values[i] && values->values[i + 2]; i++)
        printf("%.1f ml -> %.2f\n", values->values[i][0], values->values[i][3]);
    second_estimated(values, mem);
}

void compute_derivative(titration_t *values)
{
    double temp = 0;
    double eq = 0;
    int mem = 0;

    for (int i = 1; i > 0 && values->values[i] && values->values[i - 1] &&
    values->values[i + 1]; i++) {
        if (values->values[i + 1][0] - values->values[i - 1][0] == 0)
            exit(MY_EXIT_ERROR);
        values->values[i][2] = (values->values[i + 1][1] -
        values->values[i - 1][1]) / (values->values[i + 1][0] - values->values[i - 1][0]);
        if (values->values[i][2] > temp) {
            mem = i;
            temp = values->values[i][2];
            eq = values->values[i][0];
        }
    }
    printf("Derivative:\n");
    for (int i = 1; values->values[i] && values->values[i + 1]; i++)
        printf("%.1f ml -> %.2f\n", values->values[i][0], values->values[i][2]);
    printf("\nEquivalent point at %.1f ml\n", eq);
    second_derivative(values, mem);
}
