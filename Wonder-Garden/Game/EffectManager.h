#pragma once

enum EnEffcetType
{
    Enemy_Hit,
    Boss_Hit,
    Cannon_Fire,
};

class EffectManager : public IGameObject
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EffectManager(){};
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~EffectManager(){};

    bool Start();
    void Update(){};
};
