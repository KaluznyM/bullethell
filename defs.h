#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(text, src, n) strncpy(text, src, n)

#define PI                       3.14159265358

#define SCREEN_WIDTH             1280
#define SCREEN_HEIGHT            780

#define ARENA_WIDTH              (SCREEN_WIDTH * 5)
#define ARENA_HEIGHT             (SCREEN_HEIGHT * 5)

#define MAX_NAME_LENGTH          32
#define MAX_LINE_LENGTH          1024
#define MAX_SCORE_NAME_LENGTH    16

#define FPS                      60

#define BOARD_SIZE                64

#define BOARD_RENDER_WIDTH        (SCREEN_WIDTH / BOARD_SIZE)
#define BOARD_RENDER_HEIGHT       ((SCREEN_HEIGHT / BOARD_SIZE) + 1)

#define MAX_KEYBOARD_KEYS        350
#define MAX_MOUSE_BUTTONS        6

#define NUM_HIGHSCORES           9

#define PLAYER_SPEED             8

#define GLYPH_WIDTH              18
#define GLYPH_HEIGHT             29

#define INVINCIBILITY            0.05	//time of being unable to lose health after losing one

#define PISTOL_AMMO				 12
#define SMG_AMMO				 100
#define SHOTGUN_AMMO			 16

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

enum
{
	WPN_PISTOL,
	WPN_SMG,
	WPN_SHOTGUN,
	WPN_MAX
};

enum
{
	SIDE_NONE,
	SIDE_PLAYER,
	SIDE_ENEMY
};

enum
{
	SND_PISTOL,
	SND_SMG,
	SND_SHOTGUN,
	SND_ENEMY_BULLET,
	SND_AMMO,
	SND_POINTS,
	SND_ENEMY_HIT,
	SND_DONK_HIT,
	SND_ENEMY_DIE,
	SND_DONK_DIE,
	SND_MAX
};

enum
{
	CH_ANY = -1,
	CH_DONK,
	CH_ITEM,
	CH_ENEMY_BULLET,
	CH_HIT
};

enum 
{
	ZERO,
	FIRST,
	SECOND,
	THIRD
};
