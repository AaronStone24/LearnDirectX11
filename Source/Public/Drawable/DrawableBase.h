#pragma once
#include "Drawable.h"
#include "../Bindable/IndexBuffer.h"

template<class T>
class DrawableBase : public Drawable
{
public:
	bool IsStaticInitialized() const noexcept
	{
		return !staticBinds.empty();
	}
	void AddStaticBind(std::unique_ptr<Bindable> bind) noexcept
	{
		assert("*Must* use AddIndexBuffer to bind index buffer" && typeid(*bind))
	}
private:
	const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept;
private:
	static std::vector<std::unique_ptr<Bindable>> staticBinds;
};