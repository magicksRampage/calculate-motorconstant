#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "scale_interface.h"
#include "dynamixel_interface.h"


using namespace std;

int torqueOn() {

	DxlInterface dxl_interface (430, BAUDRATE, DEVICENAME);
	
	dxl_interface.initialize();
	dxl_interface.enableTorque();
        while(1) {
    		if (getch() == ESC_ASCII_VALUE)
      			break;
		
		dxl_interface.resetPosition();
	}
	dxl_interface.disableTorque();
	dxl_interface.close();
	return 0;
}

int experiment(char * fn, int baudrate) {
	DxlInterface dxl_interface (430, baudrate, DEVICENAME);
	
	dxl_interface.initialize();
	char * filename = fn;
	std::ofstream outputFile (filename);
	cout << "Writing to " << filename << endl;

	outputFile << "Current" << "," << "Weight" << std::endl;
	int maxCurrent = 1194;
	float current = 0;
	for (int i = 5; i < 223; i+=3) {
		dxl_interface.setModeCurrent();
		dxl_interface.enableTorque();
		current = i*2.69;



	
		dxl_interface.setGoalCurrent(-i);
		
		string result = "0.0";
		while (result == "0.0") {
			string raw = read("/dev/ttyUSB1", 9600);
			size_t data = raw.find_first_of("0123456789");
			if (data != string::npos) {
				result = raw.substr(data, 13 - data);
			} else {
				result = "0.0";
			}
		}
		
		cout << "Current: " << current << "/" << maxCurrent * 2.69 << endl;	
		cout << "Read: " << result << endl;



		outputFile << current << "," << result << std::endl;


		dxl_interface.setGoalCurrent(0);

		dxl_interface.disableTorque();

		dxl_interface.setModeExtendedPosition();
		dxl_interface.enableTorque();
		//dxl_interface.setGoalPosition(3800);
		dxl_interface.resetPosition();
		dxl_interface.disableTorque();
		my_sleep(2 * 1000);
	}
	outputFile.close();
	dxl_interface.close();
	
        //dxl_interface_demo();
	//run(argc, argv);

	return 0;
}

int main(int argc, char *argv[]) {

	char * filename = "csvtest.csv";
	int baudrate = BAUDRATE;
	if (argc > 1) {
		filename = argv[1];
	}
	if (argc > 2) {
		baudrate = atoi(argv[2]);
	}
	//return torqueOn();
	return experiment(filename, baudrate);
	//return dxl_interface_demo();

}
