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

public:
	const Vector3& GetPosition() const { return m_transform.m_position; }
	const Quaternion& GetRotation() const { return m_transform.m_rotation; }
	const Vector3& GetScale() const { return m_transform.m_scale; }
protected:
	Transform m_transform;

	int hp = 0;
	int atk = 0;


};

