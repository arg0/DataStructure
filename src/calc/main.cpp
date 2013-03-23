#include <string>
#include <iostream>
#include <stack>

using namespace std;

bool is_bracket_vaild(string infix)
{
    stack<char> bracket;
    for(int i=0;i<infix.size();i++)
    {
        if(infix[i]=='(')
        {
            bracket.push(infix[i]);
        }
        else if(infix[i]==')')
        {
            if(bracket.empty())
            {
                cout<<"Bracket Error !"<<endl;
                return false;
            }
            bracket.pop();
        }
    }
    if(!bracket.empty())
    {
        cout<<"Bracket Error !"<<endl;
        return false;
    }
}


int main()
{
    return 0;
}
