#include <input.h>



Keyboard Input::keyboard()
{
        return Keyboard(_keyStates);
}

void Input::processKeyboardData(RAWKEYBOARD& data)
{
        if(data.VKey == 0xFF)
                return;

        parseKeyboardData(data);
        const USHORT flags = data.Flags;

        if((flags & RI_KEY_BREAK) != 0)
                _keyStates[data.VKey] = false;
        else
                _keyStates[data.VKey] = true;
}
// Private

const USHORT Input::EXTENDED_KEYS[] =
{
        VK_LCONTROL,
        VK_RCONTROL,
        VK_LMENU,
        VK_RMENU
};

std::vector<bool> Input::_keyStates = std::vector<bool>(256, false);

// Static

void Input::parseKeyboardData(RAWKEYBOARD& data)
{
        switch(data.VKey)
        {
                case VK_SHIFT:
                        parseShiftKey(data);
                        break;

                case VK_CONTROL:
                        parseExtendedKeys(data, 0);
                        break;

                case VK_MENU:
                        parseExtendedKeys(data, 2);
                        break;
        }
}


void Input::parseShiftKey(RAWKEYBOARD& data)
{
        data.VKey = (USHORT)MapVirtualKey(data.MakeCode, MAPVK_VSC_TO_VK_EX);
}

void Input::parseExtendedKeys(RAWKEYBOARD& data, const int index)
{
        if((data.Flags & RI_KEY_E0) != 0)
                data.VKey = EXTENDED_KEYS[index + 1];
        else
                data.VKey = EXTENDED_KEYS[index];
}