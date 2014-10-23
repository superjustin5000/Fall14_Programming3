#include <stdio.h>

int main(int argc, char* argv[]) {

	printf("argc = %d\n", argc);

	if (argc == 2) { ///the first is the program name.

		FILE *f = fopen(argv[1], "r");
	
		if (!f) {
			printf("could not open %s", argv[1]);
			return -1;
		}

		printf("beginning print of %s\n", argv[1]);
		
		int c = 0;
		while ((c = fgetc(f)) != -1) {
	
			printf("%c", c);
	
		}
		
		if (f) {
			fclose(f);
		}
	
	}

	else {
		
		char fileName[256];
		scanf("%s", fileName);
		
		FILE *f = fopen(fileName, "r");

		if (!f) {
			printf ("could not open %s", fileName);
			return -1;
		}
		char c;
		while ((c = fgetc(f)) != EOF) {

			printf ("%c", c);
		}

		if (f) {
			fclose(f);
		}

	}

	return 0;
}
