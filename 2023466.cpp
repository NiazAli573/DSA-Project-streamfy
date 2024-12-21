#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;



template <typename K, typename V>
class HashMap
{
private:
    static const int TABLE_SIZE = 100;
    struct HashNode
    {
        K key;
        V value;
        HashNode *next;

        HashNode(K k, V v) : key(k), value(v), next(nullptr) {}
    };
    HashNode *table[TABLE_SIZE];

    int hashFunction(const K &key) const
    {
        return std::hash<K>{}(key) % TABLE_SIZE;
    }

public:
    HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            table[i] = nullptr;
        }
    }

    ~HashMap()
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode *current = table[i];
            while (current)
            {
                HashNode *temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void insert(const K &key, const V &value)
    {
        int hashIndex = hashFunction(key);
        HashNode *newNode = new HashNode(key, value);
        if (!table[hashIndex])
        {
            table[hashIndex] = newNode;
        }
        else
        {
            HashNode *current = table[hashIndex];
            while (current->next)
            {
                if (current->key == key)
                {
                    current->value = value; // Update existing key
                    delete newNode;
                    return;
                }
                current = current->next;
            }
            current->next = newNode;
        }
    }

    bool find(const K &key, V &value) const
    {
        int hashIndex = hashFunction(key);
        HashNode *current = table[hashIndex];
        while (current)
        {
            if (current->key == key)
            {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void iterate(function<void(const K &, const V &)> callback) const
    {
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            HashNode *current = table[i];
            while (current)
            {
                callback(current->key, current->value);
                current = current->next;
            }
        }
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

    void uploadVideo(const std::string &folderPath)
    {
        std::vector<std::string> videos;
        listVideos(folderPath, videos);

        if (videos.empty())
        {
            std::cout << "No videos found in the specified folder.\n";
            return;
        }

        std::cout << "Videos available for upload:\n";
        for (size_t i = 0; i < videos.size(); ++i)
        {
            std::cout << i + 1 << ". " << videos[i].substr(videos[i].find_last_of("\\") + 1) << "\n";
        }

        int choice;
        std::cout << "Enter the number of the video you want to upload: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(videos.size()))
        {
            std::string title = videos[choice - 1].substr(videos[choice - 1].find_last_of("\\") + 1);
            videoLibrary.insert(title, Video(title, videos[choice - 1]));
            std::cout << "Video uploaded successfully: " << title << "\n";
        }
        else
        {
            std::cout << "Invalid choice.\n";
        }
    }

    void addCategory(const std::string &category) {
        categoryTree.addCategory(category);
        std::cout << "Category added: " << category << "\n";
    }

    void uploadVideosToCategory(const std::string &category, const std::string &folderPath) {
        AVLNode *node = categoryTree.getCategoryNode(category);
        if (!node) {
            std::cout << "Category not found: " << category << "\n";
            return;
        }

        std::vector<std::string> videos;
        listVideos(folderPath, videos);

        if (videos.empty()) {
            std::cout << "No videos found in the specified folder.\n";
            return;
        }

        std::cout << "Videos available for upload:\n";
        for (size_t i = 0; i < videos.size(); ++i) {
            std::cout << i + 1 << ". " << videos[i].substr(videos[i].find_last_of("\\") + 1) << "\n";
        }

        int choice;
        std::cout << "Enter the number of the video you want to upload: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(videos.size())) {
           
            node->filePathList.addFilePath(videos[choice - 1]);
            std::cout << "Video added to category '" << category << "'.\n";
        } else {
            std::cout << "Invalid choice.\n";
        }
}

    void viewCategoryVideos() const {
        std::cout << "Enter category name to view videos: ";
        std::string category;
        std::cin.ignore();
        std::getline(std::cin, category);

        AVLNode *node = categoryTree.getCategoryNode(category);
        if (node) {
            std::cout << "Videos in category '" << category << "':\n";
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
            std::cout << "Category not found.\n";
        }
    }
};


    int main() {
    AVLTree categoryTree;
     HashMap<string, Video> videoLibrary;
    Creator creator(videoLibrary,categoryTree);
    
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
