#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int f1, f2;
    
    f1 = fork();
    
    if(f1 == 0){
        FILE *titolo = fopen("titolo.txt","w");
        if(!titolo){
            printf("Errore apertura file");
            exit(1);
        }
        fprintf(titolo, "Il mistero della montagna\n");
        fclose(titolo);
        exit(0);
    }else if(f1 > 0){
        wait(&f1);
        
        f2 = fork();
        
        if(f2 == 0){
            char buffer[1024];
            FILE *opera = fopen("opera.txt","w");
            if(!opera){
                printf("Errore apertura file");
                exit(1);
            }
            printf("Inserisci contenuto");
            fgets(buffer, sizeof(buffer),stdin);
            fprintf(opera, buffer);
            fclose(opera);
            exit(0);
        }
    }else{
        printf("Errore generazione processo figlio");
        exit(1);
    }
    
    wait(&f2);
    
    FILE *titolo = fopen("titolo.txt","r");
    FILE *opera = fopen("opera.txt","r");
    FILE *finale = fopen("finale.txt","w");

    if(!opera || !titolo || !finale){
        printf("Errore apertura file");
        exit(1);
    }
    
    char c;
    while((c = fgetc(titolo)) != EOF){
        fputc(c, finale);
    }
    
    while((c = fgetc(opera)) != EOF){
        fputc(c, finale);
    }
    
    fclose(titolo);
    fclose(opera);
    fclose(finale);

    return 0;
}
