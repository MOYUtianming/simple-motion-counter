#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "usmart.h"  
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
#include "piclib.h"	
#include "string.h"	
#include "math.h"	
#include "dcmi.h"	
#include "ov2640.h"	
#include "beep.h"	
#include "timer.h"

 u8 ov2640_mode=0;						//mod:0,RGB565 mod;1,JPEG mod

#define jpeg_dma_bufsize	5*1024		//buffer size(*4 byte)
volatile u32 jpeg_data_len=0; 			//buf data length(*4 byte)
volatile u8 jpeg_data_ok=0;				//photo process flag; 
										//0,collection isn't finith;
										//1,collected but not processed;
										//2,complete all;
										
u32 *jpeg_buf0;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_buf1;							//JPEG���ݻ���buf,ͨ��malloc�����ڴ�
u32 *jpeg_data_buf;						//JPEG���ݻ���buf,ͨ��malloc�����ڴ�

//process data;
//one photo has been collected,use this function to transfer buffer and start next collection.
void jpeg_data_process(void)
{
	u16 i;
	u16 rlen;//ʣ�����ݳ���
	u32 *pbuf;
	if(ov2640_mode)//ֻ����JPEG��ʽ��,����Ҫ������.
	{
		if(jpeg_data_ok==0)	//jpeg���ݻ�δ�ɼ���?
		{
			DMA_Cmd(DMA2_Stream1,DISABLE);		//ֹͣ��ǰ����
			while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);	//�ȴ�DMA2_Stream1������ 
			rlen=jpeg_dma_bufsize-DMA_GetCurrDataCounter(DMA2_Stream1);//�õ�ʣ�����ݳ���	
			pbuf=jpeg_data_buf+jpeg_data_len;//ƫ�Ƶ���Ч����ĩβ,��������
			if(DMA2_Stream1->CR&(1<<19))for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf1[i];//��ȡbuf1�����ʣ������
			else for(i=0;i<rlen;i++)pbuf[i]=jpeg_buf0[i];//��ȡbuf0�����ʣ������ 
			jpeg_data_len+=rlen;			//����ʣ�೤��
			jpeg_data_ok=1; 				//���JPEG���ݲɼ��갴��,�ȴ�������������
		}
		if(jpeg_data_ok==2)	//��һ�ε�jpeg�����Ѿ���������
		{ DMA_SetCurrDataCounter(DMA2_Stream1,jpeg_dma_bufsize);//���䳤��Ϊjpeg_buf_size*4�ֽ�
			DMA_Cmd(DMA2_Stream1,ENABLE); //���´���
			jpeg_data_ok=0;					//�������δ�ɼ�
			jpeg_data_len=0;				//�������¿�ʼ
		}
	}
}



//data callback & splice;
void jpeg_dcmi_rx_callback(void)
{ 
	u16 i;
	u32 *pbuf;
	pbuf=jpeg_data_buf+jpeg_data_len;//offset to the end of file;
	if(DMA2_Stream1->CR&(1<<19))//buf0 has been full,use buf1;
	{ 
		for(i=0;i<jpeg_dma_bufsize;i++)pbuf[i]=jpeg_buf0[i];//read buf0;
		jpeg_data_len+=jpeg_dma_bufsize;//offset;
	}else //buf1 has been full,use buf0;
	{
		for(i=0;i<jpeg_dma_bufsize;i++)pbuf[i]=jpeg_buf1[i];//read buf1;
		jpeg_data_len+=jpeg_dma_bufsize;//offset;
	} 	
}


//OV2640 mod��GPIOC8/9/11 -> DCMI interface;��
void sw_ov2640_mode(void)
{
	OV2640_PWDN=0;//OV2640 Power Up
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_DCMI);  //PC8,AF13  DCMI_D2
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_DCMI);  //PC9,AF13  DCMI_D3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_DCMI); //PC11,AF13 DCMI_D4  
 
} 
//SD card mod��GPIOC8/9/11 -> SDIO interface;��
void sw_sdcard_mode(void)
{
	OV2640_PWDN=1;//OV2640 Power Down  
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_SDIO);  //PC8,AF12
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_SDIO);//PC9,AF12 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_SDIO); 
}
	
//file serial number "++"��avoid replacement;��
//mode:0,.bmp;1,.jpg.
//bmp  file name"0:PHOTO/PIC13141.bmp";
//jpg file name:"0:PHOTO/PIC13141.jpg";
void camera_new_pathname(u8 *pname,u8 mode)
{	 
	u8 res;					 
	u16 index=0;
	while(index<0XFFFF)
	{
		if(mode==0)sprintf((char*)pname,"0:PHOTO/PIC%05d.bmp",index);
		else sprintf((char*)pname,"0:PHOTO/PIC%05d.jpg",index);
		res=f_open(ftemp,(const TCHAR*)pname,FA_READ);//try to open the file;
		if(res==FR_NO_FILE)break;		//without a file named as it which is what we need;
		index++;
	}
} 
//OV2640_jpg_photo;
//return:0,success;
//return others , error;
u8 ov2640_jpg_photo(u8 *pname)
{
	FIL* f_jpg;
	u8 res=0;
	u32 bwr;
	u16 i;
	u8* pbuf;
	f_jpg=(FIL *)mymalloc(SRAMIN,sizeof(FIL));	//����FIL�ֽڵ��ڴ����� 
	if(f_jpg==NULL)return 0XFF;					//�ڴ�����ʧ��.
	ov2640_mode=1;
	sw_ov2640_mode();		//�л�ΪOV2640ģʽ
	dcmi_rx_callback=jpeg_dcmi_rx_callback;//�ص�����
	DCMI_DMA_Init((u32)jpeg_buf0,(u32)jpeg_buf1,jpeg_dma_bufsize,DMA_MemoryDataSize_Word,DMA_MemoryInc_Enable);//DCMI DMA����(˫����ģʽ)
	OV2640_JPEG_Mode();		//�л�ΪJPEGģʽ 
 	OV2640_ImageWin_Set(0,0,1600,1200);			 
	OV2640_OutSize_Set(1600,1200);//���ճߴ�Ϊ1600*1200
	DCMI_Start(); 			//�������� 
	while(jpeg_data_ok!=1);	//�ȴ���һ֡ͼƬ�ɼ���
	jpeg_data_ok=2;			//���Ա�֡ͼƬ,������һ֡�ɼ�
	while(jpeg_data_ok!=1);	//�ȴ��ڶ�֡ͼƬ�ɼ���
	jpeg_data_ok=2;			//���Ա�֡ͼƬ,������һ֡�ɼ�
	while(jpeg_data_ok!=1);	//�ȴ�����֡ͼƬ�ɼ���,����֡,�ű��浽SD��ȥ.
	DCMI_Stop(); 			//ֹͣDMA����
	ov2640_mode=0;
	sw_sdcard_mode();		//�л�ΪSD��ģʽ
	res=f_open(f_jpg,(const TCHAR*)pname,FA_WRITE|FA_CREATE_NEW);//ģʽ0,���߳��Դ�ʧ��,�򴴽����ļ�	 
	if(res==0)
	{
		printf("jpeg data size:%d\r\n",jpeg_data_len*4);//���ڴ�ӡJPEG�ļ���С
		pbuf=(u8*)jpeg_data_buf;
		for(i=0;i<jpeg_data_len*4;i++)//����0XFF,0XD8
		{
			if((pbuf[i]==0XFF)&&(pbuf[i+1]==0XD8))break;
		}
		if(i==jpeg_data_len*4)res=0XFD;//û�ҵ�0XFF,0XD8
		else//�ҵ���
		{
			pbuf+=i;//ƫ�Ƶ�0XFF,0XD8��
			res=f_write(f_jpg,pbuf,jpeg_data_len*4-i,&bwr);
			if(bwr!=(jpeg_data_len*4-i))res=0XFE; 
		}
	}
	jpeg_data_len=0;
	f_close(f_jpg); 
	sw_ov2640_mode();		//�л�ΪOV2640ģʽ
	OV2640_RGB565_Mode();	//RGB565ģʽ 
	DCMI_DMA_Init((u32)&LCD->LCD_RAM,0,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI DMA����   
	myfree(SRAMIN,f_jpg); 
	return res;
}  
  

int main(void)
{        
	u8 res;							 
	u8 *pname;				//file name; 
	u8 key;					//key value;
	u8 i;						 
	u8 sd_ok=1;				//0,sd card normal;1,SD card unnormal. 
 	u8 scale=1;				//full scale;
	u8 msgbuf[15];			//message buffer;
//Init;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//NVIC set as level 2;
	delay_init(168);  //delay function init;
	uart_init(115200);		//UART baud rate : 115200 ;
	LED_Init();					//LED init;
	usmart_dev.init(84);		//USMART init;
	TIM3_Int_Init(10000-1,8400-1);//10Khz timer,1 interrupt p s;
 	LCD_Init();					//LCD init;  
	FSMC_SRAM_Init();			//external SRAM init;
 	BEEP_Init();				//beep init;
 	KEY_Init();					//key init;   
	W25QXX_Init();				//W25Q128 init;
	my_mem_init(SRAMIN);		//sram init; 
	my_mem_init(SRAMEX);		//sram init;  
	my_mem_init(SRAMCCM);		//CCM init;
	exfuns_init();				//fatfs init;  
//mount SD card;
  	f_mount(fs[0],"0:",1); 		//mount memory;
//LCD set;
	POINT_COLOR=RED;      
	while(font_init()) 		//check the word set;
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//clear all;
		delay_ms(200);				  
	}
//general display;
 	Show_Str(30,50,200,16,"Explorer STM32F4������",16,0);	 			    	 
	Show_Str(30,70,200,16,"�����ʵ��",16,0);				    	 
	Show_Str(30,90,200,16,"KEY0:����(bmp��ʽ)",16,0);			    	 
	Show_Str(30,110,200,16,"KEY1:����(jpg��ʽ)",16,0);					    	 
	Show_Str(30,130,200,16,"WK_UP:FullSize/Scale",16,0);				    	 
	Show_Str(30,150,200,16,"2019��10��30��",16,0);
//SD card file block;
	res=f_mkdir("0:/PHOTO");		//mkdir:photo;
	if(res!=FR_EXIST&&res!=FR_OK) 	//error;
	{		    
		Show_Str(30,150,240,16,"SD������!",16,0);
		delay_ms(200);				  
		Show_Str(30,170,240,16,"���չ��ܽ�������!",16,0);
		sd_ok=0;  	
	} 	

	jpeg_buf0=mymalloc(SRAMIN,jpeg_dma_bufsize*4);	//dma data buffer;
	jpeg_buf1=mymalloc(SRAMIN,jpeg_dma_bufsize*4);	//dma datd buffer;
	jpeg_data_buf=mymalloc(SRAMEX,300*1024);		//data space (less than 300KB)
 	pname=mymalloc(SRAMIN,30);//file name space;
 	while(pname==NULL||!jpeg_buf0||!jpeg_buf1||!jpeg_data_buf)	//error;
 	{	    
		Show_Str(30,190,240,16,"�ڴ����ʧ��!",16,0);
		delay_ms(200);				  
		LCD_Fill(30,190,240,146,WHITE);//�����ʾ	     
		delay_ms(200);				  
	}   
//Camera set block;
	while(OV2640_Init())//init OV2640
	{
		Show_Str(30,190,240,16,"OV2640 ����!",16,0);
		delay_ms(200);
	    LCD_Fill(30,190,239,206,WHITE);
		delay_ms(200);
	}	
 	Show_Str(30,190,200,16,"OV2640 ����",16,0);
	delay_ms(2000);
	OV2640_RGB565_Mode();	//RGB565 mod;
	My_DCMI_Init();			//DCMI set;
	DCMI_DMA_Init((u32)&LCD->LCD_RAM,0,1,DMA_MemoryDataSize_HalfWord,DMA_MemoryInc_Disable);//DCMI_DMA set;  
 	OV2640_OutSize_Set(lcddev.width,lcddev.height); 
	
	DCMI_Start(); 			//start transfer.
//MAIN function block;
 	while(1)
	{	
		key=KEY_Scan(0);//can't support continue press;
		if(key)
		{
			DCMI_Stop(); //stop transfer;

			if(key==WKUP_PRES) 
			{
				scale=!scale;  
				if(scale==0)
				{
					OV2640_ImageWin_Set((1600-lcddev.width)/2,(1200-lcddev.height)/2,lcddev.width,lcddev.height);//1:1 scale
					OV2640_OutSize_Set(lcddev.width,lcddev.height); 
					sprintf((char*)msgbuf,"Full Size 1:1");
				}else 
				{
					OV2640_ImageWin_Set(0,0,1600,1200);				//full scale zoom
					OV2640_OutSize_Set(lcddev.width,lcddev.height); 
					sprintf((char*)msgbuf,"Scale");
				}
				LCD_ShowString(30,50,210,16,16,msgbuf);//show tips;
				delay_ms(800); 	
			}else if(sd_ok)//SD card need to be right;
			{    
				sw_sdcard_mode();	//switch to be sdcard mod;
				if(key==KEY0_PRES)	//BMP mod;
				{
					camera_new_pathname(pname,0);//create a file name;	
					res=bmp_encode(pname,0,0,lcddev.width,lcddev.height,0);
				}
				else if(key==KEY1_PRES)//JPG mod;
				{
					camera_new_pathname(pname,1);
					res=ov2640_jpg_photo(pname);
					if(scale==0)
					{
						OV2640_ImageWin_Set((1600-lcddev.width)/2,(1200-lcddev.height)/2,lcddev.width,lcddev.height);
						OV2640_OutSize_Set(lcddev.width,lcddev.height); 
					}else 
					{
						OV2640_ImageWin_Set(0,0,1600,1200);	 
					}
					OV2640_OutSize_Set(lcddev.width,lcddev.height); 					
				}
				sw_ov2640_mode();	//become OV2640 mod
				if(res)// if error
				{
					Show_Str(30,130,240,16,"д���ļ�����!",16,0);		 
				}else 
				{
					Show_Str(30,130,240,16,"���ճɹ�!",16,0);
					Show_Str(30,150,240,16,"����Ϊ:",16,0);
					Show_Str(30+42,150,240,16,pname,16,0);		    
					BEEP=1;	//beep bleep;
					delay_ms(100);
					BEEP=0;
				}   			
			}else //if SD card error
			{					    
				Show_Str(30,130,240,16,"SD������!",16,0);
				Show_Str(30,150,240,16,"���չ��ܲ�����!",16,0);			    
			}   	
			if(key!=WKUP_PRES)
			delay_ms(1800);//not a mod for size switching;

			DCMI_Start(); 	//start transfer;
		} 
		delay_ms(10);
		i++;//twenty photos;
		if(i==20)//DS0 flashing;.
		{
			i=0;
			LED0=!LED0;
 		}
	}
}


/*
bmpdecode function which exists in bmp.h can be used to translate bmp photos;
SD_ReadDisk function which exists in sdio_sdcard.h can be used to read SD card;

now,the road between CPU and SD card has been created;
and the road between CPU and camera has been created too;
*/





