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

string omit_spaces(string infix)
{
    string result=infix;
    size_t index;
    while((index=result.find(string(" ")))!=string::npos)
    {
        result.erase(index,1);
    }
    return result;
}

string check_string(string infix)
{
    string result=infix;
    set<char> vaild_char_set;
    for(int i=0;i<9;i++)
    {
        vaild_char_set.insert('0'+i);
    }
    vaild_char_set.insert('+');
    vaild_char_set.insert('-');
    vaild_char_set.insert('*');
    vaild_char_set.insert('/');
    vaild_char_set.insert('%');
    vaild_char_set.insert('^');
    vaild_char_set.insert('(');
    vaild_char_set.insert(')');
    vaild_char_set.insert('e');
    vaild_char_set.insert('E');
    vaild_char_set.insert('.');
    for(int i=0;i<result.size();i++)
    {
        if(vaild_char_set.find(result[i])==vaild_char_set.end())
        {
            cout<<"Input Error !"<<result[i]<<" "<<endl;
            exit(-1);
        }
    }
    return result;
}

string one_operator(string infix)
{
    string result=infix;

}


string preprocess(string infix)
{

}

int main()
{
    return 0;
}
