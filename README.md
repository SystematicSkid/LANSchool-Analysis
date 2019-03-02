# LANSchool Analysis PoC

This project is purely proof-of-concept and for educational uses only.

### What we know:

  - Program has two parts, student.exe and teacher.exe, which both send and recieve messages from each other
  - Only student.exe is present on client/user's computer
  - The software uses sockets to communicate
  - There is a sort of channel system
  - The teacher.exe program can capture desktops of all students
  
### The Process
1. Open student.exe in IDA and check for obfuscation
2. Check imports and exports
3. Begin analyzing string patterns throughout the program
4. Follow debug strings to functions
5. Begin naming important functions and static variables
6. Write the payload to hijack this information and functions

### Notable Functions
- **BadWordDetected**: Sends a message to the teacher, alerting them that the client typed a 'bad word', coming from a list of known words. This confirmed my suspicions of keylogging. 
![alt text](https://image.prntscr.com/image/quYsAKLKSoWC7aYV8wVRQg.png "BadWordDetected")
- **ChromeWebServerThread**: Seems to be the main thread executed when the student is using chrome, which allows pages to be blocked.
- **ClearStudentDesktop**: Closes the handle of all frames listed in a seperate function.
![alt text](https://image.prntscr.com/image/ZagEJN9vQ3_U0EBdosR2EQ.png "ClearStudentDesktop")
- **CloseLskWebSvr**: Closes the handle of the LskWebSvr, pretty simple.
![alt text](https://image.prntscr.com/image/m_lTP-NPQASkIk8_-2C_JQ.png "CloseLskWebSvr")
- **EnumChrome32WindowsProc**: Iterates through every chrome window/tab using GetClassNameA("ChromeWidgetWin_X") to send back to teacher. 
- **FindAndCloseWindowWithName**: Does as name states, closes a specific program on client computer using EnumWindows and CreateToolhelp32Snapshot
- **GetRegistryValue**: Gets requested registry key from Software\\\Classes\\\VirtualStore\\\MACHINE\\\. Only interesting because the program seems to keep a lot of values in here. Ex. PromptOnSecureDesktop, ConsentPromptBehaviorAdmin, Channel
![alt text](https://image.prntscr.com/image/YT9lYQAcQRCvI9xrbPHjoA.png "GetRegistryValue")
- **InitLskHooks**: Intitializes basic hooks on the client side to necessary functions. Can be bypassed by setting pSetHook to false.
- **SelectInputDesktop**: How the teacher is able to connect to the desktop of the client and get snapshots of it. Returns 1 if succeeded.
- **LoadLSKHooks**: A really interesting part of the client, loading a library into the prcocess named "LSKHOOK.DLL". This function gets seven different exports from the library noted above and then freeing the library, storing the functions in static offsets. Through some searching I was not able to find said dll, making me believe it is streamed from a server onto the computer, except you would think they would do that through manual mapping. I was able to aquire the dll by hooking LoadLibraryA and halting the process as it was loaded in. It should also be noted the dll handle is stored into a static offset as well.
-![alt text](https://image.prntscr.com/image/GpvH1VDrSAyiEI54Ug5wCA.png "LoadLSKHooks")

### Software Used
* IDA
* Reclass
* Visual Studio 2015

### Todo

 - Reverse teacher.exe
 - Manipulate send and recv packets
 
### Credits
- [stevemk14ebr - PolyHook](https://github.com/stevemk14ebr)

#### Even big companies have spelling errors... Here's a couple:
> Received a CursorInfo before we finished the last frame. I'm confuessd
> Teacher Unknonw when attempting to set SSPI state to TeacherAuthenticated
