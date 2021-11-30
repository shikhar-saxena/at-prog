#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
using namespace std;

class DFA {

public:
	int n, k, a;
	set<int> accept_states;
	set<char> sigma; 	/* For input symbols */
	map<pair<int, char>, int> transitions;

	void input();
	void display();
	void remove_node(int, int);
	void minimize();
};

void DFA::input() { 
	/* Take input in given format */
	cin >> n >> k >> a;

	for(int i = 0; i < a; i++) {
		int a_i;
		cin >> a_i;
		accept_states.insert(a_i);
	}

	for(int i = 0; i < k; i++) {
		
		int q_i, q_j;
		char symbol;
		cin >> q_i >> symbol >> q_j;

		sigma.insert(symbol);

		transitions[{q_i, symbol}] = q_j;
	}
}

void DFA::display() {

	printf("%d %d %d\n", n, k, a);

	for(auto it = accept_states.begin(); it != accept_states.end(); ++it)
		printf("%d ", *it);

	printf("\n");

	for(auto it : transitions)
		printf("%d %c %d\n", it.first.first, it.first.second, it.second);
}

/**
 * Removes node `removed` and shifts the remaining states
 * (Since nodes only from 0 to n - 1)
 * @param removed: the removed node-id  
 * @param i: node-id 
 */
void DFA::remove_node(int removed, int i) {

	if(i == removed) n--;

	auto it1 = accept_states.find(i);

	if(it1 != accept_states.end()) {
		
		accept_states.erase(it1);
		
		if(i == removed) 
			a--;

		else
			accept_states.insert(i - 1); 	
	}

	for(auto it = sigma.begin(); it != sigma.end(); it++) {

		auto it2 = transitions.find({i, *it});

		if(it2 != transitions.end()) {
			if(removed == i)
				k--;
			
			else
				transitions[{i - 1, *it}] = it2->second;
			
			transitions.erase(it2);
		}
	}

	for(auto it = transitions.begin(); it != transitions.end(); ) {

		int a = it->first.first;
		char c = it->first.second;

		if(it->second == i) {
			it = transitions.erase(it);
			
			if(removed == i) k--;
			else transitions[{a, c}] = i - 1;
		}

		else it++;
	}
}

void disp(map<pair<int, int>, int> marked) {
	
	for(auto it : marked)
		printf("(%d %d) %d\n", it.first.first, it.first.second, it.second);
  
  // std::cout << "\n";

}

void DFA::minimize() {

	/* remove the unreachable states */
	/* Unreachable states are the states not reachable from initial state of the DFA */

	// set<int> reachable_states = {0};
	// queue<int> to_explore;

	// to_explore.push(0);

	// do {

	// 	set<int> temp;

	// 	int state = to_explore.front();
	// 	to_explore.pop();

		

	// } while(!states.empty());

	/* Using Table filling method based on Myhill-Nerode Theorem */

	map<pair<int, int>, int> marked;

	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {

			bool flag_i = accept_states.find(i) != accept_states.end();
			bool flag_j = accept_states.find(j) != accept_states.end();

			if((flag_i && flag_j) || (!flag_i && !flag_j))
				marked[{i, j}] = 0;
			else
				marked[{i, j}] = 1;
		}
	}

	int change;

	do {

		change = 0;

		for(auto state_pair = marked.begin(); state_pair != marked.end(); state_pair++) {

			int i = state_pair->first.first;
			int j = state_pair->first.second;

			if(state_pair->second) continue;

			for(auto symbol = sigma.begin(); symbol != sigma.end(); symbol++) {

				int state_from_i = transitions.at({i, *symbol}); 
				int state_from_j = transitions.at({j, *symbol});

				if(state_from_i == state_from_j) continue;

				if(state_from_i > state_from_j) swap(state_from_i, state_from_j);

				if(marked.at({state_from_i, state_from_j})) {
					marked[{i, j}] = 1;
					change = 1;
					break;
				}
			}			
		}

	} while(change != 0);

	// vector<int> original_states;
	vector<int> new_states;

	for(int i = 0; i < n; i++) {
		// original_states.push_back(i);
		new_states.push_back(i);
	}

	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {

			if(!marked.at({i, j})) {
				// Puts minimum equivalent state in place of this state
				new_states.at(j) = min(i, new_states.at(j));
			}
		}
	}


}


int main(int argc, char const *argv[])
{
	DFA dfa;
	dfa.input();
	
	dfa.display();


	dfa.minimize();

	// dfa.display();
	// minimize(dfa);

	return 0;
}