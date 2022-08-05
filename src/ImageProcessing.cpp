#include "ImageProcessing.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

//class constructor
ImageProcessing::ImageProcessing(
                                 const char *_inImgName,
                                 const char *_outImgName,
                                 int *_height,
                                 int *_width,
                                 int *_bitDepth,
                                 unsigned char *_header,
                                 unsigned char *_colorTable,
                                 unsigned char *_inBuf,
                                 unsigned char *_outBuf
                                 )
{
   inImgName = _inImgName;
   outImgName = _outImgName;
   height = _height;
   width = _width;
   bitDepth = _bitDepth;
   header = _header;
   colorTable = _colorTable;
   inBuf = _inBuf;
   outBuf = _outBuf;
}

//read img
void ImageProcessing::readImage()
{
    int i;
    FILE *streamIn;
    streamIn = fopen(inImgName, "rb");
    if(streamIn == (FILE *)0)
    {
        cout<<"Cannot Open"<<endl;
        exit(0);
    }
    for(i=0; i<BMP_HEADER_SIZE; i++)
    {
        header[i] = getc(streamIn);
    }
    *width = *(int *)&header[18];   //read the width from the image header
    *height = *(int *)&header[22];  //read height
    *bitDepth = *(int *)&header[28];

    if(*bitDepth <= 8)
    {
        fread(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, streamIn);
    }
    fread(inBuf, sizeof(unsigned char), _512by512_IMG_SIZE, streamIn);

    fclose(streamIn);
}

void ImageProcessing::writeImage()
{
    FILE *fo = fopen(outImgName, "wb");
    fwrite(header, sizeof(unsigned char), BMP_HEADER_SIZE, fo);
    if(*bitDepth <= 8)
    {
        fwrite(colorTable, sizeof(unsigned char), BMP_COLOR_TABLE_SIZE, fo);
    }

    fwrite(outBuf, sizeof(unsigned char), _512by512_IMG_SIZE, fo);
    fclose(fo);
}

//copy img data function
void ImageProcessing::copyImgData(unsigned char *_srcBuf, unsigned char *_destBuf, int bufSize)
{
    for(int i=0; i<bufSize; i++)
    {
        _destBuf[i] = _srcBuf[i];
    }
}

ImageProcessing::~ImageProcessing()
{
    //dtor
}
