/**********************************************************************
Filename:			Series.c
Version:			1.0
Author:				Jagmandeep Singh
Student No:			
Course Name/Number: Numarical Computing CST8233
Lab Sect:			301
Assignment #:		00
Assignment name:	Frames
Due Date:			October 14 2017
Submission Date:	October 13 2017
Professor:			ANDREW TYLER
Purpose:			Evaluate the Maclaurin Series approximation to D(t) = exp(t)*Cos(t).
					Also calculte %relative Exact Error and %relative Series Error
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

/********************************************************************
Function name:	main
Purpose:		main function
				Takes input from user for number of terms in series and range 
				upto which our serise would go.
In parameters:	none
Out parameters:	Integer
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/

int main(void) {

	int userInput = 1;
	while (userInput == 1) {
		printf("\nEvaluate the Maclaurin Series approximation to D(t) = exp(t)*Cos(t)\n\n");
		printf("1: Evaluate the series\n2: Quit\n\n");
		scanf_s("%d", &userInput);
		if (userInput <= 0 || userInput > 2) {
			printf("Invalid input\n");
			return 0;
		}
		else if (userInput == 2) {
			return 0;
		}
		else {
			double array[7];
			double t = 0.0, range = 0.0;
			int i, j, numOfTerms = 0;
			double answer = 0.0, exactValue = 0.0, relativeExactError = 0.0, relativeSeriesError = 0.0;
			printf("\nEvaluating the series\n");
			printf("Please enter the number of(non-zero) terms in the series (1, 2, 3, 4, 5 or 6):\n");
			scanf_s("%d", &numOfTerms);
			if (numOfTerms <= 0 || numOfTerms > 6) {
				printf("Invalid input\n");
				return 0;
			}
			printf("\nPlease enter the range of t to evaluate in 10 increments (0.0 < t <+4.0):\n");
			scanf_s("%lf", &range);
			printf("MACLAURIN SERIES\n");
			if (range <= 0 || range > 4) {
				printf("Invalid input\n");
				return 0;
			}
			printf("t\t\tD(t) Series\tD(t) Exact\t%RExactE\t\t%RSerE\n");
			/*Array is created to save values for Maclaurin series in parts so that we can go upto a limit
			which is decided according to user input to calculate our answer*/
			for (j = 0; j < 11; j++) {
				answer = 0.0;
				array[0] = 1;
				array[1] = t;
				array[2] = -(t*t*t) / 3;
				array[3] = -(t*t*t*t) / 6;
				array[4] = -(t*t*t*t*t) / 30;
				array[5] = (t*t*t*t*t*t*t) / 630;
				array[6] = (t*t*t*t*t*t*t*t) / 2520;
				for (i = 0; i < numOfTerms; i++) {
					answer = answer + array[i];
				}
				exactValue = (exp(t))*cos(t);
				relativeExactError = 100 * ((exactValue - answer) / exactValue);
				relativeSeriesError = 100 * (array[numOfTerms] / answer);
				printf("%.3e\t%.5e\t%.5e\t%.5e\t%.5e\n", t, answer, exactValue, relativeExactError, relativeSeriesError);
				t = t + (range / 10);
			}
		}
	}
	return 0;
}
