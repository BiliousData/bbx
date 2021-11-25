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
	{XA_BackA, XA_LENGTH(9200)}, //XA_GroovyBrass
	{XA_BackA, XA_LENGTH(9100)}, //XA_Conscience
	{XA_BackB, XA_LENGTH(14900)}, //XA_YapSquad
	{XA_BackB, XA_LENGTH(14600)}, //XA_Intertwined
	{XA_MemeA, XA_LENGTH(14600)}, //XA_CopyCat
	{XA_MemeA, XA_LENGTH(16500)}, //XA_JumpOut
	{XA_MemeB, XA_LENGTH(20100)}, //XA_RonaldMcDonaldSlide
};

static const char *xa_paths[] = {
	"\\MUSIC\\MENU.XA;1",   //XA_MENU
	"\\MUSIC\\BOBA.XA;1",   //XA_BOBA
	"\\MUSIC\\BOBB.XA;1",   //XA_BOBB
	"\\MUSIC\\BACKA.XA;1",
	"\\MUSIC\\BACKB.XA;1",
	"\\MUSIC\\MEMEA.XA;1",
	"\\MUSIC\\MEMEB.XA;1",
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
	//BACKA.XA
	{"groovybrass", true},
	{"conscience", true},
	//BACKB.XA
	{"yapsquad", true},
	{"intertwined", true},
	//MEMEA.XA
	{"copycat", true},
	{"jumpout", true},
	//MEMEB.XA
	{"ronaldmcdonaldslide", true},
	
	{NULL, false}
};
