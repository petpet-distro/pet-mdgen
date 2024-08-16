#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

int
writeDeps(char *c, size_t size)
{
	int i = 0;
	char d = 0;

	while (1) {
		d = c[i];

		switch (d)
		{
		case ' ':
			write(1, &"\0", 1);
			break;
		case '\0':
			write(1, &"\0\1", 2);
			i++;
			goto ugh;
			break;
		default:
			write(1, &d, 1);
		}

		i++;
		if (i == size-1) {
			break;
		}
	}

	goto ugh;

ugh:
	return i;
}

int
main(int argc, char **argv)
{
	uint64_t metadataVersion = 0;

	size_t packageNameLength = 0;
	size_t packageVersionLength = 0;
	size_t packageDescriptionLength = 0;
	size_t packageDependenciesLength = 0;

	if (argc != 5) {
		fprintf(stderr, "Invalid amount of arguments received! Expected 5, received %d!\n", argc);

		return 1;
	}

	packageNameLength = strlen(argv[1])+1;
	packageVersionLength = strlen(argv[2])+1;
	packageDescriptionLength = strlen(argv[3])+1;
	packageDependenciesLength = strlen(argv[4]);

	write(1, &metadataVersion, sizeof(metadataVersion));

	write(1, argv[1], packageNameLength);
	write(1, argv[2], packageVersionLength);
	write(1, argv[3], packageDescriptionLength);
	writeDeps(argv[4], packageDescriptionLength);

	return 0;
}
