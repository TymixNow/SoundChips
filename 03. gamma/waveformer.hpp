#ifndef WAVEFORM
#define WAVEFORM

#include "wavstream.hpp"
#include "freq_gen.hpp"

namespace Waveformer
{

    using namespace std;
    using namespace WavWrapper;

    vector<sample> Repeat(vector<unsigned char> waveform, unsigned int note, unsigned int length)
    {
        int period = FreqGen::FreqGen::gen(note)/waveform.size();
        vector<sample> wave;
        for (int i = 0; i < waveform.size(); i++)
        {
            vector<unsigned char> reps(period, waveform[i]);        
            wave += reps;
        }
        vector<sample> stream;
        for (int i = 0; i < length; i++)
        {
            stream += wave;
        }
        return stream;
    }
} // namespace Waveformer


#endif
