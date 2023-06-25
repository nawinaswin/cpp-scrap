#include <iostream>
#include <thread>
#include <mutex>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <atomic>


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

std::mutex mtx; // Mutex for protecting the shared variable
std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Create a unique_lock without acquiring the lock initially
int sharedVariable = 0; // Shared variable
std::atomic<bool> shouldExit(false);  // Shared flag to signal thread to exit

void listenfks() {
    while (shouldExit == false) {
        char input;
        if (read(STDIN_FILENO, &input, 1) != -1) {
            if (input == 'q' || input == 'Q') {
                lock.lock(); // Manually acquire the lock
                sharedVariable = 3;    
                lock.unlock(); 
            }
            else if (input == 'p' || input == 'P') { // <-- Missing semicolon here
                std::cout << "Paused! press 'c' to continue." << std::endl;
                lock.lock(); // Manually acquire the lock
                sharedVariable = 1;    
                lock.unlock();
                while (true) {
                    if (read(STDIN_FILENO, &input, 1) != -1) {
                        if (input == 'c' || input == 'C') {
                        lock.lock(); // Manually acquire the lock
                        sharedVariable = 2;    
                        lock.unlock();
                        break;
                        }
                    }
                }
            }
            //std::cout << input << std::endl;
        }
    }
    std::cout<<"Input listenfks terminated!"<<std::endl;
}

int main() {
    // Create two threads
    std::thread t1(listenfks);

    setTerminalAttributes();

    while(true){
        if(sharedVariable == 1){        
        lock.lock(); // Manually acquire the lock
        sharedVariable = 0;    
        lock.unlock(); 
        while(true){
            if(sharedVariable == 2){break;}
            }
        }

        if(sharedVariable == 3){ // 3 is code for quit
        lock.lock(); 
        sharedVariable = 0;    
        lock.unlock(); 
        break; 
        }

        //you application 


        //


        std::cout<<"..."<<std::endl;
    }

    std::cout<<"Main loop is done!"<<std::endl; 

    // Signal the thread to exit
    shouldExit = true;   

    restoreTerminalAttributes();
    return 0;
    // Wait for the threads to finish
    t1.join();
}
