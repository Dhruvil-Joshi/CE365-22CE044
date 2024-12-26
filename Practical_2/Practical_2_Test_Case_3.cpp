#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n=36;
    cout << "Number of input symbols: "<<n<<endl;
    vector<char> inputSymbols;
    char temp;
    cout << "Input symbols: ";
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> temp;
    //     inputSymbols.push_back(temp);
    // }
    for (char i = 'a'; i <= 'z'; i++)
    {
        inputSymbols.push_back(i);
    }
    
    for (char i = '0'; i <= '9'; i++)
    {
        inputSymbols.push_back(i);
    }
    for(int i=0;i<inputSymbols.size();i++)
    {
        cout<<inputSymbols[i]<<" ";
    }
    cout<<endl;
    int states = 3;
    cout << "Enter number of states: "<<states<<endl;
    int initial = 1;
    cout << "Initial state: "<<initial<<endl;
    int numberofaccept = 1;
    cout << "Number of accepting states: "<<numberofaccept<<endl;
    int acceptingstates=2;
    cout << "Accepting state: "<<acceptingstates<<endl;
    int m = states;
    printf("Transition table: \n");
    int mat[m + 1][n];
    for (int i = 0; i < n; i++)
    {
        mat[0][i] = 0;
    }

    // for (int i = 1; i <= m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << i << " to " << inputSymbols[j] << " -> ";
    //         cin >> mat[i][j];
    //     }
    // }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i==1)
            {
                if(inputSymbols[j]>='a' && inputSymbols[j]<='z')
                {
                    mat[i][j]=2;
                }
                else
                {
                    mat[i][j]=3;
                }
            }
            else if(i==2)
            {
                if((inputSymbols[j]>='a' && inputSymbols[j]<='z') || (inputSymbols[j]>='0' && inputSymbols[j]<='9'))
                {
                    mat[i][j]=2;
                }
                else
                {
                    mat[i][j]=3;
                }
            }
            else
            mat[i][j]=3;
            cout << i << " to " << inputSymbols[j] << " -> " << mat[i][j] << endl;
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
        if (currentstate == acceptingstates)
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