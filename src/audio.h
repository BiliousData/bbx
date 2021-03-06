/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_AUDIO_H
#define PSXF_GUARD_AUDIO_H

#include "psx.h"

//XA enumerations
typedef enum
{
	XA_Menu,   //MENU.XA
	XA_BobA,
	XA_BobB,
	XA_BackA,
	XA_BackB,
	XA_MemeA,
	XA_MemeB,
	
	XA_Max,
} XA_File;

typedef enum
{
	//MENU.XA
	XA_GettinFreaky, //Gettin' Freaky
	XA_GameOver,     //Game Over
	//BOBA.XA
	XA_JumpIn,
	XA_Swing,
	//BOBB.XA
	XA_Split,
	XA_Tutorial,
	//BACKA.XA
	XA_GroovyBrass,
	XA_Conscience,
	//BACKB.XA
	XA_YapSquad,
	XA_Intertwined,
	//MEMEA.XA
	XA_CopyCat,
	XA_JumpOut,
	//MEMEB.XA
	XA_RonaldMcDonaldSlide,
	
	XA_TrackMax,
} XA_Track;

//Audio functions
void Audio_Init(void);
void Audio_Quit(void);
void Audio_PlayXA_Track(XA_Track track, u8 volume, u8 channel, boolean loop);
void Audio_SeekXA_Track(XA_Track track);
void Audio_PauseXA(void);
void Audio_StopXA(void);
void Audio_ChannelXA(u8 channel);
s32 Audio_TellXA_Sector(void);
s32 Audio_TellXA_Milli(void);
boolean Audio_PlayingXA(void);
void Audio_WaitPlayXA(void);
void Audio_ProcessXA(void);

#endif
