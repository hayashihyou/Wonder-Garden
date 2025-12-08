#include "stdafx.h"

#include "Coin.h"
#include "CoinCount.h"
#include "Player/Player.h"
#include "UI/CoinUI.h"

namespace
{
    const float HIT_DISTANCE = 40.0f;                                    // プレイヤーとの当たり判定距離
    const float ROTATION_SPEED_NORMAL = 5.0f;                            // 回転速度(通常時)
    const float ROTATION_SPEED_SPEED_UP = ROTATION_SPEED_NORMAL * 15.0f; // 回転速度(スピードアップ時)
    const float GET_ANIMATION_TIME = 0.25f;                              // アニメーション時間(秒)
    const float BOUNCE_SPEED = 4.0f;                                     // 跳ね上げ速度

} // namespace

bool Coin::Start()
{
    m_countCointer = FindGO<CountCointer>("CoinCounter");
    m_player = FindGO<Player>("Player");

    // 初期回転速度設定
    m_rotationSpeed = ROTATION_SPEED_NORMAL;

    // モデル初期化
    m_model.Init("Assets/item/coin/coin.tkm");
    UpdateModel();

    return true;
}

void Coin::Update()
{
    switch (m_currentState)
    {
    // 待機状態
    case Coin::State::IDLE:
        UpdateIdleState();
        break;
    // 取得アニメーション中
    case Coin::State::PLAYING_GET_ANIMATION:
        UpdatePlayingGetAnimationState();
        break;
    // コイン取得
    case Coin::State::GET_COIN:
        UpdateGetCoinState();
        break;
    }

    // 回転
    Rotation();

    // モデル更新
    UpdateModel();
}

void Coin::Render(RenderContext& rc)
{
    m_model.Draw(rc);
}

void Coin::UpdateModel()
{
    m_model.SetPosition(m_position);
    m_model.SetRotation(m_rotation);
    m_model.Update();
}

void Coin::UpdateIdleState()
{
    // プレイヤーとの距離を計算
    auto toPlayer = m_player->GetPosition() - m_position;

    // コイン取得判定
    if (toPlayer.Length() < HIT_DISTANCE)
    {
        // 取得アニメーションを再生させる
        m_currentState = State::PLAYING_GET_ANIMATION;
    }
}

void Coin::UpdatePlayingGetAnimationState()
{
    // Y軸回転のスピードアップ
    m_rotationSpeed = ROTATION_SPEED_SPEED_UP;

    // 位置を毎フレームY軸方向に跳ね上げる
    m_getAnimationTimer++;
    m_position.y += BOUNCE_SPEED;

    // アニメーション時間経過でコイン取得状態へ
    // TODO: 60FPS固定前提になっているため、修正が必要
    if (m_getAnimationTimer >= GET_ANIMATION_TIME * 60.0f)
    {
        m_currentState = State::GET_COIN;
    }
}

void Coin::UpdateGetCoinState()
{
    // コインカウント
    m_countCointer->Count();

    // 体力回復
    HealHp();

    DeleteGO(this);
}

void Coin::Rotation()
{
    m_rotation.AddRotationDegY(m_rotationSpeed);
}

void Coin::HealHp()
{
    // プレイヤーの体力を1回復
    // TODO: プレイヤーのMAX体力値は別クラスで管理
    auto newHp = m_player->GetHP() + 1;
    if (newHp >= 8)
    {
        return;
    }
    m_player->SetHP(newHp);
}
