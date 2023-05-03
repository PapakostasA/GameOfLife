/**
    ÐÁÐÁÊÙÓÔÁÓ ÁÈÁÍÁÓÉÏÓ
    ÁÌ 1097361
    ÅÔÏÓ ÖÏÉÔÇÓÇÓ 2o
    Õëïðïßçóç ôïõ ðáé÷íéäéïý Game Of Life
*/


#include <stdio.h>
#include <stdlib.h>
#include<time.h>

/** ÄÏÌÅÓ ÄÅÄÏÌÅÍÙÍ */



typedef struct cell {
    struct cell *neighbours[8];
    int on;
} cell_t;

/** Oñéóìüò ôçò âáóéêÞò ðñïãñáììáôéóôéêÞò äïìÞò cell
    êÜèå êåëß ìðïñåé íá âñßóôåôáé óå êáôÜóôáóç 0 Þ 1
    åðßóåéò õðÜñ÷åé Ýíáò ðßíáêáò äåéêôþí ðïõ êáôá÷ùñåß ôéò äéåõèýíóåéò
    ôùí 8 ãåéôïíïíéêþí êåëéþí */

typedef struct word {
    cell_t **array;
    int width;
    int height;
    void *mem;
} world_t;

/** Oñéóìüò ðëÝãìáôïò üðïõ ïñßæïõìå ôï õøïò (height) êáé ðëÜôïò (width)
    Ç õëïðïßçóç ãßíåôå ìå ÷ñÞóç ôçò äïìÞò word.
    Ðñüêåéôå ãéá Ýíá äõíáìéêü ðßíáêá êåëéþí ðïõ ìÝóù ôïõ äåßêôç mem äåóìåýåé ìíÞìç ãéá êåëßá
 */


/** ÓÕÍÁÑÔÇÓÅÉÓ ×ÅÉÑÉÓÌÏÕ */

int createworld(world_t *world, int width, int height);
/** Äçìéïõñãßá ôïõ êüóìïõ ìå äÝóìåõóç ôïõ áðáéôïýìåíïõ ÷þñïõ ãéá ôïí äõíáìéêü ðßíáêá*/

void randomizeworld(world_t *world);
/** Äçìéïõñãßá áñ÷éêþí êõôôÜñùí ôïõ  êüóìïõ (ìçäåíéêÞ ãåíéÜ) ìå ôõ÷áßï ôñüðï  */

void updateworld(world_t *world);
/** Äçìéïõñãßá  êõôôÜñùí ôïõ  êüóìïõ ôçò åðüìåíçò ãåíéÜò óýìöùíá ìå ôïõò êáíüíåò  */

void printworld(world_t *world, FILE *pOutput);
/** Åêôýðùóç åíüò óôéãìéüôõðïõ ôïõ êüóìïõ  óôçí standard Ýîïäï */


void updateworld_nTimes(world_t *world, int n);
/** Äçìéïõñãßá åðüìåíùí n óõíå÷üìåíùí ãåíéþí  */

void destroyworld(world_t *world);
/**  ÁðåëåõèÝñùóç ôïõ ÷þñïõ ðïõ äåóìåýèçêå ãéá ôç äçìéïõñãßá ôïõ êüóìïõ */

void delay(unsigned int mseconds);
/** Oñéóìüò ÷ñïíïêáèõóôÝñéóçò */

void initialization(int *x, int *y, int *n, int *time);
/** áëëáãÞ âáóéêþí ðáñáìÝôñùí êüóìïõ (äéÜóôáóçò grid, ÷ñïíïêáèçóôÝñçóçò ê.á */

void printmenu(void);
/** åêôýðùóç âáóéêïý menu */

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
 /** ãéá êÜèå êåëß ìåôñÜ ôá ãåéôïíéêÜ êýôôáñá ðïõ åßíáé æùíôáíÜ (on) êáé
     óôç óõíÝ÷åéá ìå ÷ñÞóç ôïõ ôåëåóôÞ |= äßíåé åéêïíéêÝò ôéìÝò 2,3,4,5 óôá êåëéÜ
     áíÜëïãá ìå ôï åÜí ôï êýôôáñï óôçí åðüìåíç ãåíéÜ ðñÝðåé íá åðéâéþóåé (2,3) Þ íá ðåèÜíåé (4,5)
     Åí óõíå÷åßá ãßíåôáé åíá ðÝñáóìá óôïí ðßíáêá êáé( ìå ÷ñÞóç ôïõ ôåëåóôÞ &)
     ôá êåëéÜ ôïõ ðßíáêá ðáßñíïõí  ôéò êáíïíéêÝò 1 Þ 0 áíôßóôïé÷á

 */
    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++, neighbours = 0) {
            for(i = 0; i < 8; i++)
                if((world->array[y][x].neighbours[i]) && ((world->array[y][x]).neighbours[i]->on & 1))
                    neighbours++;

           if((neighbours < 2) || (neighbours > 3))
                (world->array[y][x]).on |= 2;   /** äßíåé óôï êåëß ôéìÞ 2 Þ 3 áíüëïãá ìå ôï åÜí Þôáí 0 Þ 1 */

            else if(neighbours == 3)
                (world->array[y][x]).on |= 4;  /** äßíåé óôï êåëß ôéìÞ 4 Þ 5 áíüëïãá ìå ôï åÜí Þôáí 0 Þ 1 */
        }
    }


    for(y = 0; y < world->height; y++) {
        for(x = 0; x < world->width; x++) {
            if(world->array[y][x].on & 4)        /** áí  ôï êåëß Ý÷åé ôéìÞ 4 Þ 5  ãßíåôáé 1 */
                world->array[y][x].on = 1;
            else if(world->array[y][x].on & 2)   /** áí  ôï êåëß Ý÷åé ôéìÞ 2 Þ 3  ãßíåôáé 0 */
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

    if(!(world->mem = calloc(base + (rowlen * height), 1)))  /** äÝóìåõóç ÷þñïõ ðßíáêá */
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
