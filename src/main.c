#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int isLeapYear(int g) {
		return (g % 400 == 0) || ((g % 4 == 0) && (g % 100 != 0));
}

/* Требуемая функция: количество дней в месяце */
static int daysInMonth(int g, int m) {
		switch (m) {
				case 1:  return 31;
				case 2:  return isLeapYear(g) ? 29 : 28;
				case 3:  return 31;
				case 4:  return 30;
				case 5:  return 31;
				case 6:  return 30;
				case 7:  return 31;
				case 8:  return 31;
				case 9:  return 30;
				case 10: return 31;
				case 11: return 30;
				case 12: return 31;
				default: return 0; /* неверный месяц */
		}
}

static int parseInt(const char *s, int *out) {
		long v;
		char *endptr = NULL;

		errno = 0;
		v = strtol(s, &endptr, 10);

		if (errno != 0 || endptr == s || *endptr != '\0') {
				return 0;
		}
		if (v < 1 || v > INT_MAX) {
				return 0;
		}
		*out = (int)v;
		return 1;
}

static int isValidDate(int g, int m, int n) {
		int dim = daysInMonth(g, m);
		if (g < 1) return 0;
		if (dim == 0) return 0;
		if (n < 1 || n > dim) return 0;
		return 1;
}

static void printDate(const char *label, int g, int m, int n) {
		printf("%s %04d-%02d-%02d\n", label, g, m, n);
}

static void prevDate(int g, int m, int n, int *pg, int *pm, int *pn) {
		if (n > 1) {
				*pg = g;
				*pm = m;
				*pn = n - 1;
				return;
		}

		/* n == 1 -> переходим в предыдущий месяц */
		if (m > 1) {
				*pg = g;
				*pm = m - 1;
				*pn = daysInMonth(g, m - 1);
				return;
		}

		/* 1 января -> 31 декабря предыдущего года */
		*pg = g - 1;
		*pm = 12;
		*pn = 31;
}

static void nextDate(int g, int m, int n, int *ng, int *nm, int *nn) {
		int dim = daysInMonth(g, m);

		if (n < dim) {
				*ng = g;
				*nm = m;
				*nn = n + 1;
				return;
		}

		/* последний день месяца -> следующий месяц */
		if (m < 12) {
				*ng = g;
				*nm = m + 1;
				*nn = 1;
				return;
		}

		/* 31 декабря -> 1 января следующего года */
		*ng = g + 1;
		*nm = 1;
		*nn = 1;
}

int main(int argc, char *argv[]) {
		int g, m, n;
		int pg, pm, pn;
		int ng, nm, nn;

		if (argc != 4) {
				printf("Usage: %s <year g> <month m> <day n>\n", argv[0]);
				printf("Example: %s 2024 3 1\n", argv[0]);
				return 1;
		}

		if (!parseInt(argv[1], &g) || !parseInt(argv[2], &m) || !parseInt(argv[3], &n)) {
				printf("Error: all arguments must be natural numbers.\n");
				return 1;
		}

		if (!isValidDate(g, m, n)) {
				printf("Error: invalid date.\n");
				return 1;
		}

		printDate("Given date:     ", g, m, n);

		prevDate(g, m, n, &pg, &pm, &pn);
		if (pg < 1) {
				printf("Previous date:  (does not exist for year < 1)\n");
		} else {
				printDate("Previous date:  ", pg, pm, pn);
		}

		nextDate(g, m, n, &ng, &nm, &nn);
		printDate("Next date:      ", ng, nm, nn);

		printf("Leap year: %s\n", isLeapYear(g) ? "yes" : "no");
		printf("Days in month: %d\n", daysInMonth(g, m));

		return 0;
}