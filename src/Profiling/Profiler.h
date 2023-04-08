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
	};
}

#define DEBUG_START_PROFILING() Profiling::Object::Create(true)

#else

#define DEBUG_START_PROFILING()

#endif