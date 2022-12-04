typedef struct Texture Texture;
typedef struct Entity Entity;
typedef struct Effect Effect;

//handling draw and logic in the main loop
typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Handler;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
	int x;
	int y;
	int button[MAX_MOUSE_BUTTONS];
	int wheel;
} Mouse;

struct Entity {
	int whose;
	float y;
	float x;
	int w;
	int h;
	float dy;
	float dx;
	int radius;
	int health;
	int reload;
	int angle;
	int weaponType;
	SDL_Texture *texture;
	SDL_Color color;
	void (*type)(void);
	void (*touch)(Entity *other);
	void (*die)(void);
	Entity *next;
};

struct Effect {
	float y;
	float x;
	float dy;
	float dx;
	int life;
	SDL_Color color;
	SDL_Texture* texture;
	Effect* next;
};

typedef struct {
	SDL_Window* window;
	SDL_Renderer *renderer;
	Handler handler;
	Mouse mouse;
	Texture textureHead, *textureTail;
	int keyboard[MAX_KEYBOARD_KEYS];
	char inputText[MAX_LINE_LENGTH];
} Program;

typedef struct {
	int score;
	int ammo[WPN_MAX];
	Entity entityHead, *entityTail;
	Entity bulletHead, *bulletTail;
	Effect effectHead, *effectTail;
	SDL_Point camera;
	int type;
} Arena;

typedef struct {
	int t1;
	int t2;
	double delta;
	double worldTime;
	double hitTime;
} Time;

typedef struct {
	char name[MAX_SCORE_NAME_LENGTH];
	int recent;
	int score;
} Highscore;

typedef struct {
	Highscore highscore[NUM_HIGHSCORES];
} Highscores;

