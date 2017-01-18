clock_t zaman1, zaman2;

typedef struct oyuncuYapisi{
	int x;
	int y;
}oyuncuYapisi;

typedef struct canavarYapisi{
	int x;
	int y;
}canavarYapisi;

typedef struct haritaYapisi{
	int x;
	int y;
	char ic;
}haritaYapisi;

haritaYapisi **harita;
canavarYapisi *canavar;
oyuncuYapisi oyuncu;
int puan=0;
int can=CAN_SAYISI;



// Harita sil ve goster
void haritaGoster(){
	int x,y;
	system("cls");

	for(x=0;x<BOYUT;x++){
		for(y=0;y<BOYUT;y++){
			printf("%c",harita[x][y].ic);
		}
		printf("\n");
	}
	
	printf("\nCAN: %d\tPUAN: %d",can,puan);
}

int gidebilirMi(int cx, int cy){
	if(harita[cx][cy].ic==YOL){
		return 1;
	}
	else if(harita[cx][cy].ic==PUAN){
		puan+=10;
		return 1;
	}
	else if(harita[cx][cy].ic==CANAVAR){
		can--;
		return 0;
	}
	else{
		return 0;
	}
	
}

int bittiMi(){
	int k;
	if (puan==PUAN_SAYISI*10){
		printf("\nKazandiniz!\nPUAN: %d",puan);		
		return 1;
	}
	else if(can==0){
		printf("\nCaniniz bitti!\nPUAN: %d",puan);
		return 2;
	}
	return 0;
}
