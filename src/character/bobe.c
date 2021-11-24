/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "bobe.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//Bobe character structure
enum
{
	Bobe_ArcMain_Idle,
	Bobe_ArcMain_Hit,
	Bobe_ArcMain_Left,
	Bobe_ArcMain_Right,
	Bobe_ArcMain_Up,
	
	Bobe_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Bobe_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_Bobe;

//Bobe character definitions
static const CharFrame char_bobe_frame[] = {
	{Bobe_ArcMain_Idle, {  0,   0, 86, 171}, { 42, 183}}, //0 idle 1
	{Bobe_ArcMain_Idle, { 86,   0, 85, 172}, { 42, 184}}, //1 idle 2
	{Bobe_ArcMain_Idle, {171,   0, 85, 172}, { 43, 184}}, //2 idle 3
	{Bobe_ArcMain_Hit,  {  0,   0, 84, 173}, { 43, 185}}, //3 idle 4
	
	{Bobe_ArcMain_Left, {  0,   0,  87, 176}, { 51, 188}}, //4 left 1
	{Bobe_ArcMain_Left, { 87,   0,  86, 177}, { 50, 189}}, //5 left 2
	
	{Bobe_ArcMain_Hit, { 84,   0,  82, 174}, { 34, 183}}, //6 down 1
	{Bobe_ArcMain_Hit, {166,   0,  81, 174}, { 34, 183}}, //7 down 2
	
	{Bobe_ArcMain_Up, {  0,   0,  86, 188}, { 34, 200}}, //8 up 1
	{Bobe_ArcMain_Up, { 86,   0,  86, 187}, { 34, 199}}, //9 up 2
	
	{Bobe_ArcMain_Right, {  0,   0,  90, 180}, { 30, 192}}, //10 right 1
	{Bobe_ArcMain_Right, { 90,   0,  89, 181}, { 29, 193}}, //11 right 2
};

static const Animation char_bobe_anim[CharAnim_Max] = {
	{2, (const u8[]){ 0, 1,  2,  3,  ASCR_BACK, 1}}, //CharAnim_Idle
	{2, (const u8[]){ 4,  5, ASCR_BACK, 1}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 6,  7, ASCR_BACK, 1}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{2, (const u8[]){ 8,  9, ASCR_BACK, 1}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{2, (const u8[]){10, 11, ASCR_BACK, 1}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//Bobe character functions
void Char_Bobe_SetFrame(void *user, u8 frame)
{
	Char_Bobe *this = (Char_Bobe*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_bobe_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_Bobe_Tick(Character *character)
{
	Char_Bobe *this = (Char_Bobe*)character;
	
	if (stage.flag & STAGE_FLAG_JUST_STEP)
		{
			//Perform dance
			if (stage.note_scroll >= character->sing_end && (stage.song_step % stage.gf_speed) == 0)
			{
				character->set_anim(character, CharAnim_Idle);
			}
		}
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Bobe_SetFrame);
	Character_Draw(character, &this->tex, &char_bobe_frame[this->frame]);
}

void Char_Bobe_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Bobe_Free(Character *character)
{
	Char_Bobe *this = (Char_Bobe*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Bobe_New(fixed_t x, fixed_t y)
{
	//Allocate bobe object
	Char_Bobe *this = Mem_Alloc(sizeof(Char_Bobe));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Bobe_New] Failed to allocate bobe object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Bobe_Tick;
	this->character.set_anim = Char_Bobe_SetAnim;
	this->character.free = Char_Bobe_Free;
	
	Animatable_Init(&this->character.animatable, char_bobe_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	this->character.health_i = 2;
	
	this->character.focus_x = FIXED_DEC(65,1);
	this->character.focus_y = FIXED_DEC(-115,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\BOBE.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle.tim", //Bobe_ArcMain_Idle0
		"hit.tim",
		"left.tim",
		"right.tim",
		"up.tim",
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
