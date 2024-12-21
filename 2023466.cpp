#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;


// Linked List Node for file paths
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

// AVL Tree Node
struct AVLNode {

    string category;
    FilePathList filePathList;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(const string &cat) : category(cat), left(nullptr), right(nullptr), height(1) {}
};

// AVL Tree for managing categories
class AVLTree {
private:
    AVLNode *root;

    int getHeight(AVLNode *node) const {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode *node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    AVLNode *rotateRight(AVLNode *y) {
        AVLNode *x = y->left;
        AVLNode *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode *rotateLeft(AVLNode *x) {
        AVLNode *y = x->right;
        AVLNode *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode *insert(AVLNode *node, const string &category) {
        if (!node)
            return new AVLNode(category);

        if (category < node->category)
            node->left = insert(node->left, category);
        else if (category > node->category)
            node->right = insert(node->right, category);
        else
            return node; // Duplicate categories not allowed

        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Check balance
        int balance = getBalance(node);

        // Balance the tree
        if (balance > 1 && category < node->left->category)
            return rotateRight(node);
        if (balance < -1 && category > node->right->category)
            return rotateLeft(node);
        if (balance > 1 && category > node->left->category) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && category < node->right->category) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(AVLNode *node) const {
        if (!node)
            return;
        inorder(node->left);
        cout << "Category: " << node->category << "\n";
        node->filePathList.displayFilePaths();
        inorder(node->right);
    }

    AVLNode *find(AVLNode *node, const string &category) {
        if (!node || node->category == category)
            return node;
        if (category < node->category)
            return find(node->left, category);
        return find(node->right, category);
    }

public:
    AVLTree() : root(nullptr) {}

    void addCategory(const string &category) {
        root = insert(root, category);
        cout << "Category added: " << category << "\n";
    }

    void addFilePathToCategory(const string &category, const string &filePath) {
        AVLNode *node = find(root, category);
        if (node) {
            node->filePathList.addFilePath(filePath);
        } else {
            cout << "Category not found: " << category << "\n";
        }
    }

    AVLNode *getCategoryNode(const string &category) {
        return find(root, category);
    }

    
};


void listVideos(const string &folderPath, vector<string> &videos) {
    string searchPath = folderPath + "\\*";
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = FindFirstFile(searchPath.c_str(), &findFileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        cout << "Failed to open folder.\n";
        return;
    }

    do {
        string fileName = findFileData.cFileName;
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            string extension = fileName.substr(fileName.find_last_of(".") + 1);
            if (extension == "mp4" || extension == "mkv" || extension == "avi" || extension == "wmv") {
                videos.push_back(folderPath + "\\" + fileName);
            }
        }
    } while (FindNextFile(hFind, &findFileData));

    FindClose(hFind);
}

void playVideo(const string &videoPath) {
    string command = "start wmplayer \"" + videoPath + "\"";
    system(command.c_str());
}

class Creator {
private:
    AVLTree &categoryTree;

public:
    Creator(AVLTree &ct) : categoryTree(ct) {}

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
    AVLTree categoryTree;
    Creator creator(categoryTree);

    while (true) {
        cout << "\nVideo Organizer\n";
        cout << "1. Add Category\n";
        cout << "2. Upload Videos to Category\n";
        cout<<  "3. Display by category\n"<<endl;
        cout << "4. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;
        cin.ignore(); 
switch (choice) {
    case 1: {
        cout << "Enter category name: ";
        cin.ignore(); 
        string category;
        getline(cin, category);
        creator.addCategory(category);
        break;
    }
    case 2: {
        cout << "Enter category name: ";
        cin.ignore(); 
        string category;
        getline(cin, category);

        cout << "Enter folder path to upload videos: ";
        string folderPath;
        getline(cin, folderPath);

        creator.uploadVideosToCategory(category, folderPath);
        break;
    }
    case 3: {
        creator.viewCategoryVideos();
        break;
    }
    case 4: {
        cout << "Exiting the platform. Goodbye!\n";
        return 0;
    }
    default:
        cout << "Invalid choice. Please try again.\n";
}

    }

    return 0;


}
