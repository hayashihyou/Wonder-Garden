#pragma once


class Boss;
class HPUI : public IGameObject
{
public:
    HPUI();
    ~HPUI();

    bool Start() override;
    void Update() override;
    void Render(RenderContext& rc) override;


    void SetRatio(const float ratio) { m_hpRatio = ratio; }
    void InitHPBar();
    void UpdateHPBar();


private:
    float m_hpRatio;
    std::vector<std::unique_ptr<SpriteRender>> m_hpList;
    SpriteRender m_HPBar;
    SpriteRender m_HPBarBack;
    SpriteRender m_HPBarFrame;
    Boss* m_boss = nullptr;

    Vector3 scal = {1.0f, 1.0f, 0.5f};
};
