#include <iostream>
#include <exception>
#include <cstddef>

size_t max(size_t n, size_t m)
{
    if (n > m)
    {
        return n;
    }
    else
    {
        return m;
    }
}
void free_matrix(int **matrix, size_t rows)
{
    if (matrix != nullptr)
    {
        for (size_t i = 0; i < rows; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

int **concat_rows(
    const int *const *lhs, size_t n1, size_t m1,
    const int *const *rhs, size_t n2, size_t m2)
{
    size_t res_rows = max(n1, n2);
    int **res = nullptr;
    size_t notnull_rows = 0;

    try
    {
        res = new int *[res_rows];

        for (size_t i = 0; i < res_rows; i++)
        {
            size_t cur_len = 0;
            if (i < n1)
            {
                cur_len += m1;
            }
            if (i < n2)
            {
                cur_len += m2;
            }

            res[i] = new int[cur_len];
            notnull_rows++;

            size_t index = 0;
            if (i < n1)
            {
                for (size_t j = 0; j < m1; j++)
                {
                    res[i][index] = lhs[i][j];
                    index++;
                }
            }

            if (i < n2)
            {
                for (size_t j = 0; j < m2; j++)
                {
                    res[i][index] = rhs[i][j];
                    index++;
                }
            }
        }
    }
    catch (const std::bad_alloc &)
    {
        if (res != nullptr)
        {
            free_matrix(res, notnull_rows);
        }
        throw;
    }

    return res;
}

int main()
{
    int **lhs = nullptr;
    int **rhs = nullptr;
    int **res = nullptr;

    long long m1x = 0, m2x = 0;
    long long n1x = 0, n2x = 0;
    size_t m1 = 0, m2 = 0;
    size_t n1 = 0, n2 = 0;
    size_t res_rows = 0;
    size_t notnull_lhs = 0;
    size_t notnull_rhs = 0;

    try
    {
        std::cout << "Введите количество строк и столбцов 1-й матрицы: ";
        std::cin >> n1x >> m1x;
        if (!(std::cin) || n1x <= 0 || m1x <= 0)
        {
            std::cerr << "Ошибка ввода данных матрицы\n";
            return 1;
        }
        n1 = n1x;
        m1 = m1x;
        lhs = new int *[n1];
        std::cout << "\nВведите элементы 1-й матрицы:\n";
        for (size_t i = 0; i < n1; i++)
        {
            lhs[i] = new int[m1];
            notnull_lhs++;

            for (size_t j = 0; j < m1; j++)
            {
                std::cin >> lhs[i][j];
                if (!(std::cin))
                {
                    std::cerr << "Ошибка ввода элементов\n";
                    free_matrix(lhs, notnull_lhs);
                    return 1;
                }
            }
        }

        std::cout << "\nВведите количество строк и столбцов 2-й матрицы: ";
        std::cin >> n2x >> m2x;
        if (!(std::cin) || n2x <= 0 || m2x <= 0)
        {
            std::cerr << "Ошибка ввода данных матрицы\n";
            free_matrix(lhs, notnull_lhs);
            return 1;
        }
        n2 = n2x;
        m2 = m2x;
        rhs = new int *[n2];
        std::cout << "\nВведите элементы 2-й матрицы:\n";
        for (size_t i = 0; i < n2; i++)
        {
            rhs[i] = new int[m2];
            notnull_rhs++;

            for (size_t j = 0; j < m2; j++)
            {
                std::cin >> rhs[i][j];
                if (!(std::cin))
                {
                    std::cerr << "Ошибка ввода элементов\n";
                    free_matrix(lhs, notnull_lhs);
                    free_matrix(rhs, notnull_rhs);
                    return 1;
                }
            }
        }

        res = concat_rows(lhs, n1, m1, rhs, n2, m2);
        res_rows = max(n1, n2);

        std::cout << "\nРезультирующий массив массивов:\n";
        for (size_t i = 0; i < res_rows; i++)
        {
            size_t cur_len = 0;
            if (i < n1)
            {
                cur_len += m1;
            }
            if (i < n2)
            {
                cur_len += m2;
            }

            for (size_t j = 0; j < cur_len; j++)
            {
                std::cout << res[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        free_matrix(lhs, notnull_lhs);
        free_matrix(rhs, notnull_rhs);
        return 2;
    }

    free_matrix(lhs, n1);
    free_matrix(rhs, n2);
    free_matrix(res, res_rows);
    return 0;
}