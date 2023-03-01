#include <cs50.h>
#include <stdio.h>

typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[3];
bool locked[3][3];

int initial = 1;
int visited = 2;
int finished = 3;

int vertices_status[3];

void lock_pairs(void);
void dfs(int vertice);

int main(void)
{
    for (int i = 0; i < 3; i++)
    {
        pairs[i].winner = get_int("Winner: ");
        pairs[i].loser = get_int("Loser: ");
    }

    lock_pairs();

}



void lock_pairs(void)
{
    // 1. create a control array to keep status of a vertice (initial = 1, visited = 2, finished = 3)
    // made in top of the file

    // 2. iterate over array and put all vertices to initial status
    for (int i = 0; i < 3; i++)
    {
        vertices_status[i] = initial;
    }

    // 3. apply depth first search function in first winner and after for any other winner with initial status
    dfs(pairs[0].winner);

    for (int i = 0; i < 3; i++)
    {
        if (vertices_status[pairs[i].winner] == initial)
        {
            dfs(pairs[i].winner);
        }
    }

}

void dfs(int winner)
{
    // 4. dfs function starts updating vertice status to visited
    vertices_status[vertice] = visited;

    // 5. for this vertice iterate over adjecents (edge comcept origin > dest, in this case winner > loser)
    for (int i = 0; i < 3; i++)
    {
        // 6. check if edge exists
        if (i == loser)
        {
            // 6. if status of next adjecnt is initial, lock and apply dfs
            if (vertices_status[loser] == initial)
            {
                locked[winner][loser] = true;
                dfs(loser);
            }
            // 7. else if status of next adjecnt is visited, it's a back edge and do not lock
            else if (vertices_status[loser] == visited)
            {
                printf("Back edge");
            }
        }
    }
    vertices_status[vertice] = finished;
}



// pick next pair and save winner in already passed winners

// save loser wins in temp array

// if loser has won one person that won a already passed winner, it's a cycle


