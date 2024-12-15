#include <iostream>
using namespace std;

class Stack {
private:
    struct Node {
        string data;
        Node* next;

        Node(const string& value) : data(value), next(nullptr) {}
    };

    Node* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const string& value) {
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
    }

    string peek() const {
        if (isEmpty()) {
            return "";
        }
        return top->data;
    }

    bool isEmpty() const {
        return top == nullptr;
    }
};

struct VideoNode {
    string videoName;
    string videoPath;
    VideoNode* next;

    VideoNode(const string& name, const string& path) : videoName(name), videoPath(path), next(nullptr) {}
};

class Playlist {
public:
    VideoNode* head;

    Playlist() : head(nullptr) {}

    void addVideo(const string& name, const string& path) {
        VideoNode* newNode = new VideoNode(name, path);
        if (!head) {
            head = newNode;
        } else {
            VideoNode* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        cout << "Video added to playlist: " << name << "\n";
    }

    void displayPlaylist() {
        if (!head) {
            cout << "Playlist is empty!\n";
            return;
        }
        VideoNode* temp = head;
        int index = 1;
        while (temp) {
            cout << index++ << ". " << temp->videoName << "\n";
            temp = temp->next;
        }
    }

    VideoNode* getVideoAt(int position) {
        VideoNode* temp = head;
        int index = 1;
        while (temp && index < position) {
            temp = temp->next;
            index++;
        }
        return temp;
    }
};


Stack videoHistory;

void playVideo(const string& videoPath) {
    cout << "Playing: " << videoPath << "\n";
    system(("start wmplayer \"" + videoPath + "\"").c_str());
}

void backNavigation() {
    if (!videoHistory.isEmpty()) {
        string lastVideo = videoHistory.peek();
        videoHistory.pop();
        playVideo(lastVideo);
    } else {
        cout << "No videos in history!\n";
    }
}

int main() {
    Playlist playlist;
    int choice;

    do {
        cout << "\nVideo Player Menu:\n";
        cout << "1. Add Video to Playlist\n";
        cout << "2. View Playlist\n";
        cout << "3. Play Video from Playlist\n";
        cout << "4. Back to Previous Video\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cin.ignore(); 
                string name, path;
                cout << "Enter video name: ";
                getline(cin, name);
                cout << "Enter video path: ";
                getline(cin, path);
                playlist.addVideo(name, path);
                break;
            }
            case 2: {
                cout << "Playlist:\n";
                playlist.displayPlaylist();
                break;
            }
            case 3: {
                int videoNumber;
                cout << "Enter video number to play: ";
                cin >> videoNumber;
                VideoNode* selectedVideo = playlist.getVideoAt(videoNumber);
                if (selectedVideo) {
                    videoHistory.push(selectedVideo->videoPath);
                    playVideo(selectedVideo->videoPath);
                } else {
                    cout << "Invalid video number!\n";
                }
                break;
            }
            case 4: {
                backNavigation();
                break;
            }
            case 5: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 5);

    return 0;
}
