/*
 * ui_display.c
 *
 *  Created on: avril 13, 2025
 *      Author: ohinpari & diallosou
 */

#include "ui_display.h"
#include "lcd.h"

// Affichage du titre et des informations sur l'écran
void displayUI() {
    LCD_Clear(WHITE);  // Efface l'écran

    // Affichage du titre
    LCD_SetFont(&Font16);  // Taille de la police
    LCD_SetTextColor(BLACK);
    LCD_DisplayStringAt(10, 10, (uint8_t*)"Hunter", LEFT_MODE);

    // Affichage du nombre de balles restantes
    char buffer[10];
    sprintf(buffer, "Balles restantes: %d", currentLoad);
    LCD_DisplayStringAt(10, 40, (uint8_t*)buffer, LEFT_MODE);

    // Affichage du nombre de cartouches restantes
    sprintf(buffer, "Cartouches: %d", cartouches);
    LCD_DisplayStringAt(10, 70, (uint8_t*)buffer, LEFT_MODE);

    // Affichage de la barre de progression de la recharge
    LCD_FillRect(10, 100, 200, 20, WHITE);  // Dessine un rectangle pour la barre
    LCD_FillRect(10, 100, (int)(200 * loadProgress), 20, GREEN);  // Progrès de la recharge
}
