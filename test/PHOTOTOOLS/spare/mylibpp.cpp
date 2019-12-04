bool BW_BITMAP::ReadBMP(char *fileName)
    {
        FILE *fileR ,fileW ;
        fileR = fopen(fileName , "rb") ;
        if (fileR != NULL)
        {
            //BW_BITMAP* bitMap = new BW_BITMAP ;
             
            fread(&bitMapFileHeader , 1 , sizeof(BITMAPFILEHEADER) , fileR) ;
            if (0x4d42 != bitMapFileHeader.fileType)
            {
                fclose(fileR) ;
                return NULL ;
            }
            fread(&bitMapInfoHead, 1, sizeof(BITMAPINFOHEAD) , fileR) ;

            rgbquad = new    RGBQUAD[bitMapInfoHead.clrUsed] ;
            for (int icount = 0 ; icount < bitMapInfoHead.clrUsed ; ++icount)
            {
                fread((char *)&(rgbquad[icount].rgbBlue),1,sizeof(BYTE),fileR);  
                fread((char *)&(rgbquad[icount].rgbGreen),1,sizeof(BYTE),fileR);  
                fread((char *)&(rgbquad[icount].rgbRed),1,sizeof(BYTE),fileR);  
                //fread((char *)&(bitMap->rgbquad[icount].rgbReserved),1,sizeof(BYTE),fileR);  
            }

            int width =  bitMapInfoHead.width ;

            int height = bitMapInfoHead.height ;  
            pixelData =   new PIXEL[width * height * sizeof(PIXEL)];  
            //初始化原始图片的像素数组  

            //fseek(fpi,54,SEEK_SET);  
            //读出图片的像素数据  
            fread(pixelData,sizeof(PIXEL) * width,height,fileR);    
            fclose(fileR);  
            return true ;
        }  
        else  
        {  
            //cout<<"file open error!"<<endl;  
            return false ;
        }  
    }
}