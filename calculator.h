#pragma once
#include <string>
#include <vector>
#include <stack>
using namespace std;

bool isOperand(char c) {
	auto n = static_cast<int>(c);
	if( (n >= 48 && n <= 57) || c == '.')
		return true;
	else return false;
}

bool isOperator(char c) 
{
	switch (c) 
	{
		case '+': return true;
		case '-': return true;
		case '*': return true;
		case '/': return true;
		case '(': return true;
		case ')': return true;
		case '^': return true;

		default: return false;
	}
}

int priority(char op) 
{
	switch (op) 
	{
		case '+': return 1;
		case '-': return 1;
		case '*': return 2;
		case '/': return 2;
		case '^': return 3;

		default: return 0;
	}
}

bool precedence(char a, char b)
{
	if (priority(a) >= priority(b)) return true;
	else return false;
}

std::string pop(string s)
{
	return s.substr(0, s.size() - 1);
}

std::vector<std::string> infix_postfix(const std::string& infix)
{
	std::vector<std::string> postfix;
	std::string operand;
	std::string stack;

	for (int i = 0; i < infix.length(); ++i) {
		//if operand
		if (isOperand(infix[i])) {
			operand.push_back(infix[i]);
		}
		//if operator
		else if (isOperator(infix[i])) {

			if (!operand.empty()) {
				postfix.push_back(operand);
				operand.clear();
			}

			//if stack is empty
			if (stack.empty()) {
				stack.push_back(infix[i]);
			}

			//if stack not empty
			else if (!stack.empty()) {

				//if (
				if (infix[i] == '(') {
					stack.push_back(infix[i]);
				}

				//if ) is encountered pop till ( to postfix
				else if (infix[i] == ')') {

					while (*(stack.end() - 1) != '(') {
						std::string c; c.push_back(*(stack.end() - 1));
						postfix.push_back(c);
						stack = pop(stack);
					}
					stack = pop(stack);
				}

				else {
					//pop until tos has lesser precedence or tos is null.
					while (!stack.empty() && precedence(*(stack.end() - 1), infix[i])) {
						std::string c; c.push_back(*(stack.end() - 1));
						postfix.push_back(c);
						stack = pop(stack);
					}

					if (!stack.empty() && !(precedence(*(stack.end() - 1), infix[i])))
						stack.push_back(infix[i]);
					else if(stack.empty())
						stack.push_back(infix[i]);
				}
			}
		}
	}

	if (!operand.empty()) {
		postfix.push_back(operand);
		operand.clear();
	}

	while (!stack.empty()) {
		auto tos = stack.end() - 1;
		std::string c; c.push_back(*tos);
		postfix.push_back(c);
		stack = pop(stack);
	}
	return postfix;
}

float calculate(const std::vector<std::string>& postfix)
{
	float result(0.0);
	std::stack<float> st;
	for (auto& i : postfix) {
		if (i.length() == 1 && isOperator(i[0]) && st.size() >= 2) {
			float x = st.top(); st.pop();
			float y = st.top(); st.pop();
			switch (i[0]) {
				case '+': st.push(y + x); break;
				case '-': st.push(y - x); break;
				case '*': st.push(y * x); break;
				case '/': st.push(y / x); break;
				default : st.push(0); break;
			}
		}
		else {
			st.push(std::stof(i));
		}
	}
	if (!st.empty()) result = st.top();
	return result;
}
