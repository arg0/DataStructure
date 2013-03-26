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
    for(int i = 0 ;i < result.size() ; i++ )
    {
        char temp = result[i];
        if ( temp != '+' && temp != '-' )
        {
            continue;
        }
        if ( i == 0 )
        {
            result.insert(i,1,0+'0');
        }
        else if ( i-1>0 &&!isdigit(result[i-1]) && result[i-1]!=')' )
        {
            result.insert(i,"(0");
            int j=i+3;
            int bracket_count=0;
            for(;j<result.size();j++)
            {
                if(isdigit(result[j])||result[j]=='.')
                {
                    continue;
                }
                else if(result[j]=='(')
                {

                    bracket_count++;
                }
                else if(result[j]==')')
                {
                    if((--bracket_count) == 0)
                    {
                        break;
                    }
                }
                else if(bracket_count==0)
                {
                    break;
                }
            }
            i = j;
            result.insert(j,')');

        }
    }
    return result;
}


string preprocess(string infix)
{
    return one_operator(check_string(omit_spaces(infix)));
}

int main()
{
    return 0;
}
