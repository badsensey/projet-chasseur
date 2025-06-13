/*
 * main.c
 *
 *  Created on: Mar 21, 2025
 *      Author: ohinpari & diallosou
 */

#include "main.h"
#include "stm32g4xx_hal.h"
#include "lcd.h"  // Bibliothèque pour l'écran TFT
#include "ui_display.h"
#include "load.h"

// Déclaration des variables globales
uint8_t cartouches = 4;   // Nombre de cartouches pleines
uint8_t lastLoading = 0;   // Quantité de balles chargées dans la dernière cartouche
uint8_t currentLoad = 15;  // Nombre de balles restantes dans la cartouche actuelle
float loadProgress = 0.0f; // Progression de la recharge
float loadLastTick = 0.0f;  // Dernier instant de la recharge
float lastShot[15] = {0};  // Enregistrement des derniers tirs

// Déclaration des fonctions
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_SPI1_Init(void);
void MX_TIM3_Init(void);
void initLCD(void);
void displayUI(void);
void loadBalle(void);

int main(void) {
    // Initialisation des composants
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_SPI1_Init();
    MX_TIM3_Init();

    // Initialisation de l'écran LCD
    initLCD();

    // Affichage initial
    displayUI();

    // Boucle principale
    while (1) {
        // Met à jour l'interface avec les informations courantes
        displayUI();

        // Gestion du chargement des balles
        loadBalle();

        HAL_Delay(100);  // Attente pour éviter un surmenage du processeur
    }
}

// Initialisation de l'écran TFT
void initLCD() {
    LCD_Init();
    LCD_Clear(WHITE);  // Efface l'écran avec une couleur blanche
}

// Affichage de l'interface utilisateur
void displayUI() {
    // Affichage du titre "Hunter"
    LCD_SetFont(&Font16);  // Choisir la taille de la police
    LCD_SetTextColor(BLACK);
    LCD_DisplayStringAt(10, 10, (uint8_t*)"Hunter", CENTER_MODE);

    // Affichage du nombre de balles restantes
    LCD_DisplayStringAt(10, 40, (uint8_t*)"Balles restantes: ", LEFT_MODE);
    char buffer[10];
    sprintf(buffer, "%d", currentLoad);
    LCD_DisplayStringAt(150, 40, (uint8_t*)buffer, LEFT_MODE);

    // Affichage du nombre de cartouches disponibles
    LCD_DisplayStringAt(10, 70, (uint8_t*)"Cartouches: ", LEFT_MODE);
    sprintf(buffer, "%d", cartouches);
    LCD_DisplayStringAt(150, 70, (uint8_t*)buffer, LEFT_MODE);

    // Affichage de la barre de progression de la recharge
    LCD_FillRect(10, 100, 200, 20, WHITE);  // Dessine un rectangle blanc pour la barre de progression
    LCD_FillRect(10, 100, (int)(200 * loadProgress), 20, GREEN);  // Dessine la barre de progression
}

// Fonction de gestion du chargement des balles
void loadBalle() {
    if (currentLoad == 0) {
        if (cartouches > 0) {
            // Recharge la cartouche actuelle
            loadProgress = 0.0f;
            currentLoad = 15;
            cartouches--;
        }
    }
    if (loadProgress < 1.0f) {
        loadProgress += 0.05f;  // Augmente la progression de la recharge
    }
}
