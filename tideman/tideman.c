#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9
#define initial 1
#define visited 2
#define finished 3

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

bool has_cycle = false;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void check_cycle(int winner, int loser, int original_winner);
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
    for (int i = 0; i < pair_count; i ++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // loop into the candidates array
    for (int i = 0; i < candidate_count; i++)
    {
        // check if name is the ith cadidate
        if (strcmp(name, candidates[i]) == 0)
        {
            // ranks[i] = index of the candidate, who is the rank preference for the voter
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // loop over ranks
    for (int i = 0; i < candidate_count; i++)
    {
        int candidate_idx = ranks[i];
        int rank = i + 1;

        // for every rank compare others candidates
        for (int j = i + 1; j < candidate_count; j++)
        {
            int compare_candidate_idx = ranks[j];
            int compare_rank = j + 1;

            if (rank < compare_rank)
            {
                preferences[candidate_idx][compare_candidate_idx] += 1;
            }
            else
            {
                preferences[compare_candidate_idx][candidate_idx] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // loop over candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pair_count += 1;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pair_count += 1;
                pairs[pair_count - 1].winner = j;
                pairs[pair_count - 1].loser = i;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        int winner_idx = pairs[i].winner;
        int loser_idx = pairs[i].loser;
        int pair_winner_strength = preferences[winner_idx][loser_idx];

        for (int j = i + 1; j < pair_count; j++)
        {
            int compare_winner_idx = pairs[j].winner;
            int compare_loser_idx = pairs[j].loser;
            int compare_pair_winner_strength = preferences[compare_winner_idx][compare_loser_idx];

            if (pair_winner_strength < compare_pair_winner_strength)
            {
                pair a =  pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = a;
            }

        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        has_cycle = false;

        check_cycle(winner, loser, winner);

        if (has_cycle == false)
        {
            locked[winner][loser] = true;
        }
    }
}

void check_cycle(int winner, int loser, int original_winner)
{
    if (loser == original_winner)
    {
        has_cycle = true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        // check if loser has win
        if (locked[loser][i] == 1)
        {
            check_cycle(loser, i, original_winner);
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        int sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] != 0)
            {
                sum += 1;
            }
        }
        if (sum == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }
}
