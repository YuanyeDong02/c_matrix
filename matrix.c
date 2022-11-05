#include "matrix.h"

#include <errno.h> /* for ENOSYS */
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

int matrix_allocate(matrix_t *m, int rows, int columns) {

    m->content = (int **) malloc(rows * sizeof(int *));
    m->rows = rows;
    m->columns = columns;
    for (int i = 0; i < rows; i++) {
        m->content[i] = (int *) malloc(columns * sizeof(int));
    }
    return 0;



}

void matrix_free(matrix_t *m) {

    free(m->content);

}

void matrix_init_zeros(matrix_t *m) {
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->columns; ++j) {
            m->content[i][j] = 0;

        }


    }
    /* implement the function here ... */

}

int matrix_init_identity(matrix_t *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            if (i == j) {
                m->content[i][j] = 1;
            } else {
                m->content[i][j] = 0;
            }
            /* implement the function here ... */

        }
    }
    return 0;
}

void matrix_init_rand(matrix_t *m) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            m->content[i][j] = rand() % 201 - 100;
        }
    }
}


/* implement the function here ... */


int matrix_equal(matrix_t *m1, matrix_t *m2) {
    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        return 0;
    }
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            if (m1->content[i][j] != m2->content[i][j]) {
                return 0;
            }
        }
    }


    return 1;
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    if (m1->rows != m2->rows || m1->columns != m2->columns) {
        return 1;
    }
    matrix_allocate(result, m1->rows, m1->columns);

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m1->columns; j++) {
            result->content[i][j] = m1->content[i][j] + m2->content[i][j];
        }
    }

    return 0;
}


int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    matrix_allocate(result, m->rows, m->columns);
    /* implement the function here ... */
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            result->content[i][j] = m->content[i][j] * scalar;
        }
    }


    return 0;
}

int matrix_transposition(matrix_t *m, matrix_t *result) {
    matrix_allocate(result, m->columns, m->rows);
    for (int i = 0; i < m->columns; i++) {
        for (int j = 0; j < m->rows; j++) {
            result->content[i][j] = m->content[j][i];
        }
    }


    return 0;
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    if (m1->columns != m2->rows) {
        return 1;
    }
    matrix_allocate(result, m1->rows, m2->columns);
    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->columns; j++) {
            result->content[i][j] = 0;
            for (int k = 0; k < m1->columns; k++) {
                result->content[i][j] += m1->content[i][k] * m2->content[k][j];
            }
        }
    }

    return 0;
}

int matrix_dump_file(matrix_t *m, char *output_file) {
    FILE *file;
    file = fopen(output_file, "w");
    if (file == NULL) {
        return 1;
    }

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            fprintf(file, "%d", m->content[i][j]);
            if (j != m->columns - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
    /* implement the function here ... */
    fclose(file);
    return 0;
}

int matrix_allocate_and_init_file(matrix_t *m, char *input_file) {
    FILE *file;
    file = fopen(input_file, "r");

    if (file == NULL) {
        return 1;
    }
    int rows = 0;
    int columns = 0;
    char a;
    while ((a = fgetc(file)) != EOF) {
        if (a == '\n') {
            rows++;
        }
        if (a == ' ') {
            columns++;
        }
    }
    columns = (columns / rows) + 1;
    matrix_allocate(m, rows, columns);
    rewind(file);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            fscanf(file, "%d ", &m->content[i][j]);
        }
    }

    fclose(file);
    /* implement the function here ... */
    return 0;
}
