#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cycle(int winner, int loser);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    printf("%d\n", locked[2][1]);
    printf("%s y %s", candidates[2], candidates[1]);
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // this prompt compare two strings and store the number of candidate in the array called ranks
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // sabemos que ranks[] nos da un int que indica el candidato
    // use j=i+1 to avoid things like preference of the same candidate
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //Check the preferences of each pair and stored in the array
    //Estos dos for solo checan los valores encima de la diagonal de 0's
    //Por eso usamos el caso else if para tomar en cuenta los valores debajo de la diagonal
    //no tomamos en cuenta la diagonal pq no hay preferencias i de i
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;

            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // use a do while loop with a counter of swaps
    int swap_count;
    do
    {
        swap_count = 0;
        for (int i = 0; i < pair_count - 1; i++)
        {
            //use if statement to order the pairs array by strength of victory
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
            {
                pair aux1;
                aux1 = pairs[i + 1];
                pairs[i + 1] = pairs[i];
                pairs[i] = aux1;
                swap_count++;
            }
        }
    }
    while (swap_count != 0);
    return;
}
//create a bool function to see if we created a cycle or not
bool cycle(int winner, int loser)
{
    //Prompt to compare if the next loser isn't equal to the winner after use recursion (to compare i = winner)
    //because the first attempt is obviosly false
    if (loser == winner)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        //esto checa si locked es verdadero o falso, si es falso no entra al if
        if (locked[loser][i] && cycle(winner, i))
        {
            return true;
        }
    }
    return false;

}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // we check if the pair create a cycle if not we locked.
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //in terms of the array locked, when the winner has all the column false
    string winner;
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
            if (false_count == candidate_count)
            {
                winner = candidates[i];
            }
        }
    }
    printf("%s\n", winner);
    return;
}