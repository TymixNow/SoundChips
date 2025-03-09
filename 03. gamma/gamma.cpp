#include "wavstream.hpp"
#include "freq_gen.hpp"
#include "sorter.hpp"
#include "waveformer.hpp"
#include "shuffle.hpp"
#include <iostream>
#include <random>

using namespace std;
using namespace WavWrapper;

int main(int argc, char const *argv[])
{
    vector<unsigned char> waveform;
    cout << "waveform (-1 to end): ";
    int input;
    do
    {
        cin >> input;
        waveform.push_back(input);
    } while (input != -1);
    waveform.pop_back();
    cout << "seed: ";
    int seed;
    cin >> seed;

    vector<unsigned char> order;
    for (int i = 0; i < waveform.size(); i++)
    {
        order.push_back(i);
    }

    cout << "note: ";
    int note;
    cin >> note;

    cout << "length: ";
    int length;
    cin >> length;

    order = Waveformer::Repeat(order, note, length);

    Shuffle::Swap::shuffle(order, seed);
    vector<vector<sample>> cache;
    Sort::Swap::bubble(order, cache);

    wavstream stream;
    for (auto &&ordering : cache)
    {
        vector<sample> wave;
        for (auto &&samp : ordering)
        {
            wave.push_back(waveform[samp]);
        }
        stream << wave;
    }

    stream >> "output.wav";
    
    return 0;
}
