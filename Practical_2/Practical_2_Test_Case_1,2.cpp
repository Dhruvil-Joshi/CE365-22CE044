#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cout << "Number of input symbols: ";
    cin>>n;
    vector<char> inputSymbols;
    char temp;
    cout << "Input symbols: ";
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        inputSymbols.push_back(temp);
    }
    
    int states;
    cout << "Enter number of states: ";
    cin>>states;
    int initial;
    cout << "Initial state: ";
    cin>>initial;
    int numberofaccept;
    cout << "Number of accepting states: ";
    cin>>numberofaccept;
    vector<int> acceptingstates;
    cout << "Accepting state: ";
    for(int i=0;i<numberofaccept;i++)
    {
        int temp;
        cin>>temp;
        acceptingstates.push_back(temp);
    }
    int m = states;
    printf("Transition table: \n");
    int mat[m + 1][n];
    for (int i = 0; i < n; i++)
    {
        mat[0][i] = 0;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << i << " to " << inputSymbols[j] << " -> ";
            cin >> mat[i][j];
        }
    }

    string input;
    cout << "Input string: ";
    cin >> input;

    int currentstate = initial;

    for (int i = 0; i < input.length(); i++)
    {
        int intermediate = -1;
        for (int j = 0; j < inputSymbols.size(); j++)
        {
            if (input[i] == inputSymbols[j])
            {
                intermediate = j;
                break;
            }
        }
        // cout<<currentstate<<" to "<<inputSymbols[intermediate]<<": "<<mat[currentstate][intermediate]<<endl;
        currentstate = mat[currentstate][intermediate];
    }

    // cout << currentstate;
    bool flag = false;
    for (int i = 0; i < numberofaccept; i++)
    {
        if (currentstate == acceptingstates[i])
        {
            flag = true;
            break;
        }
    }
    if (flag)
    {
        cout << "Valid String" << endl;
    }
    else
    {
        cout << "Invalid String" << endl;
    }
    return 0;
}