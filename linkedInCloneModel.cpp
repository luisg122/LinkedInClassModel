#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>

using namespace std;

class UserProfile{
	private:
		int userProfileId      = 0;
		string profileName 	   = "";
		string profileImageUrl = "";
		string profileLocation = "";		
		vector<UserProfile> connections;
		
		// method for finding the degrees of separation between two users, will use DFS for searching 
		bool dfs(unordered_set<int> &visited, UserProfile &user, int targetUserId, int degrees, int &degreesOfSeparation);
	
	public:
		// increments for every instantiated object
		static int userId;	
		
		// constructor
		UserProfile(string profileName, string profileImageUrl, string profileLocation);
		
		
		// getters and setters
		void setProfileName(string profileName);
		string getProfileName();
			
		void setImageUrl(string profileImageUrl);
		string getImageUrl();
			
		void setLocation(string setProfileLocation);
		string getLocation();
		
		// user id info		
		int getUserProfileId();		
		
		// methods for establishing connections, displaying connections and finding degrees of separation
		void addConnection(UserProfile &user);
		int  getDegreesOfSeparation(UserProfile &user);
		vector<UserProfile> getAllConnections();						
};

UserProfile::UserProfile(string profileName, string profileImageUrl, string profileLocation){
	this->userProfileId   = userId++;
	this->profileName     = profileName;
	this->profileImageUrl = profileImageUrl;
	this->profileLocation = profileLocation;
}


void UserProfile::setImageUrl(string profileName){
	this->profileName = profileName;
}

string UserProfile::getImageUrl(){
	return profileImageUrl;
}

void UserProfile::setProfileName(string profileName){
	this->profileName = profileName;
}

string UserProfile::getProfileName(){
	return profileName;
}

void UserProfile::setLocation(string profileLocation){
	this->profileLocation = profileLocation;
}

string UserProfile::getLocation(){
	return profileLocation;
}

int UserProfile::getUserProfileId(){
	return userProfileId;
}

// methods for establishing connections, displaying connections and finding degrees of separation
void UserProfile::addConnection(UserProfile &user){
	// bi-directiontional connections
	this->connections.push_back(user);
	user.connections.push_back(*this);
} 

vector<UserProfile> UserProfile::getAllConnections(){
	return connections;
}

bool UserProfile::dfs(unordered_set<int> &visited, UserProfile &user, int targetUserId, int degrees, int &degreesOfSeparation){
	if(user.getUserProfileId() == targetUserId) {
		degreesOfSeparation = degrees;
		return true;
	}
	
	// we use the unordered set to avoid cycles and thus a stack overflow
	if(visited.find(user.getUserProfileId()) != visited.end()) return false;
	visited.insert(user.getUserProfileId());
	
	int val = 0;
	for(UserProfile &connection : user.getAllConnections())
		if(dfs(visited, connection, targetUserId, degrees + 1, degreesOfSeparation) == true) return true;
	
	return false;
}

int UserProfile::getDegreesOfSeparation(UserProfile &user){
	unordered_set<int> visited;
	
	int degreesOfSeparation = 0;
	return dfs(visited, *this, user.getUserProfileId(), 0, degreesOfSeparation) == true ? degreesOfSeparation : -1;
}

// initializing static data members outside of the class
int UserProfile::userId = 0;


int main(){
	
	UserProfile alex("Alex", "https://dummy.com/alex/pic.png", "New York");
	
	UserProfile jake("Jake", "https://dummy.com/jake/pic.png", "Texas");
	
	UserProfile sam("Sam", "https://dummy.com/sam/pic.png", "New Jersey");
	
	UserProfile dan("Dan", "https://dummy.com/dan/pic.png", "Washington");
	
	UserProfile dave("Dave", "https://dummy.com/dave/pic.png", "California");
	
	UserProfile jon("Jon", "https://dummy.com/jon/pic.png", "Florida");	
	
	
	alex.addConnection(jake);
	alex.addConnection(dan);
	alex.addConnection(jon);
	
	jake.addConnection(sam);
	jake.addConnection(dave);
	jake.addConnection(jon);
	
	cout << alex.getProfileName() << "'s Connections : " << endl;
	for(UserProfile &user : alex.getAllConnections()) cout << user.getProfileName() << endl;
	
	cout << endl << jake.getProfileName() << "'s Connections : " << endl;
	for(UserProfile &user : jake.getAllConnections()) cout << user.getProfileName() << endl;
	
	
	int degrees = alex.getDegreesOfSeparation(jake);
	cout << endl << "The degrees of separation between " << 
		alex.getProfileName() << " and " << jake.getProfileName() << " is: " << degrees << endl;
	
	
	return 0;
}
