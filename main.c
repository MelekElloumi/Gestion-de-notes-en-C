#include <stdio.h>
#include <stdlib.h>
#include "econio.h"
#include "econio.cpp"

typedef struct{
    int code;
    char section[11];
    char intitule[31];
    float coef;
}Matiere;

typedef struct{
    int carte;
    char section[11];
    char nom[31];
    char prenom[31];
}Etudiant;

typedef struct{
    int carte;
    int code;
    float note;
}Notes;

FILE* matiere;
FILE* etudiant;
FILE* notes;

//Effet de transition entre les interfaces
void transition(){
	int i,j;
	for (i=2;i<=30;i++)
		for (j=1;j<=110;j++)
		{
			gotoxy(j,i);
			printf("%c",178);
		}
}
//Affichage du menu
void menu(){
    printf("******************\n");
    printf("1- Ajouter un %ctudiant\n",130);
    printf("2- Ajouter une mati%cre\n",138);
    printf("3- Ajouter une note\n");
    printf("4- Moyenne %ctudiant\n",130);
    printf("5- Mise %c jour note %ctudiant\n",133,130);
    printf("6- Bulletin des notes\n");
    printf("7- Quitter\n");
    printf("******************\n");

}
//creation des fichiers si ils n'existent pas
void creerFichier(FILE *f,char *ch){
    f=fopen(ch,"r");
    if (f==NULL){
        fclose(f);
        f=fopen(ch,"w");
    }
    fclose(f);
}
//verifie si le code existe dans le fichier ou non
int existe1(int d,FILE *f,char *ch1){
    f=fopen(ch1,"r");
    char ch[76];
    while(fgets(ch,76,f)){
        int n;
        sscanf(ch,"%5d",&n);
        if (d==n)
            return ftell(f);
    }
    fclose(f);
    return 0;
}
//verfie si la note de l'etudiant d de la matiere e existe
int existe2(int d, int e, FILE *f){
    f=fopen("notes.txt","r");
    char ch[20];
    while(fgets(ch,20,f)){
        int n,m;
        sscanf(ch,"%5d%5d",&n,&m);
        if (d==n&&e==m)
            return ftell(f);
    }
    fclose(f);
    return 0;
}
//ajout de n etudiant
void ajoutEtud(){
    etudiant=fopen("etudiant.txt","a");
    Etudiant etd;
    clrscr();
    int k;
    do{
        printf("Donner le nombre d'%ctudiant %c ajouter: ",130,133);
        scanf("%d",&k);
    }while(k<1);
    int i;
    for (i=0;i<k;i++){
        clrscr();
        printf("Ajout de l'%ctudiant %d: \n",130,i+1);
        int b;
        do{
            fflush(stdin);
            printf("Donner la carte de l'%ctudiant: ",130);
            scanf("%d",&(etd.carte));
            b=existe1(etd.carte,etudiant,"etudiant.txt");
            if (b)
                printf("Carte d%cj%c existante.\n",130,133);
        }while(b);
        fflush(stdin);
        printf("Donner le nom de l'%ctudiant: ",130);
        gets(etd.nom);
        fflush(stdin);
        printf("Donner le pr%cnom de l'%ctudiant: ",130,130);
        gets(etd.prenom);
        fflush(stdin);
        printf("Donner la section de l'%ctudiant: ",130);
        gets(etd.section);
        fprintf(etudiant,"%5.5d%-30.30s%-30.30s%-10.10s\n",etd.carte,etd.nom,etd.prenom,etd.section);
        if (i<k-1){
            printf("Appuyez sur une touche\n");
            getch();
        }
    }
    fclose(etudiant);
    printf("Ajout termin%c\nAppuyez sur une touche",130);
    getch();
}
//ajout de n matieres
void ajoutMat(){
    clrscr();
    matiere=fopen("matiere.txt","a");
    Matiere mat;
    int k;
    do{
        printf("Donner le nombre de mati%cre %c ajouter: ",138,133);
        scanf("%d",&k);
    }while(k<1);
    int i;
    for (i=0;i<k;i++){
        clrscr();
        printf("Ajout de la mati%cre %d: \n",138,i+1);
        int b;
        do{
            fflush(stdin);
            printf("Donner le code de la mati%cre: ",138);
            scanf("%d",&(mat.code));
            b=existe1(mat.code,matiere,"matiere.txt");
            if (b)
                printf("Code d%cj%c existant.\n",130,133);
        }while(b);
        fflush(stdin);
        printf("Donner la section de la mati%cre: ",138);
        gets(mat.section);
        fflush(stdin);
        printf("Donner l'intitul%c de la mati%cre: ",130,138);
        gets(mat.intitule);
        fflush(stdin);
        printf("Donner le coefficient de la mati%cre: ",138);
        scanf("%f",&(mat.coef));
        fprintf(matiere,"%5.5d%-10.10s%-30.30s%05.2f\n",mat.code,mat.section,mat.intitule,mat.coef);
        if (i<k-1){
            printf("Appuyez sur une touche\n");
            getch();
        }
    }
    fclose(matiere);
    printf("Ajout termin%c\nAppuyez sur une touche",130);
    getch();
}
//ajout de n notes
void ajoutNot(){
    clrscr();
    notes=fopen("notes.txt","a");
    Notes note;
    int k;
    do{
        printf("Donner le nombre de notes %c ajouter: ",133);
        scanf("%d",&k);
    }while(k<1);
    int i;
    for (i=0;i<k;i++){
        clrscr();
        printf("Ajout de la mati%cre %d: \n",138,i+1);
        int b;
        do{
            fflush(stdin);
            printf("Donner la carte de l'%ctudiant: ",130);
            scanf("%d",&(note.carte));
            fflush(stdin);
            printf("Donner le code de la mati%cre: ",138);
            scanf("%d",&(note.code));
            b=existe2(note.carte,note.code,notes);
            if (b)
                printf("L'%ctudiant a d%cj%c une note dans cette mati%cre\n",130,130,133,138);
        }while(b);
        do{
            fflush(stdin);
            printf("Donner la note: ");
            scanf("%f",&(note.note));
        }while(note.note<0||note.note>20);
        fprintf(notes,"%5.5d%5.5d%05.2f\n",note.carte,note.code,note.note);
        if (i<k-1){
            printf("Appuyez sur une touche\n");
            getch();
        }
    }
    fclose(notes);
    printf("Ajout termin%c\nAppuyez sur une touche",130);
    getch();
}
//calcule le total des coefficient avec une section donnée
float totCoef(char *sec){
    float som=0;
    matiere=fopen("matiere.txt","r");
    char ch[60];
    while(fgets(ch,60,matiere)){
        char sect[15];
        sscanf(ch+5,"%10s",sect);
        if(!strcmp(sec,sect)){
            float co;
            sscanf(ch+45,"%5f",&co);
            som+=co;
        }
    }
    fclose(matiere);
    return som;
}
//retourne le coefficient d'une matiere donnée
float coef(int co){
    matiere=fopen("matiere.txt","r");
    char ch[60];
    while(fgets(ch,60,matiere)){
        int cod; float cf;
        sscanf(ch,"%5d",&cod);
        sscanf(ch+45,"%5f",&cf);
        if (cod==co){
            return cf;
        }
    }
    fclose(matiere);
    return -1;
}
//calcule la somme des notes multiplié par leur coefficient d'un etudiant donné
float totNot(int carte){
    float som=0;
    notes=fopen("notes.txt","r");
    char ch[20];
    while(fgets(ch,20,notes)){
        int ca,co;float no;
        sscanf(ch,"%5d%5d",&ca,&co);
        sscanf(ch+10,"%5f",&no);
        if(ca==carte){
                if (coef(co)==-1) return 0;
            som+=(no*coef(co));
        }
    }
    fclose(notes);
    return som;
}
// affiche la moyenne d'un etudiant
void afficheMoy(){
    clrscr();
    Etudiant etd;
    fflush(stdin);
    printf("Donner la carte de l'%ctudiant: ",130);
    scanf("%d",&(etd.carte));
    int ex=0;
    etudiant=fopen("etudiant.txt","r");
    char ch[80];
    while (fgets(ch,80,etudiant)){
        int c;
        sscanf(ch,"%5d",&c);
        if (c==etd.carte){
            ex=1;
            sscanf(ch+5,"%30s%30s%10s",etd.nom,etd.prenom,etd.section);
        }
    }
    if (!ex){
        printf("L'%ctudiant n'est pas enregistr%c.\n",130,130);
        printf("Appuyez sur une touche\n");
        getch();
        fclose(etudiant);
        return;
    }

    float tc=totCoef(etd.section);
    if (!tc){
        printf("Il n'y a pas des mati%cres dont leur section est celle de l'%ctudiant.\n",138,130);
        printf("Appuyez sur une touche\n");
        getch();
        fclose(etudiant);
        return;
    }
    float tn=totNot(etd.carte);
    if (!tn){
        printf("Notes ou mati%cres non enregistr%cs.\n",138,130);
        printf("Appuyez sur une touche\n");
        getch();
        fclose(etudiant);
        return;
    }
    float me=tn/tc;
    fclose(etudiant);
    printf("La moyenne de %s %s est %5.2f\n",etd.prenom,etd.nom,me);
    printf("Appuyez sur une touche\n");
    getch();
}

//Modifie la note d'un etudiant dans une matiere donnée
void modifiNot(){
    clrscr();
    notes=fopen("notes.txt","r+");
    Notes note;
    fflush(stdin);
        printf("Donner la carte de l'%ctudiant: ",130);
        scanf("%d",&(note.carte));
    fflush(stdin);
    printf("Donner le code de la mati%cre: ",138);
    scanf("%d",&(note.code));
    int r;
    if (!(r=existe2(note.carte,note.code,notes))){
            fclose(notes);
        printf("Cette note n'existe pas.\n");
        printf("Appuyez sur une touche\n");
        getch();
        return;
    }
    fseek(notes,r-7,SEEK_SET);
    float nn;
    fflush(stdin);
    printf("Donner la nouvelle note: ");
    scanf("%f",&nn);
    fprintf(notes,"%05.2f",nn);
    fclose(notes);
    printf("Appuyez sur une touche\n");
    getch();
}
//retourne la moyenne de l'etudiant
float moygen(Etudiant etd){
    int ex=0;
    etudiant=fopen("etudiant.txt","r");
    char ch[80];
    float tc=totCoef(etd.section);
    if (!tc){
        fclose(etudiant);
        return -1;
    }
    float tn=totNot(etd.carte);
    if (!tn){
        fclose(etudiant);
        return-1;
    }
    float me=tn/tc;
    fclose(etudiant);
    return me;
}
//retourne l'intitulé d'une matière donnée
void getintit(char *in,int cod){
    matiere=fopen("matiere.txt","r");
    char ch[55];
    while(fgets(ch,55,matiere)){
        int c;
        sscanf(ch,"%5d",&c);
        if (cod==c){
            fseek(matiere,-39L,SEEK_CUR);
            fgets(in,30,matiere);
            fseek(matiere,+9L,SEEK_CUR);
            sscanf(in,"%s",in);
            fclose(matiere);
            return;
        }
    }
}
//affiche le bulletin d'un étudiant
void afficheBult(){
    clrscr();
    Etudiant etd;
    fflush(stdin);
    printf("Donner la carte de l'%ctudiant: ",130);
    scanf("%d",&(etd.carte));
    int r;
    if (!(r=existe1(etd.carte,etudiant,"etudiant.txt"))){
        printf("L'%ctudiant n'est pas enregistr%c\n",130,130);
        printf("Appuyez sur une touche\n");
        getch();
        return;
    }
    printf("%ctudiant trouv%c\n",130,130);
    printf("Appuyez sur une touche\n");
    getch();
    etudiant=fopen("etudiant.txt","r");
    fseek(etudiant,r-70,SEEK_SET);
    fscanf(etudiant,"%30s%30s%10s",etd.nom,etd.prenom,etd.section);
    fclose(etudiant);
    clrscr();
    printf("Carte Etudiant\t: %d\n",etd.carte);
    printf("Nom Etudiant\t: %s\n",etd.nom);
    printf("Pr%cnom Etudiant\t: %s\n",130,etd.prenom);
    printf("Section\t\t: %s\n",etd.section);
    float moy=moygen(etd);
    if(moy<0){
        printf("donn%ces manquantes pour calculer la moyenne",130);
        printf("Appuyez sur une touche\n");
        getch();
        return;
    }
    printf("Moyenne G%cn%crale: %5.2f\n",130,130,moy);
    notes=fopen("notes.txt","r");
    printf("\tMatiere\t\tNote\tCoefficient\tTotal\n");
    char ch[20];
    while(fgets(ch,20,notes)){
        int car,cod;float no;
        sscanf(ch,"%5d%5d%5f",&car,&cod,&no);
        char intit[31];
        getintit(intit,cod);
        printf("\t%s\t%5.2f\t%5.2f\t\t%5.2f\n",intit,no,coef(cod),no*coef(cod));
    }
    printf("Appuyez sur une touche\n");
    getch();
}

int main()
{
    creerFichier(matiere,"matiere.txt");
    creerFichier(etudiant,"etudiant.txt");
    creerFichier(notes,"notes.txt");
    transition();
    int choix;
    do{
      clrscr();
        menu();
        do{
            printf("Tapez votre choix: ");
            scanf("%d",&choix);
        }while (choix<1||choix>7);
        transition();
        switch(choix){
        case 1: ajoutEtud();break;
        case 2: ajoutMat();break;
        case 3: ajoutNot();break;
        case 4: afficheMoy();break;
        case 5: modifiNot();break;
        case 6: afficheBult();break;
        }
    }while (choix!=7);
    clrscr();
    printf("\n\nAu revoir ^_^\n\n");
    getch();
    return 0;
}
