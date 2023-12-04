#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Initialisation
#define BUFFER 8 // places dans le buffer
#define MAX_PRODUCT 8192 // nombre de produits à produire


sem_t empty;
sem_t full;
pthread_mutex_t mutex_producer;
pthread_mutex_t mutex_consumer;
int n_prod;
int n_cons;
int prod;
int cons;

// Producteur
void* producer(void)
{
	while (prod < MAX_PRODUCT)
	{
		pthread_mutex_lock(&mutex_producer);
		if (prod >= MAX_PRODUCT)
		{
			pthread_mutex_unlock(&mutex_producer);
			break;
		}
		sem_wait(&empty); // attente d'une place libre
		prod++;
		pthread_mutex_unlock(&mutex_producer);
		sem_post(&full); // une place remplie en plus
	}
	for (int i = 0; i < 10000; i++)
	{
		//simulation de traitement
	}
	
}

// Consommateur
void* consumer(void)
{
	while (cons < MAX_PRODUCT)
	{
		pthread_mutex_lock(&mutex_consumer);
		if (cons >= MAX_PRODUCT)
		{
			pthread_mutex_unlock(&mutex_consumer);
			break;
		}
		sem_wait(&full); // attente d'une place remplie
		cons++;
		pthread_mutex_lock(&mutex_consumer);
		sem_post(&empty); // une place libre en plus
	}
	for (int i = 0; i < 10000; i++)
	{
		//simulation de traitement
	}
}

int main (int argc, char *argv[])
{

	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, BUFFER); // buffer vide
	sem_init(&full, 0, 0);	// buffer vide

	//recevoir arguments de la ligne de commande

}
