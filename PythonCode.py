"""
PythonCode.py

Author: Andrei Kim
Date: 2/22/2026
Purpose: Read CS210_Project_Three_Input_File.txt, count item frequencies,
         and create frequency.dat automatically for backup.

frequency.dat format:
ItemName count
"""

INPUT_FILE = "CS210_Project_Three_Input_File.txt"
OUTPUT_FILE = "frequency.dat"


def _to_display_name(word: str) -> str:
    """Convert to a nice display name: first letter uppercase, rest lowercase."""
    word = word.strip()
    return word[:1].upper() + word[1:].lower() if word else word


def build_frequency_dat():
    """Read input file, compute frequencies (case-insensitive), write frequency.dat."""
    freq = {}

    with open(INPUT_FILE, "r") as f:
        for line in f:
            item = line.strip()
            if item:
                key = item.lower()
                freq[key] = freq.get(key, 0) + 1

    # Write sorted for clean output (alphabetical by item)
    with open(OUTPUT_FILE, "w") as out:
        for key in sorted(freq.keys()):
            out.write(f"{_to_display_name(key)} {freq[key]}\n")


if __name__ == "__main__":
    # This ensures that running "py PythonCode.py" actually creates frequency.dat
    build_frequency_dat()