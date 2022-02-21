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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //printf("candidates[i] = %s\n", candidates[i]);
        //printf("Name = %s\n", name);
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            //printf("Ranks %i = %i\n", rank + 1, ranks[rank]);
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
            //printf("preferences[%i][%i] = %i\n", ranks[i], ranks[j], preferences[ranks[i]][ranks[j]]);
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != i)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    //printf("Pair %i Winner: %i Loser: %i\n", pair_count, pairs[pair_count].winner, pairs[pair_count].loser);
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair placeholder1;
    for (int i = 0; i < pair_count - 1; i++)
    {
        int biggest = 0;
        for (int j = i; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > biggest)
            {
                biggest = preferences[pairs[j].winner][pairs[j].loser];
                placeholder1 = pairs[j];
            }
        }
        for (int k = i; k < pair_count; k++)
        {
            if (placeholder1.winner == pairs[k].winner && placeholder1.loser == pairs[k].loser)
            {
                pair placeholder2 = pairs[i];
                pairs[i] = pairs[k];
                pairs[k] = placeholder2;
            }
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        //   printf("Pair %i [%i][%i]: %i\n", i, pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
        //    printf("Pair [%i]: %i\n", i, preferences[pairs[i].winner][pairs[i].loser]);
    }
    return;
}

bool circle(int m, int n, int stop)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[n][j] == true && j != m)
        {
            if (circle(m, j, stop) == true)
            {
                return true;
            }
            if (stop == 1)
            {
                return true;
            }

        }
        else if (locked[n][j] == true && j == m)
        {
            stop = 1;
            return true;
        }

    }
    if (stop == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int STOP;
    int stop = 0;
    for (int i = 0; i < pair_count; i++)
    {
        STOP = 0;
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (circle(pairs[i].winner, pairs[i].loser, STOP) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    for (int i = 0; i < pair_count; i++)
    {
        printf("Locked[%i][%i] = %i\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser]);
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s\n", candidates[i]);
        for (int j = 0; j < candidate_count; i++)
        {
            if (locked[j][i] == false)
            {
                continue;
            }
            if (locked[j][i] == true)
            {
                break;
            }
            if (j == candidate_count - 1)
            {
                printf("%s\n", candidates[i]);
            }
        }
    }
    return;
}

