#include <windows.h>
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>




//TODO 
//create a sequence for index specific swap function (Self determined words for swapped 



/**
* SWAP TEXT SHORTCUT SCRIPT
* 
* Uses Windows Hooks to scan for a certain command;
* If command is pressed, 
*   
*   Simulate a "Control + C" using "keybd_event();
*   Store whatever the last value in clipboard was;
*    
* 
*   "swapFirstAndLastWords()"
*     Uses utility functions "findFirstWord()" and "findLastWord()" 
*     swaps those values in the array
*   
*   Use keybd_event() to simulate key strokes of the characters in the new string
*   
* 
*   EXAMPLE:
* 
*   "They took the ball" >>
*   *Text is highlighted and user presses F10*
*   "ball took the They"
*/




//PROTOTYPES

void SendCopyCommand();                                                             //Used directly after callback function
void pasteBufferCommand(wchar_t* arr);                                              //prints new string
void findFirstWord(wchar_t* str, wchar_t** start, wchar_t** end);                   //finds first word
void findLastWord(wchar_t* str, wchar_t** start, wchar_t** end);                    //finds last word
void swapFirstAndLastWords(wchar_t* str);                                           //first and last words are swapped from text
void ReadClipboardText();                                                           //If F10 is hit, first sends copy command, then read clipboard text
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);     //Hook callback function to look for an "F10" hit (is changeable)






//delimiter for first and last word
const wchar_t delim = ' ';





// Hook handle
HHOOK hKeyboardHook;





//ENTRY POINT
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Set the hook
    hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
    if (hKeyboardHook == NULL) {
        OutputDebugStringW(L"Failed to install hook!\n");
        return 1;
    }

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Remove the hook
    UnhookWindowsHookEx(hKeyboardHook);

    return (int)msg.wParam;
}



// Function to send a Ctrl+C command
void SendCopyCommand() {
    keybd_event(VK_CONTROL, 0, 0, 0);
    keybd_event('C', 0, 0, 0);
    keybd_event('C', 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}

//
void pasteBufferCommand(wchar_t* arr) {
    OutputDebugString(arr);
    for (int i = 0; arr[i] != L'\0'; i++) {        //for every character...

        char asciiChar = (char)arr[i]; // Truncate to ASCII - this is a simplification!
        SHORT vk = VkKeyScan(asciiChar); // Get the virtual-key code and shift state for the character
        BYTE vkCode = LOBYTE(vk); // Virtual-key code
        BYTE shiftState = HIBYTE(vk);


        if (shiftState & 1) {
            keybd_event(VK_SHIFT, 0, 0, 0);
        }

        // Press and release the key
        keybd_event(vkCode, 0, 0, 0); // Key down
        keybd_event(vkCode, 0, KEYEVENTF_KEYUP, 0); // Key up

        // Release shift if needed
        if (shiftState & 1) {
            keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
        }

    }


}




// Utility Function
// Finds first word of string, not including utility function
void findFirstWord(wchar_t* str, wchar_t** start, wchar_t** end) {
    *start = str;
    while (**start == L' ' && **start != L'\0') { // Skip leading spaces
        (*start)++;
    }
    *end = *start;
    while ( (**end != L' '  && **end != L',') && **end != L'\0') { // Find the end of the first word
        (*end)++;
    }
}

//mouse ate, cat the The



// Utility function to find the boundaries of the last word
void findLastWord(wchar_t* str, wchar_t** start, wchar_t** end) {
    *end = str + wcslen(str); // Start at the end of the string
    while (*end > str && *(*end - 1) == L' ') { // Skip trailing spaces
        (*end)--;
    }
    *start = *end;
    while ( (*start > str) && (*(*start - 1) != L' ' && *(*start -1) != ',') ) { // Find the start of the last word
        (*start)--;
    }
}



// Function to swap the first and last words in a string
void swapFirstAndLastWords(wchar_t* str) {
    wchar_t* firstStart, * firstEnd, * lastStart, * lastEnd;
    findFirstWord(str, &firstStart, &firstEnd);
    findLastWord(str, &lastStart, &lastEnd);

    size_t firstWordLength = firstEnd - firstStart;
    size_t lastWordLength = lastEnd - lastStart;
    size_t middleSectionLength = lastStart - firstEnd;

    // Allocate a buffer to hold the entire string including the null terminator
    size_t strLength = wcslen(str) + 1;
    wchar_t* buffer = (wchar_t*)malloc(strLength * sizeof(wchar_t));

    // Copy the last word to the beginning
    wcsncpy_s(buffer, strLength, lastStart, lastWordLength);
    // Copy the middle section
    wcsncpy_s(buffer + lastWordLength, strLength - lastWordLength, firstEnd, middleSectionLength);
    // Copy the first word to the end
    wcsncpy_s(buffer + lastWordLength + middleSectionLength, strLength - (lastWordLength + middleSectionLength), firstStart, firstWordLength);
    // Null-terminate the buffer
    buffer[lastWordLength + middleSectionLength + firstWordLength] = L'\0';

    // Copy the buffer back to the original string
    wcscpy_s(str, strLength, buffer);

    // Free the temporary buffer
    free(buffer);
}



// Function to read the text from the clipboard
void ReadClipboardText() {
    if (!OpenClipboard(NULL)) {
        OutputDebugStringW(L"Failed to open clipboard\n");
        return;
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == NULL) {
        OutputDebugStringW(L"No text on the clipboard\n");
        CloseClipboard();
        return;
    }

    //assign pText most recent on clip board
    wchar_t* pText = static_cast<wchar_t*>(GlobalLock(hData));
    if (pText == NULL) {
        CloseClipboard();
        return;
    }

    // Output the text to the debug output
    OutputDebugStringW(pText);

    //call function to swap first and last words of pText
    swapFirstAndLastWords(pText);

    //call function to type new text
    pasteBufferCommand(pText);

    // Release the lock and close the clipboard
    GlobalUnlock(hData);
    CloseClipboard();
}



// Implementation of the hook callback
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
        if (wParam == WM_KEYDOWN) {
            // Check if F10 is pressed
            if (p->vkCode == VK_F10) {
                // Simulate Ctrl+C and read the clipboard
                SendCopyCommand();
                // Allow some time for the clipboard to get the data
                Sleep(50);
                ReadClipboardText();
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}