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
char sharedVariable = 'a'; // Shared variable
std::atomic<bool> shouldExit(false); // Shared flag to signal thread to exit

void inputListening() {
    while (!shouldExit.load()) {
        char input;
        if (read(STDIN_FILENO, &input, 1) != -1) {
            lock.lock(); // Manually acquire the lock
            sharedVariable = input;    
            lock.unlock(); 
            }
    }
    std::cout<<"Input listen thread terminated!"<<std::endl;
}

int main() {
    // Create two threads
    std::thread t1(inputListening);

    setTerminalAttributes();

    while(true){
        if(sharedVariable == 'p'){        
        //.......execute pause confition.............. 


        //.............................................
        while(true){ if(sharedVariable == 'c'){break;} } }

        if(sharedVariable == 'q'){            
        shouldExit.store(true); 
        //std::this_thread::sleep_for(std::chrono::nanoseconds(1000000));
        break;}

        //you application 


        //


        std::cout<<"........."<<std::endl;
    }

    std::cout<<"Press Enter to Exit!"<<std::endl;   

    restoreTerminalAttributes();

    // Wait for the threads to finish
    t1.join();
    return 0;
}