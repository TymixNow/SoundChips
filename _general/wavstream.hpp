#ifndef WAV_STREAM_HPP
#define WAV_STREAM_HPP

#include <fstream>
#include <sstream>
#include <vector>

#define FILE_ADD file_output +=
#define sample unsigned char

namespace WavWrapper
{
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
    vector<unsigned char> byte_array(int number)
    {
        return { (unsigned char)((number & (0xff << 0)) >> 0), (unsigned char)((number & (0xff << 8)) >> 8), (unsigned char)((number & (0xff << 16)) >> 16), (unsigned char)((number & (0xff << 24)) >> 24) };
    }
    vector<unsigned char> byte_array(short number)
    {
        return { (unsigned char)((number & (0xff << 0)) >> 0), (unsigned char)((number & (0xff << 8)) >> 8) };
    }

    class wavstream
    {
    private:
        vector<sample> data;
        int sample_rate;
    public:
        void operator<<(vector<sample> input)
        {
            data += input;
        }
        void operator<<(string input)
        {
            data += input;
        }
        void operator>>(string filename)
        {
            ofstream file(filename, ios::out | ios::binary);
            size_prefix();
            auto temp = data;
            data.clear();
            data += "WAVE";
            data += "fmt ";
            //constant block size
            data += byte_array(16);
            //constant audio format
            data += byte_array((short)1);
            //channels
            data += byte_array((short)1);
            //freq
            data += byte_array(sample_rate);
            // bytes/sec
            data += byte_array(sample_rate);
            // bytes/block
            data += byte_array((short)1);
            // bits/sample
            data += byte_array((short)8);
    
            data += "data";
            data += temp;

            size_prefix();

            temp = data;
            data.clear();

            data += "RIFF";

            data += temp;

            for (auto ch : data)
            {
                file << ch;
            }

            data.clear();
        }
        void size_prefix()
        {
            int size = data.size();
            vector<unsigned char> length = byte_array(size);
            auto temp = data;
            data = length;
            data += temp;
        }
        wavstream(int rate = 44100);
        ~wavstream();
    };
    
    wavstream::wavstream(int rate = 44100)
    {
        sample_rate = rate;
    }
    
    wavstream::~wavstream()
    {
    }
} // namespace WavWrapper
#endif
