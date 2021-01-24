#pragma once
#include <queue>

class Mouse
{
	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Enter,
			Leave,
			Invalid
		};
	private:
		Type type;
		bool isLeftPressed;
		bool isRightPressed;
		int x;
		int y;
	public:
		Event() noexcept
			:
			type(Type::Invalid),
			isLeftPressed(false),
			isRightPressed(false),
			x(0),
			y(0)
		{}
		Event(Type type, const Mouse& parent) noexcept
			:
			type(type),
			isLeftPressed(parent.isLeftPressed),
			isRightPressed(parent.isRightPressed),
			x(parent.x),
			y(parent.y)
		{}
		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
		Type GetType() const noexcept
		{
			return type;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return std::make_pair(x, y);
		}
		int GetPosX() const noexcept
		{
			return x;
		}
		int GetPosY() const noexcept
		{
			return y;
		}
		bool IsLeftPressed() const noexcept
		{
			return isLeftPressed;
		}
		bool IsRightPressed() const noexcept
		{
			return isRightPressed;
		}
	};
public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	std::pair<int, int> GetPos() const noexcept;
	int GetPosX() const noexcept;
	int GetPosY() const noexcept;
	bool IsInWindow() const noexcept;
	bool IsLeftPressed() const noexcept;
	bool IsRightPressed() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept
	{
		return buffer.empty();
	}
	void Flush() noexcept;
private:
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightReleased(int x, int y) noexcept;
	void OnMouseLeave() noexcept;
	void OnMouseEnter() noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;
private:
	static constexpr unsigned int bufferSize = 16u;
	int x = 0;
	int y = 0;
	bool isLeftPressed = false;
	bool isRightPressed = false;
	bool isInWindow = false;
	std::queue<Event> buffer;
};