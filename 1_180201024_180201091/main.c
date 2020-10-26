#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TREE_HT 100


struct Min_Yigin_Dugum
{

    char karakter;


    unsigned frekans;


    struct MinYigin_Dugum *sol, *sag;
};


struct Min_Yigin
{


    unsigned boyut;


    unsigned kapasite;


    struct Min_Yigin_Dugum **dizi;
};


struct Min_Yigin_Dugum *yeni_Dugum(char karakter, unsigned frekans)
{
    struct Min_Yigin_Dugum *temp=(struct Min_Yigin_Dugum*)malloc(sizeof(struct Min_Yigin_Dugum));

    temp->sol = temp->sag = NULL;
    temp->karakter =karakter;
    temp->frekans = frekans;

    return temp;
}


struct Min_Yigin *Min_Yigin_Olustur(unsigned kapasite)

{

    struct Min_Yigin *minYigin= (struct Min_Yigin*)malloc(sizeof(struct Min_Yigin));


    minYigin->boyut = 0;

    minYigin->kapasite = kapasite;

    minYigin->dizi=(struct Min_Yigin_Dugum*)malloc(minYigin->kapasite * sizeof(struct Min_Yigin_Dugum));
    return minYigin;
}


void Min_Yigin_Dugum_Degistirme(struct Min_Yigin_Dugum **d1,struct Min_Yigin_Dugum **d2)

{

    struct Min_Yigin_Dugum *temp = *d1;
    *d1 = *d2;
    *d2 = temp;
}


void minYigin_Yerdegistirme(struct Min_Yigin *minYigin, int index)

{

    int en_kucuk = index;
    int sol = 2 * index+1;
    int sag = 2 * index+2;

    if (sol < minYigin->boyut && minYigin->dizi[sol]->frekans < minYigin->dizi[en_kucuk]->frekans)
        en_kucuk = sol;

    if (sag < minYigin->boyut && minYigin->dizi[sag]->frekans < minYigin->dizi[en_kucuk]->frekans)
        en_kucuk = sag;

    if (en_kucuk!= index)
    {
        Min_Yigin_Dugum_Degistirme(&minYigin->dizi[en_kucuk],&minYigin->dizi[index]);
        minYigin_Yerdegistirme(minYigin,en_kucuk);
    }
}


int Boyut_Kontrol(struct Min_Yigin* minYigin)
{

    return (minYigin->boyut == 1);
}


struct Min_Yigin_Dugum *Dugum_Cikarma(struct Min_Yigin *minYigin)

{

    struct Min_Yigin_Dugum *temp = minYigin->dizi[0];
    minYigin->dizi[0]=minYigin->dizi[minYigin->boyut - 1];
    --minYigin->boyut;
    minYigin_Yerdegistirme(minYigin, 0);

    return temp;
}


void Min_Yigin_Ekleme(struct Min_Yigin *minYigin,struct Min_Yigin_Dugum *minYiginDugum)

{

    ++minYigin->boyut;
    int i = minYigin->boyut - 1;

    while (i && minYiginDugum->frekans < minYigin->dizi[(i - 1) / 2]->frekans)
    {

        minYigin->dizi[i] = minYigin->dizi[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minYigin->dizi[i] = minYiginDugum;
}


void Min_Yigin_Olusturma(struct Min_Yigin* minYigin)

{

    int n = minYigin->boyut - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        minYigin_Yerdegistirme(minYigin, i);
}


 Dizi_Yazdir(int dizi[], int n,int tekrar[],int tekrar_indis[],FILE *cikti)
{

    int i;
    for (i = 0; i < n; ++i){
        printf("%d", dizi[i]);
        fprintf(cikti,"%d", dizi[i]);
    }

     tekrar[tekrar_indis[0]]=n;
     tekrar_indis[0]= tekrar_indis[0]+1;
    printf("\n");
    fprintf(cikti,"\n");


}


int Bos_Dugum_Kontrol(struct Min_Yigin_Dugum *kok)

{

    return !(kok->sol) && !(kok->sag);
}

struct Min_Yigin* Yeni_Dugum_Olusturma(char veri[], int frekans[], int boyut)

{

    struct Min_Yigin *minYigin = Min_Yigin_Olustur(boyut);

    for (int i = 0; i <boyut; ++i)
        minYigin->dizi[i] = yeni_Dugum(veri[i], frekans[i]);

    minYigin->boyut = boyut;
    Min_Yigin_Olusturma(minYigin);

    return minYigin;
}


struct Min_Yigin_Dugum* Huffman_Agaci_Olustur(char veri[], int frekans[], int boyut)

{
    struct Min_Yigin_Dugum *sol, *sag, *en_ust;


    struct Min_Yigin* minYigin = Yeni_Dugum_Olusturma(veri, frekans, boyut);

    while (!Boyut_Kontrol(minYigin))
    {


        sol = Dugum_Cikarma(minYigin);
        sag= Dugum_Cikarma(minYigin);


        en_ust = yeni_Dugum('$', sol->frekans + sag->frekans);

        en_ust->sol =sol;
        en_ust->sag =sag;

        Min_Yigin_Ekleme(minYigin,en_ust);
    }


    return Dugum_Cikarma(minYigin);
}


void Yazdir(struct Min_Yigin_Dugum *kok, int dizi[], int en_ust,int tekrar[], int tekrar_indis,char kontrol[],int kontrol_indis[],FILE *cikti)

{




    if (kok->sol)
    {

        dizi[en_ust] = 0;
        Yazdir(kok->sol, dizi, en_ust + 1,tekrar,tekrar_indis,kontrol,kontrol_indis,cikti);
    }

    if (kok->sag)
    {

        dizi[en_ust] = 1;
        Yazdir(kok->sag, dizi, en_ust + 1,tekrar, tekrar_indis,kontrol,kontrol_indis,cikti);
    }


    if (Bos_Dugum_Kontrol(kok))
    {


        printf("%c: ", kok->karakter);
        fprintf(cikti,"%c: ", kok->karakter);

        kontrol[kontrol_indis[0]]=kok->karakter;
        kontrol_indis[0]=kontrol_indis[0]+1;
        Dizi_Yazdir(dizi,en_ust,tekrar,tekrar_indis,cikti);
    }



}


void Huffman_Agaci(char veri[], int frekans[], int boyut,int tekrar[],int tekrar_indis[],char kontrol[],int kontrol_indis,FILE *cikti)

{

    struct Min_Yigin_Dugum *kok= Huffman_Agaci_Olustur(veri, frekans,boyut);

    int dizi[MAX_TREE_HT],en_ust = 0;

    Yazdir(kok, dizi, en_ust,tekrar,tekrar_indis,kontrol,kontrol_indis,cikti);
}



int main()
{
    FILE *dosya=fopen("C:\\Users\\Berkay\\Desktop\\lz.txt","r");
    FILE *cikti=fopen("output.txt","w");
    if(cikti==NULL){

        printf("Dosya acilamadi.\n");
        exit(1);

    }


    char arama_tamponu[100];
    char ileri_tampon[100];
    char yedek_dizi[100];
    int tekrar_sayisi[100];
    int uzaklik=0;
    int benzerlik=0;
    int i=0;
    int boyut;
    int a;
    int boy=0;
    int tek_say=0;
    int lz77=1;
    int tekrar [100];
    int tekrar_indis[1];
    tekrar_indis[0]=0;
    char kontrol[100];
    int kontrol_indis[1];
     kontrol_indis[0]=0;




    fgets(arama_tamponu,2,dosya);
    for(int j=0; j<1; j++)
    {
        yedek_dizi[j]=arama_tamponu[j];
    }
    fgets(ileri_tampon,2,dosya);
    printf("%d ,%d ,%s \n",uzaklik,benzerlik,arama_tamponu);
    fprintf(cikti,"%d ,%d ,%s \n",uzaklik,benzerlik,arama_tamponu);

    while(!feof(dosya))
    {
        do
        {

            if(arama_tamponu[i] == ileri_tampon[0])
            {

                strcat(arama_tamponu,ileri_tampon);
                boyut = strlen(arama_tamponu);
                a = i;
                fgets(ileri_tampon,2,dosya);
                i++;
                benzerlik++;

                if(arama_tamponu[i] != ileri_tampon[0])
                {
                    break;
                }
            }



            i++;
        }
        while(i<boy);


        if(benzerlik == 0)
        {
            printf("%d, %d, %s\n",uzaklik,benzerlik,ileri_tampon);
            fprintf(cikti,"%d, %d, %s\n",uzaklik,benzerlik,ileri_tampon);
            lz77++;
            strcat(yedek_dizi,ileri_tampon);
            strcat(arama_tamponu,ileri_tampon);


        }
        else
        {
            printf("%d, %d, %s\n",(boyut - a - 1),benzerlik,ileri_tampon);
            fprintf(cikti,"%d, %d, %s\n",(boyut - a - 1),benzerlik,ileri_tampon);
            lz77++;
            strcat(arama_tamponu,ileri_tampon);
            char *deneme=strstr(yedek_dizi,ileri_tampon);
            if(deneme==NULL)
            {
                strcat(yedek_dizi,ileri_tampon);
            }



        }
        fgets(ileri_tampon,2,dosya);
        benzerlik= 0;
        boy = strlen(arama_tamponu);
        i=0;
    }
    fclose(dosya);

    printf("Arama tamponu:\n %s\n",arama_tamponu);
    fprintf(cikti,"Arama tamponu:\n %s\n",arama_tamponu);

    printf("Arama tamponundaki harfler: \n %s\n",yedek_dizi);
    fprintf(cikti,"Arama tamponundaki harfler: \n %s\n",yedek_dizi);

    int yedek_dizi_sayi=strlen(yedek_dizi);
    for(int i=0; i<yedek_dizi_sayi; i++)
    {
        for(int j=0; j<strlen(arama_tamponu); j++)
        {
            if(yedek_dizi[i]==arama_tamponu[j])
            {
                tek_say++;

            }
        }
        tekrar_sayisi[i]=tek_say;
        tek_say=0;

    }
    printf("harflerin tekrar sayilari:\n");
    fprintf(cikti,"harflerin tekrar sayilari:\n");
    for(int i=0; i<yedek_dizi_sayi; i++)
    {
        printf(" %c=%d\n",yedek_dizi[i],tekrar_sayisi[i]);
        fprintf(cikti," %c=%d\n",yedek_dizi[i],tekrar_sayisi[i]);
    }

    printf("\n------------\n");
    fprintf(cikti,"\n------------\n");
    printf("Huffman kodlamalari:\n");
    fprintf(cikti,"Huffman kodlamalari:\n");
    char harf_dizi [strlen(yedek_dizi)-2];
    harf_dizi[0]= yedek_dizi[0];

    int size = strlen(yedek_dizi);

    int toplam =0;
    int swap[100];
    int swap_indis=0;
    int temp;
    char tempc;
    int toplam_txt=strlen(arama_tamponu);
    printf("%c burasi\n",yedek_dizi[0]);

    Huffman_Agaci(yedek_dizi, tekrar_sayisi,size,tekrar,tekrar_indis,kontrol,kontrol_indis,cikti);


    for(int b=0;b<size;b++){

        for(int c=0;c<size;c++){

            if(kontrol[b]==yedek_dizi[c]){
                 tempc=yedek_dizi[b];
                  yedek_dizi[b]=yedek_dizi[c];
                yedek_dizi[c]=tempc;
                temp=tekrar_sayisi[b];
                tekrar_sayisi[b]=tekrar_sayisi[c];
                tekrar_sayisi[c]=temp;

            }

        }

        }




    for(int b=0;b<size;b++){

        toplam=tekrar[b]*tekrar_sayisi[b]+toplam;

    }
    printf("Toplam Metin Boyutu=%d byte\n",toplam_txt);
    fprintf(cikti,"Toplam Metin Boyutu=%d byte\n",toplam_txt);
    printf("Deflate Sonrasi Toplam Boyutun Bit Cinsinden Ifadesi(8 e bolunmemis hali)=%d bit\n",toplam);
    fprintf(cikti,"Deflate Sonrasi Toplam Boyutun Bit Cinsinden Ifadesi(8 e bolunmemis hali)=%d bit\n",toplam);
    printf("Deflate Sonrasi Boyut = %d byte\n",toplam/8);
    fprintf(cikti,"Deflate Sonrasi Boyut= %d byte\n",toplam/8);
    printf("lz77 Sonrasi Boyut=%d byte \n",lz77);
    fprintf(cikti,"lz77 Sonrasi Boyut=%d byte \n",lz77);







    return 0;
}
