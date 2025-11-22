#include <stdio.h>

// Define the initial Sudoku puzzle
int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

// Check if placing puzzle[row][col] is valid in its current location
int is_valid_initial(int puzzle[9][9], int row, int col)
{
    int val = puzzle[row][col];
    if (val == 0) // Empty cells are always valid
    {
        return 1;
    }

    // Check row and column for duplicates
    for (int i = 0; i < 9; i++)
    {
        if (i != col && puzzle[row][i] == val)
        {
            return 0;
        }
        if (i != row && puzzle[i][col] == val)
        {
            return 0;
        }
    }

    // Check 3x3 box (Square)
    int box_start_row = row - row % 3;
    int box_start_col = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int r = box_start_row + i;
            int c = box_start_col + j;

            if ((r != row || c != col) && puzzle[r][c] == val)
            {
                return 0;
            }
        }
    }

    return 1; // Valid
}

// Validate the whole puzzle before solving
int is_valid_puzzle(int puzzle[9][9])
{
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++)
        {
            if (!is_valid_initial(puzzle, row, col))
            {
                return 0;
            }
        }
    }
    return 1;
}

// Check if placing 'val' at (row, col) is a valid move
int valid_move(int puzzle[9][9], int row, int col, int val)
{
    for (int i = 0; i < 9; i++)
    {
        if (puzzle[row][i] == val || puzzle[i][col] == val)
        {
            return 0;
        }
    }

    // Check the 3x3 box
    int r = row - row % 3;
    int c = col - col % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (puzzle[r + i][c + j] == val)
            {
                return 0;
            }
        }
    }

    return 1;
}

// Recursive function to solve the puzzle using backtracking
int solve_puzzle(int puzzle[9][9], int row, int col)
{
    if (col == 9) // If column exceeds, move to next row
    {
        if (row == 8)
        {
            return 1; // If it's the last cell, puzzle is solved
        }
        row++;
        col = 0;
    }

    if (puzzle[row][col] > 0)
    {
        return solve_puzzle(puzzle, row, col + 1); // Skip pre-filled cells
    }

    for (int i = 1; i <= 9; i++) // Try values from 1 to 9
    {
        if (valid_move(puzzle, row, col, i))
        {
            puzzle[row][col] = i;
            if (solve_puzzle(puzzle, row, col + 1))
            {
                return 1;
            }
            puzzle[row][col] = 0; // Backtracking Step
        }
    }
    return 0;
}

// Function to print the puzzle in grid format
void print_puzzle(int puzzle[9][9])
{
    printf("\n+-------+-------+-------+");
    for (int row = 0; row < 9; row++)
    {
        if (row % 3 == 0 && row != 0)
        {
            printf("\n|-------+-------+-------|");
        }
        printf("\n");

        for (int col = 0; col < 9; col++)
        {
            if (col % 3 == 0)
            {
                printf("| ");
            }

            if (puzzle[row][col] != 0)
            {
                printf("%d ", puzzle[row][col]);
            }
            else
            {
                printf("  ");
            }
        }
        printf("|");
    }
    printf("\n+-------+-------+-------+\n");
}

int main()
{
    printf("\n\t*** Welcome to SUDOKU Solver ***");
    printf("\n\nOriginal Puzzle:");
    print_puzzle(puzzle);

    if (!is_valid_puzzle(puzzle))
    {
        printf("\nThe initial puzzle is invalid.\n");
        return 1;
    }

    if (solve_puzzle(puzzle, 0, 0))
    {
        printf("\nSolved Puzzle:");
        print_puzzle(puzzle);
    }
    else
    {
        printf("\n This puzzle is not Solvable\n");
    }

    return 0;
}
