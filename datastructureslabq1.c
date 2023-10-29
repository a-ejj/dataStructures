#include <stdio.h>
#include <stdlib.h>

//Klavyeden -1 girilinceye kadar girilen sayýlardan tek olanlarý listenin baþýna, çift olanlarý listenin sonuna ekleyen program.

struct nde{
	int data;
	struct nde *next;
};
typedef struct nde node;

node *addNode(node*);
node *addLast(node*, int);
node *addFront(node*, int);
void traverseList(node*);

int main(){
	node *head=(node*)malloc(sizeof(node));
	head->data=-1;
	head->next=NULL;
	printf("Liste elemanlarini giriniz. \n(-1 girildikten sonra program sonlanacaktir.)\n\n--->");
	head=addNode(head);		//dugum ekleme islemi
	traverseList(head);		//listeyi ekrana yazdýrma
	
	while(head!=NULL){		//islemler bittikten sonra listeyi bellekten salma islemi
		node *temp2=head;
		head=head->next;
		free(temp2);
	}
	return 0;
}

node* addNode(node *head){
	int n;
	scanf("%d", &n);
	while(n!=-1){
		if(head->data==-1){
			head->data=n;
		}
		else{
			if(n%2==0)
				head=addLast(head, n);		//eklenecek eleman cift ise sona,
			else
				head=addFront(head, n);		//tek ise bastan eklenir.
		}
		printf("--->");
		scanf("%d", &n);	
	}
	printf("Eleman ekleme islemi sona erdiriliyor...\n\n");
	return head;
}


node* addFront(node *head, int veri){
	node *temp=(node*)malloc(sizeof(node));
	temp->data=veri;	//gecici degiskene veriler atanir.
	temp->next=head;	//gecici degisken head'e baglanir.
	head=temp;			//listenin basi, gecici degiskene atanir.
	return head;
}

node* addLast(node *head, int veri){
	node *temp=(node*)malloc(sizeof(node));
	temp->data=veri;		//gecici degiskene veriler atanir.
	temp->next=NULL;		//gecici degiskenin sonraki dugumu NULL'a ayarlanir.
	node *temp2=head;		//listenin basini kaybetmemek icin yeni bir gecici degisken olusturulur.
	while(temp2->next!=NULL)
		temp2=temp2->next;		//listenin son elemanýna gelene kadar kaydýrma yapýlýr.
	temp2->next=temp;			//listenin son elemanýný sonraki gosterimi gecici degiskene ayarlanýr. 
								//boylelikle listeye sondan eleman eklenmis olur.
	return head;
}

void traverseList(node *head){
	if(head->data==-1)
		printf("Liste bos...\n");
	else{
		printf("Listenin son hali:\n");
		while(head!=NULL){
			printf("%d	", head->data);		//Listede dolanýlarak ekrana veriler yazdýrýlýr.
			head=head->next;
		}
	}
}
