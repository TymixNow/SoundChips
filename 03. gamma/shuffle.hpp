#include <vector>
#include <random>
namespace Shuffle
{
    namespace Swap
    {
        using namespace std;
        #define sample unsigned char

        void Swap(vector<sample>& array, int a, int b)
        {
            int temp = array[a];
            array[a] = array[b];
            array[b] = temp;
        }

        #ifndef SHUFFLE
        #define SHUFFLE
        void shuffle(vector<sample>& array, int seed)
        {
            srand(seed);
            for (int i = array.size() - 1; i >= 0; i--)
            {
                for (int j = 0; j < array.size(); j++)
                {
                    if (rand()%2 == 0)
                    {
                        Swap(array, j, i);
                    }
                }
            }
        }

        #endif
    }
}