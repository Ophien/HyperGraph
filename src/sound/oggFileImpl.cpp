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

#ifdef _MSC_VER
#pragma warning (disable:4996)
#endif

#include <exception>
#include <string>

#include <memory.h>//para copia de blocos de memoria
#include <malloc.h>
#include <stdlib.h>//para usar o exit
#include <stdio.h>//para usar o FILE

//#include "oggFileImpl.h"

#include <sound/oggFileImpl.h>






size_t read_func(void *ptr, size_t size, size_t nmemb, void *datasource);
//---------------------------------------------------------------------------------------
int seek_func(void *datasource, ogg_int64_t offset, int whence);
//---------------------------------------------------------------------------------------
int close_func(void *datasource);
//---------------------------------------------------------------------------------------
long tell_func(void *datasource);


ov_callbacks callbacks={read_func,seek_func,close_func,tell_func};

//---------------------------------------------------------------------------------------
/*
implementation of class arquivoOGG
*******************************************************************************
*                                                                             *
*  IMPLEMENTATION OF ARQUIVOOGG                                               *
*                                                                             *
*******************************************************************************
*/
//---------------------------------------------------------------------------------------
arquivoOGG::arquivoOGG(){
   position=tamanhoDoVetor=0;
   data=NULL;
}
//---------------------------------------------------------------------------------------
bool arquivoOGG::LoadFile(const char *file){//OK
   if (data!=NULL)
      free(data);
   data=NULL;
   position=tamanhoDoVetor=0;
   /**Load a entire file to data buffer
   */
   FILE *arq=fopen(file,"rb");
   if (arq!=NULL){
      /*ler o tamanho do arquivo*/
      //tamanhoDoVetor=0;
      fseek(arq,0,SEEK_END);
      tamanhoDoVetor = ftell(arq);
      fseek(arq,0,SEEK_SET);
/*
      fgetc(arq);
      while(!feof(arq)){
         tamanhoDoVetor++;
         fgetc(arq);
      }
      fclose(arq);
//*/
      //printf("tam do Arquivo:%d\n",tamanhoDoVetor);
      /*ler todo o conteudo do arquivo para o buffer*/
      data=(char*)malloc(tamanhoDoVetor);
      if (data==NULL){
        fclose(arq);
        char tmp[1024];
        sprintf(tmp,"[oggFileImpl] out of memory to allocate file: %s", file);
        throw std::runtime_error(tmp);
      }
      //arq=fopen(file,"rb");
      //for (long i=0;i<tamanhoDoVetor;i++)
      //   data[i]=fgetc(arq);
      int readedSize = (int)fread( data, sizeof(char), tamanhoDoVetor, arq );
      fclose(arq);
      if(readedSize != tamanhoDoVetor){
        char tmp[1024];
        sprintf(tmp,"[oggFileImpl] Error to load file: \"%s\"", file);
        throw std::runtime_error(tmp);
      }
      return true;
   }
   return false;
}
//---------------------------------------------------------------------------------------
arquivoOGG::~arquivoOGG(){
   if (data!=NULL)
      free(data);
   data=NULL;
}
//---------------------------------------------------------------------------------------
size_t arquivoOGG::Preencher(char *Vetor,const long Tamanho){
   long faltaParaLer=tamanhoDoVetor-position;//quantidade que tem no buffer ainda n� lido
   long quantidadeRestanteParaLer=faltaParaLer-Tamanho;
   /*
        position
        |
   ---------------
   |    |        | -> buffer
   ---------------
        |restante|->falta para ler
        ----------
        |Leit|   | -> quantidadeRestanteParaLer > 0
        ----------
        |  Leit  | -> quantidadeRestanteParaLer = 0  -> faltaParaLer=Tamanho
        ----------
        |  Leit  | Leit | -> quantidadeRestanteParaLer < 0
          
   */
   if (faltaParaLer<=0){
      return 0;
   }else
   if(quantidadeRestanteParaLer >=0 ){
      memcpy(Vetor,&data[position],Tamanho);
      position+=Tamanho;
      return Tamanho;
   }else{//<0
      memcpy(Vetor,&data[position],faltaParaLer);
      position+=faltaParaLer;
      return faltaParaLer;
   }
   return 0;
}
//---------------------------------------------------------------------------------------
long arquivoOGG::getPosition()const {
   return position;
}
//---------------------------------------------------------------------------------------
int arquivoOGG::close(){
   position=tamanhoDoVetor=0;
   if (data!=NULL)
      free(data);
   data=NULL;
   return 0;
}
//---------------------------------------------------------------------------------------
int arquivoOGG::seek(const ogg_int64_t offset,const int whence){
   long newpos=-1;
   switch(whence){
      case SEEK_SET:
         newpos=(long)offset;
         break;
      case SEEK_CUR:
         newpos=position+(long)offset;
         break;
      case SEEK_END:
         newpos=tamanhoDoVetor+(long)offset;
         break;
      default:
         return -1;
   }
   if (newpos<=tamanhoDoVetor && newpos>=0){
      position=newpos;
      return 0;
   }
   return -1;
}
//---------------------------------------------------------------------------------------
/*
implementation of callbacks for OggVorbis file manipulation function
*******************************************************************************
*                                                                             *
*  IMPLEMENTATION OF CALLBACKS OF OGGVORBITS                                  *
*                                                                             *
*******************************************************************************
*/
//---------------------------------------------------------------------------------------
size_t read_func(void *ptr, size_t size, size_t nmemb, void *datasource){
   arquivoOGG *arq=(arquivoOGG *)datasource;
   return (arq->Preencher((char*)ptr,(long)(size*nmemb)));
}
//---------------------------------------------------------------------------------------
int seek_func(void *datasource, ogg_int64_t offset, int whence){
   arquivoOGG *arq=(arquivoOGG *)datasource;
   return arq->seek(offset,whence);
}
//---------------------------------------------------------------------------------------
int close_func(void *datasource){
   return (((arquivoOGG *)datasource)->close());
}
//---------------------------------------------------------------------------------------
long tell_func(void *datasource){
   return (((arquivoOGG *)datasource)->getPosition());
}
//---------------------------------------------------------------------------------------
/*
*******************************************************************************
*                                                                             *
*  IMPLEMENTATION OF OGGBUFFER                                                *
*                                                                             *
*******************************************************************************
*/
//---------------------------------------------------------------------------------------
OggBuffer::OggBuffer(const char *file){
   streamOpen=oggData.LoadFile(file);
   if (streamOpen){
      current_section=0;
      int errNo=ov_open_callbacks(&oggData, &vf, NULL, 0,callbacks);
      if (errNo < 0){
         //error
         //printf("ERRO AO CHAMAR ov_open_callbacks!!!\n");
         streamOpen=false;
         oggData.close();

         switch(errNo){
            case OV_EREAD:throw std::runtime_error("[OggBuffer] OV_EREAD Exception");break;
            case OV_ENOTVORBIS:throw std::runtime_error("[OggBuffer] OV_ENOTVORBIS Exception");break;
            case OV_EVERSION:throw std::runtime_error("[OggBuffer] OV_EVERSION Exception");break;
            case OV_EBADHEADER:throw std::runtime_error("[OggBuffer] OV_EBADHEADER Exception");break;
            case OV_EFAULT:throw std::runtime_error("[OggBuffer] OV_EFAULT Exception");break;
            default:throw std::runtime_error("[OggBuffer] UNKNOWN Exception");break;
         }
      }else{
        vorbisInfo = ov_info(&vf, -1);
        vorbisComment = ov_comment(&vf, -1);
      }
   }
   /* Throw the comments plus a few lines about the bitstream we're
  decoding */
  /*{
    char **ptr=ov_comment(&vf,-1)->user_comments;
    vorbis_info *vi=ov_info(&vf,-1);
    while(*ptr){
      fprintf(stderr,"%s\n",*ptr);
      ++ptr;
    }
    fprintf(stderr,"\nBitstream is %d channel, %ldHz\n",vi->channels,vi->rate);
    fprintf(stderr,"\nDecoded length: %ld samples\n",(long)ov_pcm_total(&vf,-1));
    fprintf(stderr,"Encoded by: %s\n\n",ov_comment(&vf,-1)->vendor);
  }//*/
  samplesCount = (long)ov_pcm_total(&vf,-1);
  //fprintf(stderr,"\nDecoded length: %ld samples\n",(long)ov_pcm_total(&vf,-1));
  //fprintf(stderr,"\nBitstream is %d channel, %ldHz, 16Bits(2bytes) per sample\n",vorbisInfo->channels,vorbisInfo->rate);
}
//------------------------------------------------------------------------------------
OggBuffer::~OggBuffer(){
   if (streamOpen) ov_clear(&vf);
   oggData.close();
}
//------------------------------------------------------------------------------------
long OggBuffer::FillBuffer(char *buffer,const int bufferSize){
   if (!streamOpen) return 0;
   long read,total=0;
   do{
      read=ov_read(
      &vf,//pointer to vorbis file
      &buffer[total],//pointer to the buffer
      bufferSize-total,//size to fill
      0,//0-little endian 1-big endian
      2,//word size 2 bytes = 16 bits
      1,//1-signed values 0 - unsigned values
      &current_section//ponteiro para o bitstream atual
      );
      if (read==0)break;
      total+=read;
   }while(total<bufferSize);
   return total;
}
//------------------------------------------------------------------------------------
/*
AudioBuffer* LoadOggFile(char *file){
   return ((AudioBuffer*)(new OggBuffer(file)));
}//*/
//------------------------------------------------------------------------------------
int OggBuffer::getChannels()const {
  return vorbisInfo->channels;
}
//------------------------------------------------------------------------------------
int OggBuffer::getBitRate()const {
  return vorbisInfo->rate;
}
//------------------------------------------------------------------------------------
void OggBuffer::resetStream(){
  ov_pcm_seek(&vf,0);
}
//------------------------------------------------------------------------------------
int OggBuffer::getBytesPerSample()const {
  return 2*getChannels();
}
//------------------------------------------------------------------------------------
long OggBuffer::getSamplesCount()const {
  return samplesCount;
}
//------------------------------------------------------------------------------------
long OggBuffer::getRawBytePcmSize()const {
  return getBytesPerSample()*getSamplesCount();
}
//------------------------------------------------------------------------------------
void OggBuffer::changeStream(const char*file){
  if (streamOpen) ov_clear(&vf);
  oggData.close();
  streamOpen=oggData.LoadFile(file);
   if (streamOpen){
      current_section=0;
      int errNo=ov_open_callbacks(&oggData, &vf, NULL, 0,callbacks);
      if (errNo < 0){
         //error
         //printf("ERRO AO CHAMAR ov_open_callbacks!!!\n");
         streamOpen=false;
         oggData.close();

         switch(errNo){
            case OV_EREAD:throw std::runtime_error("[OggBuffer] OV_EREAD Exception");break;
            case OV_ENOTVORBIS:throw std::runtime_error("[OggBuffer] OV_ENOTVORBIS Exception");break;
            case OV_EVERSION:throw std::runtime_error("[OggBuffer] OV_EVERSION Exception");break;
            case OV_EBADHEADER:throw std::runtime_error("[OggBuffer] OV_EBADHEADER Exception");break;
            case OV_EFAULT:throw std::runtime_error("[OggBuffer] OV_EFAULT Exception");break;
            default:throw std::runtime_error("[OggBuffer] UNKNOWN Exception");break;
         }
      }else{
        vorbisInfo = ov_info(&vf, -1);
        vorbisComment = ov_comment(&vf, -1);
      }
   }
    samplesCount = (long)ov_pcm_total(&vf,-1);
}
//------------------------------------------------------------------------------------
