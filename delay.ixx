module;
#include <chrono>
#include <thread>

export module delay;

export struct delay_time
{

    explicit delay_time(std::chrono::seconds s) : duration(s) {}

    explicit delay_time(int ms) : duration(std::chrono::milliseconds(ms)) {}
    explicit delay_time(std::chrono::milliseconds ms) : duration(ms) {}
    ~delay_time()
    {
        std::this_thread::sleep_for(duration);
    }

    delay_time(const delay_time&) = delete;
    delay_time& operator=(const delay_time&) = delete;
    delay_time(delay_time&&) = default;
    delay_time& operator=(delay_time&&) = default;

private:
    std::chrono::milliseconds duration;
};
//Delay