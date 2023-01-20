#define MAXS 100
#define MAXDIAG 3
#define MAXELEM 5
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
	char nome[MAXS];
	int tipologia,
		dir_in,
		dir_out,
		req_prec,
		fin,
		dif;
	float val;
} Elemento;

typedef struct {
	int arr[5];
	int size;
	float val;
	int dif;
	int bonus;
} Diagonale;

Elemento* leggiFile(FILE* fin, int* nElem){
	fscanf(fin, "%d\n", nElem);
	Elemento* elementi = malloc(sizeof(Elemento) * *nElem);
	for(int i = 0; i < *nElem; i++){
		fscanf(fin, "%s %d %d %d %d %d %f %d\n", elementi[i].nome, &elementi[i].tipologia, &elementi[i].dir_in, &elementi[i].dir_out, &elementi[i].req_prec,&elementi[i].fin, &elementi[i].val,&elementi[i].dif );
	}
	return elementi;
}
int c = 0;
void store(Diagonale* sets, int* sol, int n, float val, int dif, int bonus){
	for(int i = 0; i < n; i++){
		sets[c].arr[i] = sol[i];
		sets[c].size = n;
		sets[c].val = val;
		sets[c].dif = dif;
		sets[c].bonus = bonus;
	}
	c++;
}

void powerset(Elemento* elementi, int* sol, int dd, int nElem, int n, int dif, int flagAcrobatico, Diagonale* sets, float val){
	if(n>= MAXELEM && flagAcrobatico){
		store(sets, sol, n,val, dif, elementi[sol[n-1]].fin && elementi[sol[n-1]].dif >= 8);	
	}

	for(int i = 0; i < nElem; i++){
		int tmpFlagAcrobatico = flagAcrobatico;
		if(elementi[i].tipologia > 0)
			tmpFlagAcrobatico = 1;
		if((n == 0 || (elementi[sol[n-1]].dir_out == elementi[i].dir_in) && elementi[sol[n-1]].fin == 0) && (dif + elementi[i].dif) <= dd){
			if(n==0 && elementi[i].dir_in != 1)
				continue;
			sol[n] = i;
			powerset(elementi, sol, dd, nElem, n+1, dif + elementi[i].dif, tmpFlagAcrobatico, sets,val + elementi[i].val); if(tmpFlagAcrobatico){
				if(n!=0 || elementi[i].req_prec == 0)
					store(sets, sol, n+1,val + elementi[i].val, dif + elementi[i].dif, elementi[i].fin && elementi[i].dif >=8);	
			}
		}

	}		

}
float getScore(Diagonale* diagonali, Elemento* elementi, int* sol, int dp){
	float score = 0;
	int diff = 0;
	int bonus = 0;
	int flagAcrobaticoAvanti = 0, flagAcrobaticoIndietro = 0;
	int maxAcrInSeq = 0;
	for(int i =0; i< MAXDIAG; i++){
		int acrInSeq = 0;
		diff += diagonali[sol[i]].dif;
		if(diff > dp)
			return 0;
		for(int j =0; j < diagonali[sol[i]].size; j++)
			if(elementi[diagonali[sol[i]].arr[j]].tipologia > 0){
				acrInSeq++;
				if(elementi[diagonali[sol[i]].arr[j]].tipologia == 1)
					flagAcrobaticoAvanti = 1;
				else if(elementi[diagonali[sol[i]].arr[j]].tipologia ==2)
					flagAcrobaticoIndietro = 1;
			}
			else {
				acrInSeq = 0;
			}
		if(i == MAXDIAG -1){
			if(elementi[diagonali[sol[i]].arr[diagonali[sol[i]].size -1]].dif >= 8)

				score += diagonali[sol[i]].val * 1.5;
			else 
				score += diagonali[sol[i]].val;
		}

		else 

			score += diagonali[sol[i]].val;
		if(acrInSeq > maxAcrInSeq)
			maxAcrInSeq = acrInSeq;

	}
	if(maxAcrInSeq < 2)
		return 0;
	if(flagAcrobaticoAvanti && flagAcrobaticoIndietro)
		return score;
	else
		return 0;
}

void disp_rip(Elemento* elementi, Diagonale* diagonali, int* sol, int nDiag, int dp, int n, int* maxDisp, float* maxp, float score){
	if(score > dp){
		return;
	}
	if(n >= MAXDIAG){
		 float val = getScore(diagonali,elementi, sol,dp);
		 if(val > *maxp){
			 *maxp = val;
			 
			 
			 printf("\nNUOVO MASSIMO: %.2f\n", *maxp);
			 for(int i = 0; i < MAXDIAG; i++){
				 printf("\t");
				 maxDisp[i] = sol[i];
				 for(int j =0; j< diagonali[sol[i]].size; j++)
					 printf("%s ",elementi[diagonali[sol[i]].arr[j]].nome);

				 printf("%f \n", diagonali[sol[i]].val);
			 }
			 printf("\n");
		 }
		return;
	}
	for(int i = 0; i<nDiag; i++){
		sol[n] = i;
		disp_rip(elementi, diagonali, sol, nDiag, dp, n+1, maxDisp, maxp, score + diagonali[sol[i]].val);

	}



}



float getMax(Elemento* elementi, int nElem, int dd, int dp){
	int* sol = (malloc(sizeof(int) * MAXELEM ));
	int* sol2 = (malloc(sizeof(int) * MAXDIAG ));
	int* maxSol = (malloc(sizeof(int) * MAXDIAG ));
	float maxVal=0;
	Diagonale* diagonali = malloc(sizeof(Diagonale) * pow(nElem, MAXELEM));
	
	powerset(elementi, sol, dd, nElem, 0, 0, 0, diagonali, 0);
	disp_rip(elementi, diagonali, sol2, c, dp, 0, maxSol, &maxVal, 0);
	if(maxVal != 0){
		printf("MASSIMO TROVATO: %.2f\n", maxVal);
		for(int i = 0; i < MAXDIAG; i++){
			printf("\t");
			 for(int j =0; j< diagonali[maxSol[i]].size; j++)
				 printf("%s ",elementi[diagonali[maxSol[i]].arr[j]].nome);

			 printf("%.3f \n", diagonali[maxSol[i]].val);
		}
	}
	else printf("Non sono state trovate configurazioni compatibili\n");
	free(sol);
	free(sol2);
	free(maxSol);

	return maxVal;

	

}


int main(){
	char name[100];
	FILE* fin;
	printf("Inserisci nome del file da leggere: \n");
	scanf(" %s", name);
	fin = fopen(name, "r");
	if(fin == NULL){
		printf("Non è stato possibile leggere il file!\n");
		return -1;
	}
	int nElem;
	int dd, dp;
	Elemento* elementi = leggiFile(fin, &nElem);
	printf("Inserisci DD: ");
	scanf(" %d", &dd);

	printf("Inserisci DP: ");
	scanf(" %d", &dp);

	getMax(elementi, nElem, dd, dp);


	fclose(fin);

}
