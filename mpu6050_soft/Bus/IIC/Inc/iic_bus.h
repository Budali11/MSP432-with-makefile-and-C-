// Copyright 2022 Budali11
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#if !defined IIC_BUS_H
#define IIC_BUS_H

#if defined PROCESS_FACE

#include "msp.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

#define IIC_IO_BASE                 P6
#define IIC_SCL_PORT                GPIO_PORT_P6
#define IIC_SDA_PORT                GPIO_PORT_P6
#define IIC_SCL_PIN                 GPIO_PIN5
#define IIC_SDA_PIN                 GPIO_PIN4

#define IIC_GET_SDA_PORT(id) \
    ((id >> 8) & 0xff)
#define IIC_GET_SDA_PIN(id) \
    ((id >> 0) & 0xff)
#define IIC_GET_SCL_PORT(id) \
    ((id >> 24) & 0xff)
#define IIC_GET_SCL_PIN(id) \
    ((id >> 16) & 0xff)

#define SDA_IN()  \
    IIC_IO_BASE->DIR &= ~IIC_SDA_PIN; \
    IIC_IO_BASE->OUT |= IIC_SDA_PIN
#define SDA_OUT() \
    IIC_IO_BASE->DIR |= IIC_SDA_PIN
#define SDA_SET(x) \
    (x)?(IIC_IO_BASE->OUT |= IIC_SDA_PIN):(IIC_IO_BASE->OUT &= ~IIC_SDA_PIN)
#define SCL_SET(x) \
    (x)?(IIC_IO_BASE->OUT |= IIC_SCL_PIN):(IIC_IO_BASE->OUT &= ~IIC_SCL_PIN)
#define READ_SDA() \
    ((IIC_IO_BASE->IN & IIC_SDA_PIN)?1:0)
#define DELAY(x) \
    for(uint32_t i = 0; i < x; i++)

/* a enum type for iic device, indicates if this device is be used of not */
enum LOCK_T {
    LOCKED = 0,
    UNLOCK = 1
};


typedef struct iic_adapter
{
    enum LOCK_T lock;
    uint32_t driver_id;
    int (*init)(struct iic_adapter *padapter);
    int (*start)(void);
    int (*stop)(void);
    int (*sendByte)(uint8_t byte);
    int (*receiveByte)(uint8_t ack);
}iic_adapter_t;

int IIC_Init(iic_adapter_t *padapter);
int IIC_Adapter_Init(iic_adapter_t *padapter);
int IIC_Adapter_Start(void);
int IIC_Adapter_Stop(void);
int IIC_Adapter_SendByte(uint8_t byte);
int IIC_Adapter_ReceiveByte(uint8_t ack);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //PROCESS_FACE

#endif //IIC_BUS_H
