/**
  ******************************************************************************
  * @file    usbd_midi.h
  * @author  MCD Application Team
  * @brief   header file for the usbd_midi.c file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2022 Illia Pikin</center></h2>
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/

#ifndef __USB_MIDI_H
#define __USB_MIDI_H

#include  "usbh_core.h"
#include  "usbh_def.h"
#include  "usbh_conf.h"

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_MIDI_Exported_Defines
  * @{
  */ 

#define MIDI_IN_PORTS_NUM 			   0x04U
#define MIDI_OUT_PORTS_NUM			   0x04U

#define USBH_MIDI_MPS_SIZE			   64

#define USB_MIDI_CLASS				   0x01U
#define USB_AUDIO_CLASS                0x01U
#define USB_MIDISTREAMING_SubCLASS     0x03U

#define MIDI_EPIN_ADDR                 0x81
#define MIDI_EPIN_SIZE                 0x40

#define MIDI_EPOUT_ADDR                0x01
#define MIDI_EPOUT_SIZE                0x40



#define USB_MIDI_CLASS_DESC_SHIFT      18
#define USB_MIDI_DESC_SIZE             7
#define USB_MIDI_REPORT_DESC_SIZE      (MIDI_IN_PORTS_NUM * 16 + MIDI_OUT_PORTS_NUM * 16 + 33)
#define USB_MIDI_CONFIG_DESC_SIZE      (USB_MIDI_REPORT_DESC_SIZE + USB_MIDI_CLASS_DESC_SHIFT)

#define MIDI_DESCRIPTOR_TYPE           0x21
  
#define MIDI_REQ_SET_PROTOCOL          0x0B
#define MIDI_REQ_GET_PROTOCOL          0x03

#define MIDI_REQ_SET_IDLE              0x0A
#define MIDI_REQ_GET_IDLE              0x02

#define MIDI_REQ_SET_REPORT            0x09
#define MIDI_REQ_GET_REPORT            0x01

#define MIDI_JACK_1    0x01
#define MIDI_JACK_2    0x02
#define MIDI_JACK_3    0x03
#define MIDI_JACK_4    0x04
#define MIDI_JACK_5    0x05
#define MIDI_JACK_6    0x06
#define MIDI_JACK_7    0x07
#define MIDI_JACK_8    0x08
#define MIDI_JACK_9    0x09
#define MIDI_JACK_10   0x0a
#define MIDI_JACK_11   0x0b
#define MIDI_JACK_12   0x0c
#define MIDI_JACK_13   0x0d
#define MIDI_JACK_14   0x0e
#define MIDI_JACK_15   0x0f
#define MIDI_JACK_16   0x10
#define MIDI_JACK_17   (MIDI_IN_PORTS_NUM * 2 + 0x01)
#define MIDI_JACK_18   (MIDI_IN_PORTS_NUM * 2 + 0x02)
#define MIDI_JACK_19   (MIDI_IN_PORTS_NUM * 2 + 0x03)
#define MIDI_JACK_20   (MIDI_IN_PORTS_NUM * 2 + 0x04)
#define MIDI_JACK_21   (MIDI_IN_PORTS_NUM * 2 + 0x05)
#define MIDI_JACK_22   (MIDI_IN_PORTS_NUM * 2 + 0x06)
#define MIDI_JACK_23   (MIDI_IN_PORTS_NUM * 2 + 0x07)
#define MIDI_JACK_24   (MIDI_IN_PORTS_NUM * 2 + 0x08)
#define MIDI_JACK_25   (MIDI_IN_PORTS_NUM * 2 + 0x09)
#define MIDI_JACK_26   (MIDI_IN_PORTS_NUM * 2 + 0x0a)
#define MIDI_JACK_27   (MIDI_IN_PORTS_NUM * 2 + 0x0b)
#define MIDI_JACK_28   (MIDI_IN_PORTS_NUM * 2 + 0x0c)
#define MIDI_JACK_29   (MIDI_IN_PORTS_NUM * 2 + 0x0d)
#define MIDI_JACK_30   (MIDI_IN_PORTS_NUM * 2 + 0x0e)
#define MIDI_JACK_31   (MIDI_IN_PORTS_NUM * 2 + 0x0f)
#define MIDI_JACK_32   (MIDI_IN_PORTS_NUM * 2 + 0x10)



#define USBH_MIDI_REPORT_SIZE                       16U
#define MIDI_QUE_SIZE									 32U

/**
  * @}
  */ 


/** @defgroup USBD_CORE_Exported_TypesDefinitions
  * @{
  */
typedef enum
{
  MIDI_IDLE = 0,
  MIDI_BUSY,
  MIDI_DATA,
  MIDI_POLL,
  MIDI_ERROR,
  MIDI_INIT
}
USBH_MIDI_StateTypeDef;


typedef struct
{
  uint32_t             Protocol;   
  uint32_t             IdleState;  
  uint32_t             AltSetting;
  USBH_MIDI_StateTypeDef     state;
  uint16_t 				length;
}
USBD_MIDI_HandleTypeDef; 

typedef struct
{
  uint8_t  *buf;
  uint16_t  head;
  uint16_t tail;
  uint16_t size;
  uint8_t  lock;
} MIDI_FIFO_TypeDef;

typedef struct _MIDI_Process
{
	USBH_MIDI_StateTypeDef	state_out;
	USBH_MIDI_StateTypeDef	state_in;
	uint8_t				buff_in[USBH_MIDI_MPS_SIZE];
	uint8_t				buff_out[USBH_MIDI_MPS_SIZE];
	uint8_t				hc_num_in;
	uint8_t 			hc_num_out;
	uint8_t				MIDIBulkOutEp;
	uint8_t				MIDIBulkInEp;
	uint16_t			MIDIBulkInEpSize;
	uint16_t			MIDIBulkOutEpSize;
	uint16_t 			length;
	uint8_t             *pData;
	MIDI_FIFO_TypeDef   fifo;
	USBH_StatusTypeDef(* Init)(USBH_HandleTypeDef *phost);
}
MIDI_HandleTypeDef;


/**
  * @}
  */ 


//we may need more elements in this struct
typedef struct
{
  uint32_t             Protocol;
  uint32_t             IdleState;
  uint32_t             AltSetting;
  USBH_MIDI_StateTypeDef     state;
  USBH_StatusTypeDef(* Init)(USBH_HandleTypeDef *phost);
}
USBH_MIDI_HandleTypeDef;


/** @defgroup USBD_CORE_Exported_Macros
  * @{
  */ 

/**
  * @}
  */ 

/** @defgroup USBD_CORE_Exported_Variables
  * @{
  */ 


extern USBH_ClassTypeDef MIDI_Class;
#define USBH_MIDI_CLASS  &MIDI_Class


USBH_StatusTypeDef USBH_MIDI_HostInit(USBH_HandleTypeDef *phost);
void USBH_MIDI_FifoInit(MIDI_FIFO_TypeDef *f, uint8_t *buf, uint16_t size);
void MIDI_App(USBH_HandleTypeDef *phost);

//extern USBD_HandleTypeDef  USBD_MIDI;
//extern void USBH_MIDI_DataInHandler(uint8_t * usb_rx_buffer, uint8_t usb_rx_buffer_length);

/**
  * @}
  */ 

/** @defgroup USB_CORE_Exported_Functions
  * @{
  */ 

/*
uint8_t USBH_MIDI_SendReport (USBH_HandleTypeDef *pdev, uint8_t *report, uint16_t len);
uint8_t *USBH_MIDI_DeviceQualifierDescriptor (uint16_t *length);
uint8_t USBH_MIDI_GetState(USBH_HandleTypeDef  *pdev);
uint8_t USBH_MIDI_GetDeviceState(USBH_HandleTypeDef  *pdev);
*/
/**
  * @}
  */ 

#endif  // __USB_MIDI_H
/**
  * @}
  */ 

/**
  * @}
  */ 
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
