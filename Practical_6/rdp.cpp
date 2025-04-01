#include<bits/stdc++.h>
using namespace std;
bool S(string s);
bool L(string s);
bool Ldash(string s);
int k=0;
bool S(string s)
{
    if('('==s[k])
    {
        k++;
        if(L(s))
        {
            if(')'==s[k])
            {
                k++;
                return true;
            }
            else
            {
                k--;
                return false;        
            } 
       }
        else
        {
            k--;
            return false;
        }
    }
    if('a'==s[k])
    {
        k++;
        return true;
    }
    return false;
}

bool L(string s)
{
    if(S(s))
    {
        if(Ldash(s))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool Ldash(string s)
{
    if(','==s[k])
    {
        k++;
        if(S(s))
        {
            if(Ldash(s))
            return true;
            else
            return false;
        }
        else
        {
            k--;
            return false;
        }
    }
    return true;
}

void RDP(string s)
{
    bool flag=S(s) && (k==s.size());
    if(flag)
    cout<<"Valid String"<<endl;
    else
    cout<<"Invalid String"<<endl;
}

int main()
{
    string s;
    cout<<"Enter string : ";
    cin>>s;
    RDP(s);
}