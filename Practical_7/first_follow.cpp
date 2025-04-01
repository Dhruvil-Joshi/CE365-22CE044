#include<bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> productions;
unordered_map<string, set<string>> first;
unordered_map<string, set<string>> follow;
unordered_map<string, bool> visited;

void DFS(string nonterminal)
{
    if (visited[nonterminal])
        return;
    
    visited[nonterminal] = true;
    
    for (string rule : productions[nonterminal])
    {
        if (!isupper(rule[0])) // Terminal or null character (@)
        {
            first[nonterminal].insert(string(1, rule[0]));
        }
        else
        {
            for (int i = 0; i < rule.length(); i++)
            {
                if (!isupper(rule[i]))
                {
                    first[nonterminal].insert(string(1, rule[i]));
                    break;
                }
                else
                {
                    DFS(string(1, rule[i]));
                    bool hasNull = false;
                    for (string val : first[string(1, rule[i])])
                    {
                        if (val == "@") // Null character
                            hasNull = true;
                        else
                            first[nonterminal].insert(val);
                    }
                    if (!hasNull)
                        break;
                }
            }
        }
    }
}

void First(string starting_nonterminal)
{
    for (auto prod : productions)
    {
        if (!visited[prod.first])
            DFS(prod.first);
    }
    
    for (auto f : first)
    {
        cout << "FIRST(" << f.first << ") = { ";
        bool firstItem = true;
        for (auto val : f.second)
        {
            if (!firstItem) cout << ", ";
            cout << val;
            firstItem = false;
        }
        cout << " } \n";
    }
}

void Follow(string starting_nonterminal)
{
    follow[starting_nonterminal].insert("$"); // Start symbol gets $
    
    for (int i = 0; i < 5; i++) // Multiple passes to ensure all dependencies resolve
    {
        for (auto prod : productions)
        {
            string nonterminal = prod.first;
            for (string rule : prod.second)
            {
                for (int j = 0; j < rule.length(); j++)
                {
                    if (isupper(rule[j])) // If it's a nonterminal
                    {
                        string B = string(1, rule[j]);
                        bool hasNull = false;
                        
                        for (int k = j + 1; k < rule.length(); k++)
                        {
                            if (!isupper(rule[k]))
                            {
                                follow[B].insert(string(1, rule[k]));
                                break;
                            }
                            else
                            {
                                for (string val : first[string(1, rule[k])])
                                {
                                    if (val == "@")
                                        hasNull = true;
                                    else
                                        follow[B].insert(val);
                                }
                                if (!hasNull) break;
                            }
                        }
                        if (hasNull || j == rule.length() - 1)
                        {
                            for (string val : follow[nonterminal])
                                follow[B].insert(val);
                        }
                    }
                }
            }
        }
    }
    
    for (auto f : follow)
    {
        cout << "FOLLOW(" << f.first << ") = { ";
        bool firstItem = true;
        for (auto val : f.second)
        {
            if (!firstItem) cout << ", ";
            cout << val;
            firstItem = false;
        }
        cout << " } \n";
    }
}

int main()
{
    int n;
    cout << "Enter number of rules: ";
    cin >> n;
    string starting_nonterminal;        
    bool starting = false;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        string Nonterminal;
        bool flag = false;
        string temp = "";
        for (int j = 0; j < s.size(); j++)
        {
            if (!flag && s[j] != '-' && s[j] != '>')
            {
                Nonterminal += s[j];
            }
            else if (s[j] == '-')
            {    
                if (!starting)
                {
                    starting_nonterminal = Nonterminal;       
                    starting = true;
                }
            }
            else if (s[j] == '>')
                flag = true;
            else
            {
                if (flag)
                {
                    if (s[j] != '|')
                        temp += s[j];
                    else
                    {
                        productions[Nonterminal].push_back(temp);
                        temp = "";
                    }
                }
            }
        }
        if (temp != "")
            productions[Nonterminal].push_back(temp);
    }
    
    cout << "Starting nonterminal: " << starting_nonterminal << endl;
    
    First(starting_nonterminal);
    Follow(starting_nonterminal);
    
    return 0;
}