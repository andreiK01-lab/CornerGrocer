/*
 * main.cpp
 *
 * Author: Andrei Kim
 * Date: 2/22/2026
 * Purpose: Starts the Corner Grocer item tracker program.
 */

#include "GroceryTracker.h"
#include <iostream>

int main() {
    GroceryTracker app(
        "CS210_Project_Three_Input_File.txt",
        "PythonCode.py",
        "frequency.dat"
    );

    if (!app.Initialize()) {
        std::cout << "Initialization failed. Check file locations and try again.\n";
        return 1;
    }

    app.Run();
    return 0;
}