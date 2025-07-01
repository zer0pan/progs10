#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// global variable of the number of voters
int voter_count;

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int difference; // eg. If voter_count = 8 preferences[i][j] = 6 then
                    // preferences[j][i] = 8-6 =2 , and difference = 6-2= 4
} pair;

// Array of candidates
string candidates[MAX];
int candidate_count;
pair pairs[MAX * (MAX - 1) / 2]; // MAX choose 2
int pair_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool iscycle(int start, int end);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ....]\n");
        return 1;
    }
    else if (argc == 2)
    {
        printf("%s\n", argv[1]);
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    //_______________________________________________________________________________!
    //____________________________START___________________________________________________!

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
            preferences[i][j] = 0; // initiallize prefenreces
        }
    }

    pair_count = 0; // must be initialized
    voter_count = get_int("Number of voters: ");

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
    // TODO ok
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
    // TODO ok
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int dif; // difference of winner with loser
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            dif = preferences[i][j] - preferences[j][i];
            if (dif > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pairs[pair_count].difference = dif;
                pair_count++;
            }
            else if (dif < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pairs[pair_count].difference = dif * -1;
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
    pair temp;
    for (int i = 1; i < pair_count; i++)
    {
        for (int j = pair_count - 1; j >= i; j--)
        {
            if (pairs[j].difference > pairs[j - 1].difference)
            {
                temp = pairs[j - 1];
                pairs[j - 1] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
    /*for (int i = 0; i < pair_count; i++)
    {
      printf("%d %d %d ", pairs[i].winner, pairs[i].loser, pairs[i].difference);
    }
    printf("\n");*/
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    locked[pairs[0].winner][pairs[0].loser] = true;
    locked[pairs[1].winner][pairs[1].loser] = true;
    for (int k = 2; k < pair_count; k++)
    {
        int start = pairs[k].winner;
        int end = pairs[k].loser;
        bool cycle = iscycle(start, end);
        if (!cycle)
        {
            locked[start][end] = true;
        }
    }

    return;
}

bool iscycle(int start, int end)
{
    if (end == start)
    {
        // Found a cycle
        return true;
    }

    for (int next = 0; next < candidate_count; next++)
    {
        if (locked[end][next])
        {
            if (iscycle(start, next))
            {
                return true;
            }
        }
    }
    return false;
}
// Print the winner of the election
void print_winner(void)
{
    // TODO
    /*for (int i = 0; i < candidate_count; i++)
    {
      for (int j = 0; j < candidate_count; j++)
      {
        printf("%d", locked[i][j]);
      }
      printf("\n");
    }*/
    for (int j = 0; j < candidate_count; j++)
    {
        int flag = 0;
        for (int i = 0; i < candidate_count; i++)
        {
            // printf("%d", i);
            if (locked[i][j] == true)
            {
                flag = 1;
            }
        }
        if (flag == 0)
        {
            printf("%s\n", candidates[j]);
            break;
        }
    }
    return;
}
