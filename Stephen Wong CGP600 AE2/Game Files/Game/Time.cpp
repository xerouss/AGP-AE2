// *********************************************************
//	Name:			Stephen Wong
//	File:			Time.cpp
//	Last Updated:	27/12/2017
//	Project:		CGP600 AE2
// *********************************************************

//////////////////////////////////////////////////////////////////////////////////////
// All The includes for the file
//////////////////////////////////////////////////////////////////////////////////////
#pragma region Includes

#include "Time.h"

#pragma endregion

//####################################################################################
// Constructor
//####################################################################################
Time::Time()
{
	m_startTime = clock();
}

//####################################################################################
// Get time from start of the game
//####################################################################################
int Time::GetSecondsSinceStartOfGame(void)
{
	// Minus the time by the time at the start of the game
	// Need to divide by clocks per sec in order to get seconds
	return (clock() - m_startTime) / CLOCKS_PER_SEC;
}

//####################################################################################
// Format time into mintues and seconds
//####################################################################################
string Time::GetTimeSinceStartOfGameFormatted(void)
{
	int time = GetSecondsSinceStartOfGame();
	int minutes = time / secondsInAMinute;
	int seconds = time % secondsInAMinute; // Mod time for seconds since if it goes over 59 will reset to 0

	// Add padding if needed
	string minutesText = TimePadding(minutes);
	string secondsText = TimePadding(seconds);

	return minutesText + ":" + secondsText;
}

//####################################################################################
// Add zeros to the time if under 10
//####################################################################################
string Time::TimePadding(int time)
{
	string timeString;

	// Add 0 if time is under 10 to make it looks better
	if (time < 10) timeString = string(amountOfZeros, '0').append(to_string(time));
	else timeString = to_string(time); // Else don't add any zeros

	return timeString;
}
