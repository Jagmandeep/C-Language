/*************************************************************************************************************************
Student name: Jagmandeep Singh
Student number: 
Assignment number: 3
Course Name/Number: Numerical Computing CST8233
Lab Sect: 301
Professor: Andrew Tyler
Assignment name: Earthquake Simulation
Due Date: 7 January 2017
Submission Date: 7 January 2017
*************************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS


#define _CRTDBG_MAP_ALLOC	// need this to get the line identification

#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include <cmath>
using namespace std;
/*************************************************************************************************************************
FONCTION PROTOTYPES
*************************************************************************************************************************/

void simulation(void);
void differentiation(double[], double[], int size);

/**************************************************************************
Function name: main(void)
Purpose: main function: Displays menu and take input from user
In parameters: none
Version: 1
Author: Jagmandeep Singh
**************************************************************************/
int main(void) {
	int selection;
	bool running = true;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // in main, after local declarations

	while (running) {
		cout << "Earthquake simulation" << endl;
		cout << "1. run the simulation \n2. Quit\n" << endl;
		/*taking input fron user*/
		cin >> selection;
		if (selection == 1) {
			simulation();
			cout << "" << endl;
		}
		else if (selection == 2) {
			running = false;
		}
		else {
			cout << "Invalid input. Try again.\n" << endl;
		}
	}

	return 0;
}
/**************************************************************************
Function name: simulation(void)
Purpose: Uses a file of earthquake data to run a simulation
		of the effect it would have on a building
In parameters: none
Version: 1
Author: Jagmandeep Singh
**************************************************************************/
void simulation(void) {
	ifstream inputFile; //file source
	string fileName;
	double time[218];
	double displacement[500];
	int lines = 0;

	cout << "Please enter the name of earthquake file to open:";
	cin >> fileName;
	inputFile.open(fileName); //open file in reading mode

	if (inputFile.fail()) { //if any error flag is thrown, file can't be opened
		cout << "\nError reading file" << endl;
		return;
	}
	/*read until end of file*/
	while (!inputFile.eof()) { 
		/*read 1st column (time) and store it*/
		inputFile >> time[lines];
		/*read 2nd column (displacement) and store it */
		inputFile >> displacement[lines];
		lines++;/*counting lines*/
	}

	cout << "\nFile opened; " << lines << " rows of data" << endl;
	differentiation(time, displacement, sizeof(time) / sizeof(time[0]));

	inputFile.close(); //close file stream
}
/**************************************************************************
Function name: differentiation(void)
Purpose: Perform calculations using the central difference and Heun's method
In parameters: none
Version: 1
Author: Jagmandeep Singh
**************************************************************************/
void differentiation(double time[], double displacement[], int size) {
	double v = 0, x = 0, h = 0.0461; /*h = time[i+1]+time[i]*/;
	double vPrime = 0, xPrime = 0, fResult = 0, fPrime = 0; /*predictors and ODE results*/
	double a[218], /*acceleration*/ buidingV[218]; /* calculated velocity*/
	double buidingX[218]; /*calculated movement*/
	const double K = 20,  B = 10;
	int readFile = 1;
	ofstream outputFile; //file destination
	string fileName;
	a[0] = 0;
	buidingV[0] = 0;
	buidingX[0] = 0;
	for (int i = 1; i <size; i++) { 
		/* determine acceleration using central difference  [f(x+h) - 2f(x) + f(x-h)]/pow(h, 2). f(x) = Displacement */
		if (i != 217) {
			a[i] = (((displacement[i + 1] / 100)) - 2 * (displacement[i] / 100) + (displacement[i - 1] / 100)) / pow(h, 2);
		}
		else {
			a[i] = 0;
		}

		fResult = (a[i - 1]) - K*(x)-B*(v);
		vPrime = v + (fResult*h);
		xPrime = x + (v * h);

		fPrime = (a[i]) - K*(xPrime)-B*(vPrime);
		buidingV[i] = v + ((fResult + fPrime) / 2)*h;
		buidingX[i] = x + ((v + buidingV[i]) / 2)*h;

		v = buidingV[i];
		x = buidingX[i];
	}

	cout << "OPEN FILE TO SAVE" << endl;
	cout << "Please enter the name of the file to open:";
	cin >> fileName;
	outputFile.open(fileName);
	if (outputFile.is_open()) { //if any error flag is thrown, file can't be opened
		outputFile << setiosflags(ios::left);
		outputFile << setw(22) << "time(t)" << setw(22) << "displacement(x)" << setw(22) << "acceleration(a)"
			<< setw(22) << "building movement(x)" << setw(22) << "buidling velocity(v)" << endl;
		for (int i = 0; i < size; i++) {
			outputFile << setw(22) << time[i] << setw(22) << displacement[i]
				<< setw(22) << a[i] << setw(22) << buidingX[i]
				<< setw(22) << buidingV[i] << endl;
		}
	}
	else {
		cout << "\nError opening file" << endl;
	}

}
