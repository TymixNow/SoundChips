#include <iostream>
#include <fstream>
#include <sstream>
#define FILE_ADD file_output +=
#include <vector>
// <ChatGPT>
struct Pentad
{
private:
	char value; // Store the nibble in the lower 5 bits of a char

	// Ensure the value always fits in 4 bits (0-31)
	void normalize() {
		value &= 0x1F; // Mask to keep only the lower 5 bits
	}

public:
	// Constructor
	Pentad(char initialValue = 0) {
		value = initialValue & 0x1F; // Only keep the lower 5 bits
	}

	// Implicit conversion to char
	operator char() const {
		return value;
	}

	// Implicit conversion from char
	Pentad& operator=(char newValue) {
		value = newValue & 0x1F;
		return *this;
	}
};
struct Nib 
{
private:
	char value; // Store the nibble in the lower 4 bits of a char

	// Ensure the value always fits in 4 bits (0-15)
	void normalize() {
		value &= 0x0F; // Mask to keep only the lower 4 bits
	}

public:
	// Constructor
	Nib(char initialValue = 0) {
		value = initialValue & 0x0F; // Only keep the lower 4 bits
	}

	// Implicit conversion to char
	operator char() const {
		return value;
	}

	// Implicit conversion from char
	Nib& operator=(char newValue) {
		value = newValue & 0x0F;
		return *this;
	}
};
// </ChatGPT>
class Chip
{
	char time;
	char rate;
	Pentad voltage;
	Pentad volume;
	Pentad offset;
	bool direction;
	bool saw;

	void init(char offset, char _rate, char vol)
	{
		time = 0;
		voltage = offset;
		rate = _rate;
		volume = vol;
	}
	char tick()
	{
		time++;
		time %= rate;
		if (time == 0) step();
		return voltage;
	}
	void step()
	{
		voltage = voltage + direction ? 1 : -1;
		if ((voltage == Pentad(volume + offset) || voltage == Pentad(offset - volume)) && !saw) direction = !direction;
	}

};
using namespace std;
struct sample
{
	int x;
	char y;
};
char nullerp(sample end, int x)
{
	char lbound_y = (end.y * x)/end.x;
	bool rounding = (lbound_y * end.x + (end.x >> 1)) >= x * end.y;
	return lbound_y + rounding;
}
sample zero_sample(char y)
{
	sample output;
	output.x = 0;
	output.y = y;
	return output;
}
sample lerp(sample start, sample end, int x)
{
	sample output;
	output.x = x;
	sample delta;
	delta.x = end.x - start.x;
	bool sign = end.x - start.x >= 0;
	delta.y = sign ? end.x - start.x : start.x - end.x;
	output.y = start.y + sign ? nullerp(delta, x - start.x) : -nullerp(delta, x - start.x);
	return output;
}
sample skip(sample mid, char y)
{
	sample output;
	output.x = mid.x;
	output.y = y;
	return output;
}
sample make(int x, char y)
{
	sample output;
	output.x = x;
	output.y = y;
	return output;
}
struct waveform
{
	char start;
	sample mid;
	char skip;
	char move;
};
string gen(int wavelength, waveform wave)
{
	string output;
	for (int i = 0; i < wavelength; i++)
	{
		if (i < wave.mid.x)
		{
			output.push_back(lerp(zero_sample(wave.start), wave.mid, i).y);
		}
		else
		{
			output.push_back(lerp(skip(wave.mid, wave.skip), make(wavelength, wave.move), i).y);
		}
	}
	return output;
}
string byte_array(int number)
{
	return { char((number & (0xff << 0)) >> 0), char((number & (0xff << 8)) >> 8), char((number & (0xff << 16)) >> 16), char((number & (0xff << 24)) >> 24) };
}
string byte_array(short number)
{
	return { char((number & (0xff << 0)) >> 0), char((number & (0xff << 8)) >> 8) };
}
string size_prefix(string data)
{
	int size = data.size();
	string length = byte_array(size);
	return length;
}

void get_data(stringstream &data)
{
	int wavelength;
	int length;
	cin >> wavelength;
	cout << endl;
	cin >> length;
	waveform wave;
	wave.start = 0;
	wave.mid = make(0, wavelength / 2);
	wave.skip = (char)255;
	wave.move = (char)255;
	for (int i = 0; i < length; i++)
	{
		data << gen(wavelength, wave);
	}
}

int main()
{
	stringstream data;

	ofstream file("output.wav");

	string file_output;

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
	FILE_ADD byte_array(10000);
	//BytePerSec
	FILE_ADD byte_array(10000);
	//BytePerBloc
	FILE_ADD byte_array((short)1);
	//BitsPerSample
	FILE_ADD byte_array((short)8);
	//DataBlocID
	FILE_ADD "data";





	get_data(data);



	string str;
	data >> str;
	string file_length = size_prefix(str);

	//DataSize
	FILE_ADD file_length;
	//SampledData
	FILE_ADD str;


	//FileTypeBlocID, FileSize 
	file << "RIFF" << size_prefix(file_output) << file_output;
}