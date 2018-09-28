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
#ifndef BresenhamIterator_h
#define BresenhamIterator_h

class BresenhamIterator{
  int deltaCol ,
      deltaRow ,
      fraction,
      nextCol ,
      nextRow ,
      endCol ,
      endRow ;
  int stepRow, stepCol;
  int iterateCol;//if not, is to iterate row
  public:
  BresenhamIterator(const int x,const int y,const int xd,const int yd);
  bool next();
  bool next(int *x,int *y);
  void getXY(int *x,int *y);
};

#endif


/*

void bresenhamIt(bool matrix[][resx], int x,int y, int xd, int yd){
  BresenhamIterator it(x,y, xd, yd);
  it.getXY(&x,&y);
  matrix[y][x] = true;
  while(it.next(&x,&y)){
    matrix[y][x] = true;
  }
  
}


void bresenham(void (*putPixel)(const int x,const int y,void* p),
               void* p, 
               int x,int y, 
               int xd, int yd){
  
  int deltaCol = xd-x,
      deltaRow = yd-y,
      fraction,
      nextCol = x,
      nextRow = y,
      endCol = xd,
      endRow = yd;
  
  int stepRow, stepCol;
  
  
  if (deltaRow <  0){ 
    stepRow=-1; 
    deltaRow = -deltaRow*2;
  }else
    stepRow=1;
  if (deltaCol <  0){ 
    stepCol=-1;
    deltaCol = -deltaCol*2; 
  }else 
    stepCol=1;
  
  putPixel(nextCol,nextRow,p);
  
  if (deltaCol >deltaRow){
    fraction = deltaRow*2-deltaCol;
    while (nextCol != endCol){
      if (fraction >=0){
        nextRow =nextRow +stepRow;
        fraction =fraction -deltaCol;
      }
      nextCol=nextCol+stepCol;
      fraction=fraction +deltaRow;
      
      putPixel(nextCol,nextRow,p);

    }
  }else{
    fraction = deltaCol*2-deltaRow;
    while (nextRow !=endRow){
      if (fraction >=0){
        nextCol=nextCol+stepCol;
        fraction=fraction -deltaRow;
      }
      nextRow =nextRow +stepRow;
      fraction=fraction +deltaCol;
      
      putPixel(nextCol,nextRow,p);
      
    }
  }
}




void putPixel(const int x,const int y, void* p){
  bool *m = (bool *)p;
  m[y*resx+ x] = true;
}


int main(){
  cleanM(matrix, resx, resy);
  //bresenhamIt(matrix,            2,3,            1,4);
  bresenham(putPixel,
            (void*)&matrix[0][0],
            2,3,
            1,4);
  printM(matrix, resx, resy);
  return 0;
}
*/
