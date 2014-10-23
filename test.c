#include <stdio.h>

 /* print Fahrenheit-Celsius table

 for fahr = 0, 20, ..., 300 */

 main()

 {

	 int fahr, cels;

	 int lower, upper, step;

	 lower = 0; /* lower limit of temperature scale */

	 upper = 100; /* upper limit */

	 step = 1; /* step size */

	 cels = lower;

	 while (cels <= upper) {

		 //cels = 5 * (fahr-32) / 9;
		 fahr = ( cels * 9 / 5 ) + 32;

		 printf("Celcius : %d\t Fahrenheit : %d\n", cels, fahr);

		 cels = cels + step;

	 }

 }