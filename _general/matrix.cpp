#include <vector>
#include <stdexcept>
namespace Mx
{
    using namespace std;
    class Triangular
    {
        vector<vector<int>> data;
        int size;
        int get(int x, int y)
        {
            if (x==y) return 1;
            if (x<y) return 0;
            if (x>y) try {return data.at(x).at(y);} catch(out_of_range) {return 0;};
        }
        Triangular(){}
        Triangular(vector<vector<int>> d)
        {
            data = d;
            size = d.size() + 1;
        }
        Triangular invert()
        {
            Triangular out;
            for (int i = 0; i < size; i++)
            {
                vector<int> out_line(i,0);
                vector<int> b(size, 0);
                b[i] = 1;
                for (int j = 0; j < size; j++)
                {
                    out_line[j] = b[j];
                    for (int k = 0; k < j; k++)
                    {
                        out_line[j] -= get(j,k)*out_line[k];
                    }
                }
                out.data.push_back(out_line);
            }
            return out;
        }
        static vector<int> transform(vector<int> vec, Triangular matrix)
        {
            vector<int> out;
            for (int i = 0; i < vec.size(); i++)
            {
                int out_dim = 0;
                for (int j = 0; j < i; j++)
                {
                    out_dim += vec[j] * matrix.get(i,j);
                }
                out.push_back(out_dim);
            }
            return out;
        }
    };
} // namespace Mx