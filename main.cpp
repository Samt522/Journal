#include<iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>


using namespace std;

int main()
{   
    bool exitCode = false;

    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();

    // Convert to a time_t, which represents the time in seconds since the epoch
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to a tm structure for formatting
    std::tm localTime = *std::localtime(&currentTime);

    // Journaling system
    string textBuffer;

    // preparing for file
    std::string filename = "journal.txt"; // Specify a filename

    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::cout << "Welcome" << std::endl;
    std::cout << "Current Date and Time: "
              << std::put_time(&localTime, "%d-%m-%y %H:%M:%S") << std::endl;
    std::cout << "To stop journaling type Exit" << std::endl;

    // Write the current date and time to the file once
    outFile << "Journal Start Date and Time: "
            << std::put_time(&localTime, "%d-%m-%y %H:%M:%S") << std::endl;

    while (!exitCode)
    {   
        std::cout << "Enter text: \n &:";
        getline(cin, textBuffer);

        if (textBuffer == "Exit") {
            exitCode = true;
        } else {
            // Write the text to the file
            outFile << textBuffer << std::endl;
        }
    }

    outFile.close();

    // Prompt for a new file name
    std::string newFilename;
    std::cout << "Enter a filename to save the journal (leave empty for default): ";
    getline(cin, newFilename);

    if (newFilename.empty()) {
        int fileIndex = 1;
        do {
            newFilename = "Journal" + std::to_string(fileIndex) + ".txt";
            std::ifstream checkFile(newFilename);
            if (!checkFile) break;
            fileIndex++;
        } while (true);
    } else {
        if (newFilename.find('.') == std::string::npos) {
            newFilename += ".txt";
        }
    }

    std::rename(filename.c_str(), newFilename.c_str());

    return 0;
}