#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Listede öðrenci numarasý, ismi ve yaþý olacak.
//Soru 3: Listedeki tüm düðümleri tek tek dolaþan, öðrenci bilgilerini ekrana yazan ve sayan fonk.
//Soru 4: Listede öðrenci adýna göre arama yapan fonk.
//Soru 5: Listede aranan öðrenci adýnýn olduðu düðümden *bir sonraki düðümü* silen fonk.
//Soru 6: Listede bulunan en uzun isimli düðümü bulan, isimle beraber ismin uzunluðunu ekrana yazdýran fonk.

struct student{
	double id;
	int age;
	char name[50];
	struct student *next;
};
typedef struct student stu;		//veri yapisi kýsaltildi.

//fonksiyon prototipleri
void listeyiYazdir(stu*);
void listedeAra(stu*);
stu* sonrakiDugumuSil(stu*);
void enUzunIsim(stu*);
stu* yeniOgrEkle(stu*);

//ana fonksiyon
int main(){
	stu *liste=(stu*)malloc(sizeof(stu));		//liste olusturuldu
	liste=NULL;			int choice;	
	printf("1 - Listeyi ekrana yazdirmak\n");
	printf("2 - Listede ad aramak\n");
	printf("3 - Listede bir isimden sonraki kaydi silmek\n");
	printf("4 - Listedeki en uzun ismi ve uzunlugunu bulmak\n");
	printf("5 - Listeye yeni ogrenci eklemek\n");
	printf("0 - Cikis yapmak\n");
	printf("Yapilacak islemi seciniz: ");
	scanf("%d", &choice);
	while(choice!=0){
		switch(choice){
			case 1: listeyiYazdir(liste);			break;
			case 2: listedeAra(liste);				break;
			case 3: liste=sonrakiDugumuSil(liste);	break;
			case 4: enUzunIsim(liste);				break;
			case 5: liste=yeniOgrEkle(liste);		break;
			default: printf("Uygun numara bulunamadi, tekrar deneyiniz: ");		break;
		}
		printf("Yapilacak islemi seciniz: ");
		scanf("%d", &choice);
	}
	while(liste!=NULL){		//islemlerden sonra bellegi temizleme islemi
		stu *temp=liste;
		liste=liste->next;
		free(temp);
	}
	printf("Cikis yapiliyor...\n");
	return 0;
}

//listenin tamamini ekrana yazdirma
void listeyiYazdir(stu* head){
	if(head==NULL){
		printf("Listeniz bostur.\n\n");
	}
	else{
		stu *temp=head;
		int i=1;
		while(temp!=NULL){
			printf("%d. ogrencinin ismi: %s\n", i, temp->name);
			printf("              yasi: %d\n", temp->age);
			printf("              numarasi: %.lf\n\n", temp->id);
			temp=temp->next;
			i++;
		}
	}
}


//istenilen ismi arama
void listedeAra(stu *head){
	char wanted[50];	int i=1;
	if(head==NULL)		//liste bos ise arama islemi yapilmaz.
		printf("Listeniz bostur.\n\n");	
	else{
		printf("Listede aramak istediginiz ismi giriniz: ");
		scanf("%s", wanted);
		while(head!=NULL){
			if(strcasecmp(head->name, wanted)==0){		//aranilan isim dugumdeki isim mi kontrolu
				printf("Aradiginiz kisi, %d. ogrencidir. Yasi %d ve numarasi %.lf\n\n", i, head->age, head->id);
				break;	}
			else		//degilse sonraki dugume ilerle
				head=head->next;
			i++;
	}
	if(head==NULL)	//listede aranilan isim olmama ihtimali
		printf("Aradiginiz kisi listede bulunmamaktadir.\n\n");
	}
}

//istenilen isimden sonraki dugumu silmek
stu* sonrakiDugumuSil(stu* head){
	if(head==NULL){
		printf("Listeniz bos.\n\n");	return head;
	}
	stu* temp=head;
	char beforeWanted[50];
	printf("Kendisinden sonra gelen ogrenciyi silmek istediginiz ogrenci ismini giriniz: ");
	scanf("%s", beforeWanted);
	while(temp!=NULL){
		if(strcmp(temp->name, beforeWanted)==0){ //isim kontrolu
			if(temp->next==NULL){		//eger silinmek istenen dugumden onceki dugum sonuncu ise silme islemi gerceklesemez
				printf("Bulunan ogrenciden sonra bir ogrenci bulunmamaktadir.\n\n");	return head;}
			else{		//eger silinecek dugumden onceki dugum son degilse silme islemi gerceklestirilir.
				stu *temp2=temp;
				temp2=temp2->next;
				temp->next=temp2->next;
				free(temp2);
				printf("%s isminden sonra gelen ogrenci bilgileri silinmistir.\n\n", beforeWanted);
				return head;
			}
		}
		else
			temp=temp->next;		//isim uyusmuyorsa listede dolanmaya devam edilir.
	}
	if(temp==NULL)		//aranilan isim listede bulunmuyorsa cikis yapilir.
		printf("Aradiginiz kisi listede bulunmamaktadir.\n\n");
		
	return head;
}

void enUzunIsim(stu* head){
	stu *temp;
	int length=0;	char longest[50]; 
	if(head==NULL)
		printf("Listeniz bostur.\n\n");
	else{
		while(head!=NULL){
			if(strlen(head->name)>length){		//eger kontrol edilen dugumdeki ismin karakter sayisi,
				length=strlen(head->name);		//en uzun karakter sayisini tutan length degiskeninin 
				strcpy(longest, head->name);	//degerinden fazlaysa length onun degerini tutmaya baslar.
				temp=head;
			}
			head=head->next;		//degilse eger listede dolasma islemi devam eder.
		}
		printf("Listedeki en uzun isim: %s ve uzunlugu %d karakterdir.\n\n", temp->name, length);
	}
	
}

stu* yeniOgrEkle(stu *head){
	stu* temp= (stu*)malloc(sizeof(stu));
	printf("Yeni eklenecek ogrencinin ismi: "); scanf("%s", temp->name);
	printf("\t\t\t  yasi: "); scanf("%d", &temp->age);
	printf("\t\t\t  numarasi: "); scanf("%lf", &temp->id);	printf("\n");
	if(head==NULL)		//eger liste bossa yeni eklenen ogrenci listenin basý olarak ayarlanýr.
		head=temp;
	else{		//degilse listeye sondan ekleme yapýlýr.
		stu *temp2=head;
		while(temp2->next!=NULL)
			temp2=temp2->next;
		temp2->next=temp;
		temp->next=NULL;
	}
	return head;
}
