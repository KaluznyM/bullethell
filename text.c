#include "text.h"

static SDL_Texture *fontTexture;
static char printTextBuffer[MAX_LINE_LENGTH];

void initializeFonts(void)
{
	fontTexture = loadTexture("graphic/font.png");
}

void printText(int x, int y, int r, int g, int b, int align, char *format, ...)
{
	int length, buffer;
	SDL_Rect rectangle;
	va_list arguments;
	
	memset(&printTextBuffer, '\0', sizeof(printTextBuffer));

	va_start(arguments, format);
	vsprintf(printTextBuffer, format, arguments);
	va_end(arguments);
	
	length = strlen(printTextBuffer);
	
	switch (align)
	{
		case TEXT_RIGHT:
			x -= (length * GLYPH_WIDTH);
			break;
			
		case TEXT_CENTER:
			x -= (length * GLYPH_WIDTH) / 2;
			break;
	}
	
	rectangle.w = GLYPH_WIDTH;
	rectangle.h = GLYPH_HEIGHT;
	rectangle.y = 0;
	
	SDL_SetTextureColorMod(fontTexture, r, g, b);
	
	for (int i = 0 ; i < length ; i++)
	{
		buffer = printTextBuffer[i];
		
		if (buffer >= ' ' && buffer <= 'Z')
		{
			rectangle.x = (buffer - ' ') * GLYPH_WIDTH;
			
			bitblitRect(fontTexture, &rectangle, x, y);
			
			x += GLYPH_WIDTH;
		}
	}
}
