#include "wav_gen.hpp"
#include "freq_gen.hpp"
#include <iostream>
#include <sstream>

using namespace std;
void operator+=(vector<unsigned char> &a, vector<unsigned char> b)
{
    a.insert(a.end(), b.begin(),b.end());
}
void operator+=(vector<unsigned char> &a, string b)
{
    vector<unsigned char> c(b.begin(),b.end());
    a.insert(a.end(), c.begin(),c.end());
}
int main(int argc, char const *argv[])
{
    unsigned int note, length;
    cout << "note, length" << endl;
    cin >> note >> length;
    vector<unsigned char> waveform = {0x80,0x40,0x00,0x40,0x80,0xc0,0xff,0xc0};
    int period = FreqGen::FreqGen::gen(note)/waveform.size();
    vector<unsigned char> wave;
    for (int i = 0; i < waveform.size(); i++)
    {
        vector<unsigned char> reps(period, waveform[i]);        
        wave += reps;
    }
    vector<unsigned char> data_stream;
    for (int i = 0; i < length; i++)
    {
        data_stream += wave;
    }
    WavWrapper::Wav::make(data_stream);
    return 0;
}
