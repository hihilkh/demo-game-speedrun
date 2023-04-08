#pragma once

#include "ProfilingConfig.h"

#if PROFILER_ENABLED

#include "Task/ObjectBase.tpp"

namespace Profiling
{
	class Object : public ObjectBase<Object>
	{
		friend ObjectBase<Object>;

	private:
		Object();

	public:
		~Object();

		void UpDate() override;			//「実行」１フレーム毎に行う処理
		void Render2D_AF() override;	//「2D描画」１フレーム毎に行う処理

	private:
		std::vector<std::unique_ptr<class ProfilerSection>> sections;
		std::vector<std::unique_ptr<class ProfilerLogger>> loggers;

		unsigned int currentSampleSize;

	private:
		void InitSections();
		void InitLoggers();

	public:
		void InsertMessage(const string& message) const;
	};
}

#define DEBUG_START_PROFILING() Profiling::Object::Create(true)

// TODO : 一時的なこーどだけです。これの代わりに、シーンの遷移イベントでトリガーする
#define DEBUG_PROFILING_SET_SCENE(sceneName) {\
	Profiling::Object::SP profiler = ge->GetTask<Profiling::Object>("デバッグ", "プロファイラ");\
	profiler->InsertMessage("Move to scene : "s + sceneName);\
}

#else

#define DEBUG_START_PROFILING()
#define DEBUG_PROFILING_SET_SCENE(sceneName)

#endif