#include <stdio.h>
#include <stdlib.h>

void instruction();
int input_operation(int *oper);
int input_size(int *line, int *column);
int input_array(int **matrix, int line, int column);
int** dynamic_declaration(int line, int column);
int sum(int **matrix_first, int line_first, int **matrix_second, int column_second);
int sub(int **matrix_first, int line_first, int **matrix_second, int column_second);
int transpose(int **matrix, int line, int column_second);
int mul(int **matrix_first, int line_first, int **matrix_second, int column_second, int line_second);
void output(int **matrix, int line, int column_second);
void cleaning(int **matrix, int column_second);

int main(void) {

    int oper;
    int line_1, column_1, line_2, column_2;

    instruction();
    if (input_operation(&oper) && oper >= 1 && oper <= 4) {
        if (input_size(&line_1, &column_1)) {
            int **matrix1 = dynamic_declaration(line_1, column_1);
            if (oper == 4)
                transpose(matrix1, line_1, column_1);
            else {
                if (input_size(&line_2, &column_2)) {
                    int **matrix2 = dynamic_declaration(line_2, column_2);
                    if (line_1 == line_2 && column_1 == column_2 && oper == 1)             
                        sum(matrix1, line_1, matrix2, column_2);
		            else if (line_1 == line_2 && column_1 == column_2 && oper == 2)
                        sub(matrix1, line_1, matrix2, column_2);
                    else if (oper == 3 && column_1 == line_2)
                        mul(matrix1, line_1, matrix2, column_2, line_2);
                    else
                        printf("n/a");

                    free(matrix2);
                } else
                    printf("n/a");
            }

            free(matrix1);
        } else
            printf("n/a");

    } else
        printf("n/a");
}

void instruction() {
    printf("Enter what you want to do\n");
    printf("1 - summation\n");
    printf("2 - subtraction\n");
    printf("3 - multiplication\n");
    printf("4 - transpose\n");
}

int input_operation(int *n) {
    char x;
    int count = 0;
    if (scanf("%d%c", n, &x) == 2 && (x == ' ' || x == '\n') && *n >= 1 && *n <= 4) count = 1;

    return count;
}

int input_size(int *line, int *column) {
    char x;
    int count = 0;
    printf("Input the size of the matrix\n");
    if (scanf("%d%d%c", line, column, &x) == 3 && x == '\n' && *line > 0 && *column > 0) count = 1;

    return count;
}

int input_array(int **matrix, int line, int column) {
    char x;
    int count = 0;
    printf("Fill in the matrix\n");
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            if(scanf("%d%c", &matrix[i][j], &x) == 2 && (x == ' ' || x == '\n'))
                count = 1;
            else{
                count = 0;
                break;
            }
        }
    }
    
    return count;
}

int** dynamic_declaration(int line, int column) {
    int **matrix = malloc(line * column * sizeof(int) + line * sizeof(int *));
    int *pointer = (int *)(matrix + line);
    for (int i = 0; i < line; i++) matrix[i] = pointer + column * i;

    input_array(matrix, line, column);

    return matrix;
}

int sum(int **matrix_first, int line_first, int **matrix_second, int column_second) {
    int **result = malloc(column_second * line_first * sizeof(int) + column_second * sizeof(int *));
    int *pointer = (int *)(result + column_second);

    for (int i = 0; i < column_second; i++) {
        result[i] = pointer + line_first * i;
        for (int j = 0; j < line_first; j++) {
            result[i][j] = matrix_first[i][j] + matrix_second[i][j];
        }
    }
    printf("Result of summation\n");
    output(result, column_second, line_first);

    free(result);

    return 0;
}

int sub(int **matrix_first, int line_first, int **matrix_second, int column_second) {
    int **result = malloc(column_second * line_first * sizeof(int) + column_second * sizeof(int *));
    int *pointer = (int *)(result + column_second);

    for (int i = 0; i < column_second; i++) {
        result[i] = pointer + line_first * i;
        for (int j = 0; j < line_first; j++) {
            result[i][j] = matrix_first[i][j] - matrix_second[i][j];
        }
    }
    printf("Result of subtraction\n");
    output(result, column_second, line_first);

    free(result);

    return 0;
}

int mul(int **matrix_first, int line_first, int **matrix_second, int column_second, int line_second) {
    int **result = malloc(column_second * line_first * sizeof(int) + column_second * sizeof(int *));
    int *pointer = (int *)(result + column_second);
    for (int i = 0; i < column_second; i++)
        result[i] = pointer + line_first * i;

    printf("%d %d\n", line_first, column_second);
    for (int i = 0; i < line_first; i++) {
        for (int j = 0; j < column_second; j++) {
            for (int k = 0; k < line_second; k++) result[i][j] += matrix_first[i][k] * matrix_second[k][j];
        }
    }
    printf("Result of multiplication\n");
    output(result, line_first, column_second);

    cleaning(result, column_second);

    return 0;
}

int transpose(int **matrix, int line, int column) {
    int **result = (int **)malloc(column * sizeof(int *));
    for (int i = 0; i < column; i++) {
        result[i] = (int *)malloc(line * sizeof(int));
        for (int j = 0; j < line; j++) result[i][j] = matrix[j][i];
    }
    printf("Result of transposition\n");
    output(result, column, line);

    cleaning(result, column);

    return 0;
}

void output(int **matrix, int line, int column) {
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < column; j++) {
            if (j == column - 1)
                printf("%d", matrix[i][j]);
            else
                printf("%d ", matrix[i][j]);
        }
        if (i != line - 1) printf("\n");
    }
}

void cleaning(int **matrix, int column) {
    for (int i = 0; i < column; i++) free(matrix[i]);
    free(matrix);
}
