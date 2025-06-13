/*
 * load.c
 *
 *  Created on: Mar 21, 2025
 *      Author: ohinpari & diallosou
 */

/*typedef struct{
	uint8_t load;
} *cartilage;*/
#include "load.h"
#include "main.h"

// Calcul du délai de recharge basé sur les tirs précédents
float equation(float* lastShot, float currentTime) {
    uint8_t tenCounting = 0;
    uint8_t minCounting = 0;

    for (uint8_t i = 0; i < 15; i++) {
        if (lastShot[i] < currentTime - 10) tenCounting++;
        if (lastShot[i] < currentTime - 60) minCounting++;
    }

    minCounting -= tenCounting;
    return (tenCounting * 0.1f + minCounting * 0.02f + 2.0f) / 1024.0f;
}

// Fonction de gestion du chargement de balle
void bulletLoad(float* lastShot, float* loadProgress, float* lastLoading, float* loadLastTick, uint8_t* cartilages, uint8_t* currentLoad, float currentTime) {
    if (*loadProgress < 1.0f) {
        if (currentTime - *loadLastTick >= equation(lastShot, currentTime)) {
            *loadProgress += 0.05f;  // Augmente la progression
            *loadLastTick = currentTime;
        }
    } else {
        *lastLoading++;
        if (*lastLoading == 15) {
            *cartilages++;
            *lastLoading = 0;
        }
    }
}

// Fonction de gestion de tir
void shoot(uint8_t* currentLoad, float* lastShot, float currentTime) {
    if (*currentLoad > 0 && (currentTime - lastShot[14] >= 0.5f)) {
        lastShot[14] = currentTime;
        (*currentLoad)--;  // Décrémenter le nombre de balles restantes
    }
}
