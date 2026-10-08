#include <iostream>
#include <exception>

int main()
{
    int n = 0;
    int m = 0;
    try
    {
        std::cin >> n >> m;
    }
    catch (std::bad_array_new_length &e)
    {
        if (n <= 0 || m <= 0)
        {
            std::cerr << "Oshibka: " << e.what() << std::endl;
            return 1;
        }
    }
    int **arr = nullptr;
    try
    {
        arr = new int *[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = new int[m];
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << "Oshibka: " << e.what() << std::endl;
        return 2;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cin >> arr[i][j];
        }
        if (!std::cin)
        {
            std::cerr << "Oshibka: std::invalid_argument" << std::endl;
            return 1;
        }
    }
    int **tr = nullptr;
    try
    {
        tr = new int *[m];
        for (int i = 0; i < m; i++)
        {
            tr[i] = new int[n];
        }
    }
    catch (const std::bad_alloc &e)
    {
        std::cout << "Oshibka: " << e.what() << std::endl;
        return 2;
    }
    int k = 0;
    for (int i = 0; i < m; i++)
    {
        k = 0;
        for (int j = 0; j < n; j++)
        {
            tr[i][j] = arr[j][i];
            k++;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << tr[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
