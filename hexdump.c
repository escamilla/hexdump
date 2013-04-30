#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum format
{
	FORMAT_DECIMAL,
	FORMAT_HEXADECIMAL_LOWER,
	FORMAT_HEXADECIMAL_UPPER,
	FORMAT_OCTAL
};

void print_usage();
void print_help();
void dump_file(FILE *fp, int format, int bytes_per_line);

int main(int argc, char *argv[])
{
	if (argc == 1) {
		print_usage();
		return EXIT_SUCCESS;
	}

	for (int i = 1; i < argc; ++i) {
		if (!strcmp("--help", argv[i])) {
			print_help();
			return EXIT_SUCCESS;
		}
	}

	int format = FORMAT_HEXADECIMAL_LOWER;
	int bytes_per_line = 8;

	int c;
	while ((c = getopt(argc, argv, "b:dhHo")) != -1) {
		switch (c) {
			case 'b':
				bytes_per_line = atoi(optarg);
				if (!bytes_per_line) {
					fprintf(stderr, "%s: invalid argument "
						"for option -b: %s\n", argv[0],
						optarg);
					return EXIT_FAILURE;
				}
				break;
			case 'd':
				format = FORMAT_DECIMAL;
				break;
			case 'h':
				format = FORMAT_HEXADECIMAL_LOWER;
				break;
			case 'H':
				format = FORMAT_HEXADECIMAL_UPPER;
				break;
			case 'o':
				format = FORMAT_OCTAL;
				break;
			case '?':
				return EXIT_FAILURE;
			default:
				abort();
		}
	}

	for (int i = optind; i < argc; ++i) {
		const char *filename = argv[i];
		FILE *fp = fopen(filename, "rb");

		if (fp == NULL) {
			fprintf(stderr, "Error opening file \"%s\": %s\n",
				filename, strerror(errno));
			return EXIT_FAILURE;
		}

		dump_file(fp, format, bytes_per_line);
		fclose(fp);
	}

	return EXIT_SUCCESS;
}

void print_usage()
{
	puts("Usage: hexdump [-dhHo] [-b count] [--help]");
}

void print_help()
{
	print_usage();
	putchar('\n');
	puts("Options:");
	puts("    -b count");
	puts("          Display `count' bytes per line (default value: 8)");
	puts("    -d");
	puts("          Display data in decimal format");
	puts("    -h");
	puts("          Display data in lowercase hexadecimal format.");
	puts("          This is the default behavior.");
	puts("    -H");
	puts("          Display data in uppercase hexadecimal format");
	puts("    -o");
	puts("          Display data in octal format");
	puts("    --help");
	puts("          Display this help and exit.");
}

void dump_file(FILE *fp, int format, int bytes_per_line)
{
	if (fp == NULL) return;

	unsigned char bytes[bytes_per_line];
	unsigned int number_bytes_read;
	unsigned int pos;

	for ( ; ; ) {
		pos = ftell(fp);

		number_bytes_read = fread(bytes, sizeof(unsigned char),
			bytes_per_line, fp);
		if (!number_bytes_read) break;

		switch (format) {
			case FORMAT_DECIMAL:
				printf("%08d", pos);
				break;
			case FORMAT_HEXADECIMAL_LOWER:
				printf("%08x", pos);
				break;
			case FORMAT_HEXADECIMAL_UPPER:
				printf("%08X", pos);
				break;
			case FORMAT_OCTAL:
				printf("%08o", pos);
		}

		fputs("  ", stdout);

		for (int i = 0; i < bytes_per_line; ++i) {
			if (i < number_bytes_read) {
				switch (format) {
					case FORMAT_DECIMAL:
						printf("%03d", bytes[i]);
						break;
					case FORMAT_HEXADECIMAL_LOWER:
						printf("%02x", bytes[i]);
						break;
					case FORMAT_HEXADECIMAL_UPPER:
						printf("%02X", bytes[i]);
						break;
					case FORMAT_OCTAL:
						printf("%03o", bytes[i]);
				}
				putchar(' ');
			} else {
				fputs("   ", stdout);
			}
		}

		putchar(' ');

		for (int i = 0; i < number_bytes_read; ++i) {
			if (isprint(bytes[i])) {
				putchar(bytes[i]);
			} else {
				putchar(' ');
			}
		}

		putchar('\n');
	}
}
