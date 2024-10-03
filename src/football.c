#include <stdio.h>
#include <stdlib.h>

// Store values of potential plays for reference
const int score_values[5] = {2,3,6,7,8};

/**
 * Take in a play combo and output the score.
 * 
 * @param plays An array of length 5 containing the number of each
 *              play in order of value.
 * @return The calculated score.
 */ 
int count_score (int * plays) {
    int tally = 0;

    for (int i = 0; i < 5; i++) {
        tally += score_values[i] * plays[i];
    }

    return tally;
}

/**
 * Print all play combos that add up to the given score.
 * 
 * @param score The score to calculate for.
 * @param plays An array of length 5 with the counts of initial plays.
 * @param current_depth Used for recursive calls, set to 0.
 */
void print_sum_combos (int score, int * plays, int current_depth) {
    int current = count_score(plays);

    if (current == score)
        printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d Safety\n",
               plays[4], plays[3], plays[2], plays[1], plays[0]);
    
    if (current >= score)
        return;

    for (int i = current_depth; i < 5; i++) {
        plays[i] += 1;
        print_sum_combos(score, plays, i);
        plays[i] -= 1;
    }
}

int main () {
    printf("Enter 0 or 1 to STOP\n");

    int score; // Declare score value for loop control
    char input[16]; // Buffer for storing input

    // Loop until stop input recieved
    do {
        printf("Enter the NFL score: ");
        fgets(input, sizeof(input), stdin);
        char *end;
        score = (int)strtol(input, &end, 10);

        // Ensure input was a valid integer
        if (*end != '\n') {
            printf("Please enter a valid integer value.\n");
            score = 2;
            continue;
        }

        // Print the combos if not stopping
        if (score >= 2) {
            int plays[5] = {0,0,0,0,0};
            printf("Possible combinations of scoring plays if a team's score is %d:\n", score);
            print_sum_combos(score, plays, 0);
            printf("\n");
        }
        
    } while (score > 1);

    return 0;
}
