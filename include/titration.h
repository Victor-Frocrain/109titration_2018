/*
** EPITECH PROJECT, 2018
** 109titration.h
** File description:
** 109titration.h
*/

#ifndef TITRATION_H_
#define TITRATION_H_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

#define USAGE ("README")
#define MY_EXIT_SUCCESS 0
#define MY_EXIT_ERROR 84

typedef struct titration_s {
    double **values;
} titration_t;

int titration(int ac, char **av);
bool compute_values(char **tab);
char **my_taballoc(char **tab);
void compute_derivative(titration_t *values);

#endif /* TITRATION_H_ */
