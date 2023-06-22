#include "pch.h"
#include "Tab.h"
#include "Input.h"
#include "Gui.h"
#include "Drawing.h"

Tab::Tab(std::string name, float x, float y, float width, float height, int* selectedtab = nullptr)
{
	Tab::Size = { width,height };
	Tab::SetVisible(true);
	Tab::Index = TabCount; // this doesn't need to be changed for a different set of tabs or whatever, you dont need to import a value here you just need a nonce value so you never get a repeated one
	Tab::Pos = {x,y };
	Tab::Selected = selectedtab;
	Tab::TabName = name;
//	Tab::Size.x += 1;
	TabCount++;
}
void Tab::Update()
{
	if (!Tab::Parent)
		Tab::SetVisible(false);

	if (!Tab::IsVisible())
		return;
	Tab::ParentPos =  Tab::GetParent()->GetPos();
	Tab::ParentSize = Tab::GetParent()->GetSize();
	// Bandaid fix
	size_t ignore_count = 0;

	for (child& it : Tab::Parent->Container())
	{
		if (it == shared_from_this())
			break;

		if (!it->IsVisible())
			++ignore_count;
	}


}
void Tab::Draw()
{
	if (!Tab::IsVisible())
		return;
	
	D2D1::ColorF textcolour = Colour(0, 0, 255, 255);
	bool selected = Index == *Selected;
	
		textcolour = Colour(255, 0, 0, 255);
		FilledRectangle(Tab::ParentPos.x +Tab::Pos.x, (Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y, Tab::Size.x, Tab::Size.y, Colour(20, 30, 160, 255));
		Text(Tab::TabName, Tab::ParentPos.x + Tab::Pos.x + (Tab::Size.x / 2), ((Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y) + (Tab::Size.y / 2), 12, "Verdana", Colour(255, 255, 255, 255), CentreCentre);
		//Text(Tab::TabName, Tab::Parent->GetPos().x + Tab::Pos.x + (Tab::Size.x / 2), Tab::Parent->GetPos().y + Tab::Pos.y + +(Tab::Size.y / 2), Colour(240, 240, 240, 255), Colour(140, 140, 140, 50), "Verdana 12", Centre);
		if (!selected)
		{
			if (IsMouseInRectangle(Tab::ParentPos.x + Tab::Pos.x, (Tab::ParentPos.y + Tab::ParentSize.y) - Tab::Pos.y, Tab::Size.x, Tab::Size.y) && IsKeyClicked(VK_LBUTTON) && !selected)
			{
				*Selected = Index;
				// ideally you just want to make a timer and use that but since this is just poc we do this
				Sleep(50); // allows us to smooth into tabs as we don't want inputs to go straight through tabs
			}
		}
	if (selected)
	{
		Container::Draw();
		Container::Update();
	}
}