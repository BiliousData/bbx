#define XA_LENGTH(x) (((u64)(x) * 75) / 100 * IO_SECT_SIZE) //Centiseconds to sectors in bytes (w)

typedef struct
{
	XA_File file;
	u32 length;
} XA_TrackDef;

static const XA_TrackDef xa_tracks[] = {
	//MENU.XA
	{XA_Menu, XA_LENGTH(11295)}, //XA_GettinFreaky
	{XA_Menu, XA_LENGTH(3840)},  //XA_GameOver
	{XA_BobA, XA_LENGTH(9900)},  //XA_JumpIn
	{XA_BobA, XA_LENGTH(13400)}, //XA_Swing
	{XA_BobB, XA_LENGTH(15200)}, //XA_Split
	{XA_BobB, XA_LENGTH(60900)}, //XA_Tutorial
};

static const char *xa_paths[] = {
	"\\MUSIC\\MENU.XA;1",   //XA_MENU
	"\\MUSIC\\BOBA.XA;1",   //XA_BOBA
	"\\MUSIC\\BOBB.XA;1",   //XA_BOBB
	NULL,
};

typedef struct
{
	const char *name;
	boolean vocal;
} XA_Mp3;

static const XA_Mp3 xa_mp3s[] = {
	//MENU.XA
	{"freaky", false},   //XA_GettinFreaky
	{"gameover", false}, //XA_GameOver
	//BOBA.XA
	{"jumpin", true},
	{"swing", true},
	//BOBB.XA
	{"split", true},
	{"tutorial", true},
	
	{NULL, false}
};
