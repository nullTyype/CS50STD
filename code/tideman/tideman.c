#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
string winner;

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool isLocked(int candidate);
void verify(pair basePair);
void check(int i);

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
    // TODO
    // ranks candidate[ith] according to name;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // return ranks that maps candidate based at voter's choice
            // so ranks[rank] is the rankth prefence of voter for i candidate;
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    // takes every rank ith refence
    // and compares with j choice position at the inner loop;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // validation for not set wrong positions to 0;
            if (i >= j && !preferences[ranks[i]][ranks[j]])
            {
                preferences[ranks[i]][ranks[j]] = 0;
            }
            else if (i < j)
            {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
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
            else if (preferences[i][j] < preferences[j][i])
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
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // define strength;
        int strong = preferences[pairs[i].winner][pairs[i].loser];
        // sorts array based at strength;
        for (int j = 0; j < pair_count; j++)
        {
            // holds value to compare;
            int compare = preferences[pairs[j].winner][pairs[j].loser];
            // if true, swaps values;
            if (strong > compare)
            {
                // holds pairs[i] value;
                pair holder;
                holder.winner = pairs[i].winner;
                holder.loser = pairs[i].loser;

                // swap values;
                pairs[i].winner = pairs[j].winner;
                pairs[i].loser = pairs[j].loser;
                pairs[j].winner = holder.winner;
                pairs[j].loser = holder.loser;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // select a basePair, if loser isn't locked to any other pair, lock basePair, in other hand,
    // if next candidate that is going to be locked, verify if it's next pair is locked to other, and so on,
    // verifying each case if in that moment, a cycle is created by verifying if the pair that is being pointed is locked to another;
    check(0);
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // show winner;
    if (winner != NULL)
    {
      printf("Winner is: %s\n", winner);
    }
    // in case there's no cycle;
    else
    {
        bool tie[candidate_count]; // tie[i] means candidate i loses

        // set all tie values to default;
        for (int k = 0; k < candidate_count; k++)
        {
            tie[k] = false;
        }

        // set all losers to true in tie array;
        for (int i = 0; i < pair_count; i++)
        {
            tie[pairs[i].loser] = true;
        }

        // search for candidate that any pair points to it;
        for (int j = 0; j < candidate_count; j++)
        {
            if (tie[j] == false)
            {
                winner = candidates[j];
                break;
            }
        }

        printf("Winner is: %s\n", winner);
    }

    return;
}

// verify if a base candidate is locked to any other candidate
bool isLocked(int candidate)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[candidate][j] == true)
        {
            return true;
        }
    }

    return false;
}


// select a basePair, if loser isn't locked to any other pair, lock basePair, in other hand,
// if next candidate that is going to be locked, verify if it's next pair is locked to other, and so on,
// verifying each case if in that moment, a cycle is created by verifying if the pair that is being pointed is locked to another;
void check(int i)
{
    pair basePair = pairs[i];
    // if isn't locked to no pair, directly lock actual pair to loser pair;
    if (!isLocked(basePair.loser))
    {
        locked[basePair.winner][basePair.loser] = true;
        check(i+1);
    }
    else
    {
        // stay aware if this one gets buggy, I mean, if cs50 requires lock pairs even if cycle is proved
        // #FIIXIXXXXXXXXXXXXXXXXITTTTTTTTTTTTTT
        if (i >= pair_count)
        {
            return;
        }
        else
        {
            verify(basePair);
            check(i+1);
        }
    }
}

// takes a base pair and verifies following loser trace if cycle returns to base pair
void verify(pair basePair)
{
    pair comparePair = basePair;
    bool cycle = false;

    // runs over every pair;
    for (int i = 0; i < pair_count; i++)
    {
        // verify if chosen pair continues to trace until reach the cycle,
        // verifying if matched pair (it is pointing to) was already locked with other one,
        // if doesn't, verify to next;
        if (comparePair.loser == pairs[i].winner && isLocked(pairs[i].winner))
        {
            comparePair = pairs[i];
            i = -1; // -1 fix loop insight bug where i jumps 0 when reseting comparePair;

            // means there's a cycle following loser trace;
            if (comparePair.loser == basePair.winner)
            {
                cycle = true;
                winner = candidates[basePair.loser];
                break;
            }
        }
    }

    if (cycle)
    {
        // ends function
        return;
    }
    else
    {
        // if pass all validations, it can lock;
        locked[basePair.winner][basePair.loser] = true;
    }
}