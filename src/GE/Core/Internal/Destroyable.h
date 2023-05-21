#pragma once

namespace GE
{
	class GameEngine;
}

namespace GE::Internal
{
	class Destroyable
	{
		friend class GE::GameEngine;

	public:
		enum class State : char
		{
			Valid,
			ToBeDestroy,
			Destroying,
		};

		virtual ~Destroyable() = default;

		bool IsValid() const { return destroyState == State::Valid; }

	protected:
		virtual void OnPreDestroy() 
		{ 
			destroyState = State::Destroying;
			PreDestroy();
		}

		/// <summary>
		/// 破棄直前の処理
		/// </summary>
		virtual void PreDestroy() {}

	private:
		// TODO : 
		// 自分でOnDestroyを呼び出すということはちょっと変だと思う。
		// 結局、派生クラスのOnDestroy実装はfriend classに依存し、コードは混乱になると思う。
		virtual void OnDestroy() = 0;
		virtual bool CheckIsInActiveScene() = 0;

	private:
		void SetToBeDestroy() { destroyState = State::ToBeDestroy; }

	private:
		State destroyState = State::Valid;
	};
}