#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

sem_t sem1, sem2, sem3, sem4, sem5;
pthread_mutex_t printLine_sync;
int remaining=6, line=0;

void printLine (char *urun) {

	pthread_mutex_lock(&printLine_sync);

	if (line==0)
		printf("-->> Başlangıç !! \n");
    
	if (urun=="Cilek" || urun=="Muz" || urun=="Kivi")
		printf("%2d. (meyve) ", ++line);
    
	else if (urun=="Camasir suyu" || urun=="Deterjan")    
		printf("%2d. (temizlik) ", ++line);
    
	else if (urun=="Kofte" || urun=="Tavuk" || urun=="Balik")    
		printf("%2d. (et) ", ++line);
    
	else if (urun=="Mercimek" || urun=="Pirinc")    
		printf("%2d. (baklagil) ", ++line);
    
	else if (urun=="Baklava" || urun=="Kadayif" || urun=="Kunefe")    
		printf("%2d. (tatli) ", ++line);
    
	printf("%s", urun);
    
	if (line > 6) {    
		if (remaining==0)        
			printf("\t--> Goreve hazirim! ");
        
		else
			printf("\t\t--> Kalan oge sayisi: %d", remaining--);           
        
		if(remaining==0)        
			sem_post(&sem_kivi);   		     
    	}

	printf("\n");
	pthread_mutex_unlock(&printLine_sync);
    
}

void *meyve (void *p) {
	
	printLine("Çilek");
	sem_post(&sem1);
	printLine("Muz");
	
	sem_wait(&sem5);
	printLine("Kivi");

	printf("[UYARI] Meyve ürünlerinin tümü alındı !! \n");

	pthread_exit(0);

}
void *temizlik (void *p) {

	sem_wait(&sem1);
	printLine("Çamaşır suyu");
	printLine("Deterjan");
	sem_post(&sem3);

	printf("[UYARI] Temizlik ürünlerinin tümü alındı !! \n");

	pthread_exit(0);

}
void *et (void *p) {

	sem_wait(&sem4);
	printLine("Tavuk");
	printLine("Köfte");
	sem_wait(&sem3);
	printLine("Balık");

	printf("[UYARI] Et ürünlerinin tümü alındı !! \n");

	pthread_exit(0);

}
void *baklagil (void *p) {

	printLine("Mercimek");
	printLine("Pirinç");

	printf("[UYARI] Baklagil ürünlerinin tümü alındı !! \n");

	pthread_exit(0);
}
void *tatli (void *p) {

	printLine("Baklava");
	printLine("Kadayıf");
	sem_post(&sem4);
	printLine("Künefe");

	printf("[UYARI] Tatlı ürünlerinin tümü alındı !! \n");

	pthread_exit(0);
}

int main() {

	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);
	sem_init(&sem3, 0, 0);
	sem_init(&sem4, 0, 0);
	sem_init(&sem5, 0, 0);
	pthread_mutex_init(&printLine_sync, NULL);
	
	pthread_t p_meyve, p_temizlik, p_et, p_baklagil, p_tatli;

	pthread_create(&p_meyve, NULL, meyve, NULL);
	pthread_create(&p_temizlik, NULL, temizlik, NULL);
	pthread_create(&p_et, NULL, et, NULL);
	pthread_create(&p_baklagil, NULL, baklagil, NULL);
	pthread_create(&p_tatli, NULL, tatli, NULL);

	pthread_join(p_meyve, NULL);
	pthread_join(p_temizlik, NULL);
	pthread_join(p_et, NULL);
	pthread_join(p_baklagil, NULL);
	pthread_join(p_tatli, NULL);

	pthread_mutex_destroy(&printLine_sync);

	sem_destroy(&sem1);
	sem_destroy(&sem2);
	sem_destroy(&sem3);
	sem_destroy(&sem4);
	sem_destroy(&sem5);
    
}
