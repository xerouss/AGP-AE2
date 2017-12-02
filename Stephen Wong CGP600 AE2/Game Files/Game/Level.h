// *********************************************************
//	Name:			Stephen Wong
//	File:			Level.h
//	Last Updated:	02/12/2017
//	Project:		CGP600 AE2
// *********************************************************

#pragma once

class Level
{
private:
	// TODO: ADD THESE:
	// Lights
	// GameObjects
	// Camera
	// Particles
	// Scene Nodes

public:
	//Level();
	//~Level();

	void SetUpLevel(void);
	void Update(void);
	void Render(void);
	void PlayerInput(unsigned char pressedKeys[]);
};
