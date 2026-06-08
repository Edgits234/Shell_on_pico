#ifndef CustomKeyboard_h
#define CustomKeyboard_h

#if !defined(ENGLISH_CANADIAN_KEYBOARD) && !defined(FRENCH_CANADIAN_KEYBOARD)
    #define FRENCH_CANADIAN_KEYBOARD
#endif

#if defined(EMULATE_KEYBOARD)

    typedef struct
    {
    uint8_t state;
    uint8_t lctrl;
    uint8_t lshift;
    uint8_t lalt;
    uint8_t lgui;
    uint8_t rctrl;
    uint8_t rshift;
    uint8_t ralt;
    uint8_t rgui;
    uint8_t keys[6];
    }
    HID_KEYBD_Info_TypeDef;

    #define KEY_NONE                               0x00
    #define KEY_ERRORROLLOVER                      0x01
    #define KEY_POSTFAIL                           0x02
    #define KEY_ERRORUNDEFINED                     0x03
    #define KEY_A                                  0x04
    #define KEY_B                                  0x05
    #define KEY_C                                  0x06
    #define KEY_D                                  0x07
    #define KEY_E                                  0x08
    #define KEY_F                                  0x09
    #define KEY_G                                  0x0A
    #define KEY_H                                  0x0B
    #define KEY_I                                  0x0C
    #define KEY_J                                  0x0D
    #define KEY_K                                  0x0E
    #define KEY_L                                  0x0F
    #define KEY_M                                  0x10
    #define KEY_N                                  0x11
    #define KEY_O                                  0x12
    #define KEY_P                                  0x13
    #define KEY_Q                                  0x14
    #define KEY_R                                  0x15
    #define KEY_S                                  0x16
    #define KEY_T                                  0x17
    #define KEY_U                                  0x18
    #define KEY_V                                  0x19
    #define KEY_W                                  0x1A
    #define KEY_X                                  0x1B
    #define KEY_Y                                  0x1C
    #define KEY_Z                                  0x1D
    #define KEY_1_EXCLAMATION_MARK                 0x1E
    #define KEY_2_AT                               0x1F
    #define KEY_3_NUMBER_SIGN                      0x20
    #define KEY_4_DOLLAR                           0x21
    #define KEY_5_PERCENT                          0x22
    #define KEY_6_CARET                            0x23
    #define KEY_7_AMPERSAND                        0x24
    #define KEY_8_ASTERISK                         0x25
    #define KEY_9_OPARENTHESIS                     0x26
    #define KEY_0_CPARENTHESIS                     0x27
    #define KEY_ENTER                              0x28
    #define KEY_ESCAPE                             0x29
    #define KEY_BACKSPACE                          0x2A
    #define KEY_TAB                                0x2B
    #define KEY_SPACEBAR                           0x2C
    #define KEY_MINUS_UNDERSCORE                   0x2D
    #define KEY_EQUAL_PLUS                         0x2E
    #define KEY_OBRACKET_AND_OBRACE                0x2F
    #define KEY_CBRACKET_AND_CBRACE                0x30
    #define KEY_BACKSLASH_VERTICAL_BAR             0x31
    #define KEY_NONUS_NUMBER_SIGN_TILDE            0x32
    #define KEY_SEMICOLON_COLON                    0x33
    #define KEY_SINGLE_AND_DOUBLE_QUOTE            0x34
    #define KEY_GRAVE_ACCENT_AND_TILDE             0x35
    #define KEY_COMMA_AND_LESS                     0x36
    #define KEY_DOT_GREATER                        0x37
    #define KEY_SLASH_QUESTION                     0x38
    #define KEY_CAPS_LOCK                          0x39
    #define KEY_F1                                 0x3A
    #define KEY_F2                                 0x3B
    #define KEY_F3                                 0x3C
    #define KEY_F4                                 0x3D
    #define KEY_F5                                 0x3E
    #define KEY_F6                                 0x3F
    #define KEY_F7                                 0x40
    #define KEY_F8                                 0x41
    #define KEY_F9                                 0x42
    #define KEY_F10                                0x43
    #define KEY_F11                                0x44
    #define KEY_F12                                0x45
    #define KEY_PRINTSCREEN                        0x46
    #define KEY_SCROLL_LOCK                        0x47
    #define KEY_PAUSE                              0x48
    #define KEY_INSERT                             0x49
    #define KEY_HOME                               0x4A
    #define KEY_PAGEUP                             0x4B
    #define KEY_DELETE                             0x4C
    #define KEY_END1                               0x4D
    #define KEY_PAGEDOWN                           0x4E
    #define KEY_RIGHTARROW                         0x4F
    #define KEY_LEFTARROW                          0x50
    #define KEY_DOWNARROW                          0x51
    #define KEY_UPARROW                            0x52
    #define KEY_KEYPAD_NUM_LOCK_AND_CLEAR          0x53
    #define KEY_KEYPAD_SLASH                       0x54
    #define KEY_KEYPAD_ASTERIKS                    0x55
    #define KEY_KEYPAD_MINUS                       0x56
    #define KEY_KEYPAD_PLUS                        0x57
    #define KEY_KEYPAD_ENTER                       0x58
    #define KEY_KEYPAD_1_END                       0x59
    #define KEY_KEYPAD_2_DOWN_ARROW                0x5A
    #define KEY_KEYPAD_3_PAGEDN                    0x5B
    #define KEY_KEYPAD_4_LEFT_ARROW                0x5C
    #define KEY_KEYPAD_5                           0x5D
    #define KEY_KEYPAD_6_RIGHT_ARROW               0x5E
    #define KEY_KEYPAD_7_HOME                      0x5F
    #define KEY_KEYPAD_8_UP_ARROW                  0x60
    #define KEY_KEYPAD_9_PAGEUP                    0x61
    #define KEY_KEYPAD_0_INSERT                    0x62
    #define KEY_KEYPAD_DECIMAL_SEPARATOR_DELETE    0x63
    #define KEY_NONUS_BACK_SLASH_VERTICAL_BAR      0x64
    #define KEY_APPLICATION                        0x65
    #define KEY_POWER                              0x66
    #define KEY_KEYPAD_EQUAL                       0x67
    #define KEY_F13                                0x68
    #define KEY_F14                                0x69
    #define KEY_F15                                0x6A
    #define KEY_F16                                0x6B
    #define KEY_F17                                0x6C
    #define KEY_F18                                0x6D
    #define KEY_F19                                0x6E
    #define KEY_F20                                0x6F
    #define KEY_F21                                0x70
    #define KEY_F22                                0x71
    #define KEY_F23                                0x72
    #define KEY_F24                                0x73
    #define KEY_EXECUTE                            0x74
    #define KEY_HELP                               0x75
    #define KEY_MENU                               0x76
    #define KEY_SELECT                             0x77
    #define KEY_STOP                               0x78
    #define KEY_AGAIN                              0x79
    #define KEY_UNDO                               0x7A
    #define KEY_CUT                                0x7B
    #define KEY_COPY                               0x7C
    #define KEY_PASTE                              0x7D
    #define KEY_FIND                               0x7E
    #define KEY_MUTE                               0x7F
    #define KEY_VOLUME_UP                          0x80
    #define KEY_VOLUME_DOWN                        0x81
    #define KEY_LOCKING_CAPS_LOCK                  0x82
    #define KEY_LOCKING_NUM_LOCK                   0x83
    #define KEY_LOCKING_SCROLL_LOCK                0x84
    #define KEY_KEYPAD_COMMA                       0x85
    #define KEY_KEYPAD_EQUAL_SIGN                  0x86
    #define KEY_INTERNATIONAL1                     0x87
    #define KEY_INTERNATIONAL2                     0x88
    #define KEY_INTERNATIONAL3                     0x89
    #define KEY_INTERNATIONAL4                     0x8A
    #define KEY_INTERNATIONAL5                     0x8B
    #define KEY_INTERNATIONAL6                     0x8C
    #define KEY_INTERNATIONAL7                     0x8D
    #define KEY_INTERNATIONAL8                     0x8E
    #define KEY_INTERNATIONAL9                     0x8F
    #define KEY_LANG1                              0x90
    #define KEY_LANG2                              0x91
    #define KEY_LANG3                              0x92
    #define KEY_LANG4                              0x93
    #define KEY_LANG5                              0x94
    #define KEY_LANG6                              0x95
    #define KEY_LANG7                              0x96
    #define KEY_LANG8                              0x97
    #define KEY_LANG9                              0x98
    #define KEY_ALTERNATE_ERASE                    0x99
    #define KEY_SYSREQ                             0x9A
    #define KEY_CANCEL                             0x9B
    #define KEY_CLEAR                              0x9C
    #define KEY_PRIOR                              0x9D
    #define KEY_RETURN                             0x9E
    #define KEY_SEPARATOR                          0x9F
    #define KEY_OUT                                0xA0
    #define KEY_OPER                               0xA1
    #define KEY_CLEAR_AGAIN                        0xA2
    #define KEY_CRSEL                              0xA3
    #define KEY_EXSEL                              0xA4
    #define KEY_KEYPAD_00                          0xB0
    #define KEY_KEYPAD_000                         0xB1
    #define KEY_THOUSANDS_SEPARATOR                0xB2
    #define KEY_DECIMAL_SEPARATOR                  0xB3
    #define KEY_CURRENCY_UNIT                      0xB4
    #define KEY_CURRENCY_SUB_UNIT                  0xB5
    #define KEY_KEYPAD_OPARENTHESIS                0xB6
    #define KEY_KEYPAD_CPARENTHESIS                0xB7
    #define KEY_KEYPAD_OBRACE                      0xB8
    #define KEY_KEYPAD_CBRACE                      0xB9
    #define KEY_KEYPAD_TAB                         0xBA
    #define KEY_KEYPAD_BACKSPACE                   0xBB
    #define KEY_KEYPAD_A                           0xBC
    #define KEY_KEYPAD_B                           0xBD
    #define KEY_KEYPAD_C                           0xBE
    #define KEY_KEYPAD_D                           0xBF
    #define KEY_KEYPAD_E                           0xC0
    #define KEY_KEYPAD_F                           0xC1
    #define KEY_KEYPAD_XOR                         0xC2
    #define KEY_KEYPAD_CARET                       0xC3
    #define KEY_KEYPAD_PERCENT                     0xC4
    #define KEY_KEYPAD_LESS                        0xC5
    #define KEY_KEYPAD_GREATER                     0xC6
    #define KEY_KEYPAD_AMPERSAND                   0xC7
    #define KEY_KEYPAD_LOGICAL_AND                 0xC8
    #define KEY_KEYPAD_VERTICAL_BAR                0xC9
    #define KEY_KEYPAD_LOGIACL_OR                  0xCA
    #define KEY_KEYPAD_COLON                       0xCB
    #define KEY_KEYPAD_NUMBER_SIGN                 0xCC
    #define KEY_KEYPAD_SPACE                       0xCD
    #define KEY_KEYPAD_AT                          0xCE
    #define KEY_KEYPAD_EXCLAMATION_MARK            0xCF
    #define KEY_KEYPAD_MEMORY_STORE                0xD0
    #define KEY_KEYPAD_MEMORY_RECALL               0xD1
    #define KEY_KEYPAD_MEMORY_CLEAR                0xD2
    #define KEY_KEYPAD_MEMORY_ADD                  0xD3
    #define KEY_KEYPAD_MEMORY_SUBTRACT             0xD4
    #define KEY_KEYPAD_MEMORY_MULTIPLY             0xD5
    #define KEY_KEYPAD_MEMORY_DIVIDE               0xD6
    #define KEY_KEYPAD_PLUSMINUS                   0xD7
    #define KEY_KEYPAD_CLEAR                       0xD8
    #define KEY_KEYPAD_CLEAR_ENTRY                 0xD9
    #define KEY_KEYPAD_BINARY                      0xDA
    #define KEY_KEYPAD_OCTAL                       0xDB
    #define KEY_KEYPAD_DECIMAL                     0xDC
    #define KEY_KEYPAD_HEXADECIMAL                 0xDD
    #define KEY_LEFTCONTROL                        0xE0
    #define KEY_LEFTSHIFT                          0xE1
    #define KEY_LEFTALT                            0xE2
    #define KEY_LEFT_GUI                           0xE3
    #define KEY_RIGHTCONTROL                       0xE4
    #define KEY_RIGHTSHIFT                         0xE5
    #define KEY_RIGHTALT                           0xE6
    #define KEY_RIGHT_GUI                          0xE7

#else

    #if WOKWI_SIM

        #warning I suggest you do "#define EMULATE_KEYBOARD"
    #endif

    #include <USBHostGiga.h>//this is for the keyboard

#endif

struct KeyPress
{
    int press;
    int release;
    uint8_t key;
};

//useful macros
#define LOWERCASE(x) (('A' <= x && x <= 'Z')?('a' - 'A' + x):(x))
#define UPPERCASE(x) (('a' <= x && x <= 'z')?('A' - 'a' + x):(x))

/**
 * @param custom input a normal string with all of the characters you want to include as safe ending characters, if it found the specific text and after it was a character in your list than its going to allow it, else not. set to nullptr to include all
 * @retval returns a boolean representing if the two strings are the same
 */
bool checkstr(const char* text, const char* find, bool ignore_case = 0, const char* custom = " ")
{




    if(strcmp(find, "rightarrow") == 0) println("RIGHT ARROW CHECKSTR");

    //go through the find string because we want to find it inside of the bigger string (it only checks if its at the start)
    int i = 0;
    while(find[i] != '\0')
    {
        //if the characters at the same index are not the same then the strings are not the same, return false
        if(ignore_case)
        {
            if(strcmp(find, "rightarrow") == 0) println((char)UPPERCASE(text[i])," == ",(char)UPPERCASE(find[i]));
            if(UPPERCASE(text[i]) != UPPERCASE(find[i])) return false;
        }else
        {
            if(text[i] != find[i]) return false;
        }

        i++;
    }

    if(custom == nullptr || text[i] == '\0')
    {
        return true;
    }else
    {
        int j = 0;
        while(custom[j] != '\0')
        {
            //check if the thing right after the word is an allowed character
            if(text[i] == custom[j]) 
            {
                return true;
            }
            j++;
        }
        return false;
    }

}

int strToKey(const char* str, const char* include = " ")
{
    
    if(checkstr(str, "NONE"                              , 1, include)) return 0x00;
    if(checkstr(str, "ERRORROLLOVER"                     , 1, include)) return 0x01;
    if(checkstr(str, "POSTFAIL"                          , 1, include)) return 0x02;
    if(checkstr(str, "ERRORUNDEFINED"                    , 1, include)) return 0x03;
    if(checkstr(str, "A"                                 , 1, include)) return 0x04;
    if(checkstr(str, "B"                                 , 1, include)) return 0x05;
    if(checkstr(str, "C"                                 , 1, include)) return 0x06;
    if(checkstr(str, "D"                                 , 1, include)) return 0x07;
    if(checkstr(str, "E"                                 , 1, include)) return 0x08;
    if(checkstr(str, "F"                                 , 1, include)) return 0x09;
    if(checkstr(str, "G"                                 , 1, include)) return 0x0A;
    if(checkstr(str, "H"                                 , 1, include)) return 0x0B;
    if(checkstr(str, "I"                                 , 1, include)) return 0x0C;
    if(checkstr(str, "J"                                 , 1, include)) return 0x0D;
    if(checkstr(str, "K"                                 , 1, include)) return 0x0E;
    if(checkstr(str, "L"                                 , 1, include)) return 0x0F;
    if(checkstr(str, "M"                                 , 1, include)) return 0x10;
    if(checkstr(str, "N"                                 , 1, include)) return 0x11;
    if(checkstr(str, "O"                                 , 1, include)) return 0x12;
    if(checkstr(str, "P"                                 , 1, include)) return 0x13;
    if(checkstr(str, "Q"                                 , 1, include)) return 0x14;
    if(checkstr(str, "R"                                 , 1, include)) return 0x15;
    if(checkstr(str, "S"                                 , 1, include)) return 0x16;
    if(checkstr(str, "T"                                 , 1, include)) return 0x17;
    if(checkstr(str, "U"                                 , 1, include)) return 0x18;
    if(checkstr(str, "V"                                 , 1, include)) return 0x19;
    if(checkstr(str, "W"                                 , 1, include)) return 0x1A;
    if(checkstr(str, "X"                                 , 1, include)) return 0x1B;
    if(checkstr(str, "Y"                                 , 1, include)) return 0x1C;
    if(checkstr(str, "Z"                                 , 1, include)) return 0x1D;
    if(checkstr(str, "1_EXCLAMATION_MARK"                , 1, include)) return 0x1E;
    if(checkstr(str, "2_AT"                              , 1, include)) return 0x1F;
    if(checkstr(str, "3_NUMBER_SIGN"                     , 1, include)) return 0x20;
    if(checkstr(str, "4_DOLLAR"                          , 1, include)) return 0x21;
    if(checkstr(str, "5_PERCENT"                         , 1, include)) return 0x22;
    if(checkstr(str, "6_CARET"                           , 1, include)) return 0x23;
    if(checkstr(str, "7_AMPERSAND"                       , 1, include)) return 0x24;
    if(checkstr(str, "8_ASTERISK"                        , 1, include)) return 0x25;
    if(checkstr(str, "9_OPARENTHESIS"                    , 1, include)) return 0x26;
    if(checkstr(str, "0_CPARENTHESIS"                    , 1, include)) return 0x27;
    if(checkstr(str, "ENTER"                             , 1, include)) return 0x28;
    if(checkstr(str, "ESCAPE"                            , 1, include)) return 0x29;
    if(checkstr(str, "BACKSPACE"                         , 1, include)) return 0x2A;
    if(checkstr(str, "TAB"                               , 1, include)) return 0x2B;
    if(checkstr(str, "SPACEBAR"                          , 1, include)) return 0x2C;
    if(checkstr(str, "MINUS_UNDERSCORE"                  , 1, include)) return 0x2D;
    if(checkstr(str, "EQUAL_PLUS"                        , 1, include)) return 0x2E;
    if(checkstr(str, "OBRACKET_AND_OBRACE"               , 1, include)) return 0x2F;
    if(checkstr(str, "CBRACKET_AND_CBRACE"               , 1, include)) return 0x30;
    if(checkstr(str, "BACKSLASH_VERTICAL_BAR"            , 1, include)) return 0x31;
    if(checkstr(str, "NONUS_NUMBER_SIGN_TILDE"           , 1, include)) return 0x32;
    if(checkstr(str, "SEMICOLON_COLON"                   , 1, include)) return 0x33;
    if(checkstr(str, "SINGLE_AND_DOUBLE_QUOTE"           , 1, include)) return 0x34;
    if(checkstr(str, "GRAVE_ACCENT_AND_TILDE"            , 1, include)) return 0x35;
    if(checkstr(str, "COMMA_AND_LESS"                    , 1, include)) return 0x36;
    if(checkstr(str, "DOT_GREATER"                       , 1, include)) return 0x37;
    if(checkstr(str, "SLASH_QUESTION"                    , 1, include)) return 0x38;
    if(checkstr(str, "CAPS_LOCK"                         , 1, include)) return 0x39;
    if(checkstr(str, "F1"                                , 1, include)) return 0x3A;
    if(checkstr(str, "F2"                                , 1, include)) return 0x3B;
    if(checkstr(str, "F3"                                , 1, include)) return 0x3C;
    if(checkstr(str, "F4"                                , 1, include)) return 0x3D;
    if(checkstr(str, "F5"                                , 1, include)) return 0x3E;
    if(checkstr(str, "F6"                                , 1, include)) return 0x3F;
    if(checkstr(str, "F7"                                , 1, include)) return 0x40;
    if(checkstr(str, "F8"                                , 1, include)) return 0x41;
    if(checkstr(str, "F9"                                , 1, include)) return 0x42;
    if(checkstr(str, "F10"                               , 1, include)) return 0x43;
    if(checkstr(str, "F11"                               , 1, include)) return 0x44;
    if(checkstr(str, "F12"                               , 1, include)) return 0x45;
    if(checkstr(str, "PRINTSCREEN"                       , 1, include)) return 0x46;
    if(checkstr(str, "SCROLL_LOCK"                       , 1, include)) return 0x47;
    if(checkstr(str, "PAUSE"                             , 1, include)) return 0x48;
    if(checkstr(str, "INSERT"                            , 1, include)) return 0x49;
    if(checkstr(str, "HOME"                              , 1, include)) return 0x4A;
    if(checkstr(str, "PAGEUP"                            , 1, include)) return 0x4B;
    if(checkstr(str, "DELETE"                            , 1, include)) return 0x4C;
    if(checkstr(str, "END1"                              , 1, include)) return 0x4D;
    if(checkstr(str, "PAGEDOWN"                          , 1, include)) return 0x4E;
    if(checkstr(str, "RIGHTARROW"                        , 1, include)) return 0x4F;
    if(checkstr(str, "LEFTARROW"                         , 1, include)) return 0x50;
    if(checkstr(str, "DOWNARROW"                         , 1, include)) return 0x51;
    if(checkstr(str, "UPARROW"                           , 1, include)) return 0x52;
    if(checkstr(str, "KEYPAD_NUM_LOCK_AND_CLEAR"         , 1, include)) return 0x53;
    if(checkstr(str, "KEYPAD_SLASH"                      , 1, include)) return 0x54;
    if(checkstr(str, "KEYPAD_ASTERIKS"                   , 1, include)) return 0x55;
    if(checkstr(str, "KEYPAD_MINUS"                      , 1, include)) return 0x56;
    if(checkstr(str, "KEYPAD_PLUS"                       , 1, include)) return 0x57;
    if(checkstr(str, "KEYPAD_ENTER"                      , 1, include)) return 0x58;
    if(checkstr(str, "KEYPAD_1_END"                      , 1, include)) return 0x59;
    if(checkstr(str, "KEYPAD_2_DOWN_ARROW"               , 1, include)) return 0x5A;
    if(checkstr(str, "KEYPAD_3_PAGEDN"                   , 1, include)) return 0x5B;
    if(checkstr(str, "KEYPAD_4_LEFT_ARROW"               , 1, include)) return 0x5C;
    if(checkstr(str, "KEYPAD_5"                          , 1, include)) return 0x5D;
    if(checkstr(str, "KEYPAD_6_RIGHT_ARROW"              , 1, include)) return 0x5E;
    if(checkstr(str, "KEYPAD_7_HOME"                     , 1, include)) return 0x5F;
    if(checkstr(str, "KEYPAD_8_UP_ARROW"                 , 1, include)) return 0x60;
    if(checkstr(str, "KEYPAD_9_PAGEUP"                   , 1, include)) return 0x61;
    if(checkstr(str, "KEYPAD_0_INSERT"                   , 1, include)) return 0x62;
    if(checkstr(str, "KEYPAD_DECIMAL_SEPARATOR_DELETE"   , 1, include)) return 0x63;
    if(checkstr(str, "NONUS_BACK_SLASH_VERTICAL_BAR"     , 1, include)) return 0x64;
    if(checkstr(str, "APPLICATION"                       , 1, include)) return 0x65;
    if(checkstr(str, "POWER"                             , 1, include)) return 0x66;
    if(checkstr(str, "KEYPAD_EQUAL"                      , 1, include)) return 0x67;
    if(checkstr(str, "F13"                               , 1, include)) return 0x68;
    if(checkstr(str, "F14"                               , 1, include)) return 0x69;
    if(checkstr(str, "F15"                               , 1, include)) return 0x6A;
    if(checkstr(str, "F16"                               , 1, include)) return 0x6B;
    if(checkstr(str, "F17"                               , 1, include)) return 0x6C;
    if(checkstr(str, "F18"                               , 1, include)) return 0x6D;
    if(checkstr(str, "F19"                               , 1, include)) return 0x6E;
    if(checkstr(str, "F20"                               , 1, include)) return 0x6F;
    if(checkstr(str, "F21"                               , 1, include)) return 0x70;
    if(checkstr(str, "F22"                               , 1, include)) return 0x71;
    if(checkstr(str, "F23"                               , 1, include)) return 0x72;
    if(checkstr(str, "F24"                               , 1, include)) return 0x73;
    if(checkstr(str, "EXECUTE"                           , 1, include)) return 0x74;
    if(checkstr(str, "HELP"                              , 1, include)) return 0x75;
    if(checkstr(str, "MENU"                              , 1, include)) return 0x76;
    if(checkstr(str, "SELECT"                            , 1, include)) return 0x77;
    if(checkstr(str, "STOP"                              , 1, include)) return 0x78;
    if(checkstr(str, "AGAIN"                             , 1, include)) return 0x79;
    if(checkstr(str, "UNDO"                              , 1, include)) return 0x7A;
    if(checkstr(str, "CUT"                               , 1, include)) return 0x7B;
    if(checkstr(str, "COPY"                              , 1, include)) return 0x7C;
    if(checkstr(str, "PASTE"                             , 1, include)) return 0x7D;
    if(checkstr(str, "FIND"                              , 1, include)) return 0x7E;
    if(checkstr(str, "MUTE"                              , 1, include)) return 0x7F;
    if(checkstr(str, "VOLUME_UP"                         , 1, include)) return 0x80;
    if(checkstr(str, "VOLUME_DOWN"                       , 1, include)) return 0x81;
    if(checkstr(str, "LOCKING_CAPS_LOCK"                 , 1, include)) return 0x82;
    if(checkstr(str, "LOCKING_NUM_LOCK"                  , 1, include)) return 0x83;
    if(checkstr(str, "LOCKING_SCROLL_LOCK"               , 1, include)) return 0x84;
    if(checkstr(str, "KEYPAD_COMMA"                      , 1, include)) return 0x85;
    if(checkstr(str, "KEYPAD_EQUAL_SIGN"                 , 1, include)) return 0x86;
    if(checkstr(str, "INTERNATIONAL1"                    , 1, include)) return 0x87;
    if(checkstr(str, "INTERNATIONAL2"                    , 1, include)) return 0x88;
    if(checkstr(str, "INTERNATIONAL3"                    , 1, include)) return 0x89;
    if(checkstr(str, "INTERNATIONAL4"                    , 1, include)) return 0x8A;
    if(checkstr(str, "INTERNATIONAL5"                    , 1, include)) return 0x8B;
    if(checkstr(str, "INTERNATIONAL6"                    , 1, include)) return 0x8C;
    if(checkstr(str, "INTERNATIONAL7"                    , 1, include)) return 0x8D;
    if(checkstr(str, "INTERNATIONAL8"                    , 1, include)) return 0x8E;
    if(checkstr(str, "INTERNATIONAL9"                    , 1, include)) return 0x8F;
    if(checkstr(str, "LANG1"                             , 1, include)) return 0x90;
    if(checkstr(str, "LANG2"                             , 1, include)) return 0x91;
    if(checkstr(str, "LANG3"                             , 1, include)) return 0x92;
    if(checkstr(str, "LANG4"                             , 1, include)) return 0x93;
    if(checkstr(str, "LANG5"                             , 1, include)) return 0x94;
    if(checkstr(str, "LANG6"                             , 1, include)) return 0x95;
    if(checkstr(str, "LANG7"                             , 1, include)) return 0x96;
    if(checkstr(str, "LANG8"                             , 1, include)) return 0x97;
    if(checkstr(str, "LANG9"                             , 1, include)) return 0x98;
    if(checkstr(str, "ALTERNATE_ERASE"                   , 1, include)) return 0x99;
    if(checkstr(str, "SYSREQ"                            , 1, include)) return 0x9A;
    if(checkstr(str, "CANCEL"                            , 1, include)) return 0x9B;
    if(checkstr(str, "CLEAR"                             , 1, include)) return 0x9C;
    if(checkstr(str, "PRIOR"                             , 1, include)) return 0x9D;
    if(checkstr(str, "RETURN"                            , 1, include)) return 0x9E;
    if(checkstr(str, "SEPARATOR"                         , 1, include)) return 0x9F;
    if(checkstr(str, "OUT"                               , 1, include)) return 0xA0;
    if(checkstr(str, "OPER"                              , 1, include)) return 0xA1;
    if(checkstr(str, "CLEAR_AGAIN"                       , 1, include)) return 0xA2;
    if(checkstr(str, "CRSEL"                             , 1, include)) return 0xA3;
    if(checkstr(str, "EXSEL"                             , 1, include)) return 0xA4;
    if(checkstr(str, "KEYPAD_00"                         , 1, include)) return 0xB0;
    if(checkstr(str, "KEYPAD_000"                        , 1, include)) return 0xB1;
    if(checkstr(str, "THOUSANDS_SEPARATOR"               , 1, include)) return 0xB2;
    if(checkstr(str, "DECIMAL_SEPARATOR"                 , 1, include)) return 0xB3;
    if(checkstr(str, "CURRENCY_UNIT"                     , 1, include)) return 0xB4;
    if(checkstr(str, "CURRENCY_SUB_UNIT"                 , 1, include)) return 0xB5;
    if(checkstr(str, "KEYPAD_OPARENTHESIS"               , 1, include)) return 0xB6;
    if(checkstr(str, "KEYPAD_CPARENTHESIS"               , 1, include)) return 0xB7;
    if(checkstr(str, "KEYPAD_OBRACE"                     , 1, include)) return 0xB8;
    if(checkstr(str, "KEYPAD_CBRACE"                     , 1, include)) return 0xB9;
    if(checkstr(str, "KEYPAD_TAB"                        , 1, include)) return 0xBA;
    if(checkstr(str, "KEYPAD_BACKSPACE"                  , 1, include)) return 0xBB;
    if(checkstr(str, "KEYPAD_A"                          , 1, include)) return 0xBC;
    if(checkstr(str, "KEYPAD_B"                          , 1, include)) return 0xBD;
    if(checkstr(str, "KEYPAD_C"                          , 1, include)) return 0xBE;
    if(checkstr(str, "KEYPAD_D"                          , 1, include)) return 0xBF;
    if(checkstr(str, "KEYPAD_E"                          , 1, include)) return 0xC0;
    if(checkstr(str, "KEYPAD_F"                          , 1, include)) return 0xC1;
    if(checkstr(str, "KEYPAD_XOR"                        , 1, include)) return 0xC2;
    if(checkstr(str, "KEYPAD_CARET"                      , 1, include)) return 0xC3;
    if(checkstr(str, "KEYPAD_PERCENT"                    , 1, include)) return 0xC4;
    if(checkstr(str, "KEYPAD_LESS"                       , 1, include)) return 0xC5;
    if(checkstr(str, "KEYPAD_GREATER"                    , 1, include)) return 0xC6;
    if(checkstr(str, "KEYPAD_AMPERSAND"                  , 1, include)) return 0xC7;
    if(checkstr(str, "KEYPAD_LOGICAL_AND"                , 1, include)) return 0xC8;
    if(checkstr(str, "KEYPAD_VERTICAL_BAR"               , 1, include)) return 0xC9;
    if(checkstr(str, "KEYPAD_LOGIACL_OR"                 , 1, include)) return 0xCA;
    if(checkstr(str, "KEYPAD_COLON"                      , 1, include)) return 0xCB;
    if(checkstr(str, "KEYPAD_NUMBER_SIGN"                , 1, include)) return 0xCC;
    if(checkstr(str, "KEYPAD_SPACE"                      , 1, include)) return 0xCD;
    if(checkstr(str, "KEYPAD_AT"                         , 1, include)) return 0xCE;
    if(checkstr(str, "KEYPAD_EXCLAMATION_MARK"           , 1, include)) return 0xCF;
    if(checkstr(str, "KEYPAD_MEMORY_STORE"               , 1, include)) return 0xD0;
    if(checkstr(str, "KEYPAD_MEMORY_RECALL"              , 1, include)) return 0xD1;
    if(checkstr(str, "KEYPAD_MEMORY_CLEAR"               , 1, include)) return 0xD2;
    if(checkstr(str, "KEYPAD_MEMORY_ADD"                 , 1, include)) return 0xD3;
    if(checkstr(str, "KEYPAD_MEMORY_SUBTRACT"            , 1, include)) return 0xD4;
    if(checkstr(str, "KEYPAD_MEMORY_MULTIPLY"            , 1, include)) return 0xD5;
    if(checkstr(str, "KEYPAD_MEMORY_DIVIDE"              , 1, include)) return 0xD6;
    if(checkstr(str, "KEYPAD_PLUSMINUS"                  , 1, include)) return 0xD7;
    if(checkstr(str, "KEYPAD_CLEAR"                      , 1, include)) return 0xD8;
    if(checkstr(str, "KEYPAD_CLEAR_ENTRY"                , 1, include)) return 0xD9;
    if(checkstr(str, "KEYPAD_BINARY"                     , 1, include)) return 0xDA;
    if(checkstr(str, "KEYPAD_OCTAL"                      , 1, include)) return 0xDB;
    if(checkstr(str, "KEYPAD_DECIMAL"                    , 1, include)) return 0xDC;
    if(checkstr(str, "KEYPAD_HEXADECIMAL"                , 1, include)) return 0xDD;
    if(checkstr(str, "LEFTCONTROL"                       , 1, include)) return 0xE0;
    if(checkstr(str, "LEFTSHIFT"                         , 1, include)) return 0xE1;
    if(checkstr(str, "LEFTALT"                           , 1, include)) return 0xE2;
    if(checkstr(str, "LEFT_GUI"                          , 1, include)) return 0xE3;
    if(checkstr(str, "RIGHTCONTROL"                      , 1, include)) return 0xE4;
    if(checkstr(str, "RIGHTSHIFT"                        , 1, include)) return 0xE5;
    if(checkstr(str, "RIGHTALT"                          , 1, include)) return 0xE6;
    if(checkstr(str, "RIGHT_GUI"                         , 1, include)) return 0xE7;

    Serial.print("ERROR keyboard emulation, \"");
    
    //print the next word (stops at and doesn't print the next space)
    int i = 0;
    while(str[i] != ' ' && str[i] != '\0')
    {
        Serial.print(str[i]);
        i++;
    }

    Serial.println("\" is not a valid key, the code will output empty");

    //return invalid key
    return 255;
}

//============= CUSTOM KEYBOARD CLASS ===============//

#if !defined (EMULATE_KEYBOARD)
    /*inline*/ Keyboard keyb;
#endif

class KeyboardManager
{
    public:
    String buffer;
    uint8_t prevKeys[6];
    uint8_t lastKey;
    uint8_t currKey;
    char currChar;
    size_t Available;
    HID_KEYBD_Info_TypeDef keys;
    long long lastPress;
    long long lastRepeat;
    bool enableBuffer;
    int16_t cursorIndex;//imagine an invisible cursor, the code will try and modify the text there instead of always at the end
    uint8_t delayLimiter;//are we repeating like letters when writting text (1) or are we most rapid fire ever (0), (2) for no repeat at all
    unsigned long skipKeyboardStartTime;
    unsigned long skipKeyboardDelay;
    KeyPress key_sequence[25];//designed for key sequences

    void emulateKeyboard(const char* str)
    {
        
        if(skipKeyboardDelay != 0 && millis() - skipKeyboardStartTime < skipKeyboardDelay)
        {
            return;
        }else
        {
            skipKeyboardDelay = 0;
        }
        
        Serial.println("emulating...");

        Serial.print("emulating based on this : \"");
        Serial.print(str);
        Serial.println("\"");

        //if the string is nothing, we set the keyboard to not available (since we are sure 100% we don't have any keyboard emulation commands)
        if(str[0] == '\0')
        {
            println("string was nothing, setting Available to 0");
            Available = 0;
            println("Available : ",Available);
            return;
        }

        //go through all the strings, we will do a basic parser algorithm
        int i = 0; 
        while(str[i] != '\0')
        {

            //check to find " KEY_" sorta sketchy but we keep increasing the pointer essentially moving the start of the first string every time
            if(checkstr(str + i, "/add"))
            {
                Serial.println("ADDING A KEY");

                //if we found the magic word to emmulate a key we ... emulate that key, so just add it into the keys array
                for(size_t j = 0; j < (sizeof(keys.keys) / sizeof(keys.keys[0])); j++)
                {
                    //check if the spot inside of the keys array is empty
                    if(keys.keys[j] == 0)
                    { 
                        println(str);
                        
                        println("str + ",i," + 5 = ",str + i + 5);
                      
                        uint8_t val = strToKey(str + i + 5 /*size of the string*/);
                        
                        //set it to the correct key value based on the string right after (if its not a valid key its just going to set it to empty)
                        keys.keys[j] = val;

                        //set Available to true (because we just set a new key, we technically pressed a new key)
                        Available = true;

                        Serial.print("Successfully added key \"");
                            
                            //Print the next word
                            int k = 0;
                            while(str[k + i + 5] != ' ' && str[k + i + 5] != '\0')
                            {
                                Serial.print(str[k + i + 5]);
                                k++;
                            }
    
                            Serial.print("\" (0x");
                            Serial.print(val, HEX);
                            Serial.println(") in array : ");


                        for(unsigned int k = 0; k < (sizeof(keys.keys) / sizeof(keys.keys[0])); k++)
                        {
                            Serial.print("[");
                            Serial.print(k);
                            Serial.print("] = ");
                            Serial.print(keys.keys[k]);
                            Serial.println();
                        }
                        Serial.println();

                        //break out of the loop, we only want to set one key, and we're done
                        break;
                    }

                    if(j == (sizeof(keys.keys) / sizeof(keys.keys[0])) - 1)
                    {
                        Serial.println("can't add another key, the keys.keys array inside of KeyboardManager class is full, please remove a key before adding another one");
                    }
                }


            }else if(checkstr(str + i, "/del"))
            {
                int key = strToKey(str + i + 5 /*size of the string*/);

                //if we found the magic word to emmulate a key we ... emulate that key, so just add it into the keys array
                for(size_t j = 0; j < (sizeof(keys.keys) / sizeof(keys.keys[0])); j++)
                {
                    //if the spot in keys array is the key we want to delete
                    if(keys.keys[j] == key)
                    {
                        println("successfully removed ",keys.keys[j]," at [",j,"]");

                        //set to empty
                        keys.keys[j] = 0x00;

                        //set Available to true (because we just removed a key, we technically changed the pressed keys)
                        Available = true;


                        //break out of the loop, we only want to set one key, and we're done
                        break;
                    }

                    if(j == (sizeof(keys.keys) / sizeof(keys.keys[0])) - 1)
                    {
                        Serial.println("ERROR, couldn't remove the key ");
                    }
                }
            }else if(checkstr(str + i, "/set_buffer"))
            {

                println("setting the buffer...");

                //find next word of string
                int j = 0;//add 12 by default to skip the length of the " /set_buffer " string
                if(str[i + j + 12] == '\"')
                {
                    println("doing with double quotes");
                    char strBuff[200];
                    strBuff[0] = '\0';

                    j++;
                    println("initial j : ",j);
                    println(str[i + j + 12]," != ",'\"'," && ",str[i + j + 12]," != ",'\0');
                    while(str[i + j + 12] != '\"' && str[i + j + 12] != '\0')
                    {
                        //set character by character until we reach second double quote
                        strBuff[j - 1] = str[i + j + 12];
                        println("buffer[",j - 1,"] = ",str[i + j + 12]);
                        j++;
                        println("increased j : ",j);
                    }

                    //don't forget about the ending character
                    strBuff[j - 1] = '\0';

                    buffer = strBuff;
                }else
                {
                    println("doing without double quotes");
                    char strBuff[200];
                    
                    //advance through the string until we reach another command (another command will come up as " /" followed with anything but a space)
                    while(((str[i + j + 12] != ' ' && str[i + j + 12 + 1] != '/') || str[i + j + 12 + 2] == ' ') && str[i + j + 12] != '\0')
                    {
                        //set character by character until we reach another command "/" 
                        strBuff[j] = str[i + j + 12];
                        j++;
                    }

                    //don't forget about the ending character
                    strBuff[j] = '\0';

                    buffer = strBuff;
                }

                println("successfully set buffer to \"",buffer,"\"");
            }else if(checkstr(str + i, "/skip"))
            {
                println("found /skip command, skipping for desired amount...");

                //get the number
                double time = strToNum(str + i + 6);

                println("got output number of ",time);

                skipKeyboardStartTime = millis();
                skipKeyboardDelay     = time * 1000;

                println("set keyboard delay to ",skipKeyboardDelay);

            }else if(checkstr(str + i, "key_sequence{", 0, nullptr))
            {
                //cursor to naviage the text
                int j = i + 14;//skip right up to the good part
                
                // they had something to do with following code that I didn't have time to finish
                // int keyIndex = 0;
                // bool unwanted_char = false;

                while(true)
                {
                    //skip any unwanted characters (Ex: spaces, new lines, commas, etc...)
                    if(str[j] == ' ' || str [j] == '\n' || str[j] == ',')
                    {
                        //skip current letter
                        j++;
                        continue;
                    }

                    //if we find an ending character before we could find a curly bracket than error
                    if(str[j] == '\0')
                    {
                        print("ERROR, key_sequence missing '}' in '");
                        
                        for(int k = i; k < j; k++)
                        {
                            print(str[k]);
                        }
                        
                        println("', heres an Example : key_sequence{...<--missing)");

                        i = j;
                        break;
                    }

                    //if we find a ending character (Ex: end character, ending curly brackets)
                    if(str[j] == '}')
                    {
                        //set index to where the '}' is situated
                        i = j;

                        //get out of the loop
                        break;
                    }

                    //we are assuming whatever character we are looking in must not be an exception so we check to find a key
                    uint8_t val = strToKey(str + j, ",} \n\"\'");

                    //check if invalid (we use number instead if it is)
                    if(val == 255)
                    {
                        val = strToNum(str + j);
                    }

                    //we then take that key and put it at the corresponding place in the array


                    /*
                    
                    
                    {

                    }
                    
                    
                    
                    */
                }
            }else if(checkstr(str + i, "/help"))
            {

                for(int n = 0; n < 30; n++)
                {
                    println();
                }
                
                println("Info : ");
                println();
                println("when the a command is asking for a key, you can give like this");
                println("key by name like so -> \"enter\", \"ESCAPE\", \"B\"");
                println();
                println();
                println();
                println("Possible commands and what they do : ");
                println();
                println("/add [insert key]");
                println("-> adds a key to the keyboard (simulate pressing that key as long as you don't delete it from the array)");
                println();
                println("/del [insert key]");
                println("-> removes a key to the keyboard (this stops the constant simulated press of that key)");
                println();
                println("/set_buffer [insert string (with or without \"\")]");
                println("-> this is a String that is modified by the keyboard usually when typing in something like a text box, setting that string should set whatever is in a text box");
                println();
                println("key_sequence{ [insert key sequence (separated by commas : \",\")] }");
                println("-> this is a String that is modified by the keyboard usually when typing in something like a text box, setting that string should set whatever is in a text box");
                

                
            }

            i++;
        }
    }

    void begin()
    {
        #if !defined(EMULATE_KEYBOARD)
            keyb.begin();
        #endif
    }
    
    size_t available()
    {
        if(Available == true)
        {
            Available -= 1;
            return Available + 1;
        }else
        {
            return Available;
        }
    }

    void testKeys(HID_KEYBD_Info_TypeDef key)
    {
        //if no special keys were pressed
        if(key.lalt == 0 && key.ralt == 0 && key.lctrl == 0 && key.lshift == 0)
        {

            if(currKey == KEY_UPARROW)
            {
                //We do nothing yet (will have to do some complex as balls algorithm to make cursor go up and down)
            
                return;//return so it doesn't place the last character
            }else if(currKey == KEY_DOWNARROW)
            {
                //We do nothing yet (will have to do some complex as balls algorithm to make cursor go up and down)

                return;//return so it doesn't place the last character
            }else if(currKey == KEY_LEFTARROW)
            {
                //don't subtract to the cursor Index if its at the begining of the text (Bound check)
                if(0 < cursorIndex)
                {
                    cursorIndex -= 1;
                }

                return;//return so it doesn't place the last character
            }else if(currKey == KEY_RIGHTARROW)
            {
                //don't add to the cursor Index if its at the end of the buffer
                if(cursorIndex <= (int)buffer.length() - 1)
                {
                    cursorIndex += 1;
                }

                return;//return so it doesn't place the last character
            }
        
        }
        
        if(key.lalt == 0 && key.ralt == 0 && key.lctrl == 0)
        {
            
            //now we update the buffer
            if(4 <= currKey && currKey <= 29)
            {
                currChar = (char)(currKey + 93);

                if(key.lshift == 1)
                {
                    currChar = (char)(currChar - 32);
                }

            //if its a number
            }else if(KEY_1_EXCLAMATION_MARK <= currKey && currKey <= KEY_0_CPARENTHESIS && key.lshift == 0)
            {

                currChar = (char)(((currKey - 29) % 10) + 48);

            }else if(currKey == KEY_0_CPARENTHESIS     && key.lshift == 1)
            {
                currChar = ')';
            }else if(currKey == KEY_1_EXCLAMATION_MARK && key.lshift == 1)
            {
                currChar = '!';
            }else if(currKey == KEY_2_AT               && key.lshift == 1)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '\"';
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    currChar = '@';
                #endif
            }else if(currKey == KEY_3_NUMBER_SIGN      && key.lshift == 1)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '/';
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    currChar = '#';
                #endif
            }else if(currKey == KEY_4_DOLLAR           && key.lshift == 1)
            {
                currChar = '$';
            }else if(currKey == KEY_5_PERCENT          && key.lshift == 1)
            {
                currChar = '%';
            }else if(currKey == KEY_6_CARET            && key.lshift == 1)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '?';
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    currChar = '^';
                #endif
            }else if(currKey == KEY_7_AMPERSAND        && key.lshift == 1)
            {
                currChar = '&';
            }else if(currKey == KEY_8_ASTERISK         && key.lshift == 1)
            {
                currChar = '*';
            }else if(currKey == KEY_9_OPARENTHESIS     && key.lshift == 1)
            {
                currChar = '(';
            }else if(currKey == KEY_SLASH_QUESTION)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        // currChar = 'é';// weird character fix custom graphics
                    }else if(key.lshift == 1)
                    {
                        // currChar = 'É';// weird character fix custom graphics
                    }
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '/';
                    }else if(key.lshift == 1)
                    {
                        currChar = '?';
                    }
                #endif
            }else if(currKey == KEY_SINGLE_AND_DOUBLE_QUOTE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '`';//weird character 
                    }else if(key.lshift == 1)
                    {
                        currChar = '`';//weird character
                    }
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '\'';
                    }else if(key.lshift == 1)
                    {
                        currChar = '\"';
                    }
                #endif
            }else if(currKey == KEY_BACKSLASH_VERTICAL_BAR)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '<';
                    }else if(key.lshift == 1)
                    {
                        currChar = '>';
                    }
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '\\';
                    }else if(key.lshift == 1)
                    {
                        currChar = '|';
                    }
                #endif
            }else if(currKey == KEY_GRAVE_ACCENT_AND_TILDE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '#';
                    }else if(key.lshift == 1)
                    {
                        currChar = '|';
                    }
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '`';
                    }else if(key.lshift == 1)
                    {
                        currChar = '~';
                    }
                #endif
            }else if(currKey == KEY_MINUS_UNDERSCORE)
            {
                if(key.lshift == 0)
                {
                    currChar = '-';
                }else if(key.lshift == 1)
                {
                    currChar = '_';
                }
            }else if(currKey == KEY_EQUAL_PLUS)
            {
                if(key.lshift == 0)
                {
                    currChar = '=';
                }else if(key.lshift == 1)
                {
                    currChar = '+';
                }
            }else if(currKey == KEY_SEMICOLON_COLON)
            {
                if(key.lshift == 0)
                {
                    currChar = ';';
                }else if(key.lshift == 1)
                {
                    currChar = ':';
                }
            }else if(currKey == KEY_OBRACKET_AND_OBRACE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '^';//weird character
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = '[';
                    }else if(key.lshift == 1)
                    {
                        currChar = '{';
                    }
                #endif
            }else if(currKey == KEY_CBRACKET_AND_CBRACE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        // currChar = '¸';//weird character
                    }else if(key.lshift == 1)
                    {
                        // currChar = '¨';//weird character
                    }
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    if(key.lshift == 0)
                    {
                        currChar = ']';
                    }else if(key.lshift == 1)
                    {
                        currChar = '}';
                    }
                #endif

            //if we just pressed backspace
            }else if(currKey == KEY_BACKSPACE)
            {

                //we don't need to do anything if the string is already length 0
                if(cursorIndex != 0)
                {
                    //remove the character just behind the cursorIndex
                    buffer = buffer.substring(0, cursorIndex - 1) + buffer.substring(cursorIndex);

                    cursorIndex -= 1;
                }



                return;

                

            //if the current key is enter
            }else if(currKey == KEY_ENTER)
            {
                currChar = '\n';

            }else if(currKey == KEY_SPACEBAR)
            {
                currChar = ' ';

            }else if(currKey == KEY_DOT_GREATER)
            {
                if(key.lshift == 0)
                {
                    currChar = '.';
                }else if(key.lshift == 1)
                {
                    #if defined(FRENCH_CANADIAN_KEYBOARD)
                        currChar = '.';
                    #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                        currChar = '>';
                    #endif
                }
            }else if(currKey == KEY_COMMA_AND_LESS)
            {
                if(key.lshift == 0)
                {
                    currChar = ',';
                }else if(key.lshift == 1)
                {
                    #if defined(FRENCH_CANADIAN_KEYBOARD)
                        currChar = '\'';
                    #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                        currChar = '<';
                    #endif
                }
            }else
            {
                //we didn't find conclusive character
                return;
            }

        
        }else if(key.lalt == 0 && key.ralt == 0 && key.lctrl == 1 && key.lshift == 0)
        {

            if(currKey == KEY_BACKSPACE)
            {
                
                //we don't need to do anything if the cursorrIndex is already 0
                if(cursorIndex != 0)
                {
                    //delete all of the spaces and new lines until you hit a letter
                    while(buffer[cursorIndex - 1] == ' ' || buffer[cursorIndex - 1] == '\n')
                    {
                        
                        //remove the character just behind the cursorIndex
                        buffer = buffer.substring(0, cursorIndex - 1) + buffer.substring(cursorIndex);

                        cursorIndex -= 1;

                        //if we depleated all the string, skip the next check (it'll break everything)
                        if(cursorIndex <= 0)
                        {
                            return; //no point in continuing
                        }
                    }

                    //delete all of the letters until you hit a space or a new line again
                    while(buffer[cursorIndex - 1] != ' ' && buffer[cursorIndex - 1] != '\n')
                    {
                        
                        //remove the character just behind the cursorIndex
                        buffer = buffer.substring(0, cursorIndex - 1) + buffer.substring(cursorIndex);

                        cursorIndex -= 1;

                        //if we depleated all the string, skip the next check (it'll break everything)
                        if(cursorIndex <= 0)
                        {
                            return; //no point in continuing
                        }
                    }
                }

                return;
            }else if(currKey == KEY_UPARROW)
            {
                //We do nothing yet (will have to do some complex as balls algorithm to make cursor go up and down)
            
                return;//return so it doesn't place the last character
            }else if(currKey == KEY_DOWNARROW)
            {
                //We do nothing yet (will have to do some complex as balls algorithm to make cursor go up and down)

                return;//return so it doesn't place the last character
            }else if(currKey == KEY_LEFTARROW)
            {
                if(0 < cursorIndex)
                {
                    //go past ONE of the new lines if there are any
                    if(buffer[cursorIndex - 1] == '\n')
                    {
                    
                        //don't subtract to the cursor Index if its at the begining of the text (Bound check)
                        if(0 < cursorIndex)
                        {
                            cursorIndex -= 1;

                        //else if its out of bounds
                        }else
                        {
                            return; //no point in continuing
                        }
                    }

                    //go past all of the spaces
                    while(buffer[cursorIndex - 1] == ' ')
                    {

                        //don't subtract to the cursor Index if its at the begining of the text (Bound check)
                        if(0 < cursorIndex)
                        {
                            cursorIndex -= 1;

                        //else if its out of bounds
                        }else
                        {
                            return;//return we are at the end, no point in continuing
                        }   
                    }

                    //go past everything that is not a new line or a space
                    while(buffer[cursorIndex - 1] != ' ' && buffer[cursorIndex - 1] != '\n')
                    {

                        //don't subtract to the cursor Index if its at the begining of the text (Bound check)
                        if(0 < cursorIndex)
                        {
                            cursorIndex -= 1;

                        //else if its out of bounds
                        }else
                        {
                            return;//return we are at the end, no point in continuing
                        }
                    }

                }
              

                return;//return so it doesn't place the last character
            }else if(currKey == KEY_RIGHTARROW)
            {
                if(cursorIndex <= (int)buffer.length() - 1)
                {
                    //go past ONE of the new lines if there are any
                    if(buffer[cursorIndex] == '\n')
                    {
                    
                        //don't subtract to the cursor Index if its at the end of the text (Bound check)
                        if(cursorIndex <= (int)buffer.length() - 1)
                        {
                            cursorIndex += 1;

                        //else if its out of bounds
                        }else
                        {
                            return; //no point in continuing
                        }
                    }

                    //go past all of the spaces
                    while(buffer[cursorIndex] == ' ')
                    {

                        //don't subtract to the cursor Index if its at the end of the text (Bound check)
                        if(cursorIndex <= (int)buffer.length() - 1)
                        {
                            cursorIndex += 1;

                        //else if its out of bounds
                        }else
                        {
                            return;//return we are at the end, no point in continuing
                        }
                    }

                    //go past everything that is not a new line or a space
                    while(buffer[cursorIndex] != ' ' && buffer[cursorIndex] != '\n')
                    {

                        //don't subtract to the cursor Index if its at the end of the text (Bound check)
                        if(cursorIndex <= (int)buffer.length() - 1)
                        {
                            cursorIndex += 1;

                        //else if its out of bounds
                        }else
                        {
                            return;//return we are at the end, no point in continuing
                        }
                    }

                }

                return;//return so it doesn't place the last character
            }else
            {
                return;
            }

            return;
        }else if(key.lalt == 0 && key.ralt == 1 && key.lctrl == 0 && key.lshift == 0)
        {
            if(currKey == KEY_OBRACKET_AND_OBRACE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '[';//weird character
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    //does nothing
                #endif
            }else if(currKey == KEY_CBRACKET_AND_CBRACE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = ']';//weird character
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    //does nothing
                #endif

            }else if(currKey == KEY_SINGLE_AND_DOUBLE_QUOTE)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '{';
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    //does nothing
                #endif
            }else if(currKey == KEY_BACKSLASH_VERTICAL_BAR)
            {
                #if defined(FRENCH_CANADIAN_KEYBOARD)
                    currChar = '}';
                #elif defined(ENGLISH_CANADIAN_KEYBOARD)
                    //does nothing
                #endif
            }else
            {
                return;
            }

        }else
        {
            return;
        }

        //if the key is undefined or unusable don't do shit (the 0 <= currKey &&  is in our hearts)
        if(currKey <= 3)
        {
            return;
        }

        //add the new character just before the cursor
        buffer = buffer.substring(0, cursorIndex) + currChar + buffer.substring(cursorIndex);

        //also add to the cursorIndex (as we just added a character, its only fitting that we move the cursor to follow after what we typed)
        cursorIndex += 1;
    }

    //simple function that checks if you are currently holding the specific key
    bool checkForKey(uint8_t key)
    {
        for(int i = 0; i < 6; i++)
        {
            if(key == keys.keys[i])
            {
                return true;
            }
        }

        return false;
    }

    /**
     * @brief this function is used to check if there are no keys being pressed at the moment (this does not include modifier keys like ctrl, shift or alt)
     * @retval returns true if no keys are being pressed, and false if there are
     */
    bool keysClear()
    {
        for(int i = 0; i < 6; i++)
        {
            if(keys.keys[i] != 0)
            {
                return false;
            }
        }

        return true;
    }

    void update()
    {
        //fix the cursor if fixable (bring to the nearest good spot)
        if(cursorIndex < 0)
        {
            cursorIndex = 0;
        
        //check if out of bounds but in the bigger side (and also if the cursorIsn't at max number (kind of like a "don't do shit with the cursor"))
        }else if((int)buffer.length() < cursorIndex && cursorIndex != INT16_MAX)
        {
            cursorIndex = buffer.length();
        }

        #if defined(EMULATE_KEYBOARD)

            {
                Serial.println("Write commands and stuff for the emulated keyboard or whatever : ");

                char input[256];
                size_t len = 0;
                uint8_t state = 0;//0 = do nothng

                if(skipKeyboardDelay != 0 && millis() - skipKeyboardStartTime < skipKeyboardDelay)
                {
                    //nothing 
                }else
                {
                    skipKeyboardDelay = 0;

                    //wait and gather the user input from the Serial monitor 
                    while(true)
                    {

                        //if we have stuff comming through the serial
                        if(Serial.available() > 0)
                        {

                            //we get serial input character by character
                            char c = Serial.read();

                            //character 127 is another character that represents backspace
                            if(c == '\b' || c == 127)
                            {
                                if(len > 0)
                                {
                                    len--;
                                    if(len > 0 && input[len - 1] == '\r') len--;
                                    input[len] = '\0';
                                }
                            }

                            //this is ctrl + backspace character (so we want to delete the previous word)
                            if(c == 23)
                            {
                                //we don't need to do anything if the cursorIndex (len) is already 0
                                if(len != 0)
                                {
                                    //delete all of the spaces and new lines until you hit a letter
                                    while(input[len - 1] == ' ' || input[len - 1] == '\n' || input[len - 1] == '\r')
                                    {
                                        
                                        //remove the character just behind the cursorIndex (len)
                                        input[len - 1] = '\0';

                                        len -= 1;

                                        //if we depleated all the string, skip the next check (it'll break everything)
                                        if(len <= 0)
                                        {
                                            return; //no point in continuing
                                        }
                                    }

                                    //delete all of the letters until you hit a space or a new line again
                                    while(input[len - 1] != ' ' && input[len - 1] != '\n' && input[len - 1] != '\r')
                                    {
                                        
                                        //remove the character just behind the len
                                        input[len - 1] = '\0';

                                        len -= 1;

                                        //if we depleated all the string, skip the next check (it'll break everything)
                                        if(len <= 0)
                                        {
                                            return; //no point in continuing
                                        }
                                    }
                                }
                            } 

                            if(len >= 6 && checkstr(input + len - 6, "/enter", 0, nullptr) && c == ' ')
                            {
                                len -= 6;
                                c = 13;

                                println("getting out of the loop character : '",c,"' -> (",(int)(c),")");

                                //don't forget to set the ending character at the end of the string (replace \n by \0 in this case)
                                input[len] = '\0';

                                //we don't really need to do this, but it'll give correct length at the end so whatever (actually it wont lol it'll include the new line which is not what we want)
                                len++;

                                //we get out of the loop, we are done reading from the Serial
                                break;

                            }

                            //check if the character is a new line (if it is, it means we have pressed enter and we should get out since we are done)
                            if(c == '\n' || c == 13)
                            {
                                //text mode on command
                                if(len >= 12 && checkstr(input + len - 12, "/textmode on"))
                                {
                                    len -= 12;
                                    state = 1;
                                
                                //text mode on command
                                }else if(len >= 13 && checkstr(input + len - 13, "/textmode off"))
                                {
                                    len -= 13;
                                    state = 0;
                                
                                }else if(state == 0)
                                {
                                        
                                    println("getting out of the loop character : '",c,"' -> (",(int)(c),")");

                                    //don't forget to set the ending character at the end of the string (replace \n by \0 in this case)
                                    input[len] = '\0';

                                    //we don't really need to do this, but it'll give correct length at the end so whatever (actually it wont lol it'll include the new line which is not what we want)
                                    len++;

                                    //we get out of the loop, we are done reading from the Serial
                                    break;

                                }else if(state == 1)
                                {
                                    //new line instead
                                    input[len] = '\n';
                                    len += 1;

                                    //don't skip anything, hope it works
                                }
                            }

                            //ignore carriage returns (\r) as well as backspace and del characters
                            if(c != '\r' && c != '\b' && c != 127 && c != 23 && c != 13)
                            {
                                //set the input buffer to the current Serial input character
                                input[len] = c;

                                //increase the length
                                len++;
                            }

                            //newline command
                            if(len >= 9 && checkstr(input + len - 9, "/newline "))
                            {
                                len -= 8;
                                input[len - 1] = '\n';
                                input[len - 0] = '\0';
                            } 

                            if(true)
                            {
                                // for(unsigned int k = 0; k < 20; k++)
                                // {
                                //     Serial.println();
                                // }

                                // println("character : '",c,"' -> (",(int)(c),")");

                                println();

                                for(unsigned int k = 0; k < len; k++)
                                {
                                    if(input[k] == '\n')
                                    {
                                        Serial.print('\r');
                                    }
                                    
                                    Serial.print(input[k]);
                                }
                                //print the character so we can see what we are typing
                                // Serial.print(c);
                            }
                        }
                    }
              
                }

                emulateKeyboard(input);

            }    

        #else
            Available = keyb.available();
        #endif

        if(Available)
        {

            #if defined(EMULATE_KEYBOARD)
    
                HID_KEYBD_Info_TypeDef key = keys;

            #else

                HID_KEYBD_Info_TypeDef key = keyb.read();
                
                keys = key;
            #endif
            
            
            // printlnArray(key.keys); // can't use that

            // return;

            //go through all of the keys in the key array
            for(int i = 0; i < 6; i++)
            {
                bool success = true;

                //check if any of the keys in previous keys match the current key from key array
                for(int j = 0; j < 6; j++)
                {
                    //if they match, then make success false (is it the same, did not change)
                    if(key.keys[i] == prevKeys[j])
                    {
                        success = false;
                        break;
                    }
                }

                //if we have a key that didn't match any of the previous one, IT MUST BE A NEW KEY, so we set currKey to the NEW KEY
                if(success)
                {
                    lastPress = millis();
                    // println("got a new key : ",key.keys[i]); // can't use that
                    lastKey = currKey;
                    currKey = key.keys[i];
                    break;
                }

                //if we reached the end and didn't find conclusive character, then we return and don't do shit
                if(i == 5)
                {
                    //don't forget to update the previous keys
                    for(int i = 0; i < 6; i++)
                    {
                        prevKeys[i] = key.keys[i];
                    }

                    lastKey = currKey;
                    currKey = 0;
                    return;
                }
            }

            //don't forget to update the previous keys
            for(int i = 0; i < 6; i++)
            {
                prevKeys[i] = key.keys[i];
            }

            if(enableBuffer)
            {
                testKeys(key);
            }
        }
    
        //first / initial delay
        int delayms = 500;
        
        if(delayLimiter == 0)
        {
            delayms = 30;
        }
        
        //keyboard lib doesn't do repeat by default so we check if no change has been made on the keys and repeat
        //we first check if the last change / (last key press) was delayms which changes based on delayLimter this is the initial delay (for text 500 ms)
        //we then pass the initial delay for good and we then go on the the lastRepeat delay, this one has a shorter fixed, 30 ms cooldown
        if(Available == 0 && millis() - lastPress > delayms && millis() - lastRepeat > 30 && currKey != 0 && delayLimiter != 2)
        {
            // println("REPEATING");

            lastRepeat = millis();

            if(enableBuffer)
            {
                testKeys(keys);
            }

            Available += 1;
        }
    }

    //constructor
    KeyboardManager()
    {
        this->buffer = "";
        
        //clear the prevKeys array
        for(unsigned int i = 0; i < (sizeof(prevKeys) / sizeof(prevKeys[0])); i++)
        {
            this->prevKeys[i] = 0;
        }

        this->lastKey = 0;
        this->currKey = 0;
        this->currChar = 0;
        this->Available = false;
        this->lastPress = __LONG_LONG_MAX__;
        this->lastRepeat = 0;
        this->enableBuffer = false;
        this->cursorIndex = 0;
        this->delayLimiter = 0;
        this->skipKeyboardStartTime   = 0;
        this->skipKeyboardDelay = 0;

        clearArray(keys.keys, 0);

        for(unsigned int i = 0; i < sizeof(key_sequence)/sizeof(key_sequence[0]); i++)
        {
            key_sequence[i] = {0,0,0};
        }

    }

};

/*inline*/ KeyboardManager kbd;

//============= CUSTOM KEYBOARD CLASS ===============//

#endif