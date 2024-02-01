FLAGS = -std=c11 -pedantic -Wall -Werror -Wextra -lm

all: test s21_matrix.a gcov_report

test: s21_matrix.a
	gcc $(FLAGS) tests/*.c s21_matrix.a -lcheck -lgcov -lm -lsubunit -o s21_matrix_test

s21_matrix.a: 
	gcc $(FLAGS) -c *.c
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -rf *.o

gcov_report:
	gcc $(FLAGS) -coverage *.c tests/*.c -o gcovreport -lcheck -lm -lsubunit
	./gcovreport
	lcov -t "gcovreport" -o gcovreport.info -c -d .
	genhtml -o report gcovreport.info

style:
	clang-format -n -style=google *.c *.h tests/*.c tests/*.h

clean: 
	rm -rf *.o s21_matrix.a *.gcno *.gcda gcovreport gcovreport.info s21_matrix_test rm report rm s21_matrix.dSYM
