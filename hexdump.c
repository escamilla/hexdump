#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BYTES_PER_LINE 16
#define streq(X,Y) (!strcmp(X,Y))

enum mode
{
	MODE_HEX_LOWER,
	MODE_HEX_UPPER,
	MODE_OCT,
	MODE_DEC
};

void print_help();
void hexdump(FILE *fp, int mode);

int main(int argc, char *argv[])
{
	if (argc == 1) {
		puts("No file given");
		return EXIT_SUCCESS;
	}

	int mode = MODE_HEX_LOWER;

	for (int i = 0; i < argc; ++i) {
		if (streq(argv[i], "-h")) {
			mode = MODE_HEX_LOWER;
		} else if (streq(argv[i], "-H")) {
			mode = MODE_HEX_UPPER;
		} else if (streq(argv[i], "-o") || streq(argv[i], "-O")) {
			mode = MODE_OCT;
		} else if (streq(argv[i], "-d") || streq(argv[i], "-D")) {
			mode = MODE_DEC;
		} else if (streq(argv[i], "--help")) {
			print_help();
			return EXIT_SUCCESS;
		}
	}

	char *file = argv[1];

	FILE *fp = fopen(file, "rb");

	if (fp == NULL) {
		fprintf(stderr, "Error opening file \"%s\": %s\n",
			file, strerror(errno));
		return EXIT_FAILURE;
	}

	hexdump(fp, mode);

	fclose(fp);

	return EXIT_SUCCESS;
}

void print_help()
{
	puts("hexdump file [-h | -H | -o | -d] [--help]");
	puts("    -h      Display bytes in lowercase hexadecimal (default)");
	puts("    -H      Display bytes in uppercase hexadecimal");
	puts("    -o      Display bytes in octal");
	puts("    -d      Display bytes in decimal");
	puts("    --help  Show this help");
}

void hexdump(FILE *fp, int mode)
{
	if (fp == NULL) return;

	unsigned char bytes[BYTES_PER_LINE];
	unsigned int bytes_read;
	unsigned int pos;

	for ( ; ; ) {
		pos = ftell(fp);

		bytes_read = fread(bytes, 1, BYTES_PER_LINE, fp);
		if (!bytes_read) break;

		switch (mode) {
			case MODE_HEX_LOWER:
				printf("%08x", pos);
				break;
			case MODE_HEX_UPPER:
				printf("%08X", pos);
				break;
			case MODE_OCT:
				printf("%08o", pos);
				break;
			case MODE_DEC:
				printf("%08d", pos);
		}

		fputs("  ", stdout);

		for (int i = 0; i < BYTES_PER_LINE; ++i) {
			if (i < bytes_read) {
				switch (mode) {
					case MODE_HEX_LOWER:
						printf("%02x", bytes[i]);
						break;
					case MODE_HEX_UPPER:
						printf("%02X", bytes[i]);
						break;
					case MODE_OCT:
						printf("%03o", bytes[i]);
						break;
					case MODE_DEC:
						printf("%03d", bytes[i]);
				}
				putchar(' ');
			} else {
				fputs("   ", stdout);
			}
		}

		putchar(' ');

		for (int i = 0; i < bytes_read; ++i) {
			if (isprint(bytes[i])) {
				putchar(bytes[i]);
			} else {
				putchar(' ');
			}
		}

		putchar('\n');
	}
}
