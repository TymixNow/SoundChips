#include "wavstream.hpp"
#include "freq_gen.hpp"
#include <iostream>

using namespace std;
using namespace WavWrapper;

int main(int argc, char const *argv[])
{
    unsigned int note, length;
    cout << "note, length" << endl;
    cin >> note >> length;
    vector<unsigned char> waveform = {0x80,0x40,0x00,0x40,0x80,0xc0,0xff,0xc0};
    int period = FreqGen::FreqGen::gen(note)/waveform.size();
    vector<sample> wave;
    for (int i = 0; i < waveform.size(); i++)
    {
        vector<unsigned char> reps(period, waveform[i]);        
        wave += reps;
    }
    wavstream stream;
    for (int i = 0; i < length; i++)
    {
        stream << wave;
    }
    stream >> "output.wav";
    return 0;
}
