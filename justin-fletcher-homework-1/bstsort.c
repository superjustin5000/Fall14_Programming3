///////////
//////////

/// NOTES FOR PROFESSOR ////

/// -- when deciding which order to store things alphabetically.. this prgram takes white spaces into account
/// -- so two similar lines, if one has a white space in front, it will be alphabetically lower than than the other.
/// -- also for case sensitive.. All the upper case characters are higher than all the lowercase.
/// -- so and 'B' is higher than a 'y'.





#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 255






int compareString(char* a, char *b, int isCase) {

	int lengthA = strlen(a);
	int lengthB = strlen(b);

	int shortest = lengthA;
	if (lengthB < lengthA) {
		shortest = lengthB;
	}


	///// check whether it's case sensitive.. if not, convert to lower case.
	if (!isCase) {

		for(char *p = a;*p;++p) { *p = *p >= 'A' && *p <= 'Z' ? *p | 0x60:*p; }
		for(char *p = b;*p;++p) { *p = *p >= 'A' && *p <= 'Z' ? *p | 0x60:*p; }

	}


	int i;

	for(i = 0; i < shortest; i++) {

		printf("compare ... %c ... and ... %c ... - ", a[i], b[i]);

		if (a[i] > b[i]) {
			return 1;
		}
		else if (a[i] < b[i]) {
			return -1;
		}

	}



	return 0;

}


//////////////////
//////////////////
//////////////////
//////////////////
////////////////// ------------ binary tree.
//////////////////
//////////////////
//////////////////

struct binTree {

	char node[BUFFERSIZE];
	int count;
	struct binTree *leftSub, *rightSub;

};


//////////////////
//////////////////
//////////////////
//////////////////
////////////////// ------------ inserting into the binary tree.
//////////////////
//////////////////
//////////////////



struct binTree* insertIntoBinTree(char *s, struct binTree *tree, int isCase) {

	printf("iteration - \n");

	if (tree == NULL) {

		printf("adding Node - ");

		struct binTree *t = (struct binTree*)malloc(sizeof(struct binTree));
		//char newS[BUFFERSIZE];
		strcpy(t->node, s);
		//t->node = newS;
		t->count = 1;
		t->leftSub = NULL;
		t->rightSub = NULL;

		printf("added Node = %s\n", s);

		return t;

	}

	int comp = compareString(s, tree->node, isCase);
	
	if ( comp < 0 ) { ///insert left.
		printf("insertLeft\n");
		tree->leftSub = insertIntoBinTree(s, tree->leftSub, isCase);
	}

	else if ( comp > 0 ) { ///insert right.
		printf("insertRight\n");
		tree->rightSub = insertIntoBinTree(s, tree->rightSub, isCase);
	}

	else {
		printf("increment Count of %s\n", s);
		tree->count++;
		return tree;
	}
	
	return tree;

}

//////////////////
//////////////////
//////////////////
//////////////////
////////////////// ------------ printing the binary tree.
//////////////////
//////////////////
//////////////////

void printBinaryTree(struct binTree* tree) {


	if (tree == NULL) {
		//printf("%s\n", "null leaf");
		return;
	}

	printBinaryTree(tree->leftSub);
	
	int i;
	for (i=0; i<tree->count; i++) { ///print it for every count.
		printf("%s\n", tree->node);
	}

	printBinaryTree(tree->rightSub);


}




//////////////////
//////////////////
//////////////////
//////////////////
////////////////// ------------ reclaiming the tree and freeing memory.
//////////////////
//////////////////
//////////////////

void freeBinaryTree(struct binTree* tree) {

	if (tree == NULL) {
		return; ///nothing happens.
	}


	freeBinaryTree(tree->leftSub);
	freeBinaryTree(tree->rightSub);
	free(tree);

}











//////////////////
//////////////////
//////////////////
//////////////////
////////////////// ------------ main function
//////////////////
//////////////////
//////////////////


int main(int argc, char* argv[]) {

	int c;
	char *fileName;
	FILE *outputFile = stdout; ///by default is standard out.
	int caseSensitive = 0;

	while ( (c = getopt(argc, argv, "co:")) != -1 ) {

		switch(c) {

			case 'c':
				caseSensitive = 1;
				break;

			case 'o': ///wants output.. get the argument of 'o';

				fileName = optarg;
				outputFile = fopen(fileName, "r");

				break;


			default:
				break;

		}

	}

	printf("output file is %s\n", fileName);

	if (fileName != NULL) {

		char nextLine[BUFFERSIZE];

		char prevLine[BUFFERSIZE];
		fgets(prevLine, BUFFERSIZE, outputFile);
		
		//char firstLine[BUFFERSIZE];
		//strcpy(firstLine, prevLine);
		struct binTree *mainTree = (struct binTree*)malloc(sizeof(struct binTree));
		strcpy(mainTree->node, prevLine);
		mainTree->count = 1;
		mainTree->leftSub = NULL;
		mainTree->rightSub = NULL;
		
		while ( (fgets(nextLine, BUFFERSIZE, outputFile)) != NULL ) {

			insertIntoBinTree(nextLine, mainTree, caseSensitive);

		}


		printBinaryTree(mainTree);

		freeBinaryTree(mainTree);
		

	}


	return 0;

}


