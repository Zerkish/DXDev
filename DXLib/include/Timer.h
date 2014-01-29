#ifndef TIMER_H
#define TIMER_H

#define TO_MILLIS(X) (X) * 1000.0
#define TO_MINUTES(X) (X) / 60.0
#define TO_HOURS(X) (X) / 3600.0

namespace dx {

// Highprecision timer class.
class Timer {
public:
    Timer();
    ~Timer() {};

    inline bool IsRunning() const { return _isRunning; }
    inline bool IsPaused() const { return _isPaused; }
    inline bool IsHighPrecision() const { return _isHighPrecision; }

    void Start();
    void Stop();

    void Pause();
    void Resume();

    // Causes the timer to update,
    // only call this once per game logic iteration.
    void Tick();

    // Variations of get delta time.
    // Can be used for hourly intervals etc.
    inline double GetDeltaMillis() const { return TO_MILLIS(_deltaSeconds); }
    inline double GetDeltaSeconds() const { return _deltaSeconds; }
    inline double GetDeltaMinutes() const { return TO_MINUTES(_deltaSeconds); }
    inline double GetDeltaHours() const { return TO_HOURS(_deltaSeconds); }

    // Returns time elapsed since Start() was called.
    inline double GetTotalMillis() const { return TO_MILLIS(_totalSeconds); }
    inline double GetTotalSeconds() const { return _totalSeconds; }
    inline double GetTotalMinutes() const { return TO_MINUTES(_totalSeconds); }
    inline double GetTotalHours() const { return TO_HOURS(_totalSeconds); }

private:
    double _startTick;
    double _lastTick;
    double _thisTick;

    // We multiply ticks by this variable to convert into seconds.
    double _frequency;

    // Used to save the current delta for this tick.
    double _deltaSeconds;

    // Saves the total seconds since Start()
    double _totalSeconds;

    bool _isRunning;
    bool _isPaused;
    bool _isHighPrecision;

};

} // namespace dx
#endif // TIMER_H