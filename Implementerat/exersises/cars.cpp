
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;



class state
{
public:

	vector<int> fills;
	int carn;

	state( int ffiles, int flength ){
		fills = vector<int>(ffiles,flength);
		carn = 0;
	}
	state( vector<int>fills, int carn): fills(fills), carn(carn) {}
	~state(){
		//delete fills;
	}

	state copy() const{

		vector<int> newfills( fills.begin(), fills.end() );
		return state( newfills, carn );
	}

	bool operator==( const state other ) const{
		return carn == other.carn && fills == other.fills;
	}

	vector<state> nextStates( int carl ){

		vector<state> states;
		int nextn = carn+1;

		// cout << " ns " << carl << " "; 
		for (int i = 0; i < fills.size(); ++i)
		{
			// cout << fills[i] << " ";
			if ( fills[i]>=carl )
			{
				state news = copy();

				news.fills[i] = fills[i]-carl-1;
				news.carn = nextn;
				sort(news.fills.begin(),news.fills.end());

				states.push_back(news);
			}
		}
		// cout << endl;

		return states;

	}

};

namespace std {
template <>
struct hash<state>
{
    size_t operator()(const state& k) const
    {
      using std::size_t;
      using std::hash;

      	size_t x = 0;

      	x ^= hash<int>()(k.carn);
      	for (int i = 0; i < k.fills.size(); ++i)
      	{
      		x ^= hash<int>()(k.fills[i]<<(2*i+1));
      	}

      	return x;
    }
};
}


unordered_map<state,int> memo;
vector<int> cars;


int solveFrom( state s ){

	// cout << s.carn << endl;
	// for (int i = 0; i < s.fills.size(); ++i)
	// {
		// cout << s.fills[i] << " ";
	// }
	// cout << memo.count(s) << endl;

	if ( memo.count(s)==1 )
	{
		return memo.at(s);
	}

	vector<state> nexts = s.nextStates( cars[s.carn] );
	// cout << nexts.size() << " nexts" << endl;

	if ( nexts.size()==0 )
	{
		memo[s] = s.carn;
		return s.carn;
	}

	int best = s.carn;
	int next;

	for (int i = 0; i < nexts.size(); ++i)
	{
		next = solveFrom( nexts[i] );
		if (next>best)
		{
			best = next;
		}
	}

	memo[s] = best;
	return best;

}

int solve( int ncars, int flength, int ffiles ){

	state startstate = state(ffiles,flength);
	return solveFrom( startstate );

}

int main(int argc, char const *argv[])
{
	
	// #bilar <= 200, L <=50, 1<=|bil|<=10
	int ncars;
	int flength;
	int ffiles = 4;
	int car;

	cin >> ncars;
	cin >> flength;


	for (int i = 0; i < ncars; ++i)
	{
		cin >> car;
		cars.insert(cars.end(),car);
	}

	cout << solve( ncars, flength, ffiles ) << endl;

	return 0;
}

