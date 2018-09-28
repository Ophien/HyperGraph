#include "NewFont\Font.h"
#include "NewFont\TextureManager.h"
//--------------------------------------------------------------------------
void Font::release(){
    if (luminancePointer != NULL){
        delete[] luminancePointer;
    }
    luminancePointer = NULL;
    mGlyphs.clear();
    memset(&mHeader,0,sizeof(FontHeader));
}
//--------------------------------------------------------------------------
void Font::operator=(const Font& v){
    release();
    mHeader = v.mHeader;
    mGlyphs = v.mGlyphs;
    if (v.luminancePointer != NULL){
        luminancePointer = new char[mHeader.mTexW*mHeader.mTexH];
        memcpy(luminancePointer,v.luminancePointer,mHeader.mTexW*mHeader.mTexH*sizeof(char));
    }
}
//--------------------------------------------------------------------------
Font::Font(const Font& font){
    luminancePointer = NULL;
    (*this) = font;
}
//--------------------------------------------------------------------------
Font::Font(){
    luminancePointer = NULL;
}
//--------------------------------------------------------------------------
Font::~Font(){
    release();
}
//--------------------------------------------------------------------------
Font* Font::LoadFromBasof(const char* basofFile){
    Font *result = new Font();
    FILE* in = fopen(basofFile,"rb");
    if (in){
        FontFileBinHeader binHeader;
        fread(&binHeader,sizeof(FontFileBinHeader),1,in);
        if (memcmp(&binHeader,".asilva.lum.font",16) == 0){
            //valid basof file :)

            //byte order -- the default pack for structs is 4bytes align ... there are 5 shorts... in the structure (unaligned...)
            //   to read correctly -- need short by short reading.
            fread(&result->mHeader.mTexW,sizeof(short),1,in);//texW
            fread(&result->mHeader.mTexH,sizeof(short),1,in);//texH
            fread(&result->mHeader.nSpaceWidth,sizeof(short),1,in);
            fread(&result->mHeader.mGlyphHeight,sizeof(short),1,in);//new line height
            fread(&result->mHeader.mGlyphCount,sizeof(unsigned short),1,in);//numberOfGlyphs

            for (int i=0;i<result->mHeader.mGlyphCount;i++){
                UTF32 c;
                FontGlyphInfo glyphInfo;
                fread(&c,sizeof(UTF32),1,in);
                fread(&glyphInfo,sizeof(glyphInfo),1,in);
                result->mGlyphs[c] = glyphInfo;
            }

            unsigned int bufferTotalSize = result->mHeader.mTexW*result->mHeader.mTexH;
            result->luminancePointer = new char[bufferTotalSize];
            
            //RLE reverse
            unsigned char rle_count = 0;
            unsigned int bufferInsertPos = 0;
            while (!feof(in) && bufferInsertPos < bufferTotalSize){
                char c;
                fread(&c,sizeof(char),1,in);
                if (c == '\x00' || c == '\xff'){
                    //rel decompress
                    fread(&rle_count,sizeof(char),1,in);
                    memset(&result->luminancePointer[bufferInsertPos],(unsigned char)c,rle_count);
                    bufferInsertPos += rle_count;
                }else{
                    result->luminancePointer[bufferInsertPos] = c;
                    bufferInsertPos++;
                }
            }
        }
        fclose(in);
    }
    return result;
}
//--------------------------------------------------------------------------
OpenGLFont* Font::createOpenGLFont(){
    OpenGLFont *result = new OpenGLFont(mHeader,mGlyphs,luminancePointer);

    return result;
}
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
//  NEED OPENGL SUPPORT HERE
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
OpenGLFont::OpenGLFont(const OpenGLFont& v){
    mHeader = v.mHeader;
    mGlyphs = v.mGlyphs;

    TextureManager::getSingleton()->incrementTextureUse(v.mTextureID);
    mTextureID = v.mTextureID;
}

void OpenGLFont::operator=(const OpenGLFont&v){
    mHeader = v.mHeader;
    mGlyphs = v.mGlyphs;

    TextureManager::getSingleton()->incrementTextureUse(v.mTextureID);
    TextureManager::getSingleton()->releaseTexture(mTextureID);
    mTextureID = v.mTextureID;
}

OpenGLFont::OpenGLFont(const FontHeader& aHeader,
                       std::map<UTF32, FontGlyphInfo>& aGlyphs,
                       const char* luminancePointer){
    mHeader = aHeader;
    //mGlyphs = aGlyphs;
    float w = (float)aHeader.mTexW;
    float h = (float)aHeader.mTexH;

    std::map<UTF32, FontGlyphInfo>::iterator it = aGlyphs.begin();

    while (it != aGlyphs.end()){
        FontGlyphInfo glyph = it->second;
        GLFontGlyphInfo glGlyphInfo;
            glGlyphInfo.beforeStart = vec2(glyph.x,-glyph.h+glyph.y);
            glGlyphInfo.advance = vec2(glyph.advX, glyph.advY) ;//- glGlyphInfo.beforeStart;
            glGlyphInfo.dimension = vec2(glyph.w,glyph.h);
            glGlyphInfo.texBegin = vec2(((float)glyph.texX)/w, 1.0f-((float)glyph.texY)/h);
            glGlyphInfo.texEnd = glGlyphInfo.texBegin + glGlyphInfo.dimension/vec2(w,-h);

        //compute the 
        vec2 buffer[8]={
                        vec2(glGlyphInfo.texBegin.x, glGlyphInfo.texBegin.y), vec2(0                      , glGlyphInfo.dimension.y) + glGlyphInfo.beforeStart,
                        vec2(glGlyphInfo.texBegin.x, glGlyphInfo.texEnd.y  ), vec2(0                      , 0) + glGlyphInfo.beforeStart,
                        vec2(glGlyphInfo.texEnd.x  , glGlyphInfo.texBegin.y), vec2(glGlyphInfo.dimension.x, glGlyphInfo.dimension.y) + glGlyphInfo.beforeStart,
                        vec2(glGlyphInfo.texEnd.x  , glGlyphInfo.texEnd.y  ), vec2(glGlyphInfo.dimension.x, 0) + glGlyphInfo.beforeStart
                        };
        for (int i=0;i<8;i++)
            glGlyphInfo.TexcoordVertex2fStrip[i] = buffer[i];
        mGlyphs[it->first] = glGlyphInfo;
        it++;
    }

    //glGenTextures(1,&mTextureID);
    mTextureID = TextureManager::getSingleton()->createTexture();

    glBindTexture( GL_TEXTURE_2D, mTextureID );

    //global texenv set
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

    //wrap mode
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR ); 

    //repeat mode
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    glTexImage2D(GL_TEXTURE_2D,0, GL_INTENSITY8,
                mHeader.mTexW, mHeader.mTexH,
                0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 
                luminancePointer);

}

OpenGLFont::~OpenGLFont(){
    TextureManager::getSingleton()->releaseTexture(mTextureID);
}

GLuint OpenGLFont::getTextureHandle(){
    return mTextureID;
}

/*
void OpenGLFont::printf(const char* format,...){
  va_list args;
  char buffer[BUFSIZ];
  va_start(args,format);
  int charCount = vsnprintf (buffer, BUFSIZ, format, args );
  for (int i=0;i<charCount;i++)
    putc(buffer[i]);
  va_end(args);

  }
  */

float OpenGLFont::calcTextWidth(const char* string)
{
	//vec2 p;
	GLfloat p=0;
	size_t count = strlen(string);
	for (int i=0;i<count;i++)
	{
		//p += putc(string[i],p,i!=0,i<count-1);
		std::map<UTF32, GLFontGlyphInfo>::iterator it = mGlyphs.find(string[i]);
		if (it != mGlyphs.end())
		{
			p += it->second.advance.x;
		}
	}
	return p;
}

std::vector<std::string> OpenGLFont::calcStringWidthSplit(const char* string, int maxW)
{
	unsigned int width=0;
	std::vector<std::string> mSplit;
	std::string concat;
	GLfloat p=0;

	size_t count = strlen(string);
	for (int i=0;i<count;i++)
	{
		//p += putc(string[i],p,i!=0,i<count-1);
		std::map<UTF32, GLFontGlyphInfo>::iterator it = mGlyphs.find(string[i]);
		if (it != mGlyphs.end())
		{
			p += it->second.advance.x;
			concat += string[i];
			if(p>maxW)
			{
				mSplit.push_back(concat);
				concat.clear();
				p = 0;
			}
		}
	}
	if(concat.length()>0)
		mSplit.push_back(concat);
	return mSplit;
}

void OpenGLFont::print(const char* string){
	//glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,mTextureID);
    //glColor4ub(255,255,255,255);

    vec2 p;
    size_t count = strlen(string);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i=0;i<count;i++){
        p += putc(string[i],p,i!=0,i<count-1);
    }
    glEnd();

    //glDisable(GL_TEXTURE_2D);
}

vec2 OpenGLFont::putc(char inputChar, const vec2& p, bool repeatFirstPtn, bool repeatLastPtn){
    UTF32 c = inputChar;
/*    if (sizeof(wchar_t) == 4){
        c = inputChar;
    }else if (sizeof(wchar_t) == 2){
        c = inputChar;
    }else{
        c = L'?';
    }
    */
    //consult the glyphTable
    std::map<UTF32, GLFontGlyphInfo>::iterator it = mGlyphs.find(c);
    if (it != mGlyphs.end()){
        const GLFontGlyphInfo& glyph = it->second;
        //glTranslatef(glyph.beforeStart.x,glyph.beforeStart.y,0);
        for (int i=0;i<8;i+=2){
            if (i==0 && repeatFirstPtn){
                glVertex2fv((glyph.TexcoordVertex2fStrip[i+1]+p).array); 
            }
            glTexCoord2fv((glyph.TexcoordVertex2fStrip[i]).array); 
            glVertex2fv((glyph.TexcoordVertex2fStrip[i+1]+p).array); 
            if (i==6 && repeatLastPtn){
                glVertex2fv((glyph.TexcoordVertex2fStrip[i+1]+p).array); 
            }
        }
        
        /*
        glDisable(GL_TEXTURE_2D);
        glColor4ub(255,0,255,255);
        glBegin(GL_LINES);
            glVertex2f(0,0);
            glVertex2f(0,100);
        glEnd();
        */

       // glTranslatef(glyph.advance.x,glyph.advance.y,0);
        return glyph.advance;
    }
    return vec2(0);
}

StripText* OpenGLFont::createStripText(const char* string){
    vec4 color(1,0,1,1);
    vec2 p;
    size_t count = strlen(string);
    StripText* result = new StripText(count*4+(count-1)*2,mTextureID);
   
    int pos = 0;
    for (int i=0;i<count;i++){
		if(string[i] == '\n')
		{
			p.x = 0;
			p.y -= mHeader.mGlyphHeight;
			continue;
		}

        std::map<UTF32, GLFontGlyphInfo>::iterator it = mGlyphs.find(string[i]);
        if (it != mGlyphs.end()){
            const GLFontGlyphInfo& glyph = it->second;
            for (int j=0;j<8;j+=2){
                if (j==0 && i!=0){
                    StripInfoVertexAttrib& v = result->getVertex(pos++);
                    v.mColor = color;
                    v.mCoord = glyph.TexcoordVertex2fStrip[j+0];
                    v.mPos = glyph.TexcoordVertex2fStrip[j+1] + p;
                }
                StripInfoVertexAttrib& v = result->getVertex(pos++);
                v.mColor = color;
                v.mCoord = glyph.TexcoordVertex2fStrip[j+0];
                v.mPos = glyph.TexcoordVertex2fStrip[j+1] + p;
                if (j==6 && i<count-1){
                    StripInfoVertexAttrib& v = result->getVertex(pos++);
                    v.mColor = color;
                    v.mCoord = glyph.TexcoordVertex2fStrip[j+0];
                    v.mPos = glyph.TexcoordVertex2fStrip[j+1] + p;
                }
            }
            p += glyph.advance;
        }
    }
    result->setSize(pos);
	result->height = mHeader.mGlyphHeight;
    return result;
}

StripText::StripText(const StripText& v){
    mStripInfo = new StripInfoVertexAttrib[v.mSize];
    mSize = v.mSize;

    TextureManager::getSingleton()->incrementTextureUse(v.mTextureID);

    mTextureID = v.mTextureID;
}

void StripText::operator=(const StripText&v){
    delete[] mStripInfo;
    mStripInfo = NULL;
    mSize = 0;
    
    mStripInfo = new StripInfoVertexAttrib[v.mSize];
    mSize = v.mSize;

    TextureManager::getSingleton()->incrementTextureUse(v.mTextureID);
    TextureManager::getSingleton()->releaseTexture(mTextureID);

    mTextureID = v.mTextureID;
}

StripText::StripText(int buffSize, GLuint textureID ){
    mStripInfo = new StripInfoVertexAttrib[buffSize];
    mSize = buffSize;
    mTextureID = textureID;
    TextureManager::getSingleton()->incrementTextureUse(textureID);
}

StripText::~StripText(){
    delete[] mStripInfo;
    mStripInfo = NULL;
    mSize = 0;
    TextureManager::getSingleton()->releaseTexture(mTextureID);
}

StripInfoVertexAttrib& StripText::getVertex(int index){
    return mStripInfo[index];
}

void StripText::draw(){
    //glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,mTextureID);
    glBegin(GL_TRIANGLE_STRIP);
    for (int i=0;i<mSize;i++){
        glColor4fv(mStripInfo[i].mColor.array);
        glTexCoord2fv(mStripInfo[i].mCoord.array);
        glVertex2fv(mStripInfo[i].mPos.array);
    }
    glEnd();
    //glDisable(GL_TEXTURE_2D);
}

void StripText::setSize(int s){
    mSize = s;
}


void StripText::resetColor(vec4 c){
    for (int i=0;i<mSize;i++){
        mStripInfo[i].mColor = c;
    }
}

void StripText::saturateFromBegin(float increment){
    for (int i=0;i<mSize;i+=6){
        for (int j=0;j<4;j++){
            mStripInfo[i+j].mColor += increment;
            mStripInfo[i+j].mColor = clamp(mStripInfo[i].mColor,0.0f,1.0f);
        }
        if (distance(mStripInfo[i].mColor,vec4(1)) > 0.01f)
            return;
    }
}