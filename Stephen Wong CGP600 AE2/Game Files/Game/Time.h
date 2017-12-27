// *********************************************************
//	Name:			Stephen Wong
//	File:			Time.cpp
//	Last Updated:	27/12/2017
//	Project:		CGP600 AE2
// *********************************************************
#pragma once

#pragma region Includes

#include <time.h>
#include <string>

using namespace std;
#pragma endregion

#pragma region Constants

const int secondsInAMinute = 60;
const int amountOfZeros = 1;

#pragma endregion


class Time
{
private:
	clock_t m_startTime;

public:
	Time();
	int GetTimeSinceStartOfGame(void);
	string GetTimeSinceStartOfGameFormatted(void);
	string TimePadding(int time);
};