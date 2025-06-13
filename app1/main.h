#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx_hal.h"
#include "lcd.h"  // Bibliothèque pour l'écran TFT

// Variables globales
extern uint8_t cartouches;
extern uint8_t lastLoading;
extern uint8_t currentLoad;
extern float loadProgress;
extern float loadLastTick;
extern float lastShot[15];

// Fonctions
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_SPI1_Init(void);
void MX_TIM3_Init(void);
void initLCD(void);
void displayUI(void);
void loadBalle(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
