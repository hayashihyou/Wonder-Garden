#pragma once	
class CharacterBase : public IGameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase() {};

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CharacterBase() {};

	/// <summary>
	/// スタート
	/// </summary>
	/// <returns></returns>
	virtual bool Start();

	/// <summary>
	/// HPのベース
	/// </summary>
	virtual void HP() = 0;
	
	/// <summary>
	/// 攻撃力のベース
	/// </summary>
	virtual void Attack() = 0;
	
	/// <summary>
	/// 移動速度のベース
	/// </summary>
	virtual void Move() = 0;
	

	/// <summary>
	/// 更新処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	virtual void Render(RenderContext& rc);

	int hp = 100;
	int atk = 10;
};

