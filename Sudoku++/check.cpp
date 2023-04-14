#include <vector>
#include <string>

using namespace std;

bool now_row(int sudoku[9][9])
{
    int i, j;
    int n;
    bool res = true;
    for (i = 0; i < 9; i++)
    {
        int num[9] = { 0 };
        for (j = 0; j < 9; j++)
        {
            n = sudoku[i][j] - 1;
            if (n != -1) {
                num[n] += 1;
                if (num[n] > 1)
                {
                    res = false;
                    break;
                }
            }
        }
    }
    return (res);
}

bool now_col(int sudoku[9][9])
{
    int i, j;
    int n;
    bool res = true;
    for (j = 0; j < 9; j++)
    {
        int num[9] = { 0 };
        for (i = 0; i < 9; i++)
        {
            n = sudoku[i][j] - 1;
            if (n != -1) {
                num[n] += 1;
                if (num[n] > 1)
                {
                    res = false;
                    break;
                }
            }
        }
    }
    return (res);
}

bool now_sq(int sudoku[9][9])
{
    int i, j, k;
    int n;
    bool res = true;
    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            int num[9] = { 0 };
            for (k = 0; k < 3; k++)
            {
                for (int d = 0; d < 3; d++)
                {
                    n = sudoku[i + k][j + d] - 1;
                    if (n != -1)
                    {
                        num[n] += 1;
                        if (num[n] > 1)
                        {
                            res = false;
                            break;
                        }
                    }
                }
            }
        }
    }
    return(res);
}

bool now_check(int sudoku[9][9])
{
    bool f_1 = true;
    bool f_2 = true;
    bool f_3 = true;
    f_1 = now_row(sudoku);
    if (f_1) {
        f_2 = now_col(sudoku);
    }
    if (f_1 && f_2) {
        f_3 = now_sq(sudoku);
    }
    return (f_1 && f_2 && f_3);
}

int summ_row(int row[9])
{
    int j = 0;
    int sum = 0;
    for (j = 0; j < 9; j++)
    {
        sum += row[j];
    }
    return(sum);
}

bool check_row(int sudoku[9][9])
{
    int i = 0;
    bool flag = true;
    for (i = 0; i < 9; i++)
    {
        if (summ_row(sudoku[i]) != 45)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool check_col(int sudoku[9][9])
{
    int i = 0;
    int j = 0;
    int sum = 0;
    bool flag = true;
    for (j = 0; j < 9; j++)
    {
        sum = 0;
        for (i = 0; i < 9; i++)
        {
            sum += sudoku[i][j];
        }
        if (sum != 45)
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool check_sq(int sudoku[9][9])
{
    int i = 0;
    int j = 0;
    int k = 0;
    int sum = 0;
    bool flag = true;
    for (i = 0; i < 9; i += 3)
    {
        for (j = 0; j < 9; j += 3)
        {
            sum = 0;
            for (k = 0; k < 3; k++)
            {
                sum += sudoku[i + k][j];
                sum += sudoku[i + k][j + 1];
                sum += sudoku[i + k][j + 2];
            }
            if (sum != 45)
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

bool final_check(int sudoku[9][9])
{
    int i = 0;
    bool s_flag = check_row(sudoku);

    if (s_flag)
    {
        s_flag = check_col(sudoku);
    }
    if (s_flag)
    {
        s_flag = check_sq(sudoku);
    }
    return s_flag;
}
