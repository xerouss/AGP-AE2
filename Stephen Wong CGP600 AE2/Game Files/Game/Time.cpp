// *********************************************************
//	Name:			Stephen Wong
//	File:			Time.cpp
//	Last Updated:	30/12/2017
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
	m_totalPauseTime = 0;
}

//####################################################################################
// Get time from start of the game
//####################################################################################
int Time::GetSecondsSinceStartOfGame(void)
{
	return ConvertToSeconds(m_startTime);
}

//####################################################################################
// Format time into minutes and seconds
//####################################################################################
string Time::GetTimeSinceStartOfGameFormatted(void)
{
	// Remove the amount of time the game was paused
	// Since the timer shouldn't increased while the game is pause
	int time = GetSecondsSinceStartOfGame() - m_totalPauseTime;
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

//####################################################################################
// Converts the clock_t time to int/seconds
//####################################################################################
int Time::ConvertToSeconds(clock_t time)
{
	// Minus the clock time by the time to get current time
	// Need to divide by clocks per sec in order to get seconds
	return (clock() - time) / CLOCKS_PER_SEC;
}

//####################################################################################
// When a pause starts
//####################################################################################
void Time::StartPause(void)
{
	// Save the current time
	m_pauseStartTime = clock();
}

//####################################################################################
// When a pause ends
//####################################################################################
void Time::EndPause(void)
{
	// Work out how long the pause lasted from
	int timePaused = ConvertToSeconds(m_pauseStartTime);

	// Save the amount of seconds so it can be removed from 
	// The time since the start of the game
	m_totalPauseTime += timePaused;
}
