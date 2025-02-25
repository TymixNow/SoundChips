#ifndef WAV_FILE_GENERATOR_HPP
#define WAV_FILE_GENERATOR_HPP

#include "wav_gen.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#define FILE_ADD file_output +=

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
    class Wav
    {
    private:
        static vector<unsigned char> byte_array(int number)
        {
            return { (unsigned char)((number & (0xff << 0)) >> 0), (unsigned char)((number & (0xff << 8)) >> 8), (unsigned char)((number & (0xff << 16)) >> 16), (unsigned char)((number & (0xff << 24)) >> 24) };
        }
        static vector<unsigned char> byte_array(short number)
        {
            return { (unsigned char)((number & (0xff << 0)) >> 0), (unsigned char)((number & (0xff << 8)) >> 8) };
        }
        static vector<unsigned char> size_prefix(vector<unsigned char> data)
        {
            int size = data.size();
            vector<unsigned char> length = byte_array(size);
            return length;
        }

        static void get_data(vector<unsigned char> &data, vector<unsigned char> wave)
        {
            data = wave;
        }

    public:
        static void make(vector<unsigned char> wave)
        {
            vector<unsigned char> data;

            ofstream file("output.wav", ios::out | ios::binary);

            vector<unsigned char> file_output;

            //FileFormatID
            FILE_ADD "WAVE";
            //FormatBlocID
            FILE_ADD "fmt ";
            //BlocSize
            FILE_ADD byte_array(16);
            //AudioFormat
            FILE_ADD byte_array((short)1);
            //NbrChannels
            FILE_ADD byte_array((short)1);
            //Frequency
            FILE_ADD byte_array(44100);
            //BytePerSec
            FILE_ADD byte_array(44100);
            //BytePerBloc
            FILE_ADD byte_array((short)1);
            //BitsPerSample
            FILE_ADD byte_array((short)8);
            //DataBlocID
            FILE_ADD "data";





            get_data(data, wave);



            vector<unsigned char> str;
            str = data;
            vector<unsigned char> file_length = size_prefix(str);

            //DataSize
            FILE_ADD file_length;
            //SampledData
            FILE_ADD str;


            //FileTypeBlocID, FileSize 
            file << "RIFF";
            for (auto ch : size_prefix(file_output))
            {
                file << ch;
            }
            
            for (auto ch : file_output)
            {
                file << ch;
            }
        }
    };
} // namespace WavWrapper
#endif
