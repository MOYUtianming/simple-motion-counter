#pragma pack(1)
    typedef unsigned char BYTE ;
    typedef unsigned short  WORD ;
    typedef unsigned int    DWORD ;
    typedef long  LONG ;

    typedef struct BW_BITMAPFILEHEADER
    {
        WORD  fileType ;
        DWORD fileSize ;
        WORD  fileReserved1 ;
        WORD  fileReserved2 ;
        DWORD offSet ;
    } BITMAPFILEHEADER ;
    typedef struct BW_BITMAPFINFOHEADER
    {
        DWORD headSize ;
        LONG  width ;
        LONG  height ;
        WORD  plant ;
        WORD  bitCount ;
        DWORD compression ;
        DWORD sizeImage ;
        LONG  XPelPerMeter ;
        LONG  YPelPerMeter ;
        DWORD clrUsed ;
        DWORD clrImportant ;
    }BITMAPINFOHEAD;

    typedef struct BW_RGBQUAD
    {
        BYTE rgbBlue ;
        BYTE rgbGreen ;
        BYTE rgbRed ;
        BYTE rgbReserved ;
    }RGBQUAD;

    typedef struct BW_PIXEL 
    {
        BYTE blue ;
        BYTE green ;
        BYTE red ;
    } PIXEL ;

    class BW_BITMAP
    { 
    public:
        bool ReadBMP(char*) ;
        BITMAPFILEHEADER bitMapFileHeader ;
        BITMAPINFOHEAD bitMapInfoHead ;
        RGBQUAD *rgbquad ;
        PIXEL* pixelData ;
    };