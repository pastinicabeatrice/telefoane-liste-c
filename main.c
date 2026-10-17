#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int memorieRAM;
	char* producator;
	float pret;
} Telefon;

typedef struct Nod {
	Telefon inf;
	struct Nod* next;
} Nod;

Telefon copiereTelefon(Telefon t) {
	Telefon c = t;
	c.producator = (char*)malloc(strlen(t.producator) + 1);
	strcpy(c.producator, t.producator);
	return c;
}

Telefon* citireVector(const char* numeFisier, int* nr) {
	*nr = 0;
	FILE* f = fopen(numeFisier, "r");
	if (f == NULL) {
		printf("Fisierul %s nu a putut fi deschis.\n", numeFisier);
		return NULL;
	}
	if (fscanf(f, "%d", nr) != 1 || *nr <= 0) {
		fclose(f);
		*nr = 0;
		return NULL;
	}
	Telefon* vect = (Telefon*)malloc(*nr * sizeof(Telefon));
	char buffer[30];
	for (int i = 0; i < *nr; i++) {
		Telefon t;
		fscanf(f, "%d %29s %f", &t.memorieRAM, buffer, &t.pret);
		t.producator = buffer;
		vect[i] = copiereTelefon(t);
	}
	fclose(f);
	return vect;
}

void afisareTelefon(Telefon t) {
	printf("Memorie: %2d GB | Producator: %-8s | Pret: %8.2f\n", t.memorieRAM, t.producator, t.pret);
}

void afisareVector(Telefon* vect, int nr) {
	for (int i = 0; i < nr; i++) {
		afisareTelefon(vect[i]);
	}
}

void inserareNod(Nod** cap, Telefon tel) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = copiereTelefon(tel);
	nou->next = NULL;
	if (*cap == NULL) {
		*cap = nou;
		return;
	}
	Nod* t = *cap;
	while (t->next != NULL) {
		t = t->next;
	}
	t->next = nou;
}

void inserareSortataDupaPret(Nod** cap, Telefon tel) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->inf = copiereTelefon(tel);
	if (*cap == NULL || (*cap)->inf.pret >= tel.pret) {
		nou->next = *cap;
		*cap = nou;
		return;
	}
	Nod* t = *cap;
	while (t->next != NULL && t->next->inf.pret < tel.pret) {
		t = t->next;
	}
	nou->next = t->next;
	t->next = nou;
}

void traversare(Nod* cap) {
	for (Nod* t = cap; t != NULL; t = t->next) {
		afisareTelefon(t->inf);
	}
}

float pretMediu(Nod* cap) {
	float suma = 0;
	int nr = 0;
	for (Nod* t = cap; t != NULL; t = t->next) {
		suma += t->inf.pret;
		nr++;
	}
	return nr ? suma / nr : 0;
}

void afisareMinimRAM(Nod* cap, int ramMinim) {
	for (Nod* t = cap; t != NULL; t = t->next) {
		if (t->inf.memorieRAM >= ramMinim) {
			afisareTelefon(t->inf);
		}
	}
}

void dezalocareLista(Nod** cap) {
	while (*cap != NULL) {
		Nod* urm = (*cap)->next;
		free((*cap)->inf.producator);
		free(*cap);
		*cap = urm;
	}
}

void dezalocareVector(Telefon** vect, int* nr) {
	for (int i = 0; i < *nr; i++) {
		free((*vect)[i].producator);
	}
	free(*vect);
	*vect = NULL;
	*nr = 0;
}

int main() {
	int nrTel;
	Telefon* vect = citireVector("fisier.txt", &nrTel);

	printf("Telefoane citite in vector:\n");
	afisareVector(vect, nrTel);

	Nod* lista = NULL;
	Nod* listaSortata = NULL;
	for (int i = 0; i < nrTel; i++) {
		inserareNod(&lista, vect[i]);
		inserareSortataDupaPret(&listaSortata, vect[i]);
	}

	printf("\nLista simpla (ordinea din fisier):\n");
	traversare(lista);

	printf("\nLista ordonata crescator dupa pret:\n");
	traversare(listaSortata);

	printf("\nPret mediu: %.2f\n", pretMediu(lista));

	printf("\nTelefoane cu cel putin 16 GB RAM:\n");
	afisareMinimRAM(lista, 16);

	dezalocareLista(&lista);
	dezalocareLista(&listaSortata);
	dezalocareVector(&vect, &nrTel);
	return 0;
}
