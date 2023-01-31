#pragma once

#include "Task/ResourceBase.tpp"
#include "Task/ObjectBase.tpp"

namespace SceneTransition
{
	class Resource : public ResourceBase<Resource>
	{
		friend ResourceBase<Resource>;

	private:
		Resource();
	public:
		~Resource();

		DG::Image::SP img;
	};

	class Object : public ObjectBaseWithResource<Object, Resource>
	{
		friend ObjectBase<Object>;

	private:
		enum class State
		{
			FadedOut,
			FadedIn,

			FadingIn,
			FadingOut,
		};

	private:
		Object();

	public:
		virtual ~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		State currentState;
		// TODO : 全てのフレーム制御をタイムになる
		int totalFadeTime;				// フレーム
		int currentFadeTime;
		std::function<void()> onFinishedFading;

	private:
		float CalculateCurrentAlpha() const;
		/// <param name="fadeTime">フレーム</param>
		void Fade(bool isFadeIn, int fadeTime, std::function<void()> onFinished = nullptr);
		friend void Fade(bool isFadeIn, int fadeTime, std::function<void()> onFinished);
	};

	void Fade(bool isFadeIn, std::function<void()> onFinished = nullptr);
	void Fade(bool isFadeIn, int fadeTime, std::function<void()> onFinished = nullptr);
}