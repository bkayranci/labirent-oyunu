#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "oyun.h"
#include "fonksiyonlar.c"


int main(){
	
	
	int x, y, rx,ry,cx,cy,k,i,yon;
	float zamanFarki;
	char tus;
	
	// Harita[][] dizisi olustur
	harita=(haritaYapisi **)malloc(BOYUT * sizeof(haritaYapisi *));
	for(k=0;k<BOYUT;k++){
		harita[k]=(haritaYapisi *)malloc(BOYUT * sizeof(haritaYapisi));
	}
	
	
	if(harita==NULL){
    printf("Basarisiz! \n");
    return 1;
	}
	
	// canavar[] dizi olustur
	canavar=(canavarYapisi *)malloc(CANAVAR_SAYISI*sizeof(canavarYapisi));
	if(canavar==NULL){
    printf("Basarisiz! \n");
    return 1;
	}
	
	

	
	srand(time(NULL));
	
	// Duvar cerceve
	for(x=0;x<BOYUT;x++){
		for(y=0;y<BOYUT;y++){
			harita[x][y].x=x;
			harita[x][y].y=y;
			
			if(x==0 || x==BOYUT-1 || y==0 || y==BOYUT-1){
				harita[x][y].ic=DUVAR;
			}
			else{
				harita[x][y].ic=YOL;
			}
			
		}
	}
		
	// canavarlar olustur ve haritaya isle
	for(i=0;i<CANAVAR_SAYISI;i++){
		
		rx=1+rand()%(BOYUT-2);
		ry=1+rand()%(BOYUT-2);
	
		if(harita[rx][ry].ic==YOL){
			canavar[i].x=rx;
			canavar[i].y=ry;
			harita[rx][ry].ic=CANAVAR;
		}
		else{
			i--;
		}
	}
	

	// Rastgele duvar at
	for(i=0;i<DUVAR_SAYISI;i++){
		
		rx=1+rand()%(BOYUT-2);
		ry=1+rand()%(BOYUT-2);
		printf("(%d,%d)",rx,ry);
		if(harita[rx][ry].ic==YOL){
			harita[rx][ry].ic=DUVAR;
		}		
	}
	
	// Rastgele puan  at
	for(i=0;i<PUAN_SAYISI;i++){
		
		rx=1+rand()%(BOYUT-2);
		ry=1+rand()%(BOYUT-2);
		
		if(harita[rx][ry].ic==YOL){
			harita[rx][ry].ic=PUAN;
		}
		else{
			i--;
		}		
	}
	
	// Rastgele oyuncu at
	rx=1+rand()%(BOYUT-2);
	ry=1+rand()%(BOYUT-2);
	oyuncu.x=rx;
	oyuncu.y=ry;
	
		while(harita[rx][ry].ic!=YOL){
			rx=1+rand()%(BOYUT-2);
			ry=1+rand()%(BOYUT-2);
		}
		harita[rx][ry].ic=OYUNCU;

	
	
	haritaGoster();
	
	
	
	zaman1 = clock();
	zaman2 = clock();
	
	while (1 == 1){
		zaman2 = clock();
		if (_kbhit()){
			
			tus = getch();

			switch (tus){
			case 75:	// Sol Tus
				if (oyuncu.y != 0){

					if (gidebilirMi(oyuncu.x, oyuncu.y - 1) == 1){
						harita[oyuncu.x][oyuncu.y].ic = YOL;
						harita[oyuncu.x][oyuncu.y - 1].ic = OYUNCU;
						oyuncu.y--;

					}
					
					

				}
				haritaGoster();
				if(bittiMi()==1){
					return 0;
				}
				else if(bittiMi()==2){
					return 0;
				}
				
				break;
			case 77:	// Sag Tus
				if (oyuncu.y != BOYUT - 1){
					if (gidebilirMi(oyuncu.x, oyuncu.y + 1) == 1){
						harita[oyuncu.x][oyuncu.y].ic = YOL;
						harita[oyuncu.x][oyuncu.y + 1].ic = OYUNCU;
						oyuncu.y++;
					}
				
					
				
				}
				haritaGoster();
				if(bittiMi()==1){
					return 0;
				}
				else if(bittiMi()==2){
					return 0;
				}
				break;
			case 72:	// Yukari Tus
				if (gidebilirMi(oyuncu.x - 1, oyuncu.y) == 1){
					harita[oyuncu.x][oyuncu.y].ic = YOL;
					harita[oyuncu.x - 1][oyuncu.y].ic = OYUNCU;
					oyuncu.x--;

				}
			
				
				haritaGoster();
				if(bittiMi()==1){
					return 0;
				}
				else if(bittiMi()==2){
					return 0;
				}
				break;
			case 80:	// Asagi Tus
				if (gidebilirMi(oyuncu.x + 1, oyuncu.y) == 1){
					harita[oyuncu.x][oyuncu.y].ic = YOL;
					harita[oyuncu.x + 1][oyuncu.y].ic = OYUNCU;
					oyuncu.x++;

				}
			
				
				haritaGoster();
				if(bittiMi()==1){
					return 0;
				}
				else if(bittiMi()==2){
					return 0;
				}
				
				break;
			case 3: return 0;
			}
		}
		else{
		

			zamanFarki = zaman2 - zaman1;
			zamanFarki = zamanFarki / 1000;
			if (zamanFarki > 6-OYUN_HIZI) {
			zaman1 = clock();
					
				for (i = 0; i < CANAVAR_SAYISI; i++) {
					cx = canavar[i].x;
					cy = canavar[i].y;
					
					
					
					
					//Rastgele degil oyuncuyu takip etme
					if(cx>oyuncu.x && cy>oyuncu.y){	// canavar sag altta
						yon=1+rand()%2;
					}
					else if(cx>oyuncu.x && cy<oyuncu.y){	// canavar sol altta
						yon=rand()%2;
					}
					else if(cx<oyuncu.x && cy<oyuncu.y){	// canavar sol ustte ?
						yon=rand()%4;
					}
					else if(cx<oyuncu.x && cy>oyuncu.y){	// canavar sag ustte
						yon=2+rand()%2;
					}
					else if(cx==oyuncu.x && cy<oyuncu.y){	// canavar solda
						yon=0;
					}
					else if(cx==oyuncu.x && cy>oyuncu.y){	// canavar sagda
						yon=2;
					}
					else if(cy==oyuncu.y && cx<oyuncu.x){	// canavar ustte
						yon=3;
					}
					else if(cy==oyuncu.y && cx>oyuncu.x){	// canavar altta
						yon=1;
					}
					else{
						yon=rand()%4;
					}
					
					
					
					
				
					if (yon == 0){	// Saga git
						if (gidebilirMi(cx, cy + 1) == 1){
							harita[cx][cy].ic = YOL;
							harita[cx][cy + 1].ic = CANAVAR;
							canavar[i].y++;
			
						}
						if(harita[cx][cy+1].ic==OYUNCU){
							can--;
							if(bittiMi()==1){
								return 0;
							}
							else if(bittiMi()==2){
								return 0;
							}
						}
						
					}
					else if (yon == 1){	// Yukari git
						if (gidebilirMi(cx - 1, cy) == 1){
							harita[cx][cy].ic = YOL;
							harita[cx - 1][cy].ic = CANAVAR;
							canavar[i].x--;
						}
						if(harita[cx-1][cy].ic==OYUNCU){
							can--;
							if(bittiMi()==1){
								return 0;
							}
							else if(bittiMi()==2){
								return 0;
							}
						}
						
					}
					else if (yon == 2){	// Sola git
						if (gidebilirMi(cx, cy - 1) == 1){
							harita[cx][cy].ic = YOL;
							harita[cx][cy - 1].ic = CANAVAR;
							canavar[i].y--;
						}
						if(harita[cx][cy-1].ic==OYUNCU){
							can--;
							if(bittiMi()==1){
								return 0;
							}
							else if(bittiMi()==2){
								return 0;
							}
						}
				
					}
					else if (yon == 3){	// Asagi git
						if (gidebilirMi(cx + 1, cy) == 1){
							harita[cx][cy].ic = YOL;
							harita[cx + 1][cy].ic = CANAVAR;
							canavar[i].x++;
						}
						if(harita[cx+1][cy].ic==OYUNCU){
							can--;
							if(bittiMi()==1){
								return 0;
							}
							else if(bittiMi()==2){
								return 0;
							}
						}
					
					}
			
				}
				haritaGoster();
			}
		}

	}
	return 0;
}
