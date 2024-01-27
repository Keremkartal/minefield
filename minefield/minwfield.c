#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

//Projemde kullanicegim sabit degerler
#define tablo_kacakac 8 //tablonun kaca kaclik bir mayin tarlasi istedigimizi ifade eder
#define normal 2 //mayin sayimi ifade eder
#define galibiyet 1   //kazandiysam geriye 1 degerini dondurur.
#define maglubiyet -1  //kaybetigimizde geriye -1 degerini dondurur.
#define devam 0   //oyuna devam etmek icin 0 degerini dondurur.

//global degiskenlerim
char tab[tablo_kacakac+2][tablo_kacakac+2];    //# ve * isaretlerini tabloya doldurmaya yarar
int geneltablo[tablo_kacakac+2][tablo_kacakac+2];   //tablonun altındaki 0 lari yerlestirr
int mayin_sayisi,y=0;    //
int d_sayisi = 0;

//Projemde kullanicagim fonksiyonlar
void alttablo_olustur(); //alt tabloyu olusturmamizi saglar tablonun iskeletini cýkarýr ve 0 ile doldurur sonra bunun üzerine '*','#' ve -1 ,1,2 gibi sayilar eklicez
void ilktblo_olustur();  //ilk tabloyu olusturmamizi saglar tablonun # ile kapalý olmasini ve etrafininda '*' ile cevrili olmasini saglar
void tabloalt_bastir();  //olusturdugumuz alt tabloyu bastirir
void tumtablo_bastir();  //tum tabloyu konsola bastirmayi saglar
void mayin_yerlestir();  //mayinlari random olarak yerlestirmeyi saglar
int  sonuc_ne();          //kazanip kazanmadigimizi kontrol edicek.
void sayi_kesif(int satir,int sutun);//secilen konumu kazýp altýnda ne oldugunu gormemize saglar. '#' isaretini kaldirip sayiyi ortaya cikarir.kesif yapar
int kordinat(int satir,int sutun);//mayin tarlasinin icindeki istedigimiz kordinati acmami saglar
void Nasil_oynanir();

int main(void)
{
    int satir,sutun;
    int ilerleme;
    int secim;
    int yeniden;
    char durum;//Hangi harf
    printf("Mayin Tarlasi oyunumuza hosgeldiniz\n");
    printf("Oyundaki mayin sayisi : %d",normal);
    alttablo_olustur();
    ilktblo_olustur();
    do
    {
        tumtablo_bastir();
        printf("\n");
        printf("\n©©©©©©©©©OYUN MENUSU©©©©©©©©©©©©\n");
        printf("------------------------------------\n");
        printf("1-]Kareyi acmak icin  1'e basiniz\n");
        printf("2-]Kareye bayrak koymak icin 2'ye basiniz\n");
        printf("3-]Bayragi kaldirip ordaki hucreyi acmak  : 3'e basiniz\n");
        printf("4-]Nasil oynanir ogrenmek  icin 4 e basiniz");
        printf("\n©©©©©©©©©©©©©©©©©©©©©©©©©©\n");

        scanf("%d",&secim);


        if(secim==1)
        {
            printf("Secilicek yerin satir  degerini giriniz:");
            scanf("%d",&satir);
            printf("Secilicek yerin sutun degerini giriniz:");
            scanf("%d",&sutun);
            ilerleme=kordinat(satir,sutun);

        }

        else if(secim==2)
        {
            printf("Secilicek yerin satir  degerini giriniz:");
            scanf("%d",&satir);
            printf("Secilicek yerin sutun degerini giriniz:");
            scanf("%d",&sutun);
            if(mayin_sayisi >d_sayisi)
            {
                d_sayisi++;
                tab[satir][sutun]='D';
                ilerleme=sonuc_ne();
            }
        }
        else if(secim==3)
        {
            printf("Secilicek yerin satir  degerini giriniz:");
            scanf("%d",&satir);
            printf("Secilicek yerin sutun degerini giriniz:");
            scanf("%d",&sutun);
            if(d_sayisi>0)
            {
                d_sayisi--;
            }
            tab[sutun][sutun]='#';
            ilerleme=kordinat(satir,sutun);
        }
        else if(secim==4)
        {
            Nasil_oynanir();
        }


        if(ilerleme==maglubiyet)
        {
            printf("Uzgunuz Oyunu kaybettiniz :( :( :(\n");
            tabloalt_bastir();
            printf("Oyunu yendiden oynamak istiyorusunuz? [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Tesekkürler Gorusuruz\n");
                return 0;
                break;
            case 1:
                d_sayisi=0;
                ilerleme=devam;//ilerlemeyi 0 a esitledik
                alttablo_olustur();//tekrardan tabloyu olusturduk
                ilktblo_olustur();
                break;
            default:
                printf("Yanlis bir deger girdiniz\n");
                break;
            }
        }

        if(ilerleme==galibiyet)
        {
            printf("\n");
            printf("\n!!!!!!!Bravo Harika bir is cikardin!!!!!!!\n");
            tabloalt_bastir();
            printf("Oyunu yendiden oynamak istiyorusunuz? [1-Evet][0-Hayir] \n");
            scanf("%d",&yeniden);
            switch(yeniden)
            {
            case 0:
                printf("Tesekkürler Gorusuruz\n");
                return 0;
                break;
            case 1:
                d_sayisi=0;
                ilerleme=devam;
                alttablo_olustur();
                ilktblo_olustur();
                break;
            default:
                printf("Yanlis bir deger girdiniz\n");
                break;
            }

        }

    }
    while(1);
    return 0;

}
void Nasil_oynanir(){
    printf("\nOyunun Nasil Oynanicagi Hakkinda Bilgiler\n");
    printf("**********************************\n");
    printf("-1 sayisi mayinlari gosterir.\n");
    printf("D sayisi mayin isaretlenmis bölgeleri.\n");
    printf("3 e basarsak ordaki hucredeki kutucugu acar eger o hucrede mayin varsa oyun kaybedilir");
    printf("1-8 sayilari mayin komsuluk sayisini.\n");
    printf("Mayin tarlasi 8x8 boyutlarýndadir. \nBoyutunu degistirmek icin tablo_kacakac degerini degistirin \n");
    printf("Satir ve sutun sayilarina siz giriyorsunuz.\n");
    printf("**********************************\n");

}
void alttablo_olustur()
{
	int i,j,mayin_sayisi;


	for(i=0;i<=tablo_kacakac+1;i++)
	{
		for(j=0;j<=tablo_kacakac+1;j++)
		{
			geneltablo[i][j]= 0;
		}
	}
	for(i=0;i<=tablo_kacakac;i++)
	{
		geneltablo[i][0]= 1;
		geneltablo[i][tablo_kacakac+1]= 1;
	}
	for(j=0;j<=tablo_kacakac;j++)
	{
		geneltablo[0][j]= 1;
		geneltablo[tablo_kacakac+1][j]= 1;
	}
     mayin_sayisi =normal;
	mayin_yerlestir();

}

void ilktblo_olustur()
{
	int i,j;

	for(i=0;i<=tablo_kacakac+1;i++)
	{
		for(j=0;j<=tablo_kacakac+1;j++)

			tab[i][j]= '#';
		}
	for(i=0;i<=tablo_kacakac;i++)
		{
			tab[i][0]= '*';
			tab[i][tablo_kacakac+1]= '*';
		}
	for(j=0;j<=tablo_kacakac;j++)
		{
			tab[0][j]= '*';
			tab[tablo_kacakac+1][j]= '*';
		}

}

void tumtablo_bastir(){
	int i,j;

	printf("\n");
	for(i=1;i<=tablo_kacakac;i++){
		printf("%3d",i);
	}
	printf("\n");

	for(i=1;i<=tablo_kacakac;i++){
		printf("---");
	}
	printf("\n");

	for(i=1;i<=tablo_kacakac;i++){
		for(j=1;j<=tablo_kacakac;j++){
			printf("%3c",tab[i][j]);
		}
		printf(" |%d",i);	//her sutun sonunda dik cizgi ve onun kacýncý sutunda oldugunu belli eden sayi
		printf("\n");
	}


	for(i=1;i<=tablo_kacakac;i++){
		printf("___"); // alt kýsýmdaki cizgileri yapar
	}
}

void tabloalt_bastir(){
	int i,j;

	printf("\n");

	for(i=1;i<=tablo_kacakac;i++){
		printf("%3d",i);
	}
	printf("\n");


	for(i=1;i<=tablo_kacakac;i++){
		printf("---");
	}
	printf("\n");


	for(i=1;i<=tablo_kacakac;i++){
		for(j=1;j<=tablo_kacakac;j++){
			printf("%3d",geneltablo[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}


	for(i=1;i<=tablo_kacakac;i++){
		printf("___");
	}
	printf("\n");
}


void mayin_yerlestir()
{
	srand(time(NULL)); // Random sekilde mayinlari atamaya yarar
	int i,j,k,p,satir,sutun;
	mayin_sayisi = normal;


		for(i=1;i<=mayin_sayisi;i++)
		{
			satir=1+rand()%tablo_kacakac; // mayinin gidecegi deger 1-8 arasinda olmali ve 1,8 dahildir
			sutun=1+rand()%tablo_kacakac;
			if(geneltablo[satir][sutun]== -1)//daha onceden mayın varsa o secilen bolgede bu sefer bir onceki satıra gönderiril
                i--;
			else
			geneltablo[satir][sutun]= -1;
                    for(k=-1;k<=1;k++)//secilen bolgenin komsularının bomba olup olmadiklarini kontrol eder ve ona gore islem uygular
                    {
                        for(p=-1;p<=1;p++)
                        {//Üst Orta Alt
                            if(geneltablo[satir][sutun]==-1)
                            {//Bombaysa
                                    if(geneltablo[satir+k][sutun+p]!=-1)//Komsusu bomba degilse
                                    {
                                    geneltablo[satir+k][sutun+p]++;//Çevresindeki bomba sayisini 1 arttir
                                    }
                            }
                        }
                    }

                }

        }

int sonuc_ne()//bayrak sayisi mayin sayisina esitse oyunu kazandik demektir.
{
	int i,j,y=0,durum;
	for(i=1;i<=tablo_kacakac;i++)
	{
        for(j=1;j<=tablo_kacakac;j++)
        {
            if(tab[i][j]=='D')//Bayraksa say
			{
                if(geneltablo[i][j]==-1)//koydugum bayraklar bombanın üzerine gelmisse y yi arttir.
                {
                    y++;
                }
			}

        }
	}
	if(y==normal)//koydugum bayrak sayisi projedeki mayin sayisina esitse 1 degeri doner ve oyunu kazandik demektir
	{
		durum=galibiyet;
	}
	else
		durum=devam;

	return durum;
}

void sayi_kesif(int satir, int sutun) {
	int i, j;


	tab[satir][sutun] = '0' + geneltablo[satir][sutun];//Alt tablodaki degeri üst tabloya karakter olarak atiyoruz(açma operasyonu)
  //Tüm komþular için
	for (i = -1; i <= 1; i++)
    {//komsusunu kontrol edicez
		for (j = -1; j <= 1; j++)
		 {
			//
			if (geneltablo[satir + i][sutun + j] > 0 && tab[satir+ i][sutun + j] == '#')
			{
				tab[satir + i][sutun + j] = '0'+ geneltablo[satir + i][sutun + j];//Komsuyu aç
			}

			else if (geneltablo[satir+ i][sutun + j] == 0 && tab[satir + i][sutun + j] == '#')
                            {
				sayi_kesif(satir + i, sutun + j);//Komsuya geç ayni islemi tekrar  rekürsif olarak yap
			}
		}
	}
}


int kordinat(int satir, int sutun)
{
	int x=0;//geriye doncek deger.0 olmasının nedeni devam 0 a esittir ve oyuna devam ediyoruz
    if (geneltablo[satir][sutun] == -1)//Bomba mi
    {
    	x=maglubiyet;//Öldün
    }

    else if (geneltablo[satir][sutun] > 0)//Sayi  mi (komsusu mayinliysa)
    {
        tab[satir][sutun] = ('0' + geneltablo[satir][sutun]);//Aç

        x=devam;
	}
    else//Bossa(Komsusu bossa)
    {
    	sayi_kesif(satir,sutun); //Komsularini açarak ilerle
    }

    return x;
}




