# CornerGrocer
Portfolio
Corner Grocer is an item-tracking program that analyzes a daily purchase log stored in CS210_Project_Three_Input_File.txt. The goal was to calculate how often each item appears in the log so the store can make better decisions about produce layout and stocking priorities. The program also generates a backup file named frequency.dat at startup that records each item and its purchase frequency.

What I Did Particularly Well

The program follows the functional requirements closely by providing a clear menu with four options, including item lookup, full frequency output, histogram output, and exit. The design keeps the workflow simple for the user while using a map-based data structure for efficient counting and fast lookups. I also focused on readable, professional code by using consistent naming conventions, in-line comments, and a clear separation of responsibilities across functions and files.

Where the Code Could Be Enhanced

Input normalization could be improved further to handle edge cases such as capitalization differences, trailing spaces, and minor variations like punctuation. Error handling could also be expanded to provide more detailed feedback when files are missing or incorrectly formatted. These improvements would increase reliability, reduce user error, and make the program more secure by preventing unexpected behavior due to malformed input or file issues.

Most Challenging Parts and How I Overcame Them

The most challenging part was making sure the data flow stayed correct from start to finish. The program needed to create frequency.dat automatically, then load accurate counts for menu operations, while also keeping output consistent. I handled this by building and testing in small steps, verifying file output early, and using debugging prints and repeated test runs with known input. Resources that helped included zyBooks sections on file input and output, maps, and general C++ documentation for string handling and validation.

Transferable Skills

This project strengthened core skills that apply to most software projects, including file I O, working with maps for counting and retrieval, building a menu-driven console interface, and validating user input. It also reinforced translating functional requirements into a working program and producing output that is both correct and easy to interpret.

Maintainability, Readability, and Adaptability

The program was made maintainable by using a class with public and private sections, organizing code into small, focused functions, and keeping variable and function names descriptive. In-line comments explain the intent of key steps, especially where data is read, processed, and written. The program is adaptable because the counting logic and output logic are separated, so additional features like sorting options, different histogram symbols, or exporting reports can be added without rewriting the core counting process.
