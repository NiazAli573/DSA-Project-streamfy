#include <iostream>
#include <vector>
#include <string>

class Video {
public:
    std::string title;
    int creatorID;
    std::string filePath;

    Video(std::string t, int cid, std::string fp)
        : title(t), creatorID(cid), filePath(fp) {}
};
struct Video {
    string title;
    string filePath;
};



int main() {
    std::vector<Video> videos;
    videos.push_back(Video("Sample Video", 123, "path/to/video.mp4"));
    videos.push_back(Video("Another Video", 124, "path/to/another_video.mp4"));

    // Display the video metadata
    for (const auto& video : videos) {
        std::cout << "Title: " << video.title
                  << ", Creator ID: " << video.creatorID
                  << ", File Path: " << video.filePath << std::endl;
    }

queue<Video> playbackQueue;

    // Example: Adding videos to playback queue
    playbackQueue.push({"Introduction to C++", "C:\\Videos\\intro_cpp.mp4"});
    playbackQueue.push({"Binary Search Trees", "C:\\Videos\\bst_tutorial.mp4"});

    // Playback simulation
    cout << "Starting Video Playback:\n";
    while (!playbackQueue.empty()) {
        Video currentVideo = playbackQueue.front();
        cout << "Now Playing: " << currentVideo.title << endl;

        // Simulate playing the video using system call
#ifdef _WIN32
        string command = "start \"\" \"" + currentVideo.filePath + "\"";
#else
        string command = "xdg-open \"" + currentVideo.filePath + "\"";
#endif
        system(command.c_str());

        playbackQueue.pop();
    }

    cout << "Playback Completed!\n";

    
    return 0;
}
