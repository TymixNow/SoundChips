#include <vector>
namespace Sort
{
    namespace Swap
    {
        using namespace std;
        #define sample unsigned char

        void Swap(vector<sample>& array, int a, int b, vector<vector<sample>>& cache)
        {
            cache.push_back(array);
            int temp = array[a];
            array[a] = array[b];
            array[b] = temp;
        }

        #ifndef BUB_SORT
        #define BUB_SORT

        void bubble(vector<sample>& array, vector<vector<sample>>& cache)
        {
            for (int i = array.size() - 2; i >= 0; i--)
            {
                for (int j = 0; j < i; j++)
                {
                    if (array[j] > array[j+1])
                    {
                        Swap(array, j, j+1, cache);
                    }
                }
            }
            cache.push_back(array);
        }

        #endif
    }
}