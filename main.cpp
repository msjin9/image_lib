#include <iostream>
#include "ImageProcessing.h"

using namespace std;

int main()
{
    int imgWidth;
    int imgHeight;
    int imgBitDepth;
    //hold img header
    unsigned char imgHeader[BMP_HEADER_SIZE];
    unsigned char imgColorTable[BMP_COLOR_TABLE_SIZE];
    unsigned char imgInBuffer[_512by512_IMG_SIZE];
    unsigned char imgOutBuffer[_512by512_IMG_SIZE];

    //take img name as an argument, inImgName
    const char imgName[] = "images/girlface.bmp";
    const char newImgName[] = "images/girlface_copy.bmp";

    ImageProcessing *myImage = new ImageProcessing(imgName,
                                                   newImgName,
                                                   &imgHeight,
                                                   &imgWidth,
                                                   &imgBitDepth,
                                                   &imgHeader[0],
                                                   &imgColorTable[0],
                                                   &imgInBuffer[0],
                                                   &imgOutBuffer[0]
                                                   );

    //read girlface.bmp
    myImage ->readImage();
    myImage ->copyImgData(imgInBuffer, imgOutBuffer, _512by512_IMG_SIZE);
    myImage->writeImage();
    cout<<"Success"<<endl;
    cout<<"Image Height: "<<imgHeight<<endl;
    cout<<"Image width: "<<imgWidth<<endl;
    return 0;
}
