/**********************************************************************
Filename:			Ass2.c
Version:			1.0
Author:				Jagmandeep Singh
Student No:			
Course Name/Number: Numarical Computing CST8233
Lab Sect:			301
Assignment #:		02
Assignment name:	Assignment 2
Due Date:			December 10, 2017
Submission Date:	December 10, 2017
Professor:			ANDREW TYLER
Purpose:			A utility application to show a real float number in its normalized hexadecimal and binary
					representations together with its exponent and normalized mantissa in memory, to automate what is done
					manually in class
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS

/********************************************************************
Function name:	main
Purpose:		main function
				Takes input from user and shows the binary and
				hexadecimal representations of that number.
In parameters:	none
Out parameters:	Integer
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void print_binary(size_t, unsigned char *);
void print_hex(size_t , unsigned char *);
void lilEndian(size_t size, unsigned char *data);
void reverse(size_t , unsigned char *);
void print_exp(size_t, unsigned char *);
void print_mntsa(size_t size, unsigned char *data);

int main(void) {
	int restart = 1;
	float num = 0;
	while (restart == 1) {
		printf("1: Convert a float\n2: Quit\n\n");
		scanf_s("%d", &restart);
		if (restart <= 0 || restart > 2) {
			printf("Invalid input\n");
			restart = 1;
		}
		else if (restart == 2) {
			return 0;
		}
		else {
			printf("Please enter the number to convert: ");
			scanf_s("%f", &num);
			printf("float number is:\t%.6e\n", num);/*Changes print format to exponant with precision of 6*/
			reverse(sizeof(float), (unsigned char *)&num);
			print_binary(sizeof(float), (unsigned char *)&num);
			printf("Big: \t\t\t");
			print_hex(sizeof(float), (unsigned char *)&num);
			printf("Little: \t\t");
			reverse(sizeof(float), (unsigned char *)&num);
			lilEndian(sizeof(float), (unsigned char *)&num);
			reverse(sizeof(float), (unsigned char *)&num);
			print_exp(sizeof(float), (unsigned char *)&num);
			print_mntsa(sizeof(float), (unsigned char *)&num);
		}
	}
}
/********************************************************************
Function name:	print_binary
Purpose:		Convert floating number to binary
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void print_binary(size_t size, unsigned char *data)
{
	int x =0;
	unsigned char i, j;
	/* Allocate enough to fit the string to be reversed as well as a null terminator */

	printf("Binary:\t\t\t");

	/* cycle through each byte, storing it's binary value as chars */
	for (i = 0; i < size; i++)
	{
		for (j = 128; j > 0; j >>= 1)
		{
			if (data[i] & j)
			{
				printf("%c", '1');

			}
			else
			{
				printf("%c", '0');
			}
			/* make sure to include spaces after each nibble */
			if (j == 16 || j == 1)
			{
				printf("%c", ' ');
			}
		}
	}
	printf("\n");
}
/********************************************************************
Function name:	print_hex
Purpose:		Convert floating number to Hex-Decimal
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void print_hex(size_t size, unsigned char *data)
{

	int i;
	/*loop through each bit of data passed throgh function*/
	for (i = 0; i < size; i++)
	{
		printf("%.2X", (unsigned int)data[i]);
		printf(" ");
	}

	printf("\n");
}
/********************************************************************
Function name:	lilEndian
Purpose:		Convert floating number to lilEndian
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void lilEndian(size_t size, unsigned char *data)
{
	int i;
	/*loop through each bit of data passed throgh function*/
	for (i = 0; i < size; i++)
	{
		printf("%.2X", (unsigned int)data[i]);
		printf(" ");
	}
	printf("\n");
}
/********************************************************************
Function name:	reverse()
Purpose:		Reverse given number
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void reverse(size_t size, unsigned char *data)
{
	unsigned char *temp;
	int i = 0,j = size-1;
	
	if ((temp = malloc(size)) == NULL)
	{
		return -1;
	}
	/*Swop values*/
	/*variable i indicates starting index of given number
	 variable j in starts from last index of given number*/
	while (i < j) {
		temp = data[i];
		data[i] = data[j];
		data[j] = temp;
		i++;
		j--;
	}

}
/********************************************************************
Function name:	print_exp()
Purpose:		Calculates exponent for given number
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void print_exp(size_t size, unsigned char *data)
{
	unsigned char i, k = 0, exp = 0, j ;
	/*We make array to get exponent value in decimal*/
	int arr[] = { 128,64,32,16,8,4,2,1 };
	
	/* cycle through each byte, storing it's binary value as chars */
	for (i = 0; i < 2; i++)
	{
		for (j = 128; j > 0; j >>= 1)
		{
			if (data[i] & j)
			{
				if (k != 0) {
					/*j is always one bit behind because we skip sign bit
					so we use our oun array starting from 128 to calculate exponant */
					exp += arr[k-1];
				}
			}
			k++;
			/*Exponant is of 8 bits so we stop our loop at 8 */
			if (k > 8) {
				printf("Exponent:\t\t%d\n", exp);
				return;
			}
		}
	}
	printf("\n");
}
/********************************************************************
Function name:	print_mntsa()
Purpose:		Calculates mantisa for given number
In parameters:	size_t , unsigned char *
Out parameters:	None
Version:		1.0
Author:			Jagmandeep Singh
**********************************************************************/
void print_mntsa(size_t size, unsigned char *data)
{
	unsigned char i, j;
	float man = 0;
	int k = 0;
	/* cycle through each byte, storing it's binary value as chars */
	for (i = 0; i < size; i++)
	{
		for (j = 128; j > 0; j >>= 1)
		{
			if (data[i] & j)
			{	
				/*Ignores first 9 bits (Sign bit and Exponant)*/
				if (k < -8) {
					/*Calculates decimal after period(.) witth negative powers of 2*/
					man +=(float) pow(2,k+8);
				}
				
			}
			/*To binary to decimal after period(.) k shoulad be in negative*/
			k--;
			if (k <= -32) {
				printf("Mantisa:\t\t%.7f\n", (man+1));
				return;
			}
		}
	}
	printf("\n");
}