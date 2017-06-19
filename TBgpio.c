/*
 * TBgpio.c:
 *	A shameless steal of the Swiss-Army-Knife, Set-UID command-line interface 
 *  to the Raspberry Pi's GPIO by Gordon Henderson.
 *
 *  Stolen by Tom Walton
 *
 *	Probably the Copyright (c) 2012-2017 Gordon Henderson still applies.
 *
 *  In the unlikely event that any code is original and actually written
 *  by Tom Walton you can have it. 
 ***********************************************************************
 * This file was part of wiringPi before it was stolen:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    That lack of warranty, implied or otherwise, also applies here. 
 *
 *    I should provide a copy of the GNU Lesser General Public License,
 * 	  but realistically I probably won't have remembered.
 *    
 *    For a copy please see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

string BASE_PATH = "/sys/class/gpio/";

std::map<std::string, std::string> TinkerBoardPinMap =
{
	{3, 252},
	{5, 253},
	{7, 17},
	{8, 161},
	{10, 160},
	{11, 164},
	{12, 184},
	{13, 166},
	{15, 167},
	{16, 162},
	{18, 163},
	{19, 257},
	{21, 256},
	{22, 171},
	{23, 254},
	{24, 255},
	{26, 251},
	{29, 233},
	{26, 234},
	{29, 165},
	{31, 168},
	{32, 239},
	{33, 238},
	{35, 185},
	{36, 223},
	{37, 224},
	{38, 187},
	{40, 188}
}

// Function to export a pin using the sysfs

static int ExportPin (string pinName)
{
	//Create file name for the export function
	
	std::string exportFile = BASE_PATH + "export";
	const char* cExportFile = exportFile.c_str();

	const char* _pinName = pinName.c_str(); 
	
	FILE * fp;
	fp = fopen (cExportFile, "w");
	if (fp!=NULL)
	{
		fputs (_pinName, fp);
		fclose (fp);
		std::cout << "Exported pin: " << pinName << endl;
	}
	else if (fp==NULL)
	{
		std::cout << "File was not there: " << cExportFile << endl;
		return -1;
	}	
	return 0;	
}

// Function to set the direction of a pin using the sysfs

static int SetDirection (char* pinName, char* direction)
{
	std::string directionFile = BASE_PATH + "gpio" + pinName + "/direction";
	const char* cDirectionFile = directionFile.c_str();
	
	FILE * fp;
	fp = fopen (cDirectionFile, "w");
	if (fp!=NULL)
	{
		fputs (direction, fp);
		fclose (fp);
		std::cout << "Set Direction of pin " << pinName << " to " << direction << endl;
	}
	else if (fp==NULL)
	{
		return -1;
	}	
	return 0;	
}

// Function to set the output value of a pin using the sysfs

static int SetValue (char* pinName, char* value)
{
	std::string valueFile = BASE_PATH + "gpio" + pinName + "/value";
	const char* cValueFile = valueFile.c_str();
	
	FILE * fp;
	fp = fopen (cValueFile, "w");
	if (fp!=NULL)
	{
		fputs (value, fp);
		fclose (fp);
		std::cout << "Set value of pin " << pinName << " to " << value << endl;
	}
	else if (fp==NULL)
	{
		std::cout << "File not found: " << cValueFile << endl;
		return -1;
	}	
	return 0;	
}

// Function to unexport a pin using the sysfs

static int UnexportPin (char* pinName)
{
	//Create file name for the export function
	
	std::string unexportFile = BASE_PATH + "unexport";
	const char* cUnexportFile = unexportFile.c_str();
	
	FILE * fp;
	fp = fopen (cUnexportFile, "w");
	if (fp!=NULL)
	{
		fputs (pinName, fp);
		fclose (fp);
		std::cout << "Unexported pin: " << pinName << endl;
	}
	else if (fp==NULL)
	{
		return -1;
	}	
	return 0;	
}

// Function to reverse the output value of a pin

static int ReverseValue (char* pinName)
{
	std::string valueFile = BASE_PATH + "gpio" + pinName + "/value";
	const char* cValueFile = valueFile.c_str();
	
	char currValue [1] = "2";
	
	FILE * fp;
	fp = fopen (cValueFile, "r");
	if(fp!=NULL)
	{
		fgets(currValue, 2, fp);
		fclose(fp);
		std::cout << "Pin state is: " << currValue << endl;

	}
	else if (fp==NULL)
	{
		std::cout << "File not found: " << cValueFile << endl;
		return -1;
	}

	if(strcmp(currValue, "1")==0)
	{
		std::cout << "As Value is: 1, setting to 0" << endl;
		SetValue(pinName, "0");
	}
	else if(strcmp(currValue, "0")==0)
	{
		std::cout << "As Value is: 0, setting to 1" << endl;
		SetValue(pinName, "1");
	}
	else if(strcmp(currValue, "2")==0)
	{
		return -1;
	}
	return 0;
}

int SendAndStop(char* pinName)
{
	std::string _pinName = pinName;
	ExportPin(_pinName);
	SetDirection(pinName, "out");
	SetValue(pinName, "1");
	usleep(100000);
	SetValue(pinName, "0");
	UnexportPin(pinName);
	return 0;
}

char PinNameConverter(int pinNum)
{
	
}

int Testing()
{
	char* pinToUse = "171";
	char* directionToUse = "out";
	char* high = "1";
	char* low = "0";
	
	std::cout << "Test Run Starting" << endl;
	ExportPin(pinToUse);
	SetDirection(pinToUse, directionToUse);
	SetValue(pinToUse, high);
	for (int i = 1; i < 99; i++)
	{
		ReverseValue(pinToUse);
		sleep(1);
	}
	SetValue(pinToUse, low);
	UnexportPin(pinToUse);
	std::cout << "All done." << endl;
	return 0;
}

int main()
{
	std::cout << "GPIO Communicator started" << endl;
	SendAndStop("171");
	return 0;
}
