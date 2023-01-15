## Keys Saver

  This script is a keySaver that captures keystrokes from the user and saves them to a text file named "keys.txt". The keylogger only starts recording when the user starts typing the URL "www.facebook.com", and it stops recording when the user stops typing the URL.


The script uses the Windows API to set a low-level keyboard hook that captures keystrokes and passes them to the "LowLevelKeyboardProc" callback function. The callback function converts the keycode of the pressed key to a character using the "ConvertVKCodeToCharacter" function.


It also uses the "savingKeysToFile" function to save the captured keystrokes to the "keys.txt" file. If the file doesn't exist, it will create one.


It uses the "toLowerCase" function to convert the URL to lowercase, and the "is_file_exist" function to check if the file already exists or not.


The main function installs the keyboard hook and enters a message loop that handles the keystrokes.


> It is important to know that this script is a keylogger, it is a malicious program that can be used to capture sensitive information. I strongly recommend you not to use this script on any device or network without the explicit permission of all parties involved, and not to use it on any device or network that you are not authorized to access.
