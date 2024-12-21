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


class Creator
{
private:
    HashMap<string, Video> &videoLibrary;
    AVLTree &categoryTree;

public:
    Creator(HashMap<string, Video> &vl,AVLTree &ct) : videoLibrary(vl), categoryTree(ct) {}

    void uploadVideo(const string &title, const string &filePath)
    {
        Video tempVideo(title, filePath);
        videoLibrary.insert(title, tempVideo);
        cout << "Video uploaded successfully.\n";
    }

    void viewVideos() const
    {
        bool hasVideos = false;
        videoLibrary.iterate([&hasVideos](const string &title, const Video &video)
                             {
            if (!hasVideos) {
                cout << "Uploaded Videos:\n";
                hasVideos = true;
            }
            cout << "- " << title << " (Likes: " << video.likes << ")\n"; });
        if (!hasVideos)
        {
            cout << "No videos uploaded yet.\n";
        }
    }

    void uploadVideo(const string &folderPath)
    {
        vector<string> videos;
        listVideos(folderPath, videos);

        if (videos.empty())
        {
            cout << "No videos found in the specified folder.\n";
            return;
        }

        cout << "Videos available for upload:\n";
        for (size_t i = 0; i < videos.size(); ++i)
        {
            cout << i + 1 << ". " << videos[i].substr(videos[i].find_last_of("\\") + 1) << "\n";
        }

        int choice;
        cout << "Enter the number of the video you want to upload: ";
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(videos.size()))
        {
            string title = videos[choice - 1].substr(videos[choice - 1].find_last_of("\\") + 1);
            videoLibrary.insert(title, Video(title, videos[choice - 1]));
            cout << "Video uploaded successfully: " << title << "\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    void addCategory(const string &category) {
        categoryTree.addCategory(category);
        cout << "Category added: " << category << "\n";
    }

    void uploadVideosToCategory(const string &category, const string &folderPath) {
        AVLNode *node = categoryTree.getCategoryNode(category);
        if (!node) {
            cout << "Category not found: " << category << "\n";
            return;
        }

        vector<string> videos;
        listVideos(folderPath, videos);

        if (videos.empty()) {
            cout << "No videos found in the specified folder.\n";
            return;
        }

        cout << "Videos available for upload:\n";
        for (size_t i = 0; i < videos.size(); ++i) {
            cout << i + 1 << ". " << videos[i].substr(videos[i].find_last_of("\\") + 1) << "\n";
        }

        int choice;
        cout << "Enter the number of the video you want to upload: ";
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(videos.size())) {
           
            node->filePathList.addFilePath(videos[choice - 1]);
            cout << "Video added to category '" << category << "'.\n";
        } else {
            cout << "Invalid choice.\n";
        }
}

    void viewCategoryVideos() const {
        cout << "Enter category name to view videos: ";
        string category;
        cin.ignore();
        getline(cin, category);

        AVLNode *node = categoryTree.getCategoryNode(category);
        if (node) {
            cout << "Videos in category '" << category << "':\n";
            node->filePathList.displayFilePaths();
            cout<<"Enter the number of video you want to watch:"<<endl;
            int choice;
            cin>>choice;
            cin.ignore();
            string file=node->filePathList.search(choice);
            if(file!="NULL"){
            playVideo(file);
            } else{
                cout<<"File not found"<<endl;
            }

        } else {
            cout << "Category not found.\n";
        }
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
