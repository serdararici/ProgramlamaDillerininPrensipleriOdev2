#include "Oyun.h"
#include "Kisi.h"
#include "Dosya.h"


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

char kisiDosyasiYolu[] = ".\\docs\\Kisiler.txt";
char sayiDosyasiYolu[] = ".\\docs\\Sayilar.txt";
int beklemeSuresi = 500; //milisaniye -> 1sn için 1000

void oyun(){
    Dosya kisiDosyasi = DosyaOlustur(kisiDosyasiYolu);   //kisi dosyasi dosya yolu okunarak olusturuluyor.
    kisiDosyasi->Oku(kisiDosyasi);       //kisi dosyasi oku fonksiyonu kullanilarak okunuyor.
    Kisi* kisiler=NULL;
    int kisiSayisi = kisiDosyasi->DosyaSatirSayisi(kisiDosyasi);  //dosyadaki kisi sayisi DosyaSatirSayisi fonksiyonu kullanılarak hesaplaniyor.
    kisiler = (Kisi*)malloc(sizeof(Kisi*)*kisiSayisi);
    
    char adSoyad[5000];
    char para[5000];
    char yatirilanOran[5000];
    char sayi[5000];
    int sayac = 0;
    int harfSayac = 0;
    int kisiID = 0;

    for (int i = 0; i<strlen(kisiDosyasi->icerik); i++)
    {
        if(kisiDosyasi->icerik[i] != '\n')  //Satir sonuna gelip gelmedigini kontrol ediyor.
        {
            if(kisiDosyasi->icerik[i] == '#')  //# işaretini kontrol ederek kisinin bilgilerinin ayrılmasını saglıyor.
            {
                sayac = sayac+1;
                harfSayac = 0;
            }
            else
            {
                if(sayac == 0) adSoyad[harfSayac] = kisiDosyasi->icerik[i];
                if(sayac == 1) para[harfSayac] = kisiDosyasi->icerik[i];
                if(sayac == 2) yatirilanOran[harfSayac] = kisiDosyasi->icerik[i];
                if(sayac == 3) sayi[harfSayac] = kisiDosyasi->icerik[i];
                harfSayac = harfSayac + 1;
            }
        }

        //Satir sonu veya dosya sonu ise onceden toplanan verilerden kisi struct ına verileri atıyor.
        if(kisiDosyasi->icerik[i] == '\n' || i == strlen(kisiDosyasi->icerik)-1)
        {
            kisiler[kisiID] = KisiOlustur(strdup(adSoyad),atof(para),atof(yatirilanOran),atoi(sayi));
            
            //memset kullanarak gecici degiskenler sifirlaniyor.
            memset(adSoyad,0,5000);
            memset(para,0,5000);
            memset(yatirilanOran,0,5000);
            memset(sayi,0,5000);
            sayac = 0;
            harfSayac = 0;
            kisiID = kisiID +1;
        }
    }

    /* KİŞİLERİ EKRANA YAZDIRMAK İÇİN
    for(int i = 0;i<kisiSayisi;i++)
    {
         printf("%s ,-, %Lf ,-, %lf ,-, %d ---\n",kisiler[i]->isim,kisiler[i]->para,kisiler[i]->yatirilanPara,kisiler[i]->sayi);
    }
    */
   
    int kazananNumara = 0;
    int enZenginID = 0;
    int enZenginPara = 0;
    int Tur = 0;
    double kasa = 0;
    FILE *file;
    if (file = fopen(sayiDosyasiYolu, "r"))   //Sayilari okuyan dosya aciliyor.
    {
        while (fscanf(file, "%d", &kazananNumara) != EOF)
        {
            for (int i = 0;i<kisiSayisi;i++)
            {
                if (kisiler[i]->para >=1000)  //Sadece parasi 1000 ve uzerindekiler oyuna devam ediyor.
                {
                    double YatirilanPara = kisiler[i]->yatirilanPara * kisiler[i]->para;  //Yatirilan para orani ile kisinin parasi carpilarak yatirdigi para hesaplaniyor.
                  //  YatirilanPara = roundf(YatirilanPara*100)/100;
                
                    if(kisiler[i]->sayi == kazananNumara) //Kisinin sayisi kazan numaraya esit ise kazanmıs oluyor ve parasinin 10 kati ekleniyor.
                    {
                        kasa = kasa - YatirilanPara*9;
                        kisiler[i]->para = kisiler[i]->para + YatirilanPara*9;
                    }
                    else  //Esit degilse kisinin yatirdigi para kasaya ekleniyor ve kisinin parasindan azaliyor.
                    {
                        kasa = kasa + YatirilanPara;
                        kisiler[i]->para = kisiler[i]->para - YatirilanPara;
                    }
                    
                    //En zengini bulmak icin herkesi tek tek karsilastiriyor ve en zenginin parasini buluyor.
                    if (kisiler[i]->para > enZenginPara)
                    {
                        enZenginID =  i;
                        enZenginPara = kisiler[i]->para;
                    }
                }
            }
            Tur++;
            
          //  KAZANANLARI SATIR SATIR YAZDIRMAK İÇİN
          //  printf("\nEn Zengin ID = %d,En Zengin Kisi = %s,En Zengin Para,%Lf, kasa %Lf, Tur %d, kazanan numara %d \n"
          //  ,enZenginID,kisiler[enZenginID]->isim, kisiler[enZenginID]->para,kasa,Tur,kazananNumara);
            
            //Sonucu ekrana yazdirmak icin EkranaYazzdir fonksiyonu calistiriliyor.
            EkranaYazdir(Tur,kazananNumara,kisiler[enZenginID]->isim,kisiler[enZenginID]->para,kasa);
            enZenginID = 0;
            enZenginPara = 0;
            
        }
        fclose(file);  //Dosya kapatiliyor.
        OyunuBitir(Tur,kasa);  //Oyun bittikten sonra ekranda gozukmesi gereken veriler gosteriliyor.
        kisiYokEt(kisiler); 
        DosyaYoket(kisiDosyasi);
    }
}
    //Oyunda ekranda gozukmesi gereken verileri ekrana yazdirmaya yarayan fonksiyon.
    void EkranaYazdir(int Tur,int kazananNumara,char zenginAdi[], double ZenginPara,double Masa){

        system("cls");   //Her turdan sonra ekrani temizlemeye yariyor.

        printf("\n\n\n");
        printf("                      #############################################\n");
        printf("                      ##               SANSLI SAYI: %-5d        ##\n",kazananNumara);
        printf("                      #############################################\n");
        printf("                      #############################################\n");
        printf("                      ##               TUR: %-7d              ##\n",Tur);
        printf("                      ##       MASA BAKIYE: %-13.2Lf TL     ##\n",Masa);
        printf("                      ##                                         ##\n");
        printf("                      ##-----------------------------------------##\n");
        printf("                      ##               EN ZENGIN KISI            ##\n");
        printf("                      ##           %-20s          ##\n",zenginAdi);
        printf("                      ##       BAKIYESI: %-13.2Lf TL        ##\n",ZenginPara);
        printf("                      ##                                         ##\n");
        printf("                      #############################################");
        usleep(beklemeSuresi*1000);  //Her turda cikti gozukten sonra verilen sure kadar bekleme yapiliyor.
    }

    //Oyun bittikten sonra ekranda gozukmesi gereken ciktiyi olusturuyor.
    void OyunuBitir(int Tur,double Masa)
    {
    
        system("cls");
        printf("\n\n\n\n\n\n");
        printf("                      #############################################\n");
        printf("                      ##               TUR: %7d              ##\n",Tur);
        printf("                      ##       MASA BAKIYE: %13.2Lf TL     ##\n",Masa);
        printf("                      ##                                         ##\n");
        printf("                      ##-----------------------------------------##\n");
        printf("                      ##                                         ##\n");
        printf("                      ##                   OYUN BITTI            ##\n");
        printf("                      ##                                         ##\n");
        printf("                      ##                                         ##\n");
        printf("                      #############################################");
    

    }