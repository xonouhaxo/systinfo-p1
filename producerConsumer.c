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
void* producer(void* arg)
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

	return NULL;	
}

// Consommateur
void* consumer(void* arg)
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

	return NULL;
}

int main (int argc, char *argv[])
{
	//recevoir arguments de la ligne de commande
	if (argc < 3)
	{
		printf("Cette fonction ne prend que deux arguments\n");
		return (EXIT_FAILURE);
	}

	n_prod = atoi(argv[1]);
	n_cons = atoi(argv[2]);

	sem_init(&empty, 0, BUFFER); // buffer vide
	sem_init(&full, 0, 0);	// buffer vide
	pthread_mutex_init(&mutex_consumer, NULL);
	pthread_mutex_init(&mutex_producer, NULL);

	pthread_t *prod_thread = malloc(sizeof(pthread_t) * n_prod);
	pthread_t *cons_thread = malloc(sizeof(pthread_t) * n_cons);

	//lancement des threads

	for (int i = 0; i < n_prod; i++)
	{
		pthread_create(&prod_thread[i], NULL, producer, NULL);
	}
	for (int i = 0; i < n_cons; i++)
	{
		pthread_create(&cons_thread[i], NULL, consumer, NULL);
	}

	//attente de la fin des threads

	for (int i = 0; i < n_prod; i++)
	{
		pthread_join(prod_thread[i], NULL);
		printf("prod %d is free\n", i);
	}
	for (int i = 0; i < n_cons; i++)
	{
		pthread_join(cons_thread[i], NULL);
		printf("cons %d is free\n", i);
	}
}	
