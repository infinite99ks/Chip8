#include <cstdint>
#include <fstream> // Used for loading roms.

class Chip8{
    public:
        uint8_t registers[16]{};
        uint8_t mem[4096]{}; // ROM instructions should be stored starting from 0x200
        uint16_t i{}; // Index register.
        uint16_t pc{}; // Program counter.
        uint16_t stack[16]{}; // A 16-level stack, supporting a max of 16 nested calls.
        uint8_t sp{}; // Stack pointer.
        uint8_t delay_timer{}; // If set to a value it decrements at the cycle clock rate.
        uint8_t sound_timer{}; // If set to a value it decrements at the cycle clock rate.
        uint8_t keypad[16]{};
        uint32_t video[64*32]{};
        uint16_t opcode;

        // Our functions.
        void LoadRom(char const* filename);
};