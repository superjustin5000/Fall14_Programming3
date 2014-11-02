#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "bmplib.h"

/*
 * This method enlarges a 24-bit, uncompressed .bmp file
 * that has been read in using readFile()
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the original number of rows
 * cols     - the original number of columns
 *
 * scale    - the multiplier applied to EACH OF the rows and columns, e.g.
 *           if scale=2, then 2* rows and 2*cols
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows (scale*rows)
 * newcols  - the new number of cols (scale*cols)
 */
int enlarge(PIXEL* original, int rows, int cols, int scale, 
	    PIXEL** new, int* newrows, int* newcols) 
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */

  int row, col;

  int size = (*newrows) / rows;

  //printf("size of scale = %d\n", size);

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc((*newrows)*(*newcols)*sizeof(PIXEL));

    
  
    
  for (row=0; row < rows; row++) { /// look at every row.

    int i;
    for (i=0; i<size; i++) { //// for every row, loop through the column size times.

      for (col=0; col < cols; col++) {

        int j;
        for (j=0; j<size; j++) {
          
          int currentPixel = row*cols + (col);
          //int newPixel = ((row*size) + i)*(*newcols) + ((col*size) + j);
          //int newPixel = currentPixel * ((i+1)*size) + j;
          int sizeSquared = size * size;
          int newPixel = (row * sizeSquared * cols) + (i * size * cols) + (col * size) + j;

          PIXEL* o = original + currentPixel;
          PIXEL* n = (*new) + newPixel;
          *n = *o;

          //printf("row %d - converting pixel %d to %d\n", row, currentPixel, newPixel);

        }

      }

    }

  }


  return 0;
}

/*
 * This method rotates a 24-bit, uncompressed .bmp file that has been read 
 * in using readFile(). The rotation is expressed in degrees and can be
 * positive, negative, or 0 -- but it must be a multiple of 90 degrees
 * 
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 * rotation - a positive or negative rotation, 
 *
 * new      - the new array containing the PIXELs, allocated within
 * newrows  - the new number of rows
 * newcols  - the new number of cols
 */
int rotate(PIXEL* original, int rows, int cols, int rotation,
	   PIXEL** new, int* newrows, int* newcols)
{
  /* THIS IS THE METHOD THAT YOU SHOULD WRITE */

  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  //printf("rows not 0 and cols not 0\n");
  long unsigned int sizeOfNew = cols*rows*sizeof(PIXEL);
  *new = (PIXEL*)malloc(sizeOfNew);

  //printf("size of new pixel array is %lu\nnum rows = %d, num cols = %d\n", sizeOfNew, rows, cols);

  for (row=0; row < rows; row++) {
    //printf("starting row\n");
    for (col=0; col < cols; col++) {

      //printf("starting column - ");

      int currentPixel = row*cols + col;
      int newPixel = col*rows + (cols-1-row);

      //printf("row %d - converting pixel %d to %d\n", row, currentPixelX, newPixelY);
      //printf("getting pixel - ");
      PIXEL* o = original + currentPixel;
      //printf("setting pixel - ");
      PIXEL* n = (*new) + newPixel; ///// 90 degrees clockwise.
      //printf("saving pixel - ");

      //printf("current location compared to size is : cur = %d size = %lu\n", newPixel, sizeOfNew);

      *n = *o;

      //printf("row %d - converting pixel %d to %d\n", row, currentPixel, newPixel);
      //printf("old pixel red = %d, green = %d, blue = %d\n", o->r, o->g, o->b);
      //printf("new pixel red = %d, green = %d, blue = %d\n", n->r, n->g, n->b);

    }

    //printf("ending row\n");

  }

  //printf("finished with rows and cols\n");

  return 0;
}

/*
 * This method horizontally flips a 24-bit, uncompressed bmp file
 * that has been read in using readFile(). 
 * 
 * THIS IS GIVEN TO YOU SOLELY TO LOOK AT AS AN EXAMPLE
 * TRY TO UNDERSTAND HOW IT WORKS
 *
 * original - an array containing the original PIXELs, 3 bytes per each
 * rows     - the number of rows
 * cols     - the number of columns
 *
 * new      - the new array containing the PIXELs, allocated within
 */
int flip (PIXEL *original, PIXEL **new, int rows, int cols) 
{
  int row, col;

  if ((rows <= 0) || (cols <= 0)) return -1;

  *new = (PIXEL*)malloc(rows*cols*sizeof(PIXEL));

  for (row=0; row < rows; row++)
    for (col=0; col < cols; col++) {
      PIXEL* o = original + row*cols + col;
      PIXEL* n = (*new) + row*cols + (cols-1-col);
      *n = *o;
    }

  return 0;
}

int main(int argc, char* argv[]) {

  char *inFileName;
  char *outFileName;
  //FILE *inputFile = stdin; ////standard in by default.
  //FILE *outputFile = stdout; ///by default is standard out.

  int shouldFlip = 0;
  int shouldRotate = 0;
  int shouldScale = 0;

  int scaleAmount = 1;
  int rotateAmount = 0;

  int code;
  while ( (code = getopt(argc, argv, "fs:r:o:")) != -1 ) {

    switch (code) {

        case 'f':
          shouldFlip = 1;
          break;

        case 's':
          shouldScale = 1;
          scaleAmount = atoi(optarg);
          if (scaleAmount < 1) {
            printf("Please enter a valid integer greater than 0 after -s.\n");
            return 0;
          }
          break;

        case 'r':
          shouldRotate = 1;
          rotateAmount = atoi(optarg);
          //printf("rotateAmount = %d\n", rotateAmount);

          if (rotateAmount % 90 != 0 || rotateAmount == 0) {
            printf("Please enter a valid integer that is a multiple of 90 after -r.\n");
            return 0;
          }

          break;

        case 'o':

          outFileName = optarg;
          if ( (strstr(outFileName, ".bmp") == NULL) || (strlen(outFileName) < 5) ) {
            printf("Please enter a .bmp filename after -o\n");
            return 0;
          }
          //printf("output file is %s\n", outFileName);
          //outputFile = fopen(fileName, "r");

          break;

        case '?':
           if (optopt == 's') {
            printf("Please enter a valid integer greater than 0 after -s.\n");
            return 0;
          }
          else if (optopt == 'r') {
            printf("Please enter a valid integer that is a multiple of 90 after -r.\n");
            return 0;
          }
          else if (optopt == 'o') {
            printf("Please enter a .bmp filename after -o\n");
            return 0;
          }

          break;


        default :
          break;


    }



  }

  int index;
    for (index = optind; index < argc; index++) {
      if (strcmp(argv[index], "help") == 0) {
          //// help.

          printf("Welcome to the bmptool. Below are the options available.\n\n");
          printf("'-s' - Scale enter a valid integer greater than 0 after -s.\n");
          printf("'-r' - Rotate enter a valid integer multiple of 90 after -r.\n");
          printf("'-f' - Flip the bmp over the x axis.\n");
          printf("'-o' - Output filename. Enter a valid output filename after -o.\n");
          printf("The last argument should be the input filename.\n");
          printf("If no input or output files are specified, stdin and stdout will be used respectively.\n");

          return 0;

      } 
      else {
        inFileName = argv[index];
        printf("input file is %s\n", inFileName);
      }
    }


  int r, c;
  int newr, newc;

  PIXEL *b, *nb;

  printf("prepare to read file\n");


  readFile(inFileName, &r, &c, &b);


  printf("read file\n");


  
  if (shouldScale == 1) {
    newr = r*scaleAmount;
    newc = c*scaleAmount;
    enlarge(b, r, c, scaleAmount, &nb, &newr, &newc);

    r=r*scaleAmount;
    c=c*scaleAmount;

    printf("new rows = %d", r);

  }
  if (shouldRotate == 1) {

    if (shouldScale == 1) {
      printf("reading output file instead of input since scale was performed");
      writeFile(outFileName, r, c, nb);
      readFile(outFileName, &r, &c, &b);
    }

    printf("should rotate\n");

    int r360 = rotateAmount % 360;
    int r270 = rotateAmount % 270;
    int r180 = rotateAmount % 180;
    int r90 = rotateAmount % 90;
    printf("rotate 90 = %d\n", r90);

    if (r360 == 0) { //// multiple of 360 rotation... new = old.
      ///no rotation.
    }
    else if (r270 == 0) { /// multiple of 270... call rotate 1 time CCW
      newr = r;
      newc = c;
      if (rotateAmount < 0) {
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
        writeFile(outFileName, r, c, nb);
        readFile(outFileName, &r, &c, &b);
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
        writeFile(outFileName, r, c, nb);
        readFile(outFileName, &r, &c, &b);
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
      }
      else {
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
      }
    }
    else if (r180 == 0) { /// multiple of 180... call rotate 2 times CCW
      newr = r;
      newc = c;
      rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
      writeFile(outFileName, r, c, nb);
      readFile(outFileName, &r, &c, &b);
      rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
    }
    else if (r90 == 0) { /// multiple of 90 ... call rotate 3 time CCW
      //printf("rotating 90 degrees\n");
      newr = r;
      newc = c;
      if (rotateAmount < 0) {
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
      }
      else {
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
        writeFile(outFileName, r, c, nb);
        readFile(outFileName, &r, &c, &b);
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
        writeFile(outFileName, r, c, nb);
        readFile(outFileName, &r, &c, &b);
        rotate(b, r, c, rotateAmount, &nb, &newr, &newc);
      }
    }


  }



  if (shouldFlip == 1) {

    if (shouldRotate == 1 || shouldScale == 1 ) {
      ////reread the modified output file.
      writeFile(outFileName, r, c, nb);
      readFile(outFileName, &r, &c, &b);
    }

    flip(b, &nb, r, c);
  }
  



  printf("prepare to write file\n");

  

  writeFile(outFileName, r, c, nb);

  printf("wrote file\n");

    


  free(b);
  free(nb);

  return 0;


}