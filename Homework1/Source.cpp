#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct bookInfo {
    string Title;
    string authorName;
    int wordCount = 0;
    int lineCount = 0;
    double letFreq;
};

int main() {
    ifstream inputFile; // File of book to be read
    ofstream outputFile; // File for output of book information

    string fileName; // Name of file given by user
    char answer;
    bool freq;
    bool continuing = true;
    int counter = 0;
    string word;
    string lines;

    bookInfo book;


    while (continuing) {    // True until the user wants to quit inputting books
        cout << "Enter the name of the file: ";
        cin >> fileName;
        cout << endl;

        inputFile.open(fileName, ios::in);

        while (inputFile.fail()) {  // Tests if file could be opened
            cout << "File could not be open" << endl;
            cout << "Enter the name of the file: ";
            cin >> fileName;
            inputFile.open(fileName, ios::in);
        }

        cout << "Would you like to see the letter frequency?" << endl;
        cout << "Type 'Y' for Yes or 'N' for No: ";
        cin >> answer;
        cout << endl;

        if (answer == 'Y') {    // Outputs frequency
            freq = true;
        }
        else if (answer == 'N') {   // Doesn't output frequency
            freq = false;
        }

        if (outputFile.fail() || counter > 0) { // If the file is found or is adding another book
            outputFile.open("CardCatalog.txt", ios::out | ios::app);
        }
        else {  // If the file is not found or needs created
            outputFile.open("CardCatalog.txt", ios::out);
        }

        getline(inputFile, book.Title);
        outputFile << "Title: " << book.Title << endl;
        getline(inputFile, book.authorName);
        int pos = book.authorName.find(' ');
        outputFile << "Author: " << book.authorName << endl;
        outputFile << "Author First Name: " << book.authorName.substr(0, pos) << endl;
        outputFile << "Author Last Name: " << book.authorName.substr(pos + 1, string::npos) << endl;

        char alphaList[] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' }; // Array of alphabet letters
        double statsList[26] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };    // Array of count for each letter
        int arrSize = sizeof(alphaList) / sizeof(alphaList[0]); // size of array
        int totalCharacters = 0;


        ifstream file(fileName);
        bool foundContents = false;
        while (inputFile >> word) {     // Finds number of words
            if (foundContents == false) {
                if (word == "Contents:") {  // Doesn't starting count till 'contents:' is found
                    foundContents = true;
                }
            }
            else {		// Finds word count, total number of characters, and each letter count
                book.wordCount++;
                for (int i = 0; i < word.length(); i++) {
                    for (int j = 0; j < arrSize; ++j) {
                        if (tolower(word.at(i)) == alphaList[j]) {
                            totalCharacters++;
                            statsList[j]++;
                        }
                    }
                }
            }
        }
        foundContents = false;
        while (getline(file, lines)) {	// finds number of lines
            if (foundContents == false) {
                if (lines == "Contents:") { // Doesn't starting count till 'contents:' is found
                    foundContents = true;
                }
            }
            else {
                book.lineCount += 1;
            }
        }
        outputFile << "Number of words: " << book.wordCount << endl;
        outputFile << "Number of lines: " << book.lineCount << endl;
        if (freq) { // If user wants to see the frequency of words
            for (int i = 0; i < arrSize; i++) {
                outputFile << alphaList[i] << ": " << setprecision(4) << static_cast<double>(statsList[i] / totalCharacters) << endl;
            }
        }
        cout << "Check CardCatalog.txt File!\n" << endl;

        outputFile << endl;

        char keepGoing;

        cout << "Do you want to continue?" << endl;
        cout << "Type 'Y' for Yes or 'N' for No: ";
        cin >> keepGoing;

        if (keepGoing == 'Y') { // If user wants to continue inputting books
            counter++;
            continuing = true;
        }
        else if (keepGoing == 'N') {    // If user wants to continue inputting books
            continuing = false;
        }
        outputFile.close();
        inputFile.close();
    }
}