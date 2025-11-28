#pragma once


class CoinCount:public IGameObject
{
public:
    CoinCount(){};
    ~CoinCount(){};
    bool Start();
    void AddCoinCount();
    int GetCoinCount() { return coinCount; }

private:
    int coinCount = 0;
};
