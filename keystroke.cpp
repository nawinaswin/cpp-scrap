
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


#include <iostream>

// Function to set terminal attributes for macOS input handling
void setTerminalAttributes() {

    struct termios termAttr;
    tcgetattr(STDIN_FILENO, &termAttr);
    termAttr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &termAttr);
}

// Function to restore terminal attributes on macOS
void restoreTerminalAttributes() {

    struct termios termAttr;
    tcgetattr(STDIN_FILENO, &termAttr);
    termAttr.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &termAttr);

}


int main() {
    // Set terminal attributes for macOS input handling
    setTerminalAttributes();

    std::cout << "Press 'Q' to quit the loop." << std::endl;

    while (true) {
        char input;
        if (read(STDIN_FILENO, &input, 1) != -1) {
            if (input == 'q' || input == 'Q') {
                break;
            }
            else if (input == 'p' || input == 'P') { // <-- Missing semicolon here
                std::cout << "Paused! press c to continue." << std::endl;
                while (true) {
                    if (read(STDIN_FILENO, &input, 1) != -1) {
                        if (input == 'c' || input == 'C') {
                            break;
                        }
                    }
                }
            }
            std::cout << input << std::endl;
        }
    }

    // Restore terminal attributes on macOS
    restoreTerminalAttributes();

    std::cout << "Loop Over." << std::endl;
    return 0;
}
