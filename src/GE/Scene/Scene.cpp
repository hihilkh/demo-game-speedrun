#include "Scene.h"
#include "GE/Core/GameObject.h"
#include <algorithm>
#include "GE/Core/Camera2D.h"
#include "GE/Render/Renderer.h"

namespace GE::Scene
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
		state(State::Initialized),
		name(name)
	{
	}

	Scene::~Scene()
	{
		state = State::Destroying;

		for (auto& gameObject : gameObjects) {
			gameObject->OnPreDestroy();
		}
	}

	GameObject* Scene::FindGameObject(const std::string& name) const
	{
		return GetOwnedGameObject(name);
	}

	void Scene::Load()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnAwake();
		}

		for (auto& gameObject : gameObjects) {
			gameObject->OnStart();
		}
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

	void Scene::OnEndOfFrame()
	{
		for (auto& gameObject : gameObjects) {
			gameObject->OnEndOfFrame();
		}
	}

	void Scene::OnRender(const std::vector<Scene*>& scenes)
	{
		// TODO : もっと効率的な方法を考える
		if (scenes.size() == 0) {
			return;
		}

		std::vector<const GE::Camera2D*> allCameras;
		std::vector<const GE::Render::Renderer*> allRenderers;

		for (auto scene : scenes) {
			allCameras.insert(allCameras.end(), scene->cameras.begin(), scene->cameras.end());
			allRenderers.insert(allRenderers.end(), scene->renderers.begin(), scene->renderers.end());
		}

		std::sort(allCameras.begin(), allCameras.end(), CameraSort());
		std::sort(allRenderers.begin(), allRenderers.end(), RendererSort());

		for (auto camera : allCameras) {
			camera->OnRender(allRenderers);
		}
	}

	void Scene::RegisterCamera(const Camera2D& camera)
	{
		cameras.push_back(&camera);
	}

	void Scene::UnregisterCamera(const Camera2D& camera)
	{
		if (state == State::Destroying) {
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
		if (state == State::Destroying) {
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