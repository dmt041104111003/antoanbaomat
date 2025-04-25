#include "String.h"

int dem_do_dai_chuoi(char s[]) {
    int do_dai = 0;
    while (s[do_dai] != '\0') do_dai++;
    return do_dai;
}

void sao_chep_chuoi(char ban_sao[], char chuoi_goc[]) {
    int i = 0;
    while (chuoi_goc[i] != '\0') {
        ban_sao[i] = chuoi_goc[i];
        i++;
    }
    ban_sao[i] = '\0';
}

void noi_chuoi(char chuoi_thunhat[], char chuoi_thuhai[]) {
    int do_dai_chuoi_thunhat = dem_do_dai_chuoi(chuoi_thunhat);
    int i = 0;
    while (chuoi_thuhai[i] != '\0') {
        chuoi_thunhat[do_dai_chuoi_thunhat + i] = chuoi_thuhai[i];
        i++;
    }
    chuoi_thunhat[do_dai_chuoi_thunhat + i] = '\0';
}

void cat_chuoi_con(char ket_qua[], char chuoi_goc[], int vitri_cat, int dodai_cancat) {
    int i = 0;
    while (i < dodai_cancat && chuoi_goc[vitri_cat + i] != '\0') {
        ket_qua[i] = chuoi_goc[vitri_cat + i];
        i++;
    }
    ket_qua[i] = '\0';
}


