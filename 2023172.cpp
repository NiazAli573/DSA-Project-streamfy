#include <iostream>
#include <filesystem>

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


// Linked List Implementation
class FilePathNode {
public:
    std::string data;
    FilePathNode* next;

    FilePathNode(const std::string& path) : data(path), next(nullptr) {}
};


struct FilePathNode
{
    string filePath;
    FilePathNode *next;

    FilePathNode(string path) : filePath(path), next(nullptr) {}
};

// Linked List for managing file paths
class FilePathList
{
private:
    FilePathNode *head;
public:

    FilePathList() : head(nullptr) {}

    void addFilePath(const string &path)
    {
        FilePathNode *newNode = new FilePathNode(path);
        newNode->next = head;
        head = newNode;
    }

    void displayFilePaths() const
    {
        if (!head)
        {
            cout << "No file paths available.\n";
            return;
        }
        cout << "File Paths:\n";
        FilePathNode *current = head;
        while (current)
        {
            cout << "- " << current->filePath << "\n";
            current = current->next;
        }
    }

    string search(int number){
        if(!head){
            cout << "No file paths available.\n";
            return "NULL";
        }
        int i=1;
        while(head){
            if(i==number){
                return head->filePath;
            }
            
            head=head->next;
            ++i;
        }
       return "NULL";
    }

   
};


template <typename T>
class Stack
{
private:
    vector<T> elements;

public:
    void push(T value)
    {
        elements.push_back(value);
    }

    void pop()
    {
        if (!elements.empty())
        {
            elements.pop_back();
        }
        else
        {
            cout << "Stack is empty.\n";
        }
    }

    T top()
    {
        if (!elements.empty())
        {
            return elements.back();
        }
        throw runtime_error("Stack is empty.");
    }

    bool empty()
    {
        return elements.empty();
    }

    void display()
    {
        if (elements.empty())
        {
            cout << "No videos watched yet.\n";
            return;
        }
        cout << "Watch History:\n";
        for (int i = elements.size() - 1; i >= 0; --i)
        {
            cout << "- " << elements[i] << "\n";
        }
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

namespace fs = filesystem;

// Simple graph structure
struct Graph {
    vector<pair<int, int>> edges;
    vector<string> nodes;

    void addNode(const string& node) {
        nodes.push_back(node);
    }

    void addEdge(int from, int to) {
        edges.emplace_back(from, to);
    }

    void displayGraph() {
        for (const auto& edge : edges) {
            cout << nodes[edge.first] << " -> " << nodes[edge.second] << endl;
        }
    }
};

// Main function
void processFolder(const string& folderPath) {
    Graph graph;
    vector<string> titles;

    // Collect titles from the folder
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            string title = entry.path().stem().string(); // getting the file from here
            titles.push_back(title);
            graph.addNode(title);
        }
    }

    // Creating simple graph connections like connections of all videos present in the videos folder
    for (size_t i = 0; i < titles.size() - 1; ++i) {
        graph.addEdge(i, i + 1);
    }

    // Display the graph
    graph.displayGraph();
}

int main() {
    // Stack operations
    Stack<string> watchHistory;
    watchHistory.push("Video1.mp4");
    watchHistory.push("Video2.mp4");
    watchHistory.display();
    watchHistory.pop();
    watchHistory.display();

    // FilePathList operations
    FilePathList filePathList;
    filePathList.addFilePath("C:/Videos/Video1.mp4");
    filePathList.addFilePath("C:/Videos/Video2.mp4");
    filePathList.displayFilePaths();

    // Graph operations
    string folderPath = "C:/Videos";
    processFolder(folderPath);

    return 0;
}
