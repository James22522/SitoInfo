#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    char buffer[1024];
    int f1, f2;
    FILE *input = fopen("input.txt","w");
    
    if(!input){
        printf("Errore nell'apertura del file");
        exit(1);
    }
    printf("Inserisci contenuto\n");
    fgets(buffer, sizeof(buffer), stdin);
    fputs(buffer, input);
    fclose(input);
    
    f1 = fork();
    if(f1 == 0){
        FILE *input2 = fopen("input.txt","r");
        FILE *copia = fopen("copia.txt","w");
        
        if(!input2 || !copia){
            printf("Errore apertura file");
            exit(1);
        }
        fputs("copia", copia);
        
        char c;
        while((c = fgetc(input2)) != EOF){
            fputc(c, copia);
        }
        
        fclose(input2);
        fclose(copia);
        exit(0);
    }else if(f1 > 0){
        wait(&f1);
        
        f2 = fork();
        
        if(f2 == 0){
            char nomeCognome[1024];
            
            FILE *copia2 = fopen("copia.txt","a");
            if(!copia2){
                printf("Errore apertura file");
                exit(1);
            }
            
            printf("Inserisci il tuo nome e cognome");
            fgets(nomeCognome, sizeof(nomeCognome), stdin);
            fputs(nomeCognome, copia2);
            
            fclose(copia2);
            
            FILE *finale = fopen("copia.txt","r");
            
            char ch;
            while((ch = fgetc(finale))!= EOF){
                putchar(ch);
            }
            fclose(finale);
            exit(0);
        }
    }
    wait(&f2);
    
    return 0;
}
