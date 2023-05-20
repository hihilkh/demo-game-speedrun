#include "Scene.h"
#include "GE/Core/GameObject.h"
#include <algorithm>
#include "GE/Core/Camera2D.h"
#include "GE/Render/Renderer.h"

namespace GE::SceneManagement
{
	namespace
	{
		struct CameraSort
		{
			bool operator()(const Camera2D* lhs, const Camera2D* rhs)
			{
				return lhs->GetPriority() < rhs->GetPriority();
			}
		};

		struct RendererSort
		{
			bool operator()(const Render::Renderer* lhs, const Render::Renderer* rhs)
			{
				return lhs->GetRenderPriority() < rhs->GetRenderPriority();
			}
		};
	}

	Scene::Scene(const std::string& name) : 
		isDestructing(false),
		name(name)
	{
	}

	Scene::~Scene()
	{
		isDestructing = true;
	}

	void Scene::OnUpdate()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnUpdate();
		}
	}

	void Scene::OnLateUpdate()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnLateUpdate();
		}
	}

	void Scene::OnRender()
	{
		// TODO : もっと効率的な方法を考える
		std::sort(cameras.begin(), cameras.end(), CameraSort());
		std::sort(renderers.begin(), renderers.end(), RendererSort());

		for (auto camera : cameras) {
			camera->OnRender(renderers);
		}
	}

	void Scene::RegisterCamera(const Camera2D& camera)
	{
		cameras.push_back(&camera);
	}

	void Scene::UnregisterCamera(const Camera2D& camera)
	{
		if (isDestructing) {
			return;
		}

		cameras.erase(std::remove(cameras.begin(), cameras.end(), &camera), cameras.end());
	}

	void Scene::RegisterRenderer(const Render::Renderer& renderer)
	{
		renderers.push_back(&renderer);
	}

	void Scene::UnregisterRenderer(const Render::Renderer& renderer)
	{
		if (isDestructing) {
			return;
		}

		renderers.erase(std::remove(renderers.begin(), renderers.end(), &renderer), renderers.end());
	}

	bool operator==(const Scene& lhs, const Scene& rhs)
	{
		return &lhs == &rhs;
	}

	bool operator!=(const Scene& lhs, const Scene& rhs)
	{
		return !(lhs == rhs);
	}
}