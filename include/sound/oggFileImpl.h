/*
SPD game library version 0.1.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef oggFileImpl_h
#define oggFileImpl_h

//#include "../SysHelper/DebugPrint.h"
//#include "../SysHelper/ERRORString.h"
//ogg vorbits library
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"
//---------------------------------------------------------------------------------------
/*
headers
*/
//---------------------------------------------------------------------------------------
class arquivoOGG{
   long position;
   char *data;
   long tamanhoDoVetor;
   public:
   arquivoOGG();
   bool LoadFile(const char *file);
   ~arquivoOGG();
   size_t Preencher(char *Vetor,const long Tamanho);
   long getPosition()const ;
   int close();
   int seek(const ogg_int64_t offset,const int whence);
};
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
/*
the prototypes of function of callbacks
*/
//---------------------------------------------------------------------------------------
//size_t read_func(void *ptr, size_t size, size_t nmemb, void *datasource);
//---------------------------------------------------------------------------------------
//int seek_func(void *datasource, ogg_int64_t offset, int whence);
//---------------------------------------------------------------------------------------
//int close_func(void *datasource);
//---------------------------------------------------------------------------------------
//long tell_func(void *datasource);
//---------------------------------------------------------------------------------------
/*
The declaration of main callback of oggvorbis file
*/
//---------------------------------------------------------------------------------------
//ov_callbacks callbacks={read_func,seek_func,close_func,tell_func};
//---------------------------------------------------------------------------------------
/*
The class of stream buffer audio AudioBuffer.

#####################
# class AudioBuffer #
#####################

*/
//---------------------------------------------------------------------------------------
/*
class AudioBuffer{
   public:
   virtual long FillBuffer(char *buffer,int bufferSize)=0;
   virtual ~AudioBuffer(){};
};//*/
//---------------------------------------------------------------------------------------
/*
###################
# class OggBuffer #
###################
*/
//---------------------------------------------------------------------------------------
class OggBuffer{
   //------------------------------------------------------------------------------------
   arquivoOGG oggData;
   OggVorbis_File vf;
   bool streamOpen;
   int current_section;
   
           vorbis_info*    vorbisInfo;
        vorbis_comment* vorbisComment;
   long samplesCount;
   //------------------------------------------------------------------------------------
   public:
   //------------------------------------------------------------------------------------
   OggBuffer(const char *file);
   //------------------------------------------------------------------------------------
   ~OggBuffer();
   //------------------------------------------------------------------------------------
   long FillBuffer(char *buffer,const int bufferSize);
   //------------------------------------------------------------------------------------
   int getChannels()const ;
   //------------------------------------------------------------------------------------
   int getBitRate()const ;
   //------------------------------------------------------------------------------------
   int getBytesPerSample()const ;
   //------------------------------------------------------------------------------------
   long getSamplesCount()const ;
   //------------------------------------------------------------------------------------
   long getRawBytePcmSize()const ;
   //------------------------------------------------------------------------------------
   void resetStream();
   //------------------------------------------------------------------------------------
   void changeStream(const char*file);
   //------------------------------------------------------------------------------------
//   friend class ControleDeSom;
};
//---------------------------------------------------------------------------------------
//AudioBuffer* LoadOggFile(char *file);
//------------------------------------------------------------------------------------

#endif
