#include "stdafx.h"

#include "SoundManager.h"

namespace
{
    // --------------------------------------
    // サウンドファイルのパス関連
    // --------------------------------------
    static const std::string SOUND_ASSETS_PATH = "Assets/sounds/";
    static const std::string BGM_ASSETS_PATH = "BGM/";
    static const std::string SE_ASSETS_PATH = "SE/";
    static const std::string WAVE_EXTENTION = ".wav";   // 拡張子.wav
    // BGMファイルパス取得
    static std::string GetBGMFilePath(const std::string& fileName)
    {
        return SOUND_ASSETS_PATH + BGM_ASSETS_PATH + fileName + WAVE_EXTENTION;
    }
    // SEファイルパス取得
    static std::string GetSEFilePath(const std::string& fileName)
    {
        return SOUND_ASSETS_PATH + SE_ASSETS_PATH + fileName + WAVE_EXTENTION;
    }

    // 登録するサウンドリスト
    struct SoundInfo
    {
        std::string name;
        bool isBGM;
        //
        SoundInfo(const char* n, const bool bgm) : name(n), isBGM(bgm) {}
        std::string GetFilePath() const
        {
            if (isBGM)
            {
                return GetBGMFilePath(name);
            }
            else
            {
                return GetSEFilePath(name);
            }
        }
    };
    static std::vector<SoundInfo> soundList = {
        // BGM
        SoundInfo("TitleBGM", true),
        SoundInfo("InGameBGM", true),
        // SE
        SoundInfo("PlayerRunningSE", false),
        SoundInfo("PlayerJumpSE", false),
        SoundInfo("PlayerPunchSE", false),
        SoundInfo("PlayerDamageSE", false),
        SoundInfo("GetCoinSE", false),
        SoundInfo("GetStarSE", false),
        SoundInfo("CanonFireSE", false),
        SoundInfo("WarpPipeSE", false),
        SoundInfo("SystemDecisionSE", false),
        SoundInfo("EnemyAttackSE", false),
        SoundInfo("EnemyDeathSE", false),
    };
}

SoundManager* SoundManager::s_instance = nullptr;

SoundManager::SoundManager()
{
    // シングルトンとして登録
    if (s_instance == nullptr)
    {
        s_instance = this;
        // 初期化
        Init();
    }
    else
    {
        // 既に存在している場合は自身を削除
        DeleteGO(this);
    }
}

SoundManager::~SoundManager()
{
}


void SoundManager::Init()
{
    for (int i = 0; i < soundList.size(); i++)
    {
        // サウンド登録
        g_soundEngine->ResistWaveFileBank(i, soundList[i].GetFilePath().c_str());
    }
}

void SoundManager::PlayBGM(SoundNumber soundNumber, float volume, bool isLoop)
{
    if (m_currentBGM == nullptr)
    {
        m_currentBGM = NewGO<SoundSource>(0);
    }
    m_currentBGM->Init(soundNumber, false);
    m_currentBGM->SetVolume(volume);
    m_currentBGM->Play(isLoop);
}

void SoundManager::PlaySE(SoundNumber soundNumber, float volume, bool isLoop)
{
    auto* soundSorce = NewGO<SoundSource>(0);
    soundSorce->Init(soundNumber, false);
    soundSorce->SetVolume(volume);
    soundSorce->Play(isLoop);
}

void SoundManager::DeleteCurrentBGM()
{
    if (m_currentBGM != nullptr)
    {
        m_currentBGM->Release();
        m_currentBGM = nullptr;
    }
}
