/*
 * GroceryTracker.cpp
 *
 * Author: Andrei Kim
 * Date: 2/22/2026
 * Purpose: Implements GroceryTracker class for Corner Grocer item tracking.
 */
#include "GroceryTracker.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>     // system()
#include <fstream>
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::string;

GroceryTracker::GroceryTracker(const string& inputFile,
    const string& pythonScript,
    const string& backupFile)
    : m_inputFile(inputFile),
    m_pythonScript(pythonScript),
    m_backupFile(backupFile) {
}

bool GroceryTracker::Initialize() {
    // Requirement: create frequency.dat at the beginning with no user intervention
    if (!CreateBackupFileWithPython()) {
        cout << "ERROR: Could not create " << m_backupFile << " using Python.\n";
        return false;
    }

    // Load frequency.dat so C++ can answer menu options efficiently
    if (!LoadBackupFile()) {
        cout << "ERROR: Could not load " << m_backupFile << ".\n";
        return false;
    }

    return true;
}

bool GroceryTracker::CreateBackupFileWithPython() {
    // Try common Python launch commands (Windows vs Codio/Linux)
    // This runs PythonCode.py which reads CS210_Project_Three_Input_File.txt
    // and writes frequency.dat.
    const string cmd1 = "py " + m_pythonScript;
    const string cmd2 = "python " + m_pythonScript;
    const string cmd3 = "python3 " + m_pythonScript;

    int rc = std::system(cmd1.c_str());
    if (rc != 0) rc = std::system(cmd2.c_str());
    if (rc != 0) rc = std::system(cmd3.c_str());

    if (rc != 0) {
        cout << "ERROR: Python did not run successfully.\n";
        cout << "Make sure Python is installed AND these files are in the program folder:\n";
        cout << "  - " << m_pythonScript << "\n";
        cout << "  - " << m_inputFile << "\n";
        return false;
    }

    return true;
}

bool GroceryTracker::LoadBackupFile() {
    std::ifstream in(m_backupFile);
    if (!in.is_open()) {
        return false;
    }

    m_counts.clear();
    m_displayNames.clear();

    string item;
    int count = 0;

    // frequency.dat lines look like: Potatoes 4
    while (in >> item >> count) {
        const string key = NormalizeKey(item);
        m_counts[key] = count;
        m_displayNames[key] = ToDisplayName(item);
    }

    return true;
}

void GroceryTracker::Run() {
    while (true) {
        PrintMenu();
        int choice = GetMenuChoice(1, 4);

        if (choice == 1) {
            OptionFindItem();
        }
        else if (choice == 2) {
            OptionPrintAll();
            Pause();
        }
        else if (choice == 3) {
            OptionPrintHistogram();
            Pause();
        }
        else { // 4
            cout << "Program Finished." << endl;
            break;
        }
    }
}

void GroceryTracker::PrintMenu() const {
    cout << "\n=========== Corner Grocer Menu ===========\n";
    cout << "1) Look up an item frequency\n";
    cout << "2) Print all item frequencies\n";
    cout << "3) Print histogram\n";
    cout << "4) Exit\n";
    cout << "Select an option (1-4): ";
}

int GroceryTracker::GetMenuChoice(int minChoice, int maxChoice) {
    int choice = 0;

    while (true) {
        if (cin >> choice && choice >= minChoice && choice <= maxChoice) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }

        // Input validation / error handling
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid choice. Enter " << minChoice << "-" << maxChoice << ": ";
    }
}

void GroceryTracker::OptionFindItem() const {
    cout << "Enter the item you wish to look for: ";
    string item;
    std::getline(cin, item);

    const string key = NormalizeKey(item);

    auto it = m_counts.find(key);
    int count = (it != m_counts.end()) ? it->second : 0;

    // Requirement: return numeric frequency of the specific word
    cout << ToDisplayName(item) << " " << count << endl;
    Pause();
}

void GroceryTracker::OptionPrintAll() const {
    // Requirement: print each item and the number of times it appears
    for (const auto& pair : m_counts) {
        const string& key = pair.first;
        int count = pair.second;

        auto nameIt = m_displayNames.find(key);
        const string display = (nameIt != m_displayNames.end()) ? nameIt->second : ToDisplayName(key);

        cout << display << " " << count << endl;
    }
}

void GroceryTracker::OptionPrintHistogram() const {
    // Requirement: print each item and asterisks equal to frequency
    for (const auto& pair : m_counts) {
        const string& key = pair.first;
        int count = pair.second;

        auto nameIt = m_displayNames.find(key);
        const string display = (nameIt != m_displayNames.end()) ? nameIt->second : ToDisplayName(key);

        cout << display << " " << string(static_cast<size_t>(count), '*') << endl;
    }
}

string GroceryTracker::NormalizeKey(string text) {
    Trim(text);
    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return text;
}

string GroceryTracker::ToDisplayName(string text) {
    Trim(text);
    if (text.empty()) return text;

    std::transform(text.begin(), text.end(), text.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    text[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(text[0])));
    return text;
}

void GroceryTracker::Trim(string& s) {
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.front()))) {
        s.erase(s.begin());
    }
    while (!s.empty() && std::isspace(static_cast<unsigned char>(s.back()))) {
        s.pop_back();
    }
}

void GroceryTracker::Pause() {
    cout << "\nPress Enter to continue...";
    string dummy;
    std::getline(cin, dummy);
}