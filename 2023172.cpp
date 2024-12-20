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

// Linked List Implementation
class FilePathNode {
public:
    std::string data;
    FilePathNode* next;

    FilePathNode(const std::string& path) : data(path), next(nullptr) {}
};

class FilePathList {
private:
    FilePathNode* head;

public:
    FilePathList() : head(nullptr) {}

    void addPath(const std::string& path) {
        FilePathNode* newNode = new FilePathNode(path);
        newNode->next = head;
        head = newNode;
    }

    void displayPaths() const {
        FilePathNode* current = head;
        while (current) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }

    ~FilePathList() {
        while (head) {
            FilePathNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Stack Implementation
template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void push(const T& item) {
        elements.push_back(item);
    }

    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        }
    }

    T top() const {
        if (!elements.empty()) {
            return elements.back();
        }
        throw std::out_of_range("Stack is empty");
    }

    bool isEmpty() const {
        return elements.empty();
    }

    size_t size() const {
        return elements.size();
    }
};



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
