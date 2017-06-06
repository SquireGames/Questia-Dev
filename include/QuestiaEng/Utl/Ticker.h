#ifndef TICKER_H
#define TICKER_H

namespace utl
{

class Ticker
{
public:
    //ctor, dtor
    Ticker(unsigned int tickInterval = 128);
    ~Ticker() = default;

    //add to currentTick
    void tick();
    //resets currentTick to 0
    void resetTicker();

    //returns if the ticker reached the tickInterval
    bool isReady();

    //resets and returns if is ready
    bool isDone();
    //ticks and returns result
    bool pulse();

    //get
    unsigned int getTick();
    float getPercentage();

private:
    unsigned int currentTick = 0;
    unsigned int tickInterval;
};

}

#endif // TICKER_H
