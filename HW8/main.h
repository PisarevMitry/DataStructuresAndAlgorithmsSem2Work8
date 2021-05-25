#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

using namespace std;

struct Patient
{
	long patient_id;
	int chronic_disease_id;
	string attending_doctor;
};

long long movements;
long long comparisons;

#endif
