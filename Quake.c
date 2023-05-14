#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX 200


void print_array(int B[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(B[i][j] == 1){
                printf("\033[1;31m%5d\033[0m", B[i][j]);
            } else {
                printf("%5d", B[i][j]);
            }
        }
        printf("\n");
    }
}

void modify_array_column(int B[HEIGHT][WIDTH], int column) {
    for (int i = 0; i < HEIGHT; i++) {
        B[i][column] = 1;
    }
}

void modify_array_row(int B[HEIGHT][WIDTH], int row) {
    for (int j = 0; j < WIDTH; j++) {
        B[row][j] = 1;
    }
}

void modify_array_circle(int B[HEIGHT][WIDTH], int x1, int y1, int radius) {
    float DTHETA = 2*PI()/7;
    float THETA = 0;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (sqrt(pow(i - x1, 2) + pow(j - y1, 2)) - radius < 1) {
                B[i][j] = 1;
            }
        }
    }
}

void modify_array_line(int B[HEIGHT][WIDTH], int x1, int y1, int x2, int y2) {
    float m = (y2 - y1) / (float)(x2 - x1);
    float b = y1 - m * x1;

    if (abs(x2 - x1) > abs(y2 - y1)) {
        for (int x = fmin(x1, x2); x <= fmax(x1, x2); x++) {
            int y = round(m * x + b);
            B[x][y] = 1;
        }
    } else {
        for (int y = fmin(y1, y2); y <= fmax(y1, y2); y++) {
            int x = round((y - b) / m);
            B[x][y] = 1;
        }
    }
}

void print_array_a(int A[HEIGHT][WIDTH]){
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(A[i][j] <= 49){
                printf("\033[0;32m%5d\033[0m", A[i][j]);
            } else if(A[i][j] >= 50 || A[i][j] <= 99){
                printf("\033[0;33m%5d\033[0m", A[i][j]);
            } else if(A[i][j] >= 100) {
                printf("\033[1;31;43m%5d\033[0m", A[i][j]);
            }
        }
        printf("\n");
    }

    // Increment each value in the array by 10 in a loop
    for (int k = 0;k < 20; k++) {
    // Clear the screen using the system function
        system("cls");

        // Print the updated array
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                int increment;
                if(A[i][j] == 1){
                    increment = rand()%11;
                } else {
                    increment = abs(rand()%11-5);
                }
                A[i][j]+=increment;
                if(A[i][j] <= 49){
                    printf("\033[0;32m%5d\033[0m", A[i][j] + k * 10);
                } else if(A[i][j] >= 50 && A[i][j] <= 99){
                    printf("\033[0;33m%5d\033[0m", A[i][j] + k * 10);
                } else if(A[i][j] >= 100 && A[i][j] <= 199){
                    printf("\033[1;31m%5d\033[0m", A[i][j] + k * 10);
                }else if(A[i][j] >= 200){
                    printf("\033[1;31;43m%6d \033[0m", A[i][j] + k * 10);
                }
            }
            printf("\n");
        }

    // Wait for 1 second using the sleep function
    sleep(1);
    }
}



int main(){

    int A[HEIGHT][WIDTH];       //  Represents the tectonic stress level (>=0)
    int B[HEIGHT][WIDTH] = {0}; //  Represents the fault line 0/1 values
    int i,j;                    //  (0:not on fault line) (1:0 fault line)
    int x1, x2;
    int y1, y2;
    int radius = 7;
    int num;

    printf("\t\t\t\t********************\t\t\t\t\n");
    printf("\t\t\t\tEARTHQUAKE SIMULATOR\t\t\t\t\n");
    printf("\t\t\t\t********************\t\t\t\t\n\n");

    do{
        printf("\n\nPlease choose a fault line shape to generate...\n");
        printf("1: Vertical Line\n");
        printf("2: Horizontal Line\n");
        printf("3: Circle\n");
        printf("4: Point to Point Line\n");
        printf("-1: Begin Simulation\n");
        printf("\nEnter: ");
        scanf("%d", &num);

        if(num==1){
            printf("\nAt what X location would you like to place this vertical line? (0-19)\n");
            printf("\nEnter: ");
            scanf("%d",&x1);
            modify_array_column(B, x1);
            printf("\n");
            printf("-----------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\tPrinting the Fault Map\n");
            printf("-----------------------------------------------------------------------------------------------------\n");
            print_array(B);
            continue;
        }
        if(num==2){
            printf("\nAt what X location would you like to place this horizontal line? (0-19)\n");
            printf("\nEnter: ");
            scanf("%d",&y1);
            modify_array_row(B, y1);
            printf("\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\tPrinting the Fault Map\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            print_array(B);
            continue;
        }
        if(num==3){
            printf("\nAt what X, Y location would you like to place this circle? (0-19), (0-19)\n");
            printf("\nEnter: ");
            scanf("%d %d",&x1,&y1);
            modify_array_circle(B, x1, y1, radius);
            printf("\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\tPrinting the Fault Map\n");
            printf("---------------------------------------------------------------------------------------------------\n");
            print_array(B);
            continue;
        }
        if(num==4){
            printf("\nEnter X,Y of start point (0-19), (0-19): ");
            scanf("%d %d",&x1, &y1);
            printf("Enter X,Y of end point (0-19), (0-19): ");
            scanf("%d %d",&x2, &y2);
            modify_array_line(B, x1, y1, x2, y2);
            printf("\n");
            printf("-------------------------------------------------------------------------------------------------\n");
            printf("\t\t\t\t\tPrinting the Fault Map\n");
            printf("-------------------------------------------------------------------------------------------------\n");
            print_array(B);
            continue;
        }


    }while(num != -1);


    //Earthquake simulation takes place.
    printf("\n\n");
    printf("****************************************************************************************************");
    printf("\n\t\t\t\t\tEARTHQUAKE!!!!!\n");
    printf("****************************************************************************************************");
    printf("\n\n");
    for(i=0;i<WIDTH;i++){
        for(j=0;j<HEIGHT;j++){
            A[i][j] = B[i][j];
            if(A[i][j] <= 49){
                printf("\033[0;32m%5d\033[0m", A[i][j]);
            } else if(A[i][j] >= 50 || A[i][j] <= 99){
                printf("\033[0;33m%5d\033[0m", A[i][j]);
            } else if(A[i][j] >= 100) {
                printf("\033[1;31;43m%5d\033[0m", A[i][j]);
            }
        }
    printf("\n");
    }

    print_array_a(A);

    printf("\n\n");



    return 0;
}
