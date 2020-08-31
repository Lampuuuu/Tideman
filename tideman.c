#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
// so if there are three candidates i & j go up to 2 starting by 0
// preferences [1][2] might be 1 or 2 or else
// this actually saves 3 values
// REPRESENTS THE NUMBER OF VOTERS WHO PREFER CANDIDATE I OVER CANDIDATE J
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
// the integers are the candidate indexes
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void swap(int a, int b);

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
    
    printf("pair count post sort: %i\n", pair_count);
    for (int j = 0; j < pair_count; j++)
    {
        printf("pair: %i, winner: %s, loser: %s, preferred by %i to %i \n", j + 1, candidates[pairs[j].winner], candidates[pairs[j].loser], preferences[pairs[j].winner][pairs[j].loser], preferences[pairs[j].loser][pairs[j].winner]);
    }
    
    lock_pairs();
    print_winner();
    return 0;
}


// returns bool
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //checks validity of the vote and then ranks it in "ranks"
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;    //i being the index of the candidate name
            return true;
        }
    }
    return false;
}

// since "ranks" is changed for every voter, this records it in preferences
void record_preferences(int ranks[])
{
    // double loop: recording candidate i over candidate j
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i+1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
// add it to the pairs count

void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] - preferences[j][i] > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            int dummyw = pairs[i].winner;
            int dummyl = pairs[i].loser;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].winner = dummyw;
            pairs[i + 1].loser = dummyl;
        }

    }
    return;
}


// Lock pairs into the candidate graph in order, without creating cycles
// lock pairs
// if a winner over the current winner has not yet lost, he is the new winner 
//SKIP OVER circling edges

void lock_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if ()
            {
                locked[pairs[i].winner][pairs[i].loser] = true
            }
        }
    }
    


    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

