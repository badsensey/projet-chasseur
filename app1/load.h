#ifndef __LOAD_H
#define __LOAD_H

#ifdef __cplusplus
extern "C" {
#endif

// Fonction pour calculer le délai de recharge
float equation(float* lastShot, float currentTime);

// Fonction pour gérer le chargement des balles
void bulletLoad(float* lastShot, float* loadProgress, float* lastLoading, float* loadLastTick, uint8_t* cartilages, uint8_t* currentLoad, float currentTime);

// Fonction pour gérer un tir
void shoot(uint8_t* currentLoad, float* lastShot, float currentTime);

#ifdef __cplusplus
}
#endif

#endif /* __LOAD_H */
