#include<bits/stdc++.h>
using namespace std;

int prec(char c) {
    if(c == '^')
        return 3;
    else if(c == '/' || c=='*')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string infix_postfix(string s) {

    stack<char> st;
    string res;

    for(int i = 0; i < s.length(); i++) {

        if(isdigit(s[i])){
            res += '#';
            while(isdigit(s[i]) || s[i] == '.'){
                res +=s[i];
                i++;
            }
        }
        if(s[i]== '(')
            st.push('(');
        else if(s[i] == ')') {
            while(st.top() != '(')
            {
                res += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while(st.size() != 0 && prec(s[i]) <= prec(st.top())) {
                res += st.top();
                st.pop();
            }
            st.push(s[i]);
        }
    }
    while(st.size() != 0) {
        res += st.top();
        st.pop();
    }

    return res;
}

float evaluate_postfix(string expression)
{
    stack<float> temp;
    int expression_size = expression.size();
    string num = "";
    float temp_num = 0;


    for (int i = 0; i < expression_size; i++)
    {
        if(expression[i] == '#')
        {
            i++;
            int j = i;
            while(isdigit(expression[j]) || expression[j] == '.')
            {
                num += expression[j];
                j++;
            }
            i = j - 1;
            stringstream toInt(num);
            toInt >> temp_num;
            temp.push(temp_num);
            num = "";
        }
        else
        {
            float val1 = temp.top();
            temp.pop();
            float val2 = temp.top();
            temp.pop();
            switch (expression[i])
            {
                case '+': temp.push(val1 + val2); break;
                case '-': temp.push(val2 - val1); break;
                case '*': temp.push(val2 * val1); break; break;
                case '/': temp.push(val2 / val1); break;
            }
        }
    }
    return temp.top();
}
int main()
{
    string s;
    s = infix_postfix("(11.5+35)*(3+4)");
    cout<<evaluate_postfix(s);
}
