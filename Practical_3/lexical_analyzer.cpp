#include <bits/stdc++.h>
using namespace std;

unordered_set<string> keywords = {"auto", "break", "case", "char", "const", "continue", "default", "do", "double",
                                  "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
                                  "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
                                  "union", "unsigned", "void", "volatile", "while"};

unordered_set<char> operators = {'+', '-', '*', '/', '=', '!', '<', '>', '&', '|', '^', '%'};
unordered_set<char> punctuation = {',', ';', '(', ')', '{', '}', '[', ']', ':'};

vector<string> symbolTable;
vector<string> lexicalErrors;

bool isNumber(const string &word) {
    for (char ch : word) {
        if (!isdigit(ch)) return false;
    }
    return true;
}

bool isValidIdentifier(const string &word) {
    if (!isalpha(word[0]) && word[0] != '_') return false; 
    for (char ch : word) {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return true;
}

void addToSymbolTable(const string &identifier) {
    if (find(symbolTable.begin(), symbolTable.end(), identifier) == symbolTable.end()) {
        symbolTable.push_back(identifier);
    }
}

void lexical_analyzer(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error: Unable to open file " << filename << ".\n";
        return;
    }

    cout << "TOKENS\n";
    string line, token;
    bool multiLineComment = false;

    while (getline(file, line)) {
        stringstream ss(line);
        while (ss >> token) {
            if (multiLineComment) {
                if (token.find("*/") != string::npos) multiLineComment = false;
                continue;
            }

            if (token == "//") break; // Ignore rest of line after //

            if (token.find("/*") != string::npos) {
                multiLineComment = true;
                continue;
            }

            if (keywords.find(token) != keywords.end()) {
                cout << "Keyword: " << token << "\n";
            } 
            else if (isNumber(token)) {
                cout << "Constant: " << token << "\n";
            } 
            else if (isValidIdentifier(token)) {
                cout << "Identifier: " << token << "\n";
                addToSymbolTable(token);
            } 
            else if (token.size() == 1 && operators.find(token[0]) != operators.end()) {
                cout << "Operator: " << token << "\n";
            } 
            else if (token.size() == 1 && punctuation.find(token[0]) != punctuation.end()) {
                cout << "Punctuation: " << token << "\n";
            } 
            else if (token.size() >= 3 && token.front() == '\'' && token.back() == '\'' && token.length() == 3) {
                cout << "String: " << token << "\n";
            } 
            else {
                lexicalErrors.push_back(token + " invalid lexeme");
            }
        }
    }
    file.close();

    cout << "LEXICAL ERRORS\n";
    for (const string &error : lexicalErrors) {
        cout << error << "\n";
    }

    cout << "SYMBOL TABLE ENTRIES\n";
    int index = 1;
    for (const string &symbol : symbolTable) {
        cout << index++ << ") " << symbol << "\n";
    }
}

int main() {
    string filename = "cfilecheck.txt"; 
    lexical_analyzer(filename);
    return 0;
}
