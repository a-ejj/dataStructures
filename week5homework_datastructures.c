#include <stdio.h>
#include <stdlib.h>
#define stack_size 10

typedef struct stack{
	int top;
	char data[stack_size];
}st;

int count=0;
void reset(st*);
void push(st*, char);
char pop(st*);
int isEmpty(st*);
int isFull(st*);
void printAll(st*);

int main(){
	FILE *filePtr;	st s;	char c;
	if((filePtr=fopen("text.txt", "r"))==NULL)		//dosyanin var olup olmama ihtimali kontrol ediliyor.
		printf("Dosya bulunamadi.\n");
	else{
		reset(&s);		//stack yapisi olusturuluyor.
		while(!feof(filePtr)){		//dosyanin sonuna ulasana kadar...
			c=fgetc(filePtr);		//dosyadan karakter alinir.
			switch(c){
				case '(': push(&s, c);	break;		// acma parantezi ise stack'e alinir.
				case '[': push(&s, c);	break;		// koseli acma parantezi ise stack'e alinir.
				case '{': push(&s, c);	break;		// suslu acma parantezi ise stack'e alinir.
				case ')': if(pop(&s)=='(')	{printAll(&s); printf("\n"); continue;}	
						  //eger stack'in en ustteki elemani elde tutulan parantezle uyusuyorsa
						  //en ustteki karakter stack'ten cikarilir (pop) ve dosya okunmaya devam eder.
						  else{
						  	printf("() hatasi!\n");	 fclose(filePtr);	exit(1); }		//eger uyusmuyorsa hata verir ve dosya kapatilarak program sonlandirilir.
				case ']': if(pop(&s)=='[')	{printAll(&s); printf("\n"); continue;}		//bir onceki case yapisinin aciklamasi bu case icin de gecerlidir.
						  else{
							printf("[] hatasi!\n");	 fclose(filePtr);	exit(1); }
				case '}': if(pop(&s)=='{')	{printAll(&s); printf("\n"); continue;}		//bir onceki ve ondan onceki case yapisina yazilan durumlar,
						  else{															//bu case icin de gecerlidir.
						  	printf("{} hatasi!\n");	 fclose(filePtr);	exit(1); }
				default: break;		//eger parantezler disinda baska bir karaktere rastlanirsa dikkate alinmaz ve dosyada bir sonraki karakterden devam edilir.
			}
			printAll(&s);	printf("\n");}
		if(!isEmpty(&s))
			printf("Acikta parantez var!\n");		//eger stack'te hala veri varsa acikta parantez var demektir.
		else
			printf("Dosyada hata bulunmadi!\n");	//eger stack bos ise dosyada hata yok demektir.
		fclose(filePtr);		//dosya ile islem bitince dosya kapatilip pointer'i serbest birakiriz.
	}
	return 0;
}

void reset(st* array){		//stack yapisini reset fonksiyonuyla olustururuz.
	array->top=-1;
}

void push(st* array, char a){		//stack yapisina eleman ekleme fonksiyonu.
	if(isFull(array))				//eger stack yapisi dolu ise eleman ekleme islemi yapilamaz.
		printf("Stack dolu.\n");
	else{
		array->top++;			//top degiskeni eklenecek elemanin indisini tutar.
		array->data[array->top]=a;		//data dizisine yeni eleman girisi yapilir.
		count++;		//ekrana yazdirmak icin eleman sayisini tutar.
	}
}

char pop(st* array){		//stack yapisindan eleman cikarma fonksiyonu.
	if(isEmpty(array))		//eger stack bos ise eleman cikarma islemi yapilamaz.
		printf("Stack bos.\n");
	else{
		count--;			//ekrana yazdirmak icin eleman sayisini tutar.
		return array->data[array->top--];		//stack yapisindaki en ustten cikarilan eleman dondurulur. 
	}
}

int isEmpty(st* array){		//stack yapisinin bos olup olmadigini kontrol etme fonksiyonu.
	if(array->top==-1)
		return 1;
	else
		return 0;
}
int isFull(st* array){		//stack yapisinin dolu olup olmadigini kontrol etme fonksiyonu.
	if(array->top==stack_size-1)
		return 1;
	else
		return 0;
}
void printAll(st* array){		//parantez kontrol etme sirasinda stack'e elemanlar nasil eklenip cikarildigini gormek icin,
	int i;						//stack'i ekrana yazdirma fonksiyonu.
	if(isEmpty(array))			
		printf("Stack bos.\n");		//ekrana stack yapisi seklinde -en alttaki eleman en altta olacak sekilde- yazdirilir. 
	else
		for(i=count-1; i>-1; i--)
		printf("%c\n", array->data[i]);
}
