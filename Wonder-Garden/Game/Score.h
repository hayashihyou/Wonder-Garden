#pragma once

class CoinCounter;
class KillCounter;

class Score : public IGameObject
{
public:
    Score(){};
    ~Score(){};
    bool Start();
    void Update(){};
    void Render(RenderContext& rc){};
    void CalcScore();


public:
    int GetScore() { return m_totalScore; }


private:
    CoinCounter* m_coinCounter = nullptr;
    KillCounter* m_killCounter = nullptr;

    int m_totalScore = 0;
};
