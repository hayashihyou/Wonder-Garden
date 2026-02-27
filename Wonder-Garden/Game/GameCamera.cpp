#include "stdafx.h"

#include "Enemy/Boss.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "Star.h"
#include "EffectManager.h"
#include "SoundManager.h"
#include "UI/BossBarsUI.h"

namespace
{
    const float TARGET_HEIGHT = 80.0f;                          // 注視点の高さ
    const float CAMERA_UPPER_LIMIT = 0.9f;                      // カメラ上方向の制限値
    const float CAMERA_LOWER_LIMIT = -0.2f;                     // カメラ下方向の制限値
    const Vector3 INITIAL_TO_CAMERA_POS(0.0f, 130.0f, -250.0f); // 初期注視点からカメラ位置までのベクトル
    const Vector3 TITLE_CAMERA_TARGET_POS(0.0f, 50.0f, 0.0f);  // タイトルカメラ注視点位置
    const Vector3 BOSS_CAMERA_POS(0.0f, 20.0f, -300.0f);       // ボスカメラ位置
    const Vector3 STAR_CAMERA_POS(2300.0f, 350.0f, 3400.0f);   // スターカメラ位置
    const Vector3 WARP_CAMERA_POS(300.0f, 200.0f, 1300.0f);    // ワープカメラ位置
    const Vector3 CANNON_CAMERA_POS(0.0, 300.0f, -500.0f);     // 大砲のカメラ位置
    const Vector3 LAND_CAMERA_POS(2400.0f, 125.0f, 2900.0f);   // 
    const Vector3 EFFECT_SCALE(15.0f, 15.0f, 1.0f);            //
    const Vector3 SMOKE_SCALE(10.0f, 10.0f, 1.0f);
    const Vector3 PLAYER_CAMERA_POS(-300.0f, 100.0f, -300.0f); // プレイヤーカメラ位置
    const Vector3 PIPE_POS = {-2200.0f, 90.0f, 660.0f};        // 土管位置
    const Vector3 CLEAR_CAMERA_OFFSET(0.0f, 40.0f, 200.0f);    // ゲームクリアの際のカメラの位置
    const float CAMERA_NEAR_CLIP = 1.0f;                       // カメラのニアクリップ距離
    const float CAMERA_FAR_CLIP = 22000.0f;                    // カメラのファークリップ距離
    const float CAMERA_ROTATION_SPEED = 1.3f;                  // カメラ回転速度
} // namespace

bool GameCamera::Start()
{
    m_player = FindGO<Player>("Player");
    m_boss = FindGO<Boss>("Boss");

    // 初期化
    Init();

    return true;
}

void GameCamera::Update()
{
    if (m_isclearCamera == true)
    {
        GameClearCamera();
    }

    // もしボス戦前のムービー部分ならこの処理を呼ぶ
    else if (m_isBossCamera == true)
    {
        BossCamera();
    }

    else if (m_isStarCamera)
    {
        if (m_star == nullptr)
        {
            m_star = FindGO<Star>("Star");
        }

        StarCamera();
    }

    else if (m_isWarpCamera)
    {
        WarpCamera();
    }

    else if (m_player->IsCannon())
    {
        CannonCamera();
    }

    else if (m_isEffectPlay)
    {
        LandCamera();
    }

    else if (m_player->IsFire())
    {
        FireCamera();
    }

    // そうでなければ通常のカメラ処理
    else
    {
        // 入力取得
        float inputX = g_pad[0]->GetRStickXF();
        float inputY = g_pad[0]->GetRStickYF();

        // 古いカメラ位置を保存
        Vector3 toCameraPosOld = m_toCameraPos;

        // カメラの回転
        Rotation(inputX, inputY);

        // カメラの角度抑制
        SuppressCameraAngle(toCameraPosOld);

        // 注視点計算
        m_targetPosition = CalcTarget();

        // 視点計算
        Vector3 cameraPosition = m_targetPosition + m_toCameraPos;

        // メインカメラに注視点と視点を設定
        g_camera3D->SetTarget(m_targetPosition);
        g_camera3D->SetPosition(cameraPosition);
    }

    // カメラ更新
    g_camera3D->Update();
}

void GameCamera::Init()
{
    // 注視点から視点までのベクトルを設定
    m_toCameraPos.Set(INITIAL_TO_CAMERA_POS);

    // カメラのニアクリップとファークリップを設定
    g_camera3D->SetNear(CAMERA_NEAR_CLIP);
    g_camera3D->SetFar(CAMERA_FAR_CLIP);
}

void GameCamera::Rotation(float inputX, float inputY)
{
    // Y軸周りの回転
    Quaternion qRot;
    qRot.SetRotationDeg(Vector3::AxisY, CAMERA_ROTATION_SPEED * inputX);
    qRot.Apply(m_toCameraPos);

    // X軸周りの回転
    Vector3 axisX;
    axisX.Cross(Vector3::AxisY, m_toCameraPos);
    axisX.Normalize();
    qRot.SetRotationDeg(axisX, CAMERA_ROTATION_SPEED * inputY);
    qRot.Apply(m_toCameraPos);
}

Vector3 GameCamera::CalcTarget()
{
    // プレイヤーの足元から少し上
    auto target = m_player->GetPosition();
    target.y += TARGET_HEIGHT;

    return target;
}

void GameCamera::SuppressCameraAngle(Vector3 oldPos)
{
    // 注視点から視点までのベクトル
    Vector3 toCameraPositionDirection = m_toCameraPos;

    // 正規化
    // NOTE: 正規化することで、ベクトルの向きだけを取得できる
    //       大きさが1になるということは、ベクトルの長さ(強さ)情報が失われるため、方向のみを扱うことができる
    toCameraPositionDirection.Normalize();

    // カメラが上向きすぎ
    if (toCameraPositionDirection.y < CAMERA_LOWER_LIMIT)
    {
        m_toCameraPos = oldPos;
    }
    // カメラが下向きすぎ
    else if (toCameraPositionDirection.y > CAMERA_UPPER_LIMIT)
    {
        m_toCameraPos = oldPos;
    }
}

void GameCamera::BossCamera()
{
    if (m_changeCamera == false)
    {
        m_changeCamera = true;

        m_bossBarsUI = NewGO<BossBarsUI>(0, "BossBarsUI");

        // カメラの注視点を設定
        m_bossTargetPos = m_boss->GetPosition();

        // カメラの視点を設定
        m_bossCameraPos = m_player->GetPosition() + BOSS_CAMERA_POS;
        g_camera3D->SetTarget(m_bossTargetPos);
        g_camera3D->SetPosition(m_bossCameraPos);
    }

    m_bossCameraPos.z += 15.0f;
    if (m_bossCameraPos.z >= 3700.0f)
    {
        m_bossCameraPos.z = 3700.0f;
        m_bossCameraPos.y += 1.0f;

        if (m_bossCameraPos.y >= 300.0f)
        {
            m_bossCameraPos.y = 300.0f;
            m_isBossCamera = false;
            m_changeCamera = false;
            m_player->SetLandTime(1.5f);
        }
    }

    g_camera3D->SetTarget(m_bossTargetPos);
    g_camera3D->SetPosition(m_bossCameraPos);
    g_camera3D->Update();
}

void GameCamera::StarCamera()
{
    if (m_changeCamera == false)
    {
        m_changeCamera = true;

        // カメラの注視点を設定
        m_starTargetPos = STAR_CAMERA_POS;

        // カメラの視点を設定
        m_starCameraPos = g_camera3D->GetPosition();
    }

    else
    {
        m_starTargetPos = m_star->GetPosition();

        if (m_starTargetPos.y >= STAR_CAMERA_POS.y)
        {
            m_isStarCamera = false;
            m_changeCamera = false;
        }
    }

    g_camera3D->SetTarget(m_starTargetPos);
    g_camera3D->SetPosition(m_starCameraPos);
}

void GameCamera::DokanStart()
{
    if (!m_changeCamera)
    {
        m_changeCamera = true;
        time = 0.0f;
    }

    cameraOffset = g_camera3D->GetPosition() - g_camera3D->GetTarget();
    m_warpTargetPos = g_camera3D->GetTarget();
}

void GameCamera::WarpCamera()
{
    if (m_changeCamera == false)
    {
        return;
    }

    Vector3 position;
    position.Lerp(time, m_warpTargetPos, PIPE_POS);
    time += g_gameTime->GetFrameDeltaTime() * 0.5f;

    g_camera3D->SetTarget(position);
    g_camera3D->SetPosition(position + cameraOffset);

    if (time >= 0.5f)
    {
        m_isWarpCamera = false;
        m_changeCamera = false;
    }
}

void GameCamera::CannonCamera()
{
    if (m_changeCamera == false)
    {
        m_changeCamera = true;

        Vector3 cannonTargetPos = m_player->GetPosition() - INITIAL_TO_CAMERA_POS;
        m_cannonCameraPos = cannonTargetPos + CANNON_CAMERA_POS;

        g_camera3D->SetTarget(cannonTargetPos);
    }

    if (m_countdown <= 0.0f)
    {
        m_player->SetFireFlag(true);
        m_changeCamera = false;
        m_isMoveCamera = false;
        m_countdown = 1.0f;
        return;
    }

    Vector3 idealPos = m_cannonCameraPos;


    /**
    * 条件が被ってしまう為、フラグを使って制御
    */
    if (m_cannonCameraPos.x <= -1400.0f && m_cannonCameraPos.z <= 2850.0f && m_isMoveCamera == false)
    {
        idealPos += Vector3(6.0f, 0.0f, 6.0f);
    }

    else if (m_cannonCameraPos.x >= -2000.0f && m_bossCameraPos.z <= 3000.0f)
    {
        m_isMoveCamera = true;
        idealPos += Vector3(-8.0f, 0.0f, 6.0f);
    }

    else if (m_cannonCameraPos.x >= -2350.0f && m_cannonCameraPos.z >= 2350.0f)
    {
        idealPos -= Vector3(8.0f, 0.0f, 8.0f);
    }

    else if (m_cannonCameraPos.x < -2350.0f && m_cannonCameraPos.z > 2350.0f)
    {
        m_countdown -= g_gameTime->GetFrameDeltaTime();
    }

    m_cannonCameraPos.Lerp(1.0f, m_cannonCameraPos, idealPos);

    if (m_player->IsFire() == false)
    {
        g_camera3D->SetTarget(m_player->GetPosition());
        g_camera3D->SetPosition(m_cannonCameraPos);
    }
}

void GameCamera::FireCamera()
{
    if (m_isPlayerDraw)
    {
        m_changeTime -= g_gameTime->GetFrameDeltaTime();
        if (m_changeTime <= 0.0f)
        {
            m_isEffectPlay = true;
            m_changeTime = 0.7f;
        }
        return;
    }

    if (m_effectTime > 0.0f)
    {
        m_effectTime -= g_gameTime->GetFrameDeltaTime();
        m_smokeTime += g_gameTime->GetFrameDeltaTime();
        if (m_smokeTime >= 0.05f)
        {
            Quaternion effectRot = m_player->GetRotation();
            effectRot.z += 1.0f;
            EffectManager::Get()->PlayEffect(m_player->GetPosition(), effectRot, SMOKE_SCALE,EnEffcetType::Cannon_Fire);
            m_smokeTime = 0.0f;
        }

        g_camera3D->SetTarget(m_player->GetPosition());
        g_camera3D->SetPosition(m_cannonCameraPos);
    }

    else
    {
        m_effectTime = 0.35f;
        m_isPlayerDraw = true;
        EffectManager::Get()->PlayEffect(m_player->GetPosition(), Quaternion::Identity, EFFECT_SCALE, Cannon_Star);
        SoundManager::GetInstance().PlaySE(SoundManager::SoundNumber::CannonStarSE);
    }
}

void GameCamera::LandCamera()
{
    m_isPlayerDraw = false;
    m_landCameraPos = LAND_CAMERA_POS;

    if (!m_player->IsLand() && m_player->GetLandTime() <= 0.0f)
    {
        m_isEffectPlay = false;
    }

    g_camera3D->SetTarget(m_player->GetPosition());
    g_camera3D->SetPosition(m_landCameraPos);
}

void GameCamera::GameClearCamera()
{

    Vector3 playerPos = m_player->GetPosition();

    if (m_changeCamera == false)
    {
        m_changeCamera = true;

        Vector3 playerCameraOffset = CLEAR_CAMERA_OFFSET;
        Quaternion rotation = m_player->GetRotation();
        rotation.Apply(playerCameraOffset);

        m_clearCameraPos = playerPos + playerCameraOffset;
    }


    Vector3 target =playerPos;
    target.y += 40.0f;

    g_camera3D->SetTarget(target);
    g_camera3D->SetPosition(m_clearCameraPos);
}


