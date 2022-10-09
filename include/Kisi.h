#ifndef KISI_H
#define KISI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dosya.h"

//Nesne yonelimli benzetim icin Kısi yapısı kuruldu.
struct KISI{
    char *isim;
    double para;
    double yatirilanPara;
    int sayi;
};
typedef struct KISI* Kisi;

Kisi KisiOlustur(char isim[], double, double, int);
void kisiYokEt(Kisi);


#endif