#include "Dosya.h"
#include "Kisi.h"

//Dosya yolunu alarak dosyayi heap hafizasinda oluşturuyor.
Dosya DosyaOlustur(char* yol){
    Dosya this;
    this = (Dosya)malloc(sizeof(struct DOSYA));
    this->yol = yol;
    this->icerik = NULL;
    this->DosyaSatirSayisi = &DosyaSatirSayisi;
    this->Oku = &oku;
    this->Yoket = &DosyaYoket;
    return this;
}

//Verilen dosyayi okuyarak dosyadaki satir sayisini donduren fonksiyon.
int DosyaSatirSayisi(const Dosya this)
{
    int satirSayisi = 0;
    FILE *fp;
    fp = fopen(this->yol, "r");
    
    char chr = getc(fp);
    while (chr != EOF)
    {
        if (chr == '\n'){
            satirSayisi = satirSayisi + 1;
        }
        chr = getc(fp);
    }
    fclose(fp);
    satirSayisi = satirSayisi+1; // End Of File
    return satirSayisi;
}

//Dosyada once satir sonuna giderek dosya boyutunu buluyor. Daha sonra dosyayi boyutu kadar okuyor ve icerigi donduruyor.
char* oku(const Dosya this){

    char* icerik=NULL;
    int boyut=0;
    FILE *fp;
    fp = fopen(this->yol, "r");
    if(!fp) longjmp(this->jumper, -3);
    fseek(fp,0,SEEK_END);
    boyut = ftell(fp);
    rewind(fp);
    icerik = (char*)malloc(sizeof(char)*boyut);
    fread(icerik,1,boyut,fp);
    icerik[boyut-1]='\0';
    fclose(fp);
    this->icerik = icerik;
    return icerik;
}

//Dosyayi olusturmak icin heap hafızasını kullandıgımız icin free fonksiyonu kullanilarak dosya yokediliyor.
void DosyaYoket(Dosya this){
    if(this == NULL) return;
    if(this->icerik != NULL) free(this->icerik);
    free(this);
}


