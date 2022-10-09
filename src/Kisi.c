#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include "Kisi.h"

//Dosyadan kişileri okuduktan sonra elde edilecek verileri kullanarak  Kişi oluşturmaya yarayan fonksiyon.
Kisi KisiOlustur(char isim[], double para, double yatirilanPara, int sayi){
    Kisi this;
    this = (Kisi)malloc(sizeof(struct KISI));
    this->isim = (char)malloc(sizeof(char)*sizeof(isim));
    this->isim = isim;
    this->para = para;
    this->yatirilanPara = yatirilanPara;
    this->sayi = sayi;
    return this;
}

//Kişi oluştururken malloc ile heap hafızasından yer ayırdığımız için free fonksiyonunu kullandığım bir yok etme fonksiyonu oluşturdum.
void kisiYokEt(Kisi this){
    if(this != NULL) free(this);
}


