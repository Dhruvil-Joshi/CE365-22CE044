#include <bits/stdc++.h>
using namespace std;

vector<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while"
};

vector<string> operators = {"+", "++", "-", "--", "*", "/", "<", ">", ">=", "<=", "^", "%", "=", "=="};
vector<string> symbols = {",", ";", "(", ")", "{", "}", "[", "]", ":"};

bool isKeyword(const string &word) {
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}

bool isOperator(const string &word) {
    return find(operators.begin(), operators.end(), word) != operators.end();
}

bool isSymbol(char ch) {
    return find(symbols.begin(), symbols.end(), string(1, ch)) != symbols.end();
}

bool isCharConstant(const string &word) 
{
    return word.size() == 3 && word[0] == '\'' && word[2] == '\''; 
}
bool isIdentifier(const string &word) 
{
    if (word.empty() || isdigit(word[0])) 
    return false;

    for (char ch : word) 
    {
        if (!isalnum(ch) && ch != '_') return false;
    }
    return !isKeyword(word); 
}

bool isNumber(const string &word) 
{
    bool hasDecimal = false;
    for (char ch : word) {
        if (!isdigit(ch)) {
            if (ch == '.' && !hasDecimal) {
                hasDecimal = true; 
            }
            else 
            {
                return false;
            }
        }
    }
    return true;
}

void lexicalAnalysis(const string &filename) 
{
    ifstream file(filename);
    if (!file) 
    {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    bool multiLineComment = false; // Flag for multi-line comment

    while (getline(file, line)) 
    {
        string token;
        bool stringLiteral = false;
        bool charConstant = false;
        string currentString = "";
        
        for (size_t i = 0; i < line.size(); i++) 
        {
            char ch = line[i];
            if (i < line.size() - 1 && line[i] == '/' && line[i + 1] == '/') 
            break;
            if (multiLineComment) 
            {
                if (i < line.size() - 1 && line[i] == '*' && line[i + 1] == '/') 
                {
                    multiLineComment = false;
                    i++;
                }
                continue;
            }
            if (i < line.size() - 1 && line[i] == '/' && line[i + 1] == '*')
            {
                multiLineComment = true;
                i++; 
                continue;
            }
            
            if (ch == '"') 
            {
                if (stringLiteral) 
                {
                    currentString += ch;
                    cout << "String Literal: " << currentString << endl;
                    currentString = "";
                } 
                else 
                {
                    currentString = "\"";
                }
                stringLiteral = !stringLiteral;
                continue;
            }
            if (stringLiteral) 
            {
                currentString += ch;
                continue;
            }

            if (ch == '\'') 
            {
                if (charConstant) 
                {   currentString += ch;
                    if (currentString.size() == 3) 
                    {
                        cout << "Character Constant: " << currentString << endl;
                    } 
                    else 
                    {
                        cout << "Invalid Character Constant: " << currentString << endl;
                    }
                    currentString = "";
                } else 
                {
                    currentString = "'";
                }
                charConstant = !charConstant;
                continue;
            }
            if (charConstant) 
            {
                currentString += ch;
                continue;
            }

            if (isSymbol(ch)) 
            {
                if (!token.empty()) 
                {
                    if (isKeyword(token)) 
                    {
                        cout << "Keyword: " << token << endl;
                    } 
                    else if (isIdentifier(token)) 
                    {
                        cout << "Identifier: " << token << endl;
                    } 
                    else if (isNumber(token)) 
                    {
                        cout << "Number: " << token << endl;
                    } 
                    else 
                    {
                        cout << "Unknown Token: " << token << endl;
                    }
                    token.clear();
                }
                cout << "Symbol: " << ch << endl;
                continue;
            }

            if (isOperator(string(1, ch))) 
            {
                if (!token.empty()) 
                {
                    if (isKeyword(token)) 
                    {
                        cout << "Keyword: " << token << endl;
                    } 
                    else if (isIdentifier(token)) 
                    {
                        cout << "Identifier: " << token << endl;
                    } 
                    else if (isNumber(token)) 
                    {
                        cout << "Number: " << token << endl;
                    } 
                    else 
                    {
                        cout << "Unknown Token: " << token << endl;
                    }
                    token.clear();
                }

                string op(1, ch);
                if (i < line.size() - 1 && isOperator(op + line[i + 1])) {
                    op += line[i + 1];
                    i++;
                }
                cout << "Operator: " << op << endl;
                continue;
            }

            if (isalnum(ch) || ch == '_') 
            {
                token += ch;
            } 
            else if (!token.empty()) 
            {
                if (isKeyword(token)) 
                {
                    cout << "Keyword: " << token << endl;
                } 
                else if (isIdentifier(token)) 
                {
                    cout << "Identifier: " << token << endl;
                } 
                else if (isNumber(token)) 
                {
                    cout << "Number: " << token << endl;
                } 
                else 
                {
                    cout << "Unknown Token: " << token << endl;
                }
                token.clear();
            }
        }

        if (!token.empty()) 
        {
            if (isKeyword(token)) 
            {
                cout << "Keyword: " << token << endl;
            } 
            else if (isIdentifier(token)) 
            {
                cout << "Identifier: " << token << endl;
            } 
            else if (isNumber(token))
            {
                cout << "Number: " << token << endl;
            } 
            else 
            {
                cout << "Unknown Token: " << token << endl;
            }
        }
    }

    file.close();
}

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    lexicalAnalysis(filename);
    return 0;
}
