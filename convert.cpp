#include <iostream>
#include <string>
#include <tuple>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

/******* TOKEN *******/
/*!!!!!!!
 * Used for parsing given expression
 * Each token can either be an operator token or alphabet token
 * Alphabet Tokens are single input alphabets (present in expression)
 * Operator Tokens have an operator with their list of operand tokens
 */
struct Token {
	char tok; 
	vector<Token> tokens;
};

Token parsed;

int check_char(char c) {
	return c >= 'a' && c <= 'z';
}

string convert_to_postfix(string regex) {

	int len = regex.length();
	string postfix(len, '\0');

	int index = -1;
	int i = 0;
	
	while(i < len) {
		
		if(check_char(regex[i])) {
			
			if(index == -1)
				postfix[++index] = regex[i];

			else if(postfix[index] == '*' || check_char(postfix[index])) 
			{
				// Add concatenation
				postfix[++index] = regex[i];
				postfix[++index] = '.';
			}
			
			i++;
		}
		
		else if(regex[i] == '(') {
// 			convert_to_postfix
		}
		else if(regex[i] == '*')
		
		
// 		switch(regex[i]) {
// 			case '+':
// 				if(regex[i + 1] == '(') {
// 					
// 				}
// 			case '*':
// 				postfix[index++] = '*';
// 				break;
// 			case '(':
// 			default:
// 		}
	}
}


Token parsing(string& regex, int i) {

	// for (int i = 0; i < regex.length; ++i)
	// {
 	switch(regex[i]) {

		case '+': 
			break;

		case '*':
			break;

		case '(':
			break;

		default:
			Token token;
			token->tok = '.';
			token->tokens.push_back(regex[i]);
			token->tokens.push_back(parsing(regex, i + 1));
	}		
	// }



	// for (int i = 0; i < regex.length(); ++i) {

	// 	switch()
 // 		case '+': 
	// 		/* Pop the last token */
	// 		token.tok = '+';
	// 		token.push_back(this->tok);
	// 		this->tok = '+';
	// 		token.push_back(parsing(regex, i+1));
	// 		parsed_expression.pop_back();
	// 		parsed_expression.push_back(token);
	// 		parsed_expression.push_back()
	// 		break;

	// 	case '*':
	// 		break;

	// 	case '(':
	// 		break;

	// 	default:
	// 		/* Input Symbols */
	// 		current_token.tok = regex[i];
	// 		if(!current_token.tokens.empty())				
	// }

}

int n, k, a;
vector<tuple<int, char, int>> transitions;

void 
parse(int initial_state, string regex, int final_state) 
{
	int len = regex.length();
	
	if(len == 0) return;
	
	if(len == 1) {
		transitions.push_back(
			make_tuple(initial_state, regex[0], final_state)
		);
		return;
	}
	
	if(regex[0] == '(') {
		
		int n1 = ++n;
		transitions.push_back(
			make_tuple(initial_state, 'E', n1)
		);
		
		int n2 = ++n;
		transitions.push_back(
			make_tuple(n2, 'E', final_state)
		);
		
		int index = regex.find(")");
		parse(n1, regex.substr(1, index - 1), n2);
		
	}
	
	if(regex[1] == '+') {
		transitions.push_back(
			make_tuple(initial_state, regex[0], final_state)
		);
		parse(initial_state, regex.substr(2), final_state);
		return;
	}
	
	if(regex[1] == '*') {
		int mid = ++n;
		transitions.push_back(
			make_tuple(initial_state, 'E', mid)
		);
		transitions.push_back(
			make_tuple(mid, 'E', final_state)
		);
		
		
		parse(initial_state, regex.substr(2), final_state);
		return;
	}
	for(int i = 0; i < len; i++) {
	
		switch(regex[i]) {
			
			case '+':
				/* Pop the last token */
				token.tok = '+';
				token.push_back(this->tok);
				this->tok = '+';
				token.push_back(parsing(regex, i+1));
				parsed_expression.pop_back();
				parsed_expression.push_back(token);
				parsed_expression.push_back()
				break;

			case '*':
				
				break;

			case '(':
				break;

			default:
				/* Input Symbols */
				current_token.tok = regex[i];
				if(!current_token.tokens.empty())				
		}
	}
}

void regex_to_NFA() {
	
	string regex;
	getline(cin, regex); /* read input regex expression */
  
	parse(regex); // , '\0');
	
}

int main(int argc, char const *argv[])
{
	if(argc != 3) exit(1);
	
	// Open File descriptors for input and output file
	int fd1 = open(argv[1], O_RDONLY);
	int fd2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	
	dup2(fd1, 0);	close(fd1);
	dup2(fd2, 1);	close(fd2);
	
	regex_to_NFA();
	
	return 0;
}
