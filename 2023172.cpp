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
