#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

 Video and Queue Implementations

// Video class definition
class Video
{
public:
    string title;
    string filePath;
    int likes;
    vector<string> comments;

    Video() : likes(0) {}

    Video(string title, string filePath) : title(title), filePath(filePath), likes(0) {}

    void addComment(const string &comment)
    {
        comments.push_back(comment);
    }

    void displayComments() const
    {
        if (comments.empty())
        {
            cout << "No comments yet.\n";
            return;
        }
        cout << "Comments:\n";
        for (const auto &comment : comments)
        {
            cout << "- " << comment << "\n";
        }
    }
};

// Custom Queue Implementation
template <typename T>
class Queue
{
private:
    vector<T> elements;

public:
    void enqueue(T value)
    {
        elements.push_back(value);
    }

    void dequeue()
    {
        if (!elements.empty())
        {
            elements.erase(elements.begin());
        }
        else
        {
            cout << "Queue is empty.\n";
        }
    }

    T front()
    {
        if (!elements.empty())
        {
            return elements.front();
        }
        throw runtime_error("Queue is empty.");
    }

    bool empty()
    {
        return elements.empty();
    }

    void display()
    {
        if (elements.empty())
        {
            cout << "Playlist is empty.\n";
            return;
        }
        cout << "Playlist:\n";
        for (const auto &element : elements)
        {
            cout << "- " << element << "\n";
        }
    }
};

// Simulating a basic HashMap with iteration capability
class HashMap
{
private:
    unordered_map<string, Video> map;

public:
    void add(const string &key, const Video &value)
    {
        map[key] = value;
    }

    bool find(const string &key, Video &value)
    {
        auto it = map.find(key);
        if (it != map.end())
        {
            value = it->second;
            return true;
        }
        return false;
    }

    template <typename Func>
    void iterate(Func func)
    {
        for (auto &pair : map)
        {
            func(pair.first, pair.second);
        }
    }
};
 User Class and Integration

// User class
class User
{
private:
    HashMap &videoLibrary;
    vector<string> watchHistory;
    Queue<string> playlist;

public:
    User(HashMap &vl) : videoLibrary(vl) {}

    void watchVideo(const string &title)
    {
        Video video;
        if (!videoLibrary.find(title, video))
        {
            cout << "Video not found.\n";
            return;
        }

        cout << "Now watching: " << title << "\n";
        watchHistory.push_back(title);

        string choice;
        cout << "Would you like to comment on this video? (yes/no): ";
        cin >> choice;
        if (choice == "yes")
        {
            string comment;
            cout << "Enter your comment: ";
            cin.ignore();
            getline(cin, comment);
            video.addComment(comment);
            cout << "Comment added.\n";
        }

        cout << "Do you want to like this video? (yes/no): ";
        cin >> choice;
        if (choice == "yes")
        {
            video.likes++;
            cout << "Video liked.\n";
        }
    }

    void viewWatchHistory()
    {
        if (watchHistory.empty())
        {
            cout << "Watch history is empty.\n";
            return;
        }

        cout << "Watch History:\n";
        for (const auto &title : watchHistory)
        {
            cout << "- " << title << "\n";
        }
    }

    void addToPlaylist(const string &title)
    {
        Video video;
        if (!videoLibrary.find(title, video))
        {
            cout << "Video not found.\n";
            return;
        }
        playlist.enqueue(title);
        cout << "Added to playlist: " << title << "\n";
    }

    void playFromPlaylist()
    {
        if (playlist.empty())
        {
            cout << "Playlist is empty.\n";
            return;
        }
        string title = playlist.front();
        playlist.dequeue();
        watchVideo(title);
    }
};

// Main functions for testing Part 2


int main()
{
    // Video v("Sample Video", "path/to/video.mp4");
    // v.addComment("Great video!");
    // v.addComment("Very informative.");

    // cout << "Video: " << v.title << "\n";
    // cout << "Path: " << v.filePath << "\n";
    // cout << "Likes: " << v.likes << "\n";
    // v.displayComments();

  // Queue<string> q;
  //   q.enqueue("Video 1");
  //   q.enqueue("Video 2");
  //   q.enqueue("Video 3");

  //   q.display();

  //   q.dequeue();
  //   cout << "After dequeue:\n";
  //   q.display();

 
  

    return 0;
    
}
