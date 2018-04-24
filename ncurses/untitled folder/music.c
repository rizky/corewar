#include <stdio.h>
#include <stdlib.h>
// #include <mpg123.h>
// #include <vlc/vlc.h>
// #include <windows.h>
// #include <MMsystem.h>

int main(int argc, char **argv)
{
    argc = 0;
    argv++;
    // ffplay example.mp3;

    system("if [ ! $(pgrep afplay) ]; then afplay ~/Downloads/LevelsIDOriginalMix.mp3& fi");
    // system("kill $(pgrep afplay)");

    // int pid;
    // pid = system("pgrep afplay");
    // if (pid == 256)
    // {

        // printf("it is dead %d must replay\n", pid);
        // system("afplay ~/Downloads/LevelsIDOriginalMix.mp3&");
    // }
    // system("kill "pid);

    return 0;
}