#include <stdio.h>
#include <unistd.h>

long
printAndSanitise(char *c)
{
	long i = 0;

	while (1) {
		switch (c[i]) {
		case '\0':
			goto ret;
		case '"':
			write(1, &"\\\"", 2);
			goto cont;
		default:
			write(1, &c[i], 1);
			/* fall-through */
		}

	cont:
		i++;
	}

ret:
	return i;
}

int
main(int argc, char **argv)
{
	char c = 0;

	if (argc != 5) {
		dprintf(2, "Too few/much arguments received! Expected 5, received %d.\n", argc);

		return 1;
	}

	dprintf(1, "{");
	dprintf(1, "\"pkgname\": \"");
	printAndSanitise(argv[1]);
	dprintf(1, "\",\"pkgver\":\"");
	printAndSanitise(argv[2]);
	dprintf(1, "\",\"pkgdesc\":\"");
	printAndSanitise(argv[3]);
	dprintf(1, "\",\"pkgdeps\":\"");
	printAndSanitise(argv[4]);
	dprintf(1, "\"");
	dprintf(1, "}\n");

	return 0;
}

