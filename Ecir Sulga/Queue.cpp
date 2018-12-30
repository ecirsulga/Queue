#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
struct akademisyen 
{  
int sicilNo; 
char ad[20]; 
char soyAd[20]; 
int unvanID; 
int unvanYili; 
struct akademisyen *sonraki; 
};
akademisyen *bas=NULL,*kuyruk=NULL;
int gorev;
void listeyap()				//Bu fonksiyon dosyadaki verileri okuyup sýralý bir þekilde baðlý listeye atmaya yarar
{
	FILE *dosya=fopen("akademisyen.txt","r");
	int k=1,sicil,unvanid,unvanyil,sicil1,unvanid1,unvanyil1;
	char isim[20],soy[20],a[20],b[20];
	akademisyen *ekle;
	kuyruk=(akademisyen*)malloc(sizeof(akademisyen));
	kuyruk->unvanID=10;
	kuyruk->unvanYili=14;
	while(1)
	{
		FILE *dosya=fopen("akademisyen.txt","r");
		while(!feof(dosya))							// döngülerden biri okuma için diðeri sýralama için iç içe 2 döngü
		{
			fscanf(dosya,"%d %s %s %d %d",&sicil,&isim,&soy,&unvanid,&unvanyil);
			
			if(k==unvanid)
			{  	
				if(unvanid == kuyruk->unvanID && unvanyil < kuyruk->unvanYili)
				{
					strcpy(a,kuyruk->ad);
					strcpy(b,kuyruk->soyAd);
					sicil1=kuyruk->sicilNo;
					unvanid1=kuyruk->unvanID;
					unvanyil1=kuyruk->unvanYili;
					strcpy(kuyruk->ad,isim);
					strcpy(kuyruk->soyAd,soy);
					kuyruk->sicilNo=sicil;
					kuyruk->unvanID=unvanid;
					kuyruk->unvanYili=unvanyil;
					strcpy(isim,a);
					strcpy(soy,b);
					sicil=sicil1;
					unvanid=unvanid1;
					unvanyil=unvanyil1;
				
				}
				
				
				ekle=(akademisyen*)malloc(sizeof(akademisyen));
				ekle->sicilNo=sicil;
				strcpy(ekle->ad,isim);
				strcpy(ekle->soyAd,soy);
				ekle->unvanID=unvanid;
				ekle->unvanYili=unvanyil;
				if(bas==NULL)
				{
					bas=ekle;
					kuyruk=bas;
					kuyruk->sonraki=NULL;
				}
				else 
				{	
					kuyruk->sonraki=ekle;
					kuyruk=ekle;
					kuyruk->sonraki=NULL;
				}
				
			}
			
		}
		if(k==4)break;
		k++;
	}
	fclose(dosya);

}
void listele()				//
{	
	akademisyen *gecici;
	gecici=bas;
	while(gecici!=NULL)
	{
		if(gecici->unvanID==1)printf("%d Prof. Dr. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==2)printf("%d Doc. Dr. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==3)printf("%d Dr. Ogr. Uyesi %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==4)printf("%d Ars. Gor. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		gecici=gecici->sonraki;
	}
}
void silme()
{
	akademisyen *gecici,*gecici1;
	int sil;
	gecici=bas;
	printf("\nSilmek istediginiz kisinin sicil numarasini giriniz");
	scanf("%d",&sil);
	while(gecici!=NULL)
	{
		if(gecici->sicilNo==sil)break;
		gecici=gecici->sonraki;
	}
	if(gecici==NULL)
	{
		printf("\nAradiginiz kayit bulunamadi\n");
		return;
	}
	if(gecici==bas)
	{
		bas=bas->sonraki;
		free(gecici);
	}
	else
	{	
		gecici1=bas;
		while(1)
		{
			if(gecici1->sonraki==gecici)break;
			gecici1=gecici1->sonraki;
		}
		gecici1->sonraki=gecici1->sonraki->sonraki;
		free(gecici);
	}
}

void ekleme()
{
	akademisyen *gecici,*gecici1,*ekle;
	ekle=(akademisyen*)malloc(sizeof(akademisyen));
	printf("\nsicil no giriniz");	scanf("%d",&ekle->sicilNo);
	printf("\nisim giriniz");		scanf("%s",&ekle->ad);
	printf("\nsoyisim giriniz");	scanf("%s",&ekle->soyAd);
	printf("\nunvanid giriniz");	scanf("%d",&ekle->unvanID);
	printf("\nunvanyil giriniz");	scanf("%d",&ekle->unvanYili);
	gecici=bas;
	while(gecici->sonraki!=NULL)				//bu döngü baðlý listeyi kontrol edip eklenecek verinin yerini belirleyerek ekler
	{	
		if(kuyruk->unvanID <= ekle->unvanID)
		{
			kuyruk->sonraki=ekle;
			kuyruk=ekle;
			kuyruk->sonraki=NULL;
			break;
		}
		if(bas->unvanID>=ekle->unvanID)
		{
			if(bas->unvanYili > ekle->unvanYili)
			{
				ekle->sonraki=bas;
				bas=ekle;
				break;
			}
			else
			{
				ekle->sonraki=bas->sonraki;
				bas->sonraki=ekle;
				break;
			}
		}
		if(gecici->sonraki->unvanID == ekle->unvanID && gecici->sonraki->unvanYili > ekle->unvanYili)
		{
			ekle->sonraki=gecici->sonraki;
			gecici->sonraki=ekle;
			break;
		}
		else if(gecici->sonraki->unvanID == ekle->unvanID && gecici->sonraki->unvanYili < ekle->unvanYili)
		{
			while(gecici->sonraki->unvanYili < ekle->unvanYili)
			{
				gecici=gecici->sonraki;
				if(gecici->sonraki->unvanID !=ekle->unvanID)break;
			}
			ekle->sonraki=gecici->sonraki;
			gecici->sonraki=ekle;
			break;
		}
		gecici=gecici->sonraki;
	}
}
int gorevle (akademisyen *gecici)
{
	if(gecici->sonraki!=NULL)
	{
		gorevle(gecici->sonraki);
		gorev--;
	}
	if(gorev>=1)
	{
		if(gecici->unvanID==1)printf("%d Prof. Dr. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==2)printf("%d Doc. Dr. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==3)printf("%d Dr. Ogr. Uyesi %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
		else if(gecici->unvanID==4)printf("%d Ars. Gor. %s %s\n",gecici->sicilNo,gecici->ad,gecici->soyAd);
	}
	
	if(gorev==0)return 0;
}
int main()
{	
	int k;
	listeyap();
	while(1)
	{
		printf("LISTELEME ICIN 1\nGOREVLENDIRME ICIN 2\nSILME ICIN 3\nEKLEME ICIN 4\nCIKMAK ICIN 5 E BASINIZ");
		scanf("%d",&k);
		if(k==1)listele();
		if(k==2)
		{
			printf("gorevdirilecek kisi sayisini girin");	scanf("%d",&gorev);
			gorevle(bas);
		}
		if(k==3)silme();
		if(k==4)ekleme();
		if(k==5)break;
	}
	listele();
	return 0;
}

