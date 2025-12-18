#include "stdafx.h"

#include "GameCamera.h"
#include "Player/Player.h"
#include "Enemy/Boss.h"
#include "Star.h"
#include "UI/BossBarsUI.h"

namespace
{
    const float TARGET_HEIGHT = 80.0f;                          // 注視点の高さ
    const float CAMERA_UPPER_LIMIT = 0.9f;                      // カメラ上方向の制限値
    const float CAMERA_LOWER_LIMIT = -0.2f;                     // カメラ下方向の制限値
    const Vector3 INITIAL_TO_CAMERA_POS(0.0f, 130.0f, -250.0f); // 初期注視点からカメラ位置までのベクトル
    const Vector3 TITLE_CAMERA_TARGET_POS(0.0f, 50.0f, 0.0f); // タイトルカメラ注視点位置
    const Vector3 BOSS_CAMERA_POS(0.0f, 20.0f, -300.0f);           // ボスカメラ位置
    const Vector3 STAR_CAMERA_POS(2300.0f, 350.0f, 3400.0f);    // スターカメラ位置
    const Vector3 PLAYER_CAMERA_POS(-300.0f, 100.0f, -300.0f); // プレイヤーカメラ位置
    const float CAMERA_NEAR_CLIP = 1.0f;                        // カメラのニアクリップ距離
    const float CAMERA_FAR_CLIP = 22000.0f;                     // カメラのファークリップ距離
    const float CAMERA_ROTATION_SPEED = 1.3f;                   // カメラ回転速度
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
    // もしボス戦前のムービー部分ならこの処理を呼ぶ
    if (m_isBossCamera == true)
    {
        BossCamera();
    }

    else if (m_isStarCamera == true)
    {
        if (m_star == nullptr)
        {
            m_star = FindGO<Star>("Star");
        }

        StarCamera();
    }

    // そうでなければ通常のカメラ処理
    else 
    {
        // 入力取得
        auto inputX = g_pad[0]->GetRStickXF();
        auto inputY = g_pad[0]->GetRStickYF();

        // カメラの回転
        Rotation(inputX, inputY);

        // カメラの角度抑制
        SuppressCameraAngle();

        // 注視点計算
        auto targetPosition = CalcTarget();

        // 視点計算
        auto cameraPosition = targetPosition + m_toCameraPos;

        // メインカメラに注視点と視点を設定
        g_camera3D->SetTarget(targetPosition);
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


void GameCamera::SuppressCameraAngle()
{
    auto toCameraPosOld = m_toCameraPos;

    // 注視点から視点までのベクトル
    Vector3 toCameraPositionDirection = m_toCameraPos;

    // 正規化
    // NOTE: 正規化することで、ベクトルの向きだけを取得できる
    //       大きさが1になるということは、ベクトルの長さ(強さ)情報が失われるため、方向のみを扱うことができる
    toCameraPositionDirection.Normalize();

    // カメラが上向きすぎ
    if (toCameraPositionDirection.y < CAMERA_LOWER_LIMIT)
    {
        m_toCameraPos = toCameraPosOld;
    }
    // カメラが下向きすぎ
    else if (toCameraPositionDirection.y > CAMERA_UPPER_LIMIT)
    {
        m_toCameraPos = toCameraPosOld;
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

        //カメラの視点を設定
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

        //カメラの視点を設定
        m_starCameraPos = g_camera3D->GetPosition();
    }

    else
    {
        m_starTargetPos = m_star->GetPosition();

        if (m_starTargetPos.y >= STAR_CAMERA_POS.y)
        {
            m_isStarCamera = false;
        }
    }

    g_camera3D->SetTarget(m_starTargetPos);
    g_camera3D->SetPosition(m_starCameraPos);
}

bool TitleGameCamera::Start()
{
    // 注視点から視点までのベクトルを設定
    m_toCameraPos.Set(INITIAL_TO_CAMERA_POS);

    // カメラのニアクリップとファークリップを設定
    g_camera3D->SetNear(CAMERA_NEAR_CLIP);
    g_camera3D->SetFar(CAMERA_FAR_CLIP);

    g_camera3D->SetPosition(m_toCameraPos);
    g_camera3D->SetTarget(TITLE_CAMERA_TARGET_POS);
    g_camera3D->Update();
    return true;
}

void TitleGameCamera::Update() {}


