#pragma once

#define TX_USE_SFML

#include "Config.h"
#include <TXLib.h>
#include <SFML\Graphics.hpp>
#include <string.h>
#include "WNDL.h"

//----------------------------------------------------------------

AbstractWindow::AbstractWindow () :

	x_ (0),
	y_ (0),

	width_   (0),
	height_  (0),

	color_   (sf::Color::Black),

	manager_ (nullptr),

	parent_  (nullptr)

{}

//----------------------------------------------------------------

AbstractWindow::AbstractWindow (double x, double y, double width, double height, sf::Color color, WindowManager * manager) :

	x_       (x),
	y_       (y),

	width_   (width),
	height_  (height),
	
	color_   (color),

	manager_ (manager),

	parent_  (nullptr)

{}

//----------------------------------------------------------------

AbstractWindow::~AbstractWindow ()

{

	CHECK;

	x_ = DBL_MIN;
	y_ = DBL_MIN;

	width_  = DBL_MIN;
	height_ = DBL_MIN;

	color_ = sf::Color::Black;

	manager_ = nullptr;

	parent_ = nullptr;

}

//----------------------------------------------------------------

void AbstractWindow::draw ()

{

	CHECK;

	sf::RectangleShape rect;
	rect.setPosition (getPosition ());
	rect.setSize (getSize ());
	rect.setFillColor (color_);
	
	manager_ -> getWindowPtr () -> draw (rect);

}

//----------------------------------------------------------------

sf::Vector2f AbstractWindow::gr (sf::Vector2f pos)

{

	for (AbstractWindow * window = this; window; window = window -> parent_)

	{
	
		pos.x += window -> x_;
		pos.y += window -> y_;

	}

	return pos;

}

//----------------------------------------------------------------

bool AbstractWindow::OK ()

{

	return x_ != DBL_MIN && 
		   y_ != DBL_MIN && 
	   width_ != DBL_MIN && 
	  height_ != DBL_MIN;

}

//----------------------------------------------------------------

WindowManager::WindowManager () :

	windows_ (),

	window_ (nullptr)

{}

//----------------------------------------------------------------

WindowManager::~WindowManager ()

{

	removeAllWindows ();

}

//----------------------------------------------------------------

int WindowManager::addWindow (AbstractWindow * window)

{

	assert (window);

	if (findWindow (window) != -1) 
		
	{
	
		printf ("Failed adding window (%p): This pointer already exists.\n", window);
		return -1;

	}

	for (int n = 0; n < WINDOWS_MAX; n++)

	{
	
		if (windows_[n]) continue;
		windows_[n] = window;

		printf ("Added window #%d (%p)\n", n, window);

		return n;

	}

	printf ("Failed adding window (%p): Windows array is full.\n", window);
	return -1;

}

//----------------------------------------------------------------

int WindowManager::removeWindow (AbstractWindow * window)

{

	for (int n = 0; n < WINDOWS_MAX; n++)

		if (windows_[n] == window)
			
		{

			delete (window);
			windows_[n] = nullptr;

			printf ("Window #%d (%p) removed.\n", n, window);

			return n;

		}

	printf ("Failed to remove window (%p): window does not exists.\n", window);

	return -1;

}

//----------------------------------------------------------------

void WindowManager::removeAllWindows ()

{

	for (int n = 0; n < WINDOWS_MAX; n++)

		if (windows_[n]) removeWindow (windows_[n]);

}

//----------------------------------------------------------------

int WindowManager::findWindow (AbstractWindow * window)

{

	for (int n = 0; n < WINDOWS_MAX; n++)

		if (windows_[n] && windows_[n] == window) return n;

	return -1;

}

//----------------------------------------------------------------

void WindowManager::drawWindows ()

{

	for (int n = 0; n < WINDOWS_MAX; n++)

	{

		if (!windows_[n]) continue; 

		windows_[n] -> draw ();

	}

}

//----------------------------------------------------------------