#include <Engine/Engine.h>

#include "EditorLayer.h"
#include "EditorUILayer.h"

int main()
{
	using namespace Engine;

	const Application::Specification appSpecs = Application::Specification{
		"Editor",
		1760,
		990,
		List<Layer*>
		{
			new Editor::EditorLayer(),
			new Editor::EditorUILayer()
		}
	};

	Application* app = new Application(appSpecs);

	app->Run();

	return 0;
}
