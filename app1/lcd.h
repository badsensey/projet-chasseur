#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx_hal.h"

// Couleurs en 16 bits RGB565
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define GREEN       0x07E0
#define RED         0xF800
#define CYAN        0x07FF
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define ORANGE      0xFD20

// Modes d'affichage
#define CENTER_MODE 1
#define LEFT_MODE   0

// Taille de l'écran
#define LCD_WIDTH   240
#define LCD_HEIGHT  320

// Déclaration des fonctions
void LCD_Init(void);
void LCD_Clear(uint16_t color);
void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_DisplayStringAt(uint16_t x, uint16_t y, uint8_t *text, uint8_t mode);
void LCD_FillRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);
void LCD_SetTextColor(uint16_t color);
void LCD_SetFont(void* font);

#ifdef __cplusplus
}
#endif

#endif /* __LCD_H */
