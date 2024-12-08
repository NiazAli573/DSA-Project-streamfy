#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct UserProfile {
    string password;
    string email;
    string userID;
};

int main() {
    
    unordered_map<string, UserProfile> userDB;
    
    userDB["creator"] = {"Mehdi2001", "muhammad@gmail.com","Mehdi"};

    string viewerID = "user1";
    userDB[viewerID] = {"Data", "data@gmail.com","Yay_User"};
    
    cout << "Creator Email: " << userDB["creator"].userID << endl;
    
    cout << "Viewer Email: " << userDB[viewerID].userID << endl;

    return 0;
}
