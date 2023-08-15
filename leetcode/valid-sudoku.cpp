#include <vector>

bool solve(std::vector<std::vector<char>> const& board)
{
    std::vector<int> rowMemo(9*9, 0);
    std::vector<int> colMemo(9*9, 0);
    std::vector<int> cellMemo(9*9, 0);
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            if (board[row][col] != '.')
            {
                int const digit      = board[row][col] - '0' - 1;
                int const rowOffset  = 9*row + digit;
                int const colOffset  = 9*col + digit;
                int const cellOffset = 9*(3*(row/3) + col/3) + digit;

                if (rowMemo[rowOffset] ||
                    colMemo[colOffset] ||
                    cellMemo[cellOffset])
                {
                    return false;
                }

                rowMemo[rowOffset]   = 1;
                colMemo[colOffset]   = 1;
                cellMemo[cellOffset] = 1;
            }
        }
    }

    return true;
}

int main()
{
    solve({{'5','3','.','.','7','.','.','.','.'}
          ,{'6','.','.','1','9','5','.','.','.'}
          ,{'.','9','8','.','.','.','.','6','.'}
          ,{'8','.','.','.','6','.','.','.','3'}
          ,{'4','.','.','8','.','3','.','.','1'}
          ,{'7','.','.','.','2','.','.','.','6'}
          ,{'.','6','.','.','.','.','2','8','.'}
          ,{'.','.','.','4','1','9','.','.','5'}
          ,{'.','.','.','.','8','.','.','7','9'}});
}