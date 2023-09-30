#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count this is the stucture of the candidates
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage. If the user doesn't enter a argument return error code 1
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates. The max amount of candidates is 9 
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    //If the number of candidates is less than 9 it will be places in an array
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{   
    //The loop over the candidates
    for (int i = 0; i < candidate_count; i++)
    {
        //strcmp is string compare which will compare the candidate name with the input. 
        // If there is the vote withh increase by 1 else is false
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    //The max vote starts at 0 and increase with each count. 
    int max_votes = 0;
    for (int i = 0; i < candidate_count; i++)
    {   
        //while looping if the candidates votes is higher than max vote update the variable.
        //This way the max_vote will hold the number of the higher candidate
        if (candidates[i].votes > max_votes)
        {
            max_votes = candidates[i].votes;
        }
    } 
    for (int i = 0; i < candidate_count; i++)
    {   
        //compare the candidates votes to max vote and print the once that match since that means
        // It has the higher number of votes after going through the entire loop. 
        if (candidates[i].votes == max_votes)
        {
            //If we print a string is %s || int is %i. 
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}