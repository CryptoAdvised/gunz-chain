#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

bool containsAnyKeyword(const std::string& processName, const std::vector<std::string>& keywords) {
    for (const auto& keyword : keywords) {
        if (processName.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void AntiHack() {
    std::vector<std::string> keywords = {"hack", "h4ck", "cheat", "ch3at", "che4t", "ch34t", "exploit", "dbg", "inject", "1nject"}; 
    while (true) {
        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    // Correct conversion for CHAR[260] to std::string
                    std::string processName(pe32.szExeFile);

                    if (containsAnyKeyword(processName, keywords)) {
                        std::cout << "Detected process: " << processName << std::endl;
                    }
                } while (Process32Next(hSnapshot, &pe32));
            }
            CloseHandle(hSnapshot);
        }
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }
}
