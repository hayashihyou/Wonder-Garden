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


    SpriteRender& GetHPBarBack() { return m_HPBarBack; }
    SpriteRender& GetHPFrame() { return m_HPBarFrame; }
    SpriteRender& GetHPBar() { return m_HPBar; }


    void InitHPBar();
    void ChangeState();
    void UpdateHPBar();


    Vector3 GetScal() { return scal; }

private:
    enum EnHPBarState
    {
        enAPPEAR,
        enNormal,
        enNum,
    };


private:
    float m_hpRatio;
    std::vector<std::unique_ptr<SpriteRender>> m_hpList;
    SpriteRender m_HPBar;
    SpriteRender m_HPBarDamage;
    SpriteRender m_HPBarBack;
    SpriteRender m_HPBarFrame;
    EnHPBarState m_hpBarState = enNum;
    Boss* m_boss = nullptr;


    Vector3 scal = {1.0f, 1.0f, 0.5f};
};
