/**
  ******************************************************************************
  * @file    BSP.h
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
#ifndef __TEST_H
#define __TEST_H


#ifdef __cplusplus
extern "C" {
#endif


#undef EXTERN


#ifdef  __TEST_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
EXTERN void SD_Card_Test(void);
EXTERN void SD_Card_Readbin(void);
EXTERN void  SD_F_mount(void);
EXTERN void SD_Test_Entry(void);
EXTERN void FirmwareUpdate(void);

#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2020 *************************END OF FILE***/

