/*
Sviluppare una applicazione desktop in ANSI C che permetta di gestire una coda di attesa con priorit�.
La struttura � composta da un vettore che contiene due code, ognuna delle code � caratterizzata da un
livello di priorit� crescente (la coda 0 � prioritaria).
Gli elementi vengono estratti in base al seguente algoritmo:
1. Gli elementi sono sempre estratti dalla coda con priorit� maggiore (coda 0) tranne quando questa � vuota,
	in questo caso vengono estratti dalla coda a priorit� pi� bassa

Implementare le seguenti funzioni
1. caricamento dei dati da un file di ingresso
2. estrazione del primo elelemnto secondo l'algoritmo descritto
3. conteggio degli elementi presenti in ognuna delle due code
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define VERO	1
#define FALSO	0

#define DIMENSIONE_STRINGA	128
// Definizioni relative alla partita

typedef struct s_nodo {
	char nome[DIMENSIONE_STRINGA];
	struct s_node* successivo;
} t_elemento, * pt_elemento;

typedef struct {
	pt_elemento primo;
	pt_elemento ultimo;
} t_coda;

// coda_vuota
//	verifica se la coda � vuota
//	return:		retistuisce vero se la coda � vuota
int coda_vuota(t_coda c) {
	return (c.primo == NULL) ? VERO : FALSO;
}
// coda_aggiungi
//	La funzione inserisce un elemento in coda
//	parametri:	coda da modificare, nome da inserire
//	return:		VERO se corretta, FALSO altrimenti
// Lo studente implementi la funzione
int coda_aggiungi(t_coda* pc, const char* n) {
	pt_elemento aux = (pt_elemento)malloc(sizeof(t_elemento));
	//pt_elemento = t_lista (cioè t_nodo * )
	aux->successivo = NULL;
	strcpy(aux->nome, n);
	if (coda_vuota(*pc))
		pc->primo = pc->ultimo = aux;
	else {
		pc->ultimo->successivo = aux;
		pc->ultimo = aux;
	}
	return VERO;
}
// coda_primo
//	La funzione restituisce il puntatore al primo elemento 
//	parametri:	coda
//	return:		primo elemento o NULL se vuota
char* coda_primo(t_coda c) {
	if (coda_vuota(c))
		return NULL;
	return c.primo->nome;
}
// coda_rimuovi
//	La funzione rimuove il primo elemento della coda
//	parametri:	coda
//	return:		void
void coda_rimuovi(t_coda* pc) {
	if (coda_vuota(*pc))
		return;
	pt_elemento aux = pc->primo;
	if (pc->primo == pc->ultimo)
		pc->primo = pc->ultimo = NULL;
	else
		pc->primo = pc->primo->successivo;
	free(aux);
}
// 1. caricamento dei dati da un file di ingresso
//	carica_dati
//		parametri:	struttura dati, nome del file
//		return:		void
// Lo studente completi L'iimplementazione della funzione
void carica_dati(t_coda c[], const char* nome_file) {
	FILE* f;
	char nome[DIMENSIONE_STRINGA];
	int priorita;
	if ((f = fopen(nome_file, "r")) == NULL) {
		printf("Errore aprendo %s\n", nome_file);
		return;
	}
	while (fscanf(f, "%s%d", nome, &priorita)==2) {
		if (priorita == 0)
			coda_aggiungi(&c[0], nome); //uso c o uso &c[] - se devo assegnare al vettore &c[x]
		// c[] = *c -> è un puntatore a lista! aggiungi chiede *pc, 
		//quindi potrei passare c (che è tutto il vettore = puntatore al primo elemento) 
		//o &c[x] che è l'xesimo posto del vettore.
		else
			coda_aggiungi(&c[1], nome);
	}
	/*while (fscanf(f, "%s%d", nome, &priorita) == 2) {
		coda_aggiungi(&c[priorita], nome);
	}*/
}
// funzione estrai_archivio
//	parametri:	strtuttura dati
//	return:		1 se riuscito, 0 se la coda � vuota
// Lo studente implementi la funzione
int estrai_archivio(t_coda coda_attesa[], char* nome) {
	char buffer[DIMENSIONE_STRINGA];

	if (!coda_vuota(coda_attesa[0])) {
		strcpy(buffer, coda_primo(coda_attesa[0]));
		coda_rimuovi(&coda_attesa[0]);
		printf("\nurgenza : %s ",buffer);
		return 1;
	}
	else{
		strcpy(buffer, coda_primo(coda_attesa[1]));
		coda_rimuovi(&coda_attesa[1]);
		printf("\nnon urgente : %s",buffer);
		return 1;
	}
	return 0;

}
// conteggio_elementi
//	il vettore deve essere allocato nella funzione
//	parametri:	struttura dati, 
//	return:		vettore che contiene il risultato
// Lo studente implementi la funzione
int* conteggio_elementi(t_coda vett[]) {
	//while(l != NULL)  però con le code
	pt_elemento aux;
	int* res = (int*)malloc(sizeof(int) * 2);
	res[0] = 0;
	res[1] = 0;
	//for(i=0;i<n;i++)
	for (aux = vett[0].primo; aux != NULL; aux = aux->successivo) {
		res[0]++;
	}
	for (aux = vett[1].primo; aux != NULL; aux = aux->successivo) {
		res[1]++;
	}
	return res;

}

void stampa(t_coda c[]) {
	pt_elemento aux;
	for (aux = c[0].primo; aux != NULL; aux = aux->successivo) {
		printf("\n%s \t\tUrgente", aux->nome);
	}
	for (aux = c[1].primo; aux != NULL; aux = aux->successivo) {
		printf("\n%s", aux->nome);
	}printf("\n\n");
	// CIOE' UGUALE A 
	for (int i = 0; i < 2; i++) {
		for (aux = c[i].primo; aux != NULL; aux = aux->successivo) {
			printf("\n%s", aux->nome);
		}
	}
}
int main(void) {
	int selezione;
	char buffer[DIMENSIONE_STRINGA];
	t_coda coda_attesa[2] = { {NULL,NULL} };
	int contatore = 0;

	int numero_elementi;
	int* risultato = NULL;
	do {
		printf("\n\n1. caricamento dei dati da un file di ingresso\n");
		printf("2. estrazione del primo elelemnto secondo l'algoritmo descritto\n");
		printf("3. conteggio degli elementi presenti in ognuna delle due code\n");
		printf("0. fine\n");
		printf(">>> ");
		scanf("%d", &selezione);
		switch (selezione) {
		case 0:
			printf("fine programma\n");
			break;
		case 1:
			// Lo studente implementi quanto necessario a svolgere le seguenti operazioni
			// 1. richiesta del nome del file da cui caricare i dati
			printf("Nome del file >> ");
			scanf("%s", buffer);
			// 2. chiamata della funzione carica_dati
			carica_dati(coda_attesa, buffer);
			// da completare
			break;
		case 2:
			// Scrivere il codice necessario ad implementare l'estrazione di un elementi dalla
			// struttura dati.
			// 1.	implementare quanto necessario ad acquisire il numero di elementi
			//		da estrarre
			// 2.	scrivere il codice per estrarre il numero di elementi richiesto e stamparne
			//		il contenuto liberando le risorse non pi� necessarie
			printf("Inserire il numero di elementi da estrarre: ");
			scanf("%d", &numero_elementi);
			for (int i = 0; i < numero_elementi; i++) {
				estrai_archivio(coda_attesa, buffer);
			}

			break;
		case 3:
			// Lo studente implementi quanto necessario a chiamare la funzione conteggio elementi
			risultato=conteggio_elementi(coda_attesa);
			// stampare il risultato e deallocare se necessario
			printf("Coda urgente : %d    Coda NUrgente : %d", risultato[0], risultato[1]);
			// da completare
			break;
		case 4:
			stampa(coda_attesa); 
		}
	} while (selezione != 0);
}
