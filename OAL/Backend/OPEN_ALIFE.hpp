#pragma once
#include <vector>
#include <iostream>
#include <chrono>

#define START_TIMER     auto starttimerdefinemacro = std::chrono::high_resolution_clock::now()
#define STOP_TIMER      auto endtimerdefinemacro = std::chrono::high_resolution_clock::now()
#define TIMER_DURATION  std::chrono::duration_cast<std::chrono::microseconds>(endtimerdefinemacro - starttimerdefinemacro).count()