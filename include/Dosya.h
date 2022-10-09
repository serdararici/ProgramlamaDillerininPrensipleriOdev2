#ifndef DOSYA_H
#define DOSYA_H

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

//Nesne yonelimli benzetim icin Dosya yapisi kuruldu ve fonksiyon gostericileri eklendi.
struct DOSYA
{
    char *yol;
    char *icerik;
    jmp_buf jumper;

    char* (*Oku)(struct DOSYA*);
    void (*Yoket)(struct DOSYA*);
    int (*DosyaSatirSayisi)(struct DOSYA*);
};
typedef struct DOSYA* Dosya;

Dosya DosyaOlustur(char*);
char* oku(const Dosya);
void DosyaYoket(Dosya);
int DosyaSatirSayisi(const Dosya);





#endif