#include <Windows.h>
#include <vector>
#include <Keyboard.h>

class Input
{
        public:

                static Keyboard keyboard();

                static void processKeyboardData(RAWKEYBOARD& data);

        private:

                static const USHORT EXTENDED_KEYS[];

                static std::vector<bool> _keyStates;

                Input(const Input& input);
                ~Input();

                static void parseKeyboardData(RAWKEYBOARD& data);
                static void parseShiftKey(RAWKEYBOARD& data);
                static void parseExtendedKeys(RAWKEYBOARD& data, const int index);
};
