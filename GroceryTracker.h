/*
 * GroceryTracker.h
 *
 * Author: [Your Name]
 * Date: [Enter Date]
 * Purpose: Declares the GroceryTracker class for Corner Grocer item tracking.
 *          Uses Python to create frequency.dat, then C++ uses that data for menu options.
 */

#ifndef GROCERY_TRACKER_H
#define GROCERY_TRACKER_H

#include <map>
#include <string>

class GroceryTracker {
public:
    GroceryTracker(const std::string& inputFile,
        const std::string& pythonScript,
        const std::string& backupFile);

    // Runs Python to create frequency.dat, then loads it into memory.
    bool Initialize();

    // Menu loop: options 1–4.
    void Run();

private:
    std::string m_inputFile;
    std::string m_pythonScript;
    std::string m_backupFile;

    // Key = lowercase item name, Value = count
    std::map<std::string, int> m_counts;

    // Key = lowercase item name, Value = nice display name
    std::map<std::string, std::string> m_displayNames;

    // ----- core steps -----
    bool CreateBackupFileWithPython(); // creates frequency.dat automatically at start
    bool LoadBackupFile();             // loads frequency.dat into maps

    // ----- menu actions -----
    void PrintMenu() const;
    int GetMenuChoice(int minChoice, int maxChoice);
    void OptionFindItem() const;
    void OptionPrintAll() const;
    void OptionPrintHistogram() const;

    // ----- utilities -----
    static std::string NormalizeKey(std::string text);
    static std::string ToDisplayName(std::string text);
    static void Trim(std::string& s);
    static void Pause();
};

#endif