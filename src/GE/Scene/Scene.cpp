#include "Scene.h"
#include "GE/Core/GameObject.h"
#include <algorithm>
#include "GE/Core/Camera2D.h"
#include "GE/Render/Renderer.h"

namespace GE
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

	Event<const Scene&> Scene::onLoaded;

	Scene::Scene(const std::string& name) : 
		state(State::Initialized),
		name(name)
	{
		Camera2D::onStarted.AddListener(&Scene::RegisterCamera, *this);
		Camera2D::onDestroying.AddListener(&Scene::UnregisterCamera, *this);

		Render::Renderer::onStarted.AddListener(&Scene::RegisterRenderer, *this);
		Render::Renderer::onDestroying.AddListener(&Scene::UnregisterRenderer, *this);
	}

	Scene::~Scene()
	{
		state = State::Destroying;

		Camera2D::onStarted.RemoveListener(&Scene::RegisterCamera, *this);
		Camera2D::onDestroying.RemoveListener(&Scene::UnregisterCamera, *this);

		Render::Renderer::onStarted.RemoveListener(&Scene::RegisterRenderer, *this);
		Render::Renderer::onDestroying.RemoveListener(&Scene::UnregisterRenderer, *this);

		ownedGameObjects.OnPreDestroy();
	}

	GameObject* Scene::FindGameObject(const std::string& name) const
	{
		return GetOwnedGameObject(name);
	}

	void Scene::Load()
	{
		state = State::Loaded;

		ownedGameObjects.OnAwake();
		onLoaded.Invoke(*this);
	}

	void Scene::OnStartUnstarted()
	{
		// ownedGameObjects.OnStartUnstarted()の時、新しいGameObjectを生成することもある
		while (ownedGameObjects.OnStartUnstarted());
	}

	void Scene::OnUpdate()
	{
		ownedGameObjects.OnUpdate();
	}

	void Scene::OnLateUpdate()
	{
		ownedGameObjects.OnLateUpdate();
	}

	void Scene::OnEndOfFrame()
	{
		ownedGameObjects.OnEndOfFrame();
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
		if (this == &camera.gameObject.GetBelongingScene()) {
			cameras.push_back(&camera);
		}
	}

	void Scene::UnregisterCamera(const Camera2D& camera)
	{
		if (this == &camera.gameObject.GetBelongingScene()) {
			cameras.erase(std::remove(cameras.begin(), cameras.end(), &camera), cameras.end());
		}
	}

	void Scene::RegisterRenderer(const Render::Renderer& renderer)
	{
		if (this == &renderer.gameObject.GetBelongingScene()) {
			renderers.push_back(&renderer);
		}
	}

	void Scene::UnregisterRenderer(const Render::Renderer& renderer)
	{
		if (this == &renderer.gameObject.GetBelongingScene()) {
			renderers.erase(std::remove(renderers.begin(), renderers.end(), &renderer), renderers.end());
		}
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