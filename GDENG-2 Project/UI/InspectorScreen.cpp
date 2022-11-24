#include "InspectorScreen.h"

#include "Component/TransformComponent.h"

InspectorScreen::InspectorScreen():
	AUIScreen("Inspector Screen")
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 25));
	ImGui::SetWindowSize(ImVec2(250, UIManager::WINDOW_HEIGHT));
	this->generateEditor();
	ImGui::End();
}

void InspectorScreen::generateEditor()
{
	if (GameObjectManager::getInstance()->getSelectedObject() != NULL)
	{
		
		ImGui::Text("Selected Object: %s", GameObjectManager::getInstance()->getSelectedObject()->Name.c_str());
		this->TransformUpdate();
		if (ImGui::DragFloat3("Position", this->SelectedObjectposition, 0.01))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::DragFloat3("Rotation", this->SelectedObjectRotation, 0.01))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::DragFloat3("Scale", this->SelectedObjectScale, 0.01))
		{
			this->TransformSelected(GameObjectManager::getInstance()->getSelectedObject());
		}
		if (ImGui::Button("Delete", ImVec2(70.0f, 0.0f)))
		{
			GameObjectManager::getInstance()->
					deleteObjectByName(GameObjectManager::getInstance()->getSelectedObject()->Name);
			GameObjectManager::getInstance()->setSelectedObject(NULL);
		}
	}

	else
	{
		ImGui::Text("No object selected");
	}
}

void InspectorScreen::TransformUpdate()
{
	Vector3D position               = GameObjectManager::getInstance()->getSelectedObject()->transform().Position;
	this->SelectedObjectposition[0] = position.x;
	this->SelectedObjectposition[1] = position.y;
	this->SelectedObjectposition[2] = position.z;

	Vector3D scale               = GameObjectManager::getInstance()->getSelectedObject()->transform().Scale;
	this->SelectedObjectScale[0] = scale.x;
	this->SelectedObjectScale[1] = scale.y;
	this->SelectedObjectScale[2] = scale.z;

	Vector3D rotaion                = GameObjectManager::getInstance()->getSelectedObject()->transform().Rotation;
	this->SelectedObjectRotation[0] = rotaion.x;
	this->SelectedObjectRotation[1] = rotaion.y;
	this->SelectedObjectRotation[2] = rotaion.z;
}

void InspectorScreen::TransformSelected(AGameObject* selected)
{
	selected->transform().Position = Vector3D(this->SelectedObjectposition[0],
	                                          this->SelectedObjectposition[1],
	                                          this->SelectedObjectposition[2]);
	selected->transform().Rotation = Vector3D(this->SelectedObjectRotation[0],
	                                          this->SelectedObjectRotation[1],
	                                          this->SelectedObjectRotation[2]);
	selected->transform().Scale = Vector3D(this->SelectedObjectScale[0],
	                                       this->SelectedObjectScale[1],
	                                       this->SelectedObjectScale[2]);
}

InspectorScreen::~InspectorScreen()
{
}
