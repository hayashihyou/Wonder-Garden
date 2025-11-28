#pragma once

class CoinCount;
class CoinUI : public IGameObject
{
public:
    CoinUI(){};
    ~CoinUI(){};
    bool Start();
    void Update();
    void Render(RenderContext& rc);

private:
    FontRender m_fontRender;
    SpriteRender m_spriteRender;
    CoinCount* m_coinCount = nullptr;
};
