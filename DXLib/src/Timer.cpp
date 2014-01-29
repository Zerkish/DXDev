#include "Timer.h"
#include <windows.h>
#include <cassert>

namespace dx {

Timer::Timer() {
    _frequency = 0;
    _lastTick = 0;
    _startTick = 0;
    _thisTick = 0;
    _deltaSeconds = 0.0;
    _isRunning = false;
    _isPaused = false;
    _isHighPrecision = false;
}

void Timer::Start() {
    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency)) {
        // Highperformance counter is available.
        _isHighPrecision = true;

        _frequency = 1.0 / static_cast<double>(frequency.QuadPart);
        LARGE_INTEGER start;
        QueryPerformanceCounter(&start);

        _startTick = _lastTick = _thisTick = 
            static_cast<double>(start.QuadPart);
    } else {
        // timeGetTime() returns time in milliseconds.
        // We're measuring in seconds however.
        _frequency = 1.0 / 1000.0;

        _startTick = _lastTick = _thisTick = 
            static_cast<double>(timeGetTime());
    }

    _deltaSeconds = 0.0;
    _totalSeconds = 0.0;
    _isRunning = true;
}

void Timer::Stop() {
    _isRunning = false;
}

void Timer::Pause() {
    assert(_isRunning && !_isPaused);
    _isPaused = true;       
}

void Timer::Resume() {
    assert(_isRunning && _isPaused);
}

void Timer::Tick() {
    assert(_isRunning);

    // Don't advance paused timers.
    if (_isPaused) return;

    _lastTick = _thisTick;

    if (_isHighPrecision) {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);

        _thisTick = static_cast<double>(now.QuadPart);
    } else {
        _thisTick = static_cast<double>(timeGetTime());
    }

    _deltaSeconds = (_thisTick - _lastTick) * _frequency;
    _totalSeconds += _deltaSeconds;
}

} // namespace dx