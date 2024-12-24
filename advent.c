#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>
#include <regex.h>
#include <stdbool.h>
int list1[] = {3, 4, 2, 1, 3, 3};
int list2[] = {4, 3, 5, 3, 9, 3};

struct List{
    int value;
    struct List *next;
};

struct List *init_elem(int val){
    struct List *new_elem = (struct List *) malloc (sizeof(struct List));
    new_elem->value = val;
    new_elem->next = NULL;
    return new_elem;
}
static int length = sizeof(list1)/sizeof(int);

void load_list(struct List *list, int array[], int count){
    if(length >= count){
        struct List *nextElem = init_elem(array[count]);
        list->next = nextElem;
        load_list(nextElem, array, count+1);
    }

}

void print_list(int list[]){
    int i;
    for (i = 0; i < length; i++){
        printf("%d, ", list[i]);
    }
    printf("\n");
}

void swap(int *v1, int *v2){
    int temp = *v1;
    *v1 = *v2;
    *v2 = temp;
}

void bubbleSort(int *arr){
    int i, j;
    for (i = 0; i < length-1; i++){
        for (j = 0; j < length-1; j++){
            if (arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

int find_distances(int *arr1, int *arr2){
    int i, sum;
    sum = 0;
    for (i = 0; i < length; i++){
        int hold = arr1[i] - arr2[i];
        sum += (hold < 0) ? -hold : hold;
    }
    return sum;
}

int day1(int *arr1, int *arr2){
    bubbleSort(arr1);
    bubbleSort(arr2);
    for(int i = 0; i < length; i++){
        printf("%d, ", list1[i]);
    }
    printf("\n");
     for(int i = 0; i < length; i++){
        printf("%d, ", list2[i]);
    }
    printf("\n");
    return find_distances(list1, list2);

}

void load_lines(char lines[][128], FILE *file){
    char line [128];
    int i = 0;
    while(fgets(line, 128, file)){
        strcpy(lines[i], line);
        i++;

    }
}

void convert_string_to_int_array(char *string, int arr[]){
    char *tok = strtok(string, " ");
    int i = 0;
    while(tok != NULL){
        arr[i] = atoi(tok);
        i++;
        tok = strtok(NULL, " ");
    }
}

void convert_readings(char lines[][128], int readings[][5]){
    char buff [128];
    int i;
    for (i=0; i<1000; i++){
        strcpy(buff, lines[i]);
        convert_string_to_int_array(buff, readings[i]);
        //printf("\n");
    }
}

int safe_reports(int readings[][5]){
    int i, j, diff, flag;
    int safe = 0;
    for (i = 0; i < 1000; i++){
        flag = 0;
        for (j = 0; j < 4; j++){
            diff = (readings[i][j] - readings[i][j+1]);
            diff = (diff < 0) ? -diff : diff;
            if (diff == 1 || diff == 2){
                flag ++;
            }
        }
        if (flag == 4){
            safe ++;
        }
     }
    return safe;
}

int day2(){
    FILE *file = fopen("day2.txt", "r");
    char lines[1000][128];
    int readings [1000][5];
    load_lines(lines, file);
    convert_readings(lines, readings);
    printf("%d\n", safe_reports(readings));
    return safe_reports(readings);
}

void load_lines_day3(char lines[][4096], FILE *file){
    char line [4096];
    // char buff [4096];
    int i = 0;
    while(fgets(line, 4096, file)){
        strcpy(lines[i], line);
        i++;
    }
}

int convert_to_int_arr(char lines[][4096]){
    /*
    The idea for this function is to go through each line and use the strtok function to 
    get all of the correct "mul(X,Y)" phrases out and parse only the X and Y of them. We
    will store these X and Y values.
    */

    int result = 0;

    regex_t regex;
    regmatch_t matches[4];
    // An array of matches that holds type <regmatch_t>
    // <regmatch_t> has a start and an end byte offset
    const char *pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    // Regualr expressions patter
    regcomp(&regex, pattern, REG_EXTENDED);
    // Create the regular expression object
    int i;
    for (i = 0; i < 6; i++){
        const char *input = lines[i];
        while (regexec(&regex, input, 4, matches, 0) == 0) { 
            // This loop will match each substring that matches the pattern
            char x[4] = {0};
            char y[4] = {0};
            // Grabs the two numbers

            int x_start = matches[1].rm_so;
            int x_end = matches[1].rm_eo;
            // grabs the start and end marks of the first number
            int y_start = matches[2].rm_so;
            int y_end = matches[2].rm_eo;
            // grabs the start and end marks of the second number
            strncpy(x, input + x_start, x_end - x_start);
            strncpy(y, input + y_start, y_end - y_start);
            // copies the first and second number into the char arrays
            int alpha = atoi(x);
            int bravo = atoi(y);
            // converts the strings to numbers
            result = result + (alpha*bravo);
            // computes the product
            input += matches[0].rm_eo;
            // moves the line to the string after the current match
        }
    }
    regfree(&regex);  // Frees the regex
    return result;  
}

int day3(){

    FILE *file = fopen("day3.txt", "r");
    char lines[6][4096];
    load_lines_day3(lines, file);
    int r = convert_to_int_arr(lines);
    printf("result = %d\n", r);
    return 0;
}

void load_lines_6(char lines[131][131], FILE *file){
    int i;
    for (i = 0; i < 131; i++){
        fgets(lines[i], 131, file);
    }
}

void get_start_location(int *x, int *y, char lines[131][131]){
    int i, j;
    for (i = 0; i < 131; i++){
        for (j = 0; j < 131; j++){
            if (lines[i][j] == '^'){
                *x = i;
                *y = j;
                return;
            }
        }
    }
    *x = -99;
    *y = -99;
}

int play(int *x, int *y, char lines[131][131], char start_char, int visited){
    /**
     * Rules:
     *  If there is nothing in front, then proceed forward by one step
     *  If there is something in front, turn right
     *  if we exit the room, return the number of places we visited.
     */
    if(*x >= 0 && *y >= 0){
        // While we are in the room, lets play
        // lines[*x][*y] = '!';
        // Mark the current location as visited
        char next;
        switch (start_char){
            case '^':
                // We are going to need to check above us for barrier or boundry
                // above is [i-1][j]
                if (*x == 0){
                    // We are at the top of the room and about to move out
                    return visited + 1;
                }
                next = lines[*x-1][*y];
                if (next == '#'){
                    // This means that the next spot is an obstacle
                    visited += play(x, y, lines, '>', visited + 1);
                    // Play the next move after turning right
                }
                else{
                    *x = *x - 1;
                    visited += play(x, y, lines, '^', visited + 1);
                }
                break;
            case 'v':
                // We are going to need to check below us for barrier or boundry
                // Below is [i + 1] [j]
                if (*x == 130){
                    return visited + 1;
                }
                next = lines[*x+1][*y];
                if (next == '#'){
                    visited += play(x, y, lines, '<', visited + 1);
                }
                else{
                    *x = *x + 1;
                    visited += play(x, y, lines, 'v', visited + 1);
                }
                break;
            case '<':
                // We are going to need to check for barriers or boundries
                // Left of us is going to be [i][j-1]
                if (*y == 0){
                    return visited + 1;
                }
                next = lines[*x][*y - 1];
                if (next == '#'){
                    visited += play(x, y, lines, '^', visited + 1);
                }
                else{
                    *y = *y - 1;
                    visited += play(x, y, lines, '<', visited + 1);
                }
                break;
            case '>':
                // We are going to need to check for barriers and boundries
                // Right of us is [i][j + 1]
                if (*y == 130){
                    return visited + 1;
                }
                next = lines[*x][*y + 1];
                if (next == '#'){
                    visited += play (x, y, lines, 'v', visited + 1);
                }
                else{
                    *y = *y + 1;
                    visited += play(x, y, lines, '>', visited + 1);
                }
                break;
        }
    }
    return visited + 1;
}

int day6(){

    char lines [131][131];
    FILE *file = fopen("day6.txt", "r");
    load_lines_6(lines, file);
    int x = -99;
    int y = -99;
    get_start_location(&x, &y, lines);
    printf("start x: %d, start y: %d\n", x, y);
    int result = play(&x, &y, lines, '^', 0);
    printf("result = %d\n", result);
    return 0;
}
#define MAX7 10
#define MAXLINES7 850
void parse_lines_7(char lines[][MAX7], FILE *file){
    int i;
    for(i = 0; i < MAXLINES7; i++){
        fgets(lines[i], 2*MAX7, file);
    }
}

bool evaluate_expr(int numbers[], int size, int index, int current_value, int target){
    if (index == size){
        return target == current_value;
    }
    return evaluate_expr(numbers, size, index + 1, current_value + numbers[index], target) || 
           evaluate_expr(numbers, size, index + 1, current_value * numbers[index], target);

    /**
     * What this function does is that it will recursively call itself and update the current
     * value variable with both addition and multilpication. This recursive function will 
     * essentially create a tree where every left branch is addition and right branch is 
     * multiplication. This allows us to explore every branch until we hit the final depth.
     * There is a full-length branch for every possible combination
     */
}

bool do_line(const char *line, int *result){
    int target;
    int numbers[MAX7];
    int count = 0;

    const char *delim = strchr(line, ':');
    // Here we are using the strchr function to find the location of the deliminter. 
    if (!delim){
        return false;
    }
    sscanf(line, "%d:", &target);
    // This will place the value of the target into the target integer
    const char *numbers_string = delim + 1;
    // We increment past the delimiter to get the beginning of the numbers
    while (sscanf(numbers_string, "%d", &numbers[count]) == 1){
        // We increment over the numbers until we run out of them and we store them as we go.
        count ++;
        // This count variable will act as our length variable.
        numbers_string = strchr(numbers_string, ' ');
        if(!numbers_string){
            break;
        }
        numbers_string++;
        // We increment the base string past the number we just got
    }

    if (evaluate_expr(numbers, count, 1, numbers[0], target)){
        // If any possible expression matches the target, we add it to the result.
        *result = target;
        return true;
    }

    return false;

}

int day7(){

    FILE *file = fopen("day7.txt", "r");
   
    char line [128];
    int sum = 0;
    while(fgets(line, sizeof(line), file)){
        int result;
        if (do_line(line, &result)){
            sum += result;
        }
    }
    printf("Total results are %d\n", sum);
    return sum;
}

int main(int argc, char *argv[]){
    

    // printf("day 1 = %d\n", day1(list1, list2));
    //day2();
    // day3();
    //day6();
    day7();
    return 0;
}

    // struct List *l1 = init_elem(list1[0]);  
    // struct List *l2 = init_elem(list2[0]);
    // load_list(l1, list1, 1);
    // load_list(l2, list2, 1);

    