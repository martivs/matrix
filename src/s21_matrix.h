#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// for s21_eq_matrix
#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum error { OK, MATRIX_ERROR, CALC_ERROR };
// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц;
//     матрица, для которой нельзя провести вычисления и т.д.)

int check_matrix(matrix_t *m);
void init_matrix(matrix_t *m);

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);

int minor_matrix(matrix_t *A, int row, int column, matrix_t *result);
double proto_determinant(matrix_t *A);

int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  // SRC_S21_MATRIX_H_