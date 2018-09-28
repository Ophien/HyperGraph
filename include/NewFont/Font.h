#ifndef Font___H
#define Font___H
//--------------------------------------------------------------------------
#include <map>
#include "NewFont\ConvertUTF.h"
#include <vector>
//--------------------------------------------------------------------------
typedef char FontFileBinHeader[16];
struct FontHeader{
    unsigned short mTexW;
    unsigned short mTexH;
    unsigned short nSpaceWidth;
    unsigned short mGlyphHeight;
    unsigned short mGlyphCount;
};
struct FontGlyphInfo{
    unsigned short texX,texY;
    short x,y,advX,advY;//can be negative
    unsigned short w,h;//always positive
};
//--------------------------------------------------------------------------
class OpenGLFont;

class Font{
    FontHeader mHeader;
    std::map<UTF32, FontGlyphInfo> mGlyphs;
    char* luminancePointer;

    void release();
public:
    void operator=(const Font& v);
    Font(const Font& font);
    Font();
    virtual ~Font();
    static Font* LoadFromBasof(const char* basofFile);

    OpenGLFont* createOpenGLFont();
};
//--------------------------------------------------------------------------
// GL SUPPORT REQUIRED
//--------------------------------------------------------------------------
#include "gamelib_math.h"

struct GLFontGlyphInfo{
    //base calculations
    vec2 texBegin,texEnd;
    vec2 dimension;
    vec2 beforeStart,advance;
    //used for render
    vec2 TexcoordVertex2fStrip[8];
};

#include <Windows.h>
#include <GL/GL.h>

class StripText;

class OpenGLFont{
    FontHeader mHeader;
    std::map<UTF32, GLFontGlyphInfo> mGlyphs;
    GLuint mTextureID;

public:
    OpenGLFont(const OpenGLFont& v);
    void operator=(const OpenGLFont&v);
    OpenGLFont(const FontHeader& aHeader,
               std::map<UTF32, FontGlyphInfo>& aGlyphs,
               const char* luminancePointer);
    virtual ~OpenGLFont();

    GLuint getTextureHandle();

    //void print(const wchar_t* v,...);
    void print(const char* string);
	float calcTextWidth(const char* string);
	std::vector<std::string> calcStringWidthSplit(const char* string, int maxW);
	
    StripText* createStripText(const char* string);
private:
    vec2 putc(char c, const vec2& p, bool repeatFirstPtn, bool repeatLastPtn);
};

struct StripInfoVertexAttrib{
    vec4 mColor;
    vec2 mCoord;
    vec2 mPos;
};

class StripText{
    StripInfoVertexAttrib *mStripInfo;
    int mSize;
    int mTextureID;

public:
    StripText(const StripText& v);
    void operator=(const StripText&v);
	float height;

    void setSize(int s);

    StripText(int buffSize, GLuint textureID );
    virtual ~StripText();
    StripInfoVertexAttrib& getVertex(int index);
    void draw();
	
    void resetColor(vec4 c);

    void saturateFromBegin(float increment);
};


//--------------------------------------------------------------------------

#endif
