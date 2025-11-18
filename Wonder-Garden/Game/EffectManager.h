#pragma once

enum EnEffcetType
{
    Hit,
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
