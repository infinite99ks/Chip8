#include "chip8.h"

// Unsigned because we can't go negative, and also because we go from 0x000 to 0xFFF.
const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADDRESS = 0x50; // The start address of our fonts.

// Each character in here consists of 5 bytes, we simply stack those 5 bytes on top of each other,
// and turn them into binary, that binary should bear resemblence to the character we have in mind.

const unsigned int FONTSET_SIZE = 80; // The total size of our fonts (16 x 5 bytes).
uint8_t fontset[FONTSET_SIZE] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip8::Chip8() 
{
    // Intializing the PC, setting it to place of the first instruction
    // of our non-reserved addresses.
    pc = START_ADDRESS;

    //Loading the fonts onto memory.
    for(unsigned int i = 0; i < FONTSET_SIZE; i++)
    {
        mem[FONTSET_START_ADDRESS + i] = fontset[i];
    }
}

void Chip8::LoadRom(const char* filename)
{
    // Instantiating a file object to read data, and splacing our cursor at the tail end.
    // We will read in binary.
    std::fstream file (filename, std::ios::binary | std::ios::ate);
 
    if(file.is_open())
    {
        // Making a buffer the size of the rom.
        std::streampos size = file.tellg(); // Getting the current position(end).
        char* buffer = new char[size];

        // Going back to the beginning of the file.
        file.seekg(0, std::ios::beg);
        file.read(buffer, size); // Loading the file onto our buffer.
        file.close();

        // Loading the rom contents into memory.
        for(int i = 0; i<size; i++)
        {
            mem[START_ADDRESS + i] = buffer[i];
        }

        // Freeing the buffer.
        delete[] buffer;
    }
}
