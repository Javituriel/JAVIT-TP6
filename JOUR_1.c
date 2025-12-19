#include <stdio.h>

int main() {
    FILE *f = fopen("01.input", "r");
    

    char turn[100];
    int dist;
    int position = 0;      
    int cpt = 0;      

    while (fgets(turn, sizeof(turn), f)) {
        char direction = turn[0];//ici on a R et L         
        sscanf(turn + 1, "%d", &dist);   

        if (direction == 'R') {
            position = (position + dist) % 100;
        } else {  
            
            
            
            // pour le L
            position = (position - dist) % 100;
            if (position < 0) position += 100;
        }

        if (position == 0) {
            cpt++;
        }
    }

    fclose(f);

    printf("le 0 %d fois.\n", cpt);
    return 0;
}





//fgets(turn,sizeof(turn),monFichier)

    //fscanf(monFichier,"%s",&turn[]);

    //printf("%c\n", turn[3]);

    //fclose(monFichier);