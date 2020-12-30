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
  * @brief  SD卡挂载函数
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
  * @brief  SD卡挂载函数
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
  * @brief  MCU读取SD卡的bin文件测试函数
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
  * @brief  mcu写数据进入SD卡测试函数
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
  * @brief  mcu写数据进入SD卡测试函数
  * @param  None
  * @retval None
  */
void FirmwareUpdate(void)
{

    FIL  FileBin;
    u8   i = 0;
    u8   timer;
    u8   Res;
    u16  Br;                                /* 文件成功读写数量 */
    u16  ReadLen;
    u32  Addrx;
    u32  ReceiveData = 0;       // 计算接收到的总数据数
    u32  FileSize     = 0;      //  文件Size

    SD_F_mount();
    /* 查找是否存在要升级的BIN文件 */
    Res = f_open(&FileBin, "APP.bin", FA_OPEN_EXISTING | FA_READ);

    if (Res == FR_OK)
    {
        printf("》打开文件成功。\r\n");
    }
    else
    {
        printf("》打开文件失败。\r\n");
        return;
    }
    FileSize = f_size(&FileBin);
    printf("读取的文件大小为:%dByte\r\n", FileSize);
    printf("开始更新固件...\r\n");
    Addrx = FLASH_APP1_ADDR;
    Res = f_read(&FileBin, ReceiveDateBuffer, StmPageSize, (UINT*)&Br);
    printf("第%d次读取的Br大小为: %d Byte\r\n", i, ReadLen);
    UART1_Send_Array(ReceiveDateBuffer,1024);

}