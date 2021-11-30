#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Token {
	char tok;							// Input Symbol/Operator
	vector<Token> tokens; // Operands (For operator)
};

Token next_token(string regex, int i) {
	
	Token next; int index;
		
	switch(regex[i]) {
		
		case '(':
			index = regex.find(')', i);
			next = next_token(regex.substr(i + 1, index - i - 1), 0);
			i = index++;
			break;
		
		case '+':
			next.tok = '+';
			next.tokens.push_back(parsed_expression.tokens.back());
			parsed_expression.tokens.pop();
		
		case '*':
		
		default : 
			next.symbol = regex[i];
		
	}
	
}


Token parse(string regex) {
	
	int i = 0, len = regex.length();
	
	Token parsed_expression;
	
	while(i < len) {
		
		Token next; int index;
		
		switch(regex[i]) {
			
			case '(':
				index = regex.find(')', i);
				next = parse(regex.substr(i + 1, index - i - 1));
				i = index++;
				break;
			
			case '+':
				next.tok = '+';
				next.tokens.push_back(parsed_expression.tokens.back());
				parsed_expression.tokens.pop();
			
			case '*':
			
			default : 
				next.symbol = regex[i];
			
		}
		
		parsed_expression.push_back(next);
	}
	
}


struct Node {
	char operator;
	Node* left;
	Node* right;
};


int check_operator_bracket(char c) {
	return c == '+' || c == '(' || c == '*' || c == ')';
}

int is_symbol() {
	if(parsed_expression.empty())
		return -1;
	
	char c = parsed_expression.back().tok;
	return c >= 'a' && c <= 'z';
}

void convert(string regex) {
	
	int i = 0, len = regex.length();
	
	
	while(i < len) {
	
		Token match_bracket;
		
		int k = is_symbol();
		
		switch(regex[i]) {
			
			case '+':
				
				
			case '(':
				
				
			case ')':
				
			case '*':
				
			default :
				int index = i;
				while(!check_operator_bracket(regex[++index]));
				
				if(index == i + 1) // No concatenation required
				{
					Token next;
					next.tok = regex[i];
					parsed_expression.push_back(next);
					i++;
				}	
					
				else {
					
				}
		}
	}
}


