#include <iostream>
#include <vector>
#include <string>
using namespace std;

class UserProfile {
public:
    int user_id;
    string name;
    string password;
    string role;
    vector<int> liked_videos;

    UserProfile(int id, const string& name, const string& password, const string& role)
        : user_id(id), name(name), password(password), role(role) {}

    void likeVideo(int video_id) {
        liked_videos.push_back(video_id);
    }
};

class HashMap {
private:
    struct Node {
        int key;
        UserProfile value;
        Node* next;
    };
    Node** table;
    int capacity;

public:
    HashMap(int cap = 100) : capacity(cap) {
        table = new Node*[capacity]();
    }

    int hash(int key) {
        return key % capacity;
    }

    void insert(int user_id, const UserProfile& user) {
        int index = hash(user_id);
        Node* newNode = new Node{user_id, user, nullptr};

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* temp = table[index];
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    UserProfile* get(int user_id) {
        int index = hash(user_id);
        Node* temp = table[index];
        while (temp != nullptr) {
            if (temp->key == user_id) {
                return &temp->value;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    ~HashMap() {
        for (int i = 0; i < capacity; i++) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        delete[] table;
    }
};

int main() {
    HashMap userMap;
    int userIDCounter = 1;
    string username, password;
    int userType;

    cout << "Select user type: \n0 for Creator\n1 for User\nEnter your choice: ";
    cin >> userType;

    if (userType == 0) {
        string creatorPassword = "Mehdi";
        cout << "Enter Creator Name: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (password == creatorPassword) {
            UserProfile creator(userIDCounter++, username, password, "creator");
            userMap.insert(creator.user_id, creator);
            cout << "Creator profile created successfully!" << endl;
        } else {
            cout << "Incorrect password for creator!" << endl;
        }
    } else if (userType == 1) {
        cout << "Enter User Name: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        UserProfile user(userIDCounter++, username, password, "user");

        int likedVideoID;
        char anotherVideo = 'y';
        while (anotherVideo == 'y' || anotherVideo == 'Y') {
            cout << "Enter the video ID you want to like (1 for Video 1, 2 for Video 2, etc.): ";
            cin >> likedVideoID;
            user.likeVideo(likedVideoID);
            cout << "Do you want to like another video? (y/n): ";
            cin >> anotherVideo;
        }

        userMap.insert(user.user_id, user);
        cout << "User profile created successfully!" << endl;
    } else {
        cout << "Invalid selection! Please restart the program and choose 0 or 1." << endl;
    }

    int userIDToSearch;
    cout << "Enter user ID to fetch details: ";
    cin >> userIDToSearch;

    UserProfile* fetchedUser = userMap.get(userIDToSearch);
    if (fetchedUser != nullptr) {
        cout << "User Found!" << endl;
        cout << "User ID: " << fetchedUser->user_id << endl;
        cout << "Name: " << fetchedUser->name << endl;
        cout << "Role: " << fetchedUser->role << endl;
        cout << "Liked Videos: ";
        for (int videoID : fetchedUser->liked_videos) {
            cout << videoID << " ";
        }
        cout << endl;
    } else {
        cout << "User not found!" << endl;
    }

    return 0;
}
