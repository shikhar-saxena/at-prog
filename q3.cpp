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


void DFA::minimize() {

	/* note the unreachable states */
	/* Unreachable states are the states not reachable from initial state of the DFA */

	set<int> reachable_states = {0};
	set<int> states_to_explore = {0};

	do {
		
		set<int> temp; // Will save all the states reachable from states_to_explore

		for (int new_state : states_to_explore)
		{
			for(char c : sigma) 
				temp.insert(transitions.at({new_state, c}));
			
		}
		
		states_to_explore = {};

		for(int i : temp) {
			if(reachable_states.count(i) == 0) {
				states_to_explore.insert(i);
			}
		}
		

		for(int i : states_to_explore) 
			reachable_states.insert(i);

	} while(!states_to_explore.empty());

	set<int> not_reachable_states;

	for (int i = 0; i < n; ++i)
	{
		if(reachable_states.count(i) == 0)
			not_reachable_states.insert(i);
	}

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

	vector<set<int>> partitions; // Will store the sets containing non-distinguishable states

	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j++) {

			if(!marked.at({i, j})) {
				
				// state i is not-distinguishable from state j
				
				int found = 0;
				for(auto it = partitions.begin(); it != partitions.end(); it++) {
					if(it->find(i) != it->end()) {
						it->insert(j);
						found = 1;
						break;
					}

					if(it->find(j) != it->end()) {
						found = 1;
						it->insert(i);
						break; 
					}
				}

				if(!found) {
					partitions.push_back({i, j});
				}
			}
		}
	}

	/* The unique states will not be in partitions vector */
	
	// Now we set the partition number for each state (to construct the minimized DFA)

	int in_partition[n];

	// Init with -1
	for (int i = 0; i < n; ++i)
	{
		in_partition[i] = -1;
	}

	int no_of_partitions = partitions.size();

	int partition_index[no_of_partitions]; // Maintains partition number given to each partition in partitions

	// Init with -1
	for(int i = 0; i < no_of_partitions; i++) {
		partition_index[i] = -1;
	}

	int index = 0;

	for (int i = 0; i < n; ++i) 
	{

		if(not_reachable_states.count(i) > 0) continue; // Skip not reachable state

		int found = 0; // to check for unique states (not in partitions set)

		for(int j = 0; j < no_of_partitions; j++) {
			
			if(partitions.at(j).find(i) != partitions.at(j).end()) {

				if(partition_index[j] == -1)
					partition_index[j] = index++;

				in_partition[i] = partition_index[j];
				found = 1;
				break;
			}
		}

		if(!found) {
			in_partition[i] = index++;
		}
	}

	// Construct minimized DFA
	DFA min_dfa;
	min_dfa.n = index;
	min_dfa.k = index * sigma.size();

	for(int i: accept_states) {

		if(not_reachable_states.count(i) == 0)
			min_dfa.accept_states.insert(in_partition[i]);
	}

	min_dfa.a = min_dfa.accept_states.size();

	// Add transitions
	for(int i = 0; i < n; i++) {
		
		if(not_reachable_states.count(i) > 0) continue;

		for(auto j = sigma.begin(); j != sigma.end(); j++) {

			auto it = transitions.find({i, *j});

			min_dfa.transitions[{in_partition[i], *j}] = in_partition[it->second];
		}
	}	

	min_dfa.display();
}


int main(int argc, char const *argv[])
{
	DFA dfa;
	dfa.input();
	dfa.minimize(); // Minimizes and displays the minimized DFA

	return 0;
}