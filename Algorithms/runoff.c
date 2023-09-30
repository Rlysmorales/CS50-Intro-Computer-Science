#include <cs50.h>
#include <stdio.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status. This is the structure given
//This time the candidate has name, votes and if is eliminated
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage. If arguments is less than 2
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {   
        //We have +1 to account for the name of the file. Arguments starts at [0] with file name
        // +1 will take you to [1]
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {   
        //loop through the candidates and see if the name match. 
        if (strcmp(candidates[i].name, name) == 0)
        {   
            // here we have the candidate and the rank and added to i
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{   
    //looping over the ranks
    for (int i = 0; i < voter_count; i++)
    {
        //looping over the voters
        for (int j = 0; j < candidate_count; j++)
        {   
            //depending on the votes number for example 0 is eliminated or the lowest number
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    
    int majority_votes = voter_count/2;

    for (int i = 0; i < candidate_count; i++)
    {
        //check of the total score is more than half the total count
        //If it is it will print the name as the winner
        if (candidates[i].votes > majority_votes)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minimal_votes = voter_count;

    
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < minimal_votes)
        {
            minimal_votes = candidates[i].votes;
        }
    }
    return minimal_votes;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    int min_candidates_votes = 0;
    int max_candidates_votes = 0;

    //loop through all candidates, if candidates are tied, variable will be true
    for (int i = 0; i < candidate_count; i++)
    {
        //loop over all canidates that are not eliminated
        if (!candidates[i].eliminated)
        {
            min_candidates_votes++;
        }
        if (candidates[i].votes == min)
        {
            max_candidates_votes;
        }
    }
    // If two candidates have the same vote tie
    if (min_candidates_votes == max_candidates_votes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && min == candidates[i].votes)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}