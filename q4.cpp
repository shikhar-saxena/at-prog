#include <iostream>
#include <string>
#include <stack>
#include <tuple>
#include <utility>
#include <vector>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int operator_precedence(char c) {

	if(c == '*')
		return 3;
	else if (c == '.') // Explicit Symbol used for concatenation
		return 2;
	else if(c == '+')
		return 1;
	else return 0;
}

// checks if given character is a symbol
int check_char(char c) {
	return c >= 'a' && c <= 'z';
}

string insert_concat_symbol(string regex) {
	
	string new_regex;

	for(int i = 0; i < regex.length() - 1; i++) {

		new_regex += regex[i];

		int j = i + 1;

		int flag1 = check_char(regex[i]);
		int flag2 = check_char(regex[j]);

		if(flag1 && flag2)
			new_regex += '.';

		if((flag1 && regex[j] == '(') || ( regex[i] == ')' && flag2) || ( regex[i] == ')' && regex[j] == '('))
			new_regex += '.';

		if(regex[i] == '*' && (flag2 || regex[j] == '(') )
			new_regex += '.';
	}

	// append last character
	new_regex += regex[regex.length() - 1];
	return new_regex;
}

// convert the regex (with concat symbol) to postfix string 
string convert_to_postfix(string regex) {

	string postfix = "";

	stack<char> stk;

	for (int i = 0; i < regex.length(); ++i)
	{
		char c = regex[i];

		switch(c) {

			case '(':
				stk.push('(');
				break;

			case ')':
				while(stk.top() != '(') {
					postfix += stk.top(); 
					stk.pop();
				}
				stk.pop(); // Pop the final '('
				break;

			default:

				if(check_char(c)) {
					postfix += c;
					break;
				}

				// c is an operator
				
				// if operators on stack have greater or equal precedence then include them in postfix
				while(!stk.empty() && operator_precedence(stk.top()) >= operator_precedence(c)) {
					postfix += stk.top();
					stk.pop();
				}

				stk.push(c);
		}
	}

	while(!stk.empty()) {
		postfix += stk.top();
		stk.pop();
	}

	return postfix;
}

/********** Function not done ********/
// Creates and displays the nfa
// We create an nfa with only one accept state
// void nfa(string postfix) {

// 	int n;//, a;

// 	// n = 2; // Start with start state (0) and one accept state (1)
// 	// a = 1; // Number of accept states

// 	stack<pair<int, int>> states; // Stack of pairs to store start and end state (for transitions)

// 	vector<string> transitions; // To store transitions

// 	for(int i = 0; i < postfix.length(); i++) {

// 		char c = postfix[i];

// 		// int initial, final;

// 		// Get the initial and final states
// 		// if(states.empty()) 
// 		// {
// 		// 	initial = 0;
// 		// 	final	= 1;	
// 		// }
// 		// else {
// 		// 	tie(initial, final) = states.top();
// 		// }

// 		if(check_char(c)) {

// 			// Add new state 
// 			n++;
// 			// transitions.push_back("" + initial + c + n);
// 			// states.push({n, final});
// 			continue;
// 		}

// 		// c is an operator
// 		switch(c) {
// 			if()
// 		}
// 	}

// }

void regex_to_NFA() {
	
	string regex;
	getline(cin, regex); /* read input regex expression */

	string new_regex = insert_concat_symbol(regex); 
	string postfix = convert_to_postfix(new_regex);

	cout << "Regex (after adding concat symbol): " << new_regex << endl;
	cout << "Postfix expression for the regex  : " << postfix << endl;

	// nfa(postfix);
}

int main(int argc, char const *argv[])
{
	if(argc != 3) {
		cerr << "usage: ./a.out <input_file> <output_file>\n";
		exit(1);
	}
	
	// Open File descriptors for input and output file
	int fd1 = open(argv[1], O_RDONLY);
	
	if(fd1 < 0) {
		perror(argv[1]);
		exit(1);
	}

	int fd2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	
	if(fd2 < 0) {
		perror(argv[2]);
		exit(1);
	}

	// Redirect input and output to respective files
	dup2(fd1, 0);	close(fd1);
	dup2(fd2, 1);	close(fd2);
	
	regex_to_NFA();
	
	return 0;
}
