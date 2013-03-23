/**
 * ��׺���ʽ-->��׺���ʽ-->���ʽ��ֵ
 *
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <cctype>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
using namespace std;

/**
 * �ж��Ƿ�Ϊ������
 * ������
 *      ch : ���жϵ��ַ�
 * ����ֵ��
 *      �ǲ�����������true�����򷵻�false��
 */
bool is_operator(char ch) {
    set<char> operator_set;
    operator_set.insert('+');
    operator_set.insert('-');
    operator_set.insert('*');
    operator_set.insert('/');
    operator_set.insert('%');
    operator_set.insert('^');
    return operator_set.find(ch) != operator_set.end();
}
/**
 * �Ƚ����������������ȼ�
 */
int compare_priority(char a, char b) {
    map<char, int> operator_priority;
    operator_priority.insert(make_pair('+', 1));
    operator_priority.insert(make_pair('-', 1));
    operator_priority.insert(make_pair('*', 2));
    operator_priority.insert(make_pair('/', 2));
    operator_priority.insert(make_pair('%', 2));
    operator_priority.insert(make_pair('^', 3));

    return operator_priority[a]-operator_priority[b];
}
/**
 * �ж��Ƿ��в�ƥ�������
 */
bool is_bracket_valid(string infix) {
    stack<char> bracket;
    for(int i=0; i<infix.size(); i++) {
        if(infix[i]=='(') {
            bracket.push(infix[i]);
        } else if(infix[i]==')') {
            if(bracket.empty()) {
                cout<<"��������û��ƥ��"<<endl;
                return false;
            }
            bracket.pop();
        }
    }
    if(!bracket.empty()) {
        cout<<"��������û��ƥ��"<<endl;
        return false;
    }
    return true;
}
/**
 * Ԥ����
 * ������
 *      infix��Ԥ����ǰ��������ʽ
 * ����ֵ��
 *      ������������ʽ
 * ���裺
 *      1. ȥ���ո�
 *      2. �ж��Ƿ��в��ܴ�����ַ�
 *      3. ����һԪ������ '+'��'-'
 */
string preprocess(const string infix) {
    string result = infix;
    //ȥ���ո�
    size_t index;
    while((index = result.find(string(" "))) != string::npos) {
        result.erase(index, 1);
    }
    cout<<"ȥ���ո��  "<<result<<""<<endl;

    //��ʼ���ܹ�������ַ�����
    set<char> valid_char_set;//�ܹ�������ַ�
    for(int i=0; i<=9; i++) {
        valid_char_set.insert(i+'0');
    }
    valid_char_set.insert('+');
    valid_char_set.insert('-');
    valid_char_set.insert('*');
    valid_char_set.insert('/');
    valid_char_set.insert('%');
    valid_char_set.insert('^');
    valid_char_set.insert('(');
    valid_char_set.insert(')');
    valid_char_set.insert('e');//'e'��'E'Ϊ��ѧ������
    valid_char_set.insert('E');
    valid_char_set.insert('.');//С����

    for(int i=0; i<result.size(); i++) {
        //����ַ�����valid_char_set��˵���в��ܴ�����ַ�����������
        if(valid_char_set.find(result[i]) == valid_char_set.end()) {
            cout<<"��׺���ʽ���зǷ��ַ�: "<<result[i]<<"  "<<i<<endl;
            exit(-1);
        }
    }

    //����һԪ������
    for(int i=0; i<result.size(); i++) {
        char temp = result[i];
        if(temp != '+' && temp != '-') {
            continue;
        }
//        cout<<i<<"   "<<result<<"   "<<result[i]<<endl;
        if(i==0) { //���ʽ��ʼλ�õ� '-'
            result.insert(i, 1, 0+'0');
        } else if(i-1>=0 && !isdigit(result[i-1]) && result[i-1]!=')') { //һԪ+-���������������ź���
            result.insert(i, "(0");
            int j = i+3;
            int bracket_count=0;//��������ţ�Ӧ��������
            for(; j<result.size(); j++) {
                if(isdigit(result[j]) || result[j]=='.') {
                    continue;
                } else if(result[j]=='(') {
                    ++bracket_count;
                } else if(result[j]==')') {
//                    --left_bracket_count;
                    if((--bracket_count) == 0) {
                        break;
                    }
                } else if(bracket_count==0) {
                    break;
                }
            }
            i = j;
            result.insert(j, ")");
        }
    }
    return result;
}
/**
 * ��׺���ʽ-->��׺���ʽ
 */
queue<string> infix_to_post(string infix) {
    queue<string> postfix;//��׺���ʽ����
    stack<char> operator_stack;//ת�������У������洢��������ջ

    set<char> valid_operand_set;//������ �е��ַ�
    for(int i=0; i<=9; i++) {
        valid_operand_set.insert(i+'0');
    }
    valid_operand_set.insert('.');
    valid_operand_set.insert('e');
    valid_operand_set.insert('E');

    for(int i=0; i<infix.size(); i++) {
        cout<<endl;
        char ch = infix[i];
        cout<<"��ţ�"<<"  "<<i<<"  �ַ���  "<<ch<<endl;
        if(infix[i]=='(') {//������
            operator_stack.push(infix[i]);
        } else if(infix[i]==')') {//������
            while(!operator_stack.empty() && operator_stack.top()!='(') {
                postfix.push(string(1, operator_stack.top()));
                operator_stack.pop();
            }
            operator_stack.pop();//��"("��ջ
        } else if(is_operator(infix[i]) == true) { //�ǲ������������� �������ţ�
            if(operator_stack.empty()) { //������ջΪ��
                operator_stack.push(infix[i]);
                continue;
            }

            //������ջ�ǿ�
            char top_stack = operator_stack.top();
            //��ջ�С��ϸߺ���ȡ����ȼ��Ĳ������ŵ� ��׺���ʽ�С�
            //��ֹ����Ϊ����ǰ������>ջ�����������ȼ��������ȼ���ȡ���ջ���������Ľ�����ǡ��������󡱡�
            while(compare_priority(infix[i], top_stack)<=0) {
                //���ȼ���ȣ���ջ�������������Ϊ��������������ָ'^'
                if(compare_priority(infix[i], top_stack)==0 && infix[i]=='^') {   //��Ϊ'^'�Ľ���Դ����������Ե�������
                    break;
                }
                //��ǰ������<=ջ�����������ȼ�����ǰ�����������Ϊ������
                postfix.push(string(1, top_stack));
                operator_stack.pop();
                if(!operator_stack.empty()) {
                    top_stack = operator_stack.top();
                } else {
                    break;
                }

            }
            //����ǰ��������ջ
            operator_stack.push(infix[i]);
        } else {//������
            string current_operator;
            int j=i;
            while(valid_operand_set.find(infix[j]) != valid_operand_set.end()) {
                current_operator += infix[j];
                ++j;
            }
            postfix.push(current_operator);
            i=j-1;//��Ϊforѭ����ÿ�ζ���ִ��i++
        }

        //��ӡ�������
        cout<<"��ǰջ���� "<<(operator_stack.empty() ?' ': operator_stack.top())<<endl;
        queue<string> temp_queue = postfix;
        cout<<"��ǰ��׺���ʽ�� ";
        while(temp_queue.size()>0) {
            cout<<temp_queue.front()<<"  ";
            temp_queue.front();
            temp_queue.pop();
        }
        cout<<endl;

    }
    //���ջ������ȫ��ȡ����
    while(!operator_stack.empty()) {
        postfix.push(string(1, operator_stack.top()));
        operator_stack.pop();
    }

    return postfix;
}
/**
 * ��������������
 */
double calculate_two(double a, double b, string operand) {
    double result;
    if(operand == "+") {
        result = a+b;
    } else if(operand == "-") {
        result = a-b;
    } else if(operand == "*") {
        result = a*b;
    } else if(operand == "/") {
        if(b==0) {
            cout<<"��������Ϊ0"<<endl;
            exit(-1);
        }
        result = a/b;
    } else if(operand == "%") {
        result = (static_cast<int>(a)) % (static_cast<int>(b));
    } else if(operand == "^") {
        result = pow(a, b);
    }
    return result;
}
//�Ժ�׺���ʽ�����м���
double calculate_post(queue<string>& post) {
    stack<double> result_stack;
    while(!post.empty()) {
        string temp = post.front();
        post.pop();
        if(is_operator(temp[0])) { //�ǲ�����
            if(result_stack.size()<2) {
                cout<<"���ʽ����"<<endl;
                exit(-1);
            }
            //��ջ��ȡ������Ԫ�أ����㲢�����ѹ��ջ��
            double operand2 = result_stack.top();
            result_stack.pop();
            double operand1 = result_stack.top();
            result_stack.pop();

            double m = calculate_two(operand1, operand2, temp);
            result_stack.push(m);
        } else { //������
            double temp_operand = atof(temp.c_str());
            result_stack.push(temp_operand);
        }
    }
    return result_stack.top();
}

int main(int argc, char **argv) {
    string infix;
//    infix = "10e2+3*4-5%2-2^-(4/2)+.2 + 2^1^3";//���Ϊ��1012.95
    cout<<"��������׺���ʽ�� "<<endl;
    getline(cin, infix);
    cout<<endl<<"ԭʼǰ׺���ʽ�� "<<infix<<endl;

    //1. ��������Ƿ�ƥ��
    bool valid = is_bracket_valid(infix);
    if(valid){
        cout<<endl<<"����ƥ��"<<endl<<endl;
    }else{
        return 0;
    }

    //2.Ԥ������׺���ʽ
    string result_infix = preprocess(infix);
    cout<<"Ԥ�����Ժ�"<<result_infix<<endl;

    //3. ��׺ ת ��׺
    queue<string> result_post = infix_to_post(result_infix);
    //��ӡ��׺���ʽ
    queue<string> temp = result_post;
    cout<<"��׺���ʽ�� ";
    while(!temp.empty()) {
        cout<<temp.front()<<"  ";
        temp.pop();
    }
    cout<<endl;

    //4. ������
    double result = calculate_post(result_post);
    cout<<endl<<"�������� "<<result<<endl;

    return 0;
}
