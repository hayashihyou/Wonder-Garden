#pragma once


class HPUI : public IGameObject
{
public:
    HPUI();
    ~HPUI();

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;


    void SetRatio(const float ratio) { m_hpRatio = ratio; }


private:
    float m_hpRatio;
    std::vector<std::unique_ptr<SpriteRender>> m_hpList;
};
