#include "lcd.h"
#include "font16.h" // On va utiliser une police simple, définie ailleurs

extern SPI_HandleTypeDef hspi1; // SPI utilisé (vérifie si c'est bien SPI1 sinon tu changes)

static uint16_t textColor = BLACK;

// Commandes de base ILI9341
#define ILI9341_SWRESET   0x01
#define ILI9341_SLPOUT    0x11
#define ILI9341_DISPON    0x29
#define ILI9341_CASET     0x2A
#define ILI9341_PASET     0x2B
#define ILI9341_RAMWR     0x2C
#define ILI9341_MADCTL    0x36
#define ILI9341_COLMOD    0x3A

// Pin CS, DC, RESET (à ajuster selon ton schéma)
#define LCD_CS_LOW()    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define LCD_CS_HIGH()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define LCD_DC_LOW()    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET)
#define LCD_DC_HIGH()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET)
#define LCD_RST_LOW()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET)
#define LCD_RST_HIGH()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET)

static void LCD_WriteCommand(uint8_t cmd) {
    LCD_DC_LOW();
    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
    LCD_CS_HIGH();
}

static void LCD_WriteData(uint8_t *buff, size_t buff_size) {
    LCD_DC_HIGH();
    LCD_CS_LOW();
    HAL_SPI_Transmit(&hspi1, buff, buff_size, HAL_MAX_DELAY);
    LCD_CS_HIGH();
}

static void LCD_WriteDataByte(uint8_t data) {
    LCD_WriteData(&data, 1);
}

void LCD_Init(void) {
    // Reset hardware
    LCD_RST_LOW();
    HAL_Delay(20);
    LCD_RST_HIGH();
    HAL_Delay(20);

    LCD_WriteCommand(ILI9341_SWRESET); // Reset software
    HAL_Delay(150);

    LCD_WriteCommand(ILI9341_SLPOUT);  // Exit sleep
    HAL_Delay(500);

    LCD_WriteCommand(ILI9341_COLMOD);  // Pixel Format Set
    LCD_WriteDataByte(0x55); // 16 bits par pixel
    HAL_Delay(10);

    LCD_WriteCommand(ILI9341_MADCTL);  // Memory Access Control
    uint8_t data = 0x48; // Orientation paysage
    LCD_WriteData(&data, 1);

    LCD_WriteCommand(ILI9341_DISPON);  // Display ON
    HAL_Delay(100);
}

void LCD_SetAddressWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
    uint8_t data[4];

    LCD_WriteCommand(ILI9341_CASET);
    data[0] = (x0 >> 8) & 0xFF;
    data[1] = x0 & 0xFF;
    data[2] = (x1 >> 8) & 0xFF;
    data[3] = x1 & 0xFF;
    LCD_WriteData(data, 4);

    LCD_WriteCommand(ILI9341_PASET);
    data[0] = (y0 >> 8) & 0xFF;
    data[1] = y0 & 0xFF;
    data[2] = (y1 >> 8) & 0xFF;
    data[3] = y1 & 0xFF;
    LCD_WriteData(data, 4);

    LCD_WriteCommand(ILI9341_RAMWR);
}

void LCD_Clear(uint16_t color) {
    LCD_FillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, color);
}

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
    LCD_SetAddressWindow(x, y, x+1, y+1);
    uint8_t data[2] = {color >> 8, color & 0xFF};
    LCD_WriteData(data, 2);
}

void LCD_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
    LCD_SetAddressWindow(x, y, x+w-1, y+h-1);
    uint8_t data[2] = {color >> 8, color & 0xFF};

    LCD_DC_HIGH();
    LCD_CS_LOW();
    for(uint32_t i=0; i < w*h; i++) {
        HAL_SPI_Transmit(&hspi1, data, 2, HAL_MAX_DELAY);
    }
    LCD_CS_HIGH();
}

void LCD_DisplayStringAt(uint16_t x, uint16_t y, uint8_t *text, uint8_t mode) {
    while (*text) {
        if (mode == CENTER_MODE) {
            // En vrai, il faudrait centrer, mais pour simplifier on affiche normal
            LCD_DrawChar(x, y, *text);
            x += 8;
        } else {
            LCD_DrawChar(x, y, *text);
            x += 8;
        }
        text++;
    }
}

void LCD_SetTextColor(uint16_t color) {
    textColor = color;
}

// Affiche un caractère
void LCD_DrawChar(uint16_t x, uint16_t y, uint8_t c) {
    extern const uint8_t Font16[];
    for (uint8_t i = 0; i < 16; i++) {
        uint8_t line = Font16[(c-32)*16 + i];
        for (uint8_t j = 0; j < 8; j++) {
            if (line & 0x80) {
                LCD_DrawPixel(x+j, y+i, textColor);
            }
            line <<= 1;
        }
    }
}
