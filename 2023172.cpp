#include <iostream>
#include <stack>
#include <string>
struct VideoNode {
    std::string videoName;
    std::string videoPath;
    VideoNode* next;

    VideoNode(const std::string& name, const std::string& path)
        : videoName(name), videoPath(path), next(nullptr) {}
};
