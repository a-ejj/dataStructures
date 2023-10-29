#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Listeye rastgele eklenmiþ 100 sayýnýn büyükten küçüðe sýralanmasý

struct dugum{
	int data; struct dugum *next;
};
typedef struct dugum node;

//fonksiyon prototipleri
node *editList(node *head);
void traverseList(node*);
node *addNode(node* , int);

//ana fonksiyon
int main(){
	srand(time(NULL));		//random sayi uretme fonk. cagirilir.
	node *head=(node*)malloc(sizeof(node));		//liste basi olusturulur.
	head->next=NULL;		
	head->data=rand();		//ilk eleman olusturulur.
	int i=1, n;
	while(i<100){		//kalan 99 eleman atanir.
		n=rand();
		head=addNode(head, n);		
		i++;
	}
	printf("Siralanmadan once liste:\n");
	traverseList(head);
	printf("\n\n");
	head=editList(head);
	printf("Siralandiktan sonra liste:\n");
	traverseList(head);
	while(head!=NULL){		//islemlerden sonra bellegi temizleme islemi
		node *temp=head;
		head=head->next;
		free(temp);
	}
	
	return 0;
}


node* addNode(node *head, int veri){

	node *temp=(node*)malloc(sizeof(node));
	temp->data=veri;		//veri gecici degiskene atanir.
	temp->next=head;		//gecici degiskenin sonraki gostergesi listenin basi olarak alinir.
	head=temp;				//listenin basi gecici degiskene atanir.
	return head;
}

void traverseList(node *head){
	if(head->data==-1)
		printf("Liste bos...\n");		//Liste bos ise dolanma islemi yapilmaz.
	else
		while(head!=NULL){
			int i, j;
			for(i=0; i<10; i++){				//10*10 seklinde okuma kolayligi icin ayrilmistir.
				for(j=0; j<10; j++){
					printf("%d	", head->data);
					head=head->next;
				}
				printf("\n");
			}
		}
}

node *editList(node *head){
	//bubble sort ile siralama islemi yapilir.
	int i, j, temp2;
	node *temp=head;
	for(i=0; i<99; i++, temp=head){
		for(j=0; j<99-i; j++, temp=temp->next){
			if(temp->data>temp->next->data){
				temp2=temp->data;
				temp->data=temp->next->data;
				temp->next->data=temp2;
			}
		}
	}
}
