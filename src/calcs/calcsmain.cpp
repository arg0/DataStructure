#include <string>
#include <iostream>
#include <stack>
#include <set>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

bool is_operator(char ch)
{
    set<char> operator_set;
    operator_set.insert('+');
    operator_set.insert('-');
    operator_set.insert('*');
    operator_set.insert('/');
    operator_set.insert('%');
    operator_set.insert('^');
    return operator_set.find(ch) != operator_set.end();
}

int compare_priority(char a, char b)
{
    map<char,int> operator_priority;
    operator_priority.insert(make_pair('+',1));
    operator_priority.insert(make_pair('-',1));
    operator_priority.insert(make_pair('*',2));
    operator_priority.insert(make_pair('/',2));
    operator_priority.insert(make_pair('%',2));
    operator_priority.insert(make_pair('^',3));

    return operator_priority[a]-operator_priority[b];
}

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
            result.insert(j,")");
        }
    }
    return result;
}


string preprocess(string infix)
{
    return one_operator(check_string(omit_spaces(infix)));
}


queue<string> infix_to_post(string infix) {
    queue<string> postfix;
    stack<char> operator_stack;

    set<char> valid_operand_set;
    for(int i=0; i<=9; i++) {
        valid_operand_set.insert(i+'0');
    }
    valid_operand_set.insert('.');
    valid_operand_set.insert('e');
    valid_operand_set.insert('E');

    for(int i=0; i<infix.size(); i++) {
        cout<<endl;
        char ch = infix[i];
        cout<<"No:"<<"  "<<i<<"  char:  "<<ch<<endl;
        if(infix[i]=='(') {
            operator_stack.push(infix[i]);
        } else if(infix[i]==')') {
            while(!operator_stack.empty() && operator_stack.top()!='(') {
                postfix.push(string(1, operator_stack.top()));
                operator_stack.pop();
            }
            operator_stack.pop();
        } else if(is_operator(infix[i]) == true) {
            if(operator_stack.empty()) {
                operator_stack.push(infix[i]);
                continue;
            }

            char top_stack = operator_stack.top();
            while(compare_priority(infix[i], top_stack)<=0) {
                if(compare_priority(infix[i], top_stack)==0 && infix[i]=='^') {   //因为'^'的结合性从右向左，所以单独处理
                    break;
                }
                postfix.push(string(1, top_stack));
                operator_stack.pop();
                if(!operator_stack.empty()) {
                    top_stack = operator_stack.top();
                } else {
                    break;
                }

            }
            operator_stack.push(infix[i]);
        } else {
            string current_operator;
            int j=i;
            while(valid_operand_set.find(infix[j]) != valid_operand_set.end()) {
                current_operator += infix[j];
                ++j;
            }
            postfix.push(current_operator);
            i=j-1;
        }

        cout<<"top_stack: "<<(operator_stack.empty() ?' ': operator_stack.top())<<endl;
        queue<string> temp_queue = postfix;
        cout<<"posfix: ";
        while(temp_queue.size()>0) {
            cout<<temp_queue.front()<<"  ";
            temp_queue.front();
            temp_queue.pop();
        }
        cout<<endl;

    }
    while(!operator_stack.empty()) {
        postfix.push(string(1, operator_stack.top()));
        operator_stack.pop();
    }

    return postfix;
}

double calculate_two(double a, double b,string operand)
{
    double result;
    if(operand == "+")
    {
        result = a+b;
    }
    else if(operand == "-")
    {
        result = a-b;
    }
    else if(operand == "*")
    {
        result = a*b;
    }
    else if(operand == "/")
    {
        if(b==0)
        {
            cout<<"Divid by 0"<<endl;
            exit(-1);
        }
        result = a/b;
    }
    else if(operand == "%")
    {
        result = (static_cast<int>(a) % static_cast<int>(b));
    }
    else if(operand == "^")
    {
        result = pow(a,b);
    }
    return result;
}

double calculate_post(queue<string>& post)
{
    stack<double> result_stack;
    while(!post.empty()) {
        string temp = post.front();
        post.pop();
        if(is_operator(temp[0])) {
            if(result_stack.size()<2) {
                cout<<"Expression Error!"<<endl;
                exit(-1);
            }
            double operand2 = result_stack.top();
            result_stack.pop();
            double operand1 = result_stack.top();
            result_stack.pop();

            double m = calculate_two(operand1, operand2, temp);
            result_stack.push(m);
        } else {
            double temp_operand = atof(temp.c_str());
            result_stack.push(temp_operand);
        }
    }
    return result_stack.top();
}


int main(int argc, char *argv)
{
    string infix;
    cout<<"Input"<<endl;
    getline(cin,infix);
    cout<<endl<<"The Expression:"<<infix<<endl;

    bool vaild=is_bracket_vaild(infix);
    if(vaild){
        cout<<endl<<"Bracket Right."<<endl<<endl;
    }else{
        return 0;
    }

    string result_infix = preprocess(result_infix);
    cout<<"After preprocess:"<<result_infix<<endl;

    queue<string> result_post=infix_to_post(result_infix);
    queue<string> temp=result_post;
    cout<<"posfix:";
    while(!temp.empty()) {
        cout<<temp.front()<<"  ";
        temp.pop();
    }
    cout<<endl;
    double result = calculate_post(result_post);
    cout<<endl<<"Result: "<<result<<endl;
    return 0;
}

