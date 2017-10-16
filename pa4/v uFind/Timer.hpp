#include <chrono>

class Timer{
private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;

public:

  /*
   * Function called when starting the timer.
   */
  void begin_timer(){
    start = std::chrono::high_resolution_clock::now();
  }


  /*
   * Function called when ending the timer. Returns duration in milliseconds
   * PRECONDITION: begin_timer() must be called before this function
   */
  float end_timer(){
    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    end = std::chrono::high_resolution_clock::now();
    return ((float)std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count())/1000000;
  }


};