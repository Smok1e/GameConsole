#pragma once

#define CHECK if (!OK ())                                                                                \
                                                                                                         \
{                                                                                                        \
                                                                                                         \
	char message [MAXLINE] = "";                                                                         \
	sprintf_s (message, "%s:\nValidation failed at line %d in '%s'\n", __FUNCSIG__, __LINE__, __FILE__); \
	printf (message);                                                                                    \
	MessageBox (NULL, message, "Check failed", MB_OK | MB_ICONWARNING);                                  \
    abort ();                                                                                            \
                                                                                                         \
}

const int WINDOWS_MAX = 50;

class WindowManager;

class ContainerWindow;  

class AbstractWindow

{

public:

	AbstractWindow ();

	AbstractWindow (double x, double y, double width, double height, sf::Color color, WindowManager * manager);

	~AbstractWindow ();

	void setPosition (double x, double y)

	{
	
		CHECK;

		x_ = x;
		y_ = y;

		CHECK;

	}

	sf::Vector2f getPosition ()

	{

		CHECK;
	
		return sf::Vector2f (x_, y_);

	}

	void setSize (double width, double height)

	{
	
		CHECK;

		width_ = width;
		height_ = height;

		CHECK;

	}

	sf::Vector2f getSize ()

	{
	
		CHECK;

		return sf::Vector2f (width_, height_);

	}

	void setColor (sf::Color color)

	{
	
		color_ = color;

	}

	sf::Color getColor ()

	{
	
		return color_;

	}

	void setParent (ContainerWindow * parent)

	{

		CHECK;

		parent_ = parent;

		CHECK;

	}

	ContainerWindow * getParent ()

	{

		assert (OK ());
		assert (parent_);

		return parent_;

	}

	void setManager (WindowManager * manager)

	{
	
		CHECK;

		manager_ = manager;

		CHECK;

	}

	WindowManager * getManager ()

	{

		CHECK;
	
		return manager_;

		CHECK;

	}

	virtual bool OK ();

	virtual void draw ();

protected :

	double x_;
	double y_;

	double width_;
	double height_;

	sf::Color color_;

	WindowManager * manager_;

	ContainerWindow * parent_;

	sf::Vector2f gr (sf::Vector2f pos = sf::Vector2f (0, 0));

};

//----------------------------------------------------------------

class ContainerWindow : AbstractWindow

{

public :

	void setChild (AbstractWindow * child)

	{

		CHECK;
	
		child_ = child;

		CHECK;

	}

	AbstractWindow * getChild ()

	{
	
		CHECK;

		return child_;

	}

	void draw ();

protected :

	AbstractWindow * child_;

};

//----------------------------------------------------------------

class WindowManager

{

public :

	WindowManager ();

	~WindowManager ();

	int addWindow (AbstractWindow * window);

	int removeWindow (AbstractWindow * window);

	void removeAllWindows ();

	int findWindow (AbstractWindow * window);

	void drawWindows ();

	void setWindowPtr (sf::RenderWindow * window)
	
	{
	
		window_ = window;

	}

	unsigned windowsAmount ()

	{
	
		unsigned amount = 0u;
		for (int i = 0; i < WINDOWS_MAX; i++) if (windows_[i]) amount++;
		return amount;

	}

	sf::RenderWindow * getWindowPtr ()

	{

		return window_;

	}

private :

	AbstractWindow * windows_ [WINDOWS_MAX];

	sf::RenderWindow * window_;

};