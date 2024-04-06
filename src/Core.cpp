//Libs
#include <iostream>
#include <fstream>

// Header Files
#include "FileWatcher.h"
#include "Core.h"

using namespace std;

void uploadimg(string path_to_watch);

void mainloop() {
    FileWatcher fw {"./Screenshots", chrono::milliseconds(1000)};

    fw.start([] (string path_to_watch, FileStatus status) -> void {
        if (!filesystem::is_regular_file(filesystem::path(path_to_watch)) && status != FileStatus::erased) {
            return;
        }

        switch (status)
        {
        case FileStatus::erased:
            cout << "File erased: " << path_to_watch << '\n';
            system("osascript -e 'display notification \"message\" with title\"File Erased!\"'");
            break;
        case FileStatus::created:
            cout << "File created: " << path_to_watch << '\n';
            system("osascript -e 'display notification \"message\" with title\"File Created!\"'");
            //uploadimg(path_to_watch);
            break;
        case FileStatus::modifed:
            cout << "File modifed: " << path_to_watch << '\n';
            system("osascript -e 'display notification \"message\" with title\"File Modifed !\"'");
            break;
        
        default:
            break;
        }
    });
}

void uploadimg(string path_to_watch) {
    int pollingInterval = 2000;  // 2 second
    string upload_command = "curl -H \"authorization: [auth code here] \" [upload api endpoint] -F \"file=@" +
        path_to_watch + "\" -H \"Content-Type: multipart/form-data\" -H \"Format: random\"";

    std::this_thread::sleep_for(std::chrono::milliseconds(pollingInterval));
    system(upload_command.c_str());
}