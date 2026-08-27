#ifndef KEY_H
#define KEY_H
#include "main.h"
typedef struct
{
  GPIO_PinState previous ;
  GPIO_PinState current  ;
  GPIO_TypeDef* GPIO_Port;
  uint16_t GPIO_Pin;
  void(*ClickedCallback)(void);

} KeyHandle_TypeDef;

void Key_Init(KeyHandle_TypeDef* Handle);
void Key_Scan(KeyHandle_TypeDef* Handle);

#endif