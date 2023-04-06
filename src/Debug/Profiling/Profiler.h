#pragma once

#include "Debug/DebugConfig.h"

#if DEBUG_IS_ENABLED(DEBUG_PROFILER)

#include "Task/ObjectBase.tpp"

namespace Debug::Profiler
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
		std::unique_ptr<class ProfilerLogger> logger;

		unsigned int currentSampleSize;
	};
}

#define DEBUG_START_PROFILING() Debug::Profiler::Object::Create(true)

#else

#define DEBUG_START_PROFILING()

#endif