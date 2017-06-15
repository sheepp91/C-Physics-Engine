#pragma once

#include <map>
#include <glm/glm.hpp>

namespace Physics {

	class PhysicsScene;
	class IPhysicsObject;

	class PhysicsGizmosRenderer {
	public:
		struct RenderInfo {
			glm::vec4 color = glm::vec4(1, 1, 1, 1);
		};
	public:
		PhysicsGizmosRenderer();
		PhysicsGizmosRenderer(int sceneNum);
		virtual ~PhysicsGizmosRenderer();

		void Draw(PhysicsScene *scene);

		RenderInfo *GetRenderInfo(IPhysicsObject *object);

	protected:
		std::map<IPhysicsObject *, RenderInfo> m_renderInfo;

		int m_sceneNum;
	private:
	};
}