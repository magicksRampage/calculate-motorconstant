#include <string>
#include <iostream>
#include <cstdio>

// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "serial.h"

using std::string;
using std::exception;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;

void my_sleep(unsigned long milliseconds);
void enumerate_ports();
void print_usage();
string read(string port, unsigned long baud);
int run(int argc, char **argv);
//int main(int argc, char **argv);
