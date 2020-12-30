/**
  ******************************************************************************
  * @file    TEST.c
  * @author
  * @version V1.00
  * @date    22-Sep-2020
  * @brief   ......
  ******************************************************************************
  * @attention
  *
  * ......
  *
  ******************************************************************************
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#define __TEST_C__

/* Includes ------------------------------------------------------------------*/
#include "spi.h"
#include "sdcard.h"
#include "test.h"
#include "sdcard.h"
#include "ff.h"
#include "diskio.h"     /* FatFs lower layer API */
#include <string.h>
#include <stdio.h>
#include "test.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define  FLASH_APP1_ADDR		0x08040000 
#define  StmPageSize            1024

/* Private macro -------------------------------------------------------------*/
u8    ReceiveDateBuffer[StmPageSize] = {0};
char wrstr[2048];
u8 datalen = 0;

/* Private variables ---------------------------------------------------------*/
BYTE work[FF_MAX_SS];   /* Work area (larger is better for processing time) */
FRESULT fr ;            /* FatFs return code */
FATFS sdfs;             /* Filesystem object structure (FATFS) */
FIL fle;                /* File object structure (FIL) */



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/


/**
  * @brief  SD�����غ���
  * @param  None
  * @retval None
  */
void SD_Test_Entry(void)
{
    SD_Card_Init();
    printf("STM32_SD CARD Init Successful\r\n");
    SD_F_mount();
    printf("STM32_SD CARD f_mount Successful\r\n");
    SD_Card_Readbin();
    printf("STM32_SD CARD READ_BIN Successful\r\n");
}


/**
  * @brief  SD�����غ���
  * @param  None
  * @retval None
  */
void  SD_F_mount(void)
{
    do
    {
        fr = f_mount(&sdfs, "", 1);
        delay_ms(50);
    }

    while (fr != FR_OK); /* Mount the default drive */
}

/**
  * @brief  MCU��ȡSD����bin�ļ����Ժ���
  * @param  None
  * @retval None
  */
void SD_Card_Readbin(void)
{
    UINT wr;
    uint16_t length;

    fr = f_open(&fle, "APP.bin", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

    fr = f_lseek(&fle, fle.obj.objsize);

    sprintf(wrstr, "\r\n");

    fr = f_write(&fle, wrstr, strlen(wrstr), &wr);

    sprintf(wrstr, "STM32-cp It used to test FatFs Applications\r\n");

    length = strlen(wrstr);

    fr = f_write(&fle, wrstr, length, &wr);

    fr = f_sync(&fle);

    fr = f_close(&fle);

    fr = f_mount(NULL, "0:", 1); /* Unmount the drive */
}


/**
  * @brief  mcuд���ݽ���SD�����Ժ���
  * @param  None
  * @retval None
  */
void SD_Card_Test(void)
{
    UINT wr;
    uint16_t length;

    fr = f_open(&fle, "message.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

    fr = f_lseek(&fle, fle.obj.objsize);

    sprintf(wrstr, "\r\n");

    fr = f_write(&fle, wrstr, strlen(wrstr), &wr);

    sprintf(wrstr, "STM32 cp1 used to test FatFs Applications\r\n");

    length = strlen(wrstr);

    fr = f_write(&fle, wrstr, length, &wr);

    fr = f_sync(&fle);

    fr = f_close(&fle);

    fr = f_mount(NULL, "0:", 1); /* Unmount the drive */
}

/**
  * @brief  mcuд���ݽ���SD�����Ժ���
  * @param  None
  * @retval None
  */
void FirmwareUpdate(void)
{

    FIL  FileBin;
    u8   i = 0;
    u8   timer;
    u8   Res;
    u16  Br;                                /* �ļ��ɹ���д���� */
    u16  ReadLen;
    u32  Addrx;
    u32  ReceiveData = 0;       // ������յ�����������
    u32  FileSize     = 0;      //  �ļ�Size

    SD_F_mount();
    /* �����Ƿ����Ҫ������BIN�ļ� */
    Res = f_open(&FileBin, "APP.bin", FA_OPEN_EXISTING | FA_READ);

    if (Res == FR_OK)
    {
        printf("�����ļ��ɹ���\r\n");
    }
    else
    {
        printf("�����ļ�ʧ�ܡ�\r\n");
        return;
    }
    FileSize = f_size(&FileBin);
    printf("��ȡ���ļ���СΪ:%dByte\r\n", FileSize);
    printf("��ʼ���¹̼�...\r\n");
    Addrx = FLASH_APP1_ADDR;
    Res = f_read(&FileBin, ReceiveDateBuffer, StmPageSize, (UINT*)&Br);
    printf("��%d�ζ�ȡ��Br��СΪ: %d Byte\r\n", i, ReadLen);
    UART1_Send_Array(ReceiveDateBuffer,1024);

}