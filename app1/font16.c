#include "font16.h"

// Exemple simplifié : tableau vide ou très réduit pour tester l'affichage
const uint8_t Font16[] = {
    // Ceci devrait normalement contenir les vraies données de police.
    // Mais pour tester rapidement, on met quelques valeurs factices.

    0x00,0x00,0x00,0x00,0x00, // Espace
    0xFF,0x81,0x81,0x81,0xFF, // Carré plein pour test
    0x00,0x00,0x00,0x00,0x00, // Espace
    0x00,0x7E,0x42,0x42,0x7E, // Lettre O par exemple
    // etc... ici il faudrait normalement toutes les lettres ASCII
};
