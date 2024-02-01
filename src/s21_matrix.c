#include "s21_matrix.h"

int check_matrix(matrix_t *m) {
  int flag = OK;

  if (m == NULL) {
    flag = MATRIX_ERROR;
  } else {
    if ((m->rows <= 0) || (m->columns <= 0)) {
      flag = MATRIX_ERROR;
    } else {
      if (m->matrix == NULL) {
        flag = MATRIX_ERROR;
      }
    }
  }

  return flag;
}

void init_matrix(matrix_t *m) {
  if (m != NULL) {
    m->columns = 0;
    m->rows = 0;
    m->matrix = NULL;
  }
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = OK;

  result->rows = rows;
  result->columns = columns;

  if (result == NULL) flag = MATRIX_ERROR;

  if (!flag && ((rows <= 0) || (columns <= 0))) {
    result->matrix = NULL;
    flag = MATRIX_ERROR;
  }

  if (!flag) {
    result->matrix = calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      printf("Memorry error!");
      exit(1);
    }
  }

  if (!flag) {
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        printf("Memorry error!");
        exit(1);
      }
    }
  }

  return flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int j = 0; j < A->rows; j++) {
        free(A->matrix[j]);
      }
      free(A->matrix);
    }
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;

  if (check_matrix(A) || check_matrix(B)) {
    flag = FAILURE;
  } else {
    if ((A->rows != B->rows) || (A->columns != B->columns)) {
      flag = FAILURE;
    }
  }

  if (flag) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          flag = FAILURE;
          break;
        }
      }
      if (!flag) {
        break;
      }
    }
  }

  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A) || check_matrix(B)) flag = MATRIX_ERROR;

  if (!flag && ((A->rows != B->rows) || (A->columns != B->columns))) {
    flag = CALC_ERROR;
  }

  if (!flag) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A) || check_matrix(B)) flag = MATRIX_ERROR;

  if (!flag && ((A->rows != B->rows) || (A->columns != B->columns))) {
    flag = CALC_ERROR;
  }

  if (!flag) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A) || check_matrix(B)) flag = MATRIX_ERROR;

  if (!flag && (A->columns != B->rows)) flag = CALC_ERROR;

  if (!flag) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int minor_matrix(matrix_t *A, int row, int column, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag) {
    if (s21_create_matrix(A->rows - 1, A->columns - 1, result)) {
      flag = MATRIX_ERROR;
    }
  }

  int minor_i = 0, minor_j = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }
    for (int j = 0; j < A->columns; j++) {
      if (j == column) {
        continue;
      }
      result->matrix[minor_i][minor_j] = A->matrix[i][j];
      minor_j++;
    }
    minor_i++;
    minor_j = 0;
  }

  return flag;
}

double proto_determinant(matrix_t *A) {
  int flag = 0;
  double result = 0;

  if (A->rows == 1) {
    result = A->matrix[0][0];
    flag++;
  };

  if (!flag && (A->rows == 2)) {
    result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    flag++;
  }

  if (!flag) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      minor_matrix(A, 0, j, &minor);
      result += A->matrix[0][j] * pow(-1, j) * proto_determinant(&minor);
      s21_remove_matrix(&minor);
    }
  }

  return result;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = OK;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag && (A->rows != A->columns)) flag = CALC_ERROR;

  if (!flag) *result = proto_determinant(A);

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = OK;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag && (A->rows != A->columns)) flag = CALC_ERROR;

  if (!flag && (A->columns == 1)) flag = CALC_ERROR;

  if (!flag) {
    double determinant = 0;
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->rows; j++) {
        matrix_t minor;
        minor_matrix(A, i, j, &minor);
        s21_determinant(&minor, &determinant);
        result->matrix[i][j] = pow(-1, i + j) * determinant;
        s21_remove_matrix(&minor);
      }
    }
  }

  if (flag) init_matrix(result);

  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = OK;
  int flag_one = 0;
  double determinant = 0;

  if (check_matrix(A)) flag = MATRIX_ERROR;

  if (!flag && (A->rows != A->columns)) flag = CALC_ERROR;

  if (!flag && (A->rows == 1)) {
    if (!A->matrix[0][0]) {
      flag = CALC_ERROR;
    } else {
      s21_create_matrix(1, 1, result);
      result->matrix[0][0] = 1 / A->matrix[0][0];
      flag_one++;
    }
  }

  if (!flag && !flag_one) {
    s21_determinant(A, &determinant);
    if (!determinant) flag = CALC_ERROR;
  }

  if (!flag && !flag_one) {
    matrix_t compl ;
    matrix_t trans_compl;
    s21_create_matrix(A->rows, A->columns, &compl );
    s21_calc_complements(A, &compl );
    s21_transpose(&compl, &trans_compl);
    s21_mult_number(&trans_compl, 1.0 / determinant, result);
    s21_remove_matrix(&compl );
    s21_remove_matrix(&trans_compl);
  }

  if (flag) init_matrix(result);

  return flag;
}