/**
    ΠΑΠΑΚΩΣΤΑΣ ΑΘΑΝΑΣΙΟΣ
    ΑΜ 1097361
    ΕΤΟΣ ΦΟΙΤΗΣΗΣ 2o
    Υλοποίηση του παιχνιδιού Game Of Life
*/


#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/** ΔΟΜΕΣ ΔΕΔΟΜΕΝΩΝ */



typedef struct cell {
    struct cell *neighbours[8];
    int on;
} cell_t;

/** Oρισμός της βασικής προγραμματιστικής δομής cell
    κάθε κελί μπορει να βρίστεται σε κατάσταση 0 ή 1
    επίσεις υπάρχει ένας πίνακας δεικτών που καταχωρεί τις διευθύνσεις
    των 8 γειτονονικών κελιών */

typedef struct word {
    cell_t **array;
    int width;
    int height;
    void *mem;
} world_t;

/** Oρισμός πλέγματος όπου ορίζουμε το υψος (height) και πλάτος (width)
    Η υλοποίηση γίνετε με χρήση της δομής word.
    Πρόκειτε για ένα δυναμικό πίνακα κελιών που μέσω του δείκτη mem δεσμεύει μνήμη για κελία
 */


/** ΣΥΝΑΡΤΗΣΕΙΣ ΧΕΙΡΙΣΜΟΥ */

int createworld(world_t *world, int width, int height);
/** Δημιουργία του κόσμου με δέσμευση του απαιτούμενου χώρου για τον δυναμικό πίνακα*/

void randomizeworld(world_t *world);
/** Δημιουργία αρχικών κυττάρων του  κόσμου (μηδενική γενιά) με τυχαίο τρόπο  */

void updateworld(world_t *world);
/** Δημιουργία  κυττάρων του  κόσμου της επόμενης γενιάς σύμφωνα με τους κανόνες  */

void printworld(world_t *world, FILE *pOutput);
/** Εκτύπωση ενός στιγμιότυπου του κόσμου  στην standard έξοδο */


void updateworld_nTimes(world_t *world, int n);
/** Δημιουργία επόμενων n συνεχόμενων γενιών  */

void destroyworld(world_t *world);
/**  Απελευθέρωση του χώρου που δεσμεύθηκε για τη δημιουργία του κόσμου */

void delay(unsigned int mseconds);
/** Oρισμός χρονοκαθυστέρισης */

void initialization(int *x, int *y, int *n, int *time);
/** αλλαγή βασικών παραμέτρων κόσμου (διάστασης grid, χρονοκαθηστέρησης κ.α */

void printmenu(void);
/** εκτύπωση βασικού menu */

int getchoice(void );
int getsize(char *s );
#include <stdio.h>

void green(){
  printf("\033[32;40m");
}
void yellow(){
  printf("\033[33;40m");

}
void blue(){
  printf("\033[36;40m");
}
void reset () {
  printf("\033[0m");
}



int main(int argc, char *argv[]) {
    world_t gameoflife;
    int choice, x,y,n;
    int time, generation;
    x=64;
    y=24;
    n=1;
    time=1000;

do{ 
    printmenu();
    choice = getchoice();
    printf("\n");

  switch(choice)
     {
         case 1:
            generation=0;
            if(createworld(&gameoflife, x, y)) {
            randomizeworld(&gameoflife);
            do {
                system("CLS");
				printf("\n");
			
                green();
                printworld(&gameoflife, stdout);
                blue();
                printf("\n\tGeneration -> %d \n",generation);
                delay(time);
                fflush(stdin);
                updateworld_nTimes(&gameoflife,n);
                generation=generation+n;
            }while(1);
            destroyworld(&gameoflife);
    }
            break;
         case 2:
            initialization( &x, &y, &n, &time);

            break;
         case 3:
            printf("EXIT.....");
            break;
    }

} while (choice!=3);


    return 0;
}


void printmenu(void){

printf("\n\t--- THE GAME OF LIFE ---\n\n");
printf("\t1.  play the game\n");
printf("\t2.  change parameters\n");
printf("\t3.  Exit\n");
return;
}
int getchoice(void ) {
int x;

printf("\tgive your choice (1 or 2) give 3 for exit the program ");
scanf("%d", &x);

return x;
}
int getsize(char *s ) {
int x;
printf("%s",s);
scanf("%d", &x);
return x;
}


void initialization(int *x, int *y, int *n, int *time ){
*x= getsize("\tPlease give  x dimension  of the grid: [default = 64] " );
*y= getsize("\tPlease give  y dimension  of the grid: [default = 24] " );
*n= getsize("\tHow many steps (generations) forward each time? [default = 1] ");
*time= getsize("\tHow long to delay emergence between generations (in milliseconds)? [default = 1000] ");

}

void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void printworld(world_t *world, FILE *pOutput)
{
    int x, y;
	
    for(y = 0; y < world->height; y++) {
    	 fprintf(pOutput, "\t");
    	 for(x = 0; x < world->width; x++) {
            fprintf(pOutput, "%c", (world->array[y][x]).on ? '*' : ' ');
        }
        fputc((int)'\n', pOutput);
    }
    fflush(pOutput);

}

void randomizeworld(world_t *world)
{
    int x, y;
    srand(time(NULL));
    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            (world->array[y][x]).on = rand() & 1;
        }
    }
}

void updateworld(world_t *world)
{
    int x, y, i, neighbours;
 /** για κάθε κελί μετρά τα γειτονικά κύτταρα που είναι ζωντανά (on) και
     στη συνέχεια με χρήση του τελεστή |= δίνει εικονικές τιμές 2,3,4,5 στα κελιά
     ανάλογα με το εάν το κύτταρο στην επόμενη γενιά πρέπει να επιβιώσει (2,3) ή να πεθάνει (4,5)
     Εν συνεχεία γίνεται ενα πέρασμα στον πίνακα και( με χρήση του τελεστή &)
     τα κελιά του πίνακα παίρνουν  τις κανονικές 1 ή 0 αντίστοιχα

 */
    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++, neighbours = 0) {
            for(i = 0; i < 8; i++)
                if((world->array[y][x].neighbours[i]) && ((world->array[y][x]).neighbours[i]->on & 1))
                    neighbours++;

           if((neighbours < 2) || (neighbours > 3))
                (world->array[y][x]).on |= 2;   /** δίνει στο κελί τιμή 2 ή 3 ανόλογα με το εάν ήταν 0 ή 1 */

            else if(neighbours == 3)
                (world->array[y][x]).on |= 4;  /** δίνει στο κελί τιμή 4 ή 5 ανόλογα με το εάν ήταν 0 ή 1 */
        }
    }


    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            if(world->array[y][x].on & 4)        /** αν  το κελί έχει τιμή 4 ή 5  γίνεται 1 */
                world->array[y][x].on = 1;
            else if(world->array[y][x].on & 2)   /** αν  το κελί έχει τιμή 2 ή 3  γίνεται 0 */
                world->array[y][x].on = 0;
        }
    }


}

void destroyworld(world_t *world)
{
    free(world->mem);
}

int createworld(world_t *world, int width, int height)
{
    int i, j;
    unsigned long base   = sizeof(cell_t *) * height;
    unsigned long rowlen = sizeof(cell_t )   * width;

    if(!(world->mem = calloc(base + (rowlen * height), 1)))  /** δέσμευση χώρου πίνακα */
        return 0;

    world->array  = world->mem;
    world->width  = width;
    world->height = height;

    for(i = 0; i < height; i++) {
        world->array[i] = world->mem + base + (i * rowlen);
    }

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            if(j != 0) {
                (world->array[i][j]).neighbours[3] = &(world->array[i][j - 1]);
            }

            if(i != 0) {
                (world->array[i][j]).neighbours[1] = &(world->array[i - 1][j]);
            }

            if(j != (width - 1)) {
                (world->array[i][j]).neighbours[4] = &(world->array[i][j + 1]);
            }

            if(i != (height - 1)) {
                (world->array[i][j]).neighbours[6] = &(world->array[i + 1][j]);
            }

            if((i != 0) && (j != 0)) {
                (world->array[i][j]).neighbours[0] = &(world->array[i - 1][j - 1]);
            }

            if((i != (height - 1)) && (j != (width - 1))) {
                (world->array[i][j]).neighbours[7] = &(world->array[i + 1][j + 1]);
            }

            if((i != (height - 1)) && (j != 0)) {
                (world->array[i][j]).neighbours[5] = &(world->array[i + 1][j - 1]);
            }

            if((i != 0) && (j != (width - 1))) {
                (world->array[i][j]).neighbours[2] = &(world->array[i - 1][j + 1]);
            }
        }
    }

    return 1;
}

void updateworld_nTimes(world_t *world, int x){
int i;
for(i=0;i<x;i++) {
    updateworld(world);

}
}
