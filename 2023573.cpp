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

    return 0;
}
