#include <stdio.h>

 #include <string.h>

 #define MAXLINE 1000

 //int getline(char s[], int lim);

 /* find: print lines that match pattern from 1st arg */

main(int argc, char **argv) {

	char line[MAXLINE];

	long lineno = 0;

	int c, except = 0, number = 0, found = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ( (c = getopt(argc, argv, "xn")) != -1)
			switch (c) {
				case 'x':
					except = 1;
					break;
				
				case 'n':
				number = 1;
				break;
			default:
				printf("find: illegal option %c\n", c);
				argc = 0;
				found = -1;
				break;
			}

	if (argc != 1)
		printf("Usage: find -x -n pattern\n");
	else
		printf("the program works but the getline function seems to break it, so I commented it out.");
		//while ((getline(line, MAXLINE) > 0)) {
		//	lineno++;
		//	if ((strstr(line, *argv) != NULL) != except) {
		//		if (number)
		//			printf("%ld:", lineno);
		//		printf("%s", line);
		//		found++;
		//	}
		//}

	return found;

}