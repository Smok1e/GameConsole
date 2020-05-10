const int wWidth = 800;
const int wHeight = 800;

const int OBJ_MAX = 100;

const int MAXLINE = 512;

const int LINES = 30;

//----------------------------------------------------------------

#include <SFML\Graphics.hpp>
#include <string.h>
#include "C:\Lib\ExtraUtilits\ExtraUtilits.h"
#include "LineBuffer.h"

sf::Font * DefaultFont = nullptr;

const char * backgrounds [] = {

	"Background\\1.png",
	"Background\\2.png",
	"Background\\3.png",
	"Background\\4.png",

	nullptr

};

//----------------------------------------------------------------

class EditBox;
class ScrollBar;

//----------------------------------------------------------------

struct EventHandler 

{

	EditBox * objects_[OBJ_MAX];

	EventHandler ();

	~EventHandler ();

	int addObject (EditBox * object);

	int removeObject (EditBox * object);

	void processEvents (const sf::Event & event);

};

EventHandler::EventHandler () :

	objects_ ()

{}

EventHandler::~EventHandler ()

{

	for (int n = 0; n < OBJ_MAX; n++)

	{
	
		if (!objects_[n]) continue;

		delete (objects_[n]);

		objects_[n] = nullptr;

	}

}

//----------------------------------------------------------------

class EditBox

{

public :

	EditBox ();

	EditBox (int x, int y, int width, int height, sf::Font font, sf::RenderWindow * window, const char * str = "");

	void draw ();

	bool onKeyPressed (const sf::Event & event);

	bool onTextEntered (const sf::Event & event);

	void setForegroundColor (sf::Color color);
	
	void setBackgroundColor (sf::Color color);
	
	void setCursorColor (sf::Color color);

	void setHighlightningColor (sf::Color color);

	void setString (const char * str);

	void setFont (sf::Font font);

	void setWindow (sf::RenderWindow & window);

	void setPosition (double x, double y);

	void clear ();

	const char * getString ();

	void setBounds (sf::FloatRect bounds)

	{
	
		x_ = bounds.left;
		y_ = bounds.top;

		width_ = bounds.width;
		height_ = bounds.height;

	}

	sf::FloatRect getBounds ()

	{
	
		return sf::FloatRect (x_, y_, width_, height_);

	}

private :

	int x_;
	int y_;

	int width_;
	int height_;

	sf::Color background_;
	sf::Color foreground_;
	sf::Color curColor_;
	sf::Color highlightingColor_;

	sf::Font font_;

	std::string line_;

	int cursorPos_;

	const int blink_counter_limit_ = 50;

	int blinkCounter_;

	bool insertMode_;

	sf::RenderWindow * window_;

	bool onKeyEntered (char key);

	bool onBackspace ();

	bool onDelete ();

	bool onArrow (int arg);

	bool onInsert ();

	bool onHome ();

	bool onEnd ();

	bool onEnter ();

	bool onPaste ();

	bool onCtrl ();

	bool onCtrlShift ();

	bool onRandomString ();

	void insertString (const char * str);

};

EditBox::EditBox () :

	x_                 (0),
	y_                 (0),

	width_             (0),
	height_            (0),

	font_              (*DefaultFont),

	background_        (0, 0, 0, 100),
	foreground_        (sf::Color::Green),
	curColor_          (128, 255, 128),
	highlightingColor_ (255, 255, 255, 100),

	line_              (""),

	cursorPos_         (line_.size ()),

	blinkCounter_      (0),

	insertMode_        (false),

	window_            (nullptr)

{}

EditBox::EditBox (int x, int y, int width, int height, sf::Font font, sf::RenderWindow * window, const char * str) :

	x_                 (x),
	y_                 (y),

	width_             (width),
	height_            (height),

	font_              (font),

	background_        (0, 0, 0, 100),
	foreground_        (sf::Color::Green),
	curColor_          (128, 255, 128),
	highlightingColor_ (255, 255, 255, 100),

	line_              (str),

	cursorPos_         (line_.size ()),

	blinkCounter_      (0),

	insertMode_        (false),

	window_            (window)

{}

class GameConsole

{
	
public :

	GameConsole (double x, double y, double width, double height, sf::RenderWindow * window);

	void draw ();

	bool onTextEntered (const sf::Event & event);

	bool onKeyPressed (const sf::Event & event); 

	bool onMouseWheel (const sf::Event & event);

	void setForegroundColor (sf::Color color);
	
	void setBackgroundColor (sf::Color color);
	
	void setCursorColor (sf::Color color);

	void setHighlightningColor (sf::Color color);

	void setString (const char * str);

	void setFont (sf::Font font);

	void setWindow (sf::RenderWindow & window);

	sf::RenderWindow * getWindow ()

	{

		return window_;

	}

	void setVisibleLinesCount (unsigned count);

	unsigned getVisibleLinescount ()

	{
	
		return visibleLinesCount_;

	}

	const char * getString ();

	void print (const char * str);

	void clear ();

	void attachScrollbar (ScrollBar & scrollBar);

	void setFirstVisibleLine (int value)

	{
	
		firstVisibleLine_ = value;

		updateBounds ();

	}

	void setBackgroundImage (sf::Image & image)

	{
	
		backgroundTexture_.loadFromImage (image);

	}

	sf::FloatRect getBounds ()

	{
	
		return sf::FloatRect (x_, y_, width_, height_);

	}

	void setBounds (sf::FloatRect bounds)

	{
	
		x_ = bounds.left, y_ = bounds.top, width_ = bounds.width, height_ = bounds.height;

		updateBounds ();

	}

private :

	double x_;
	double y_;

	double width_;
	double height_;

	sf::Color background_;
	sf::Color foreground_;
	sf::Color curColor_;
	sf::Color highlightingColor_;

	sf::Font font_;

	EditBox editBox_;

	LineBuffer buffer_;

	sf::RenderWindow * window_;

	unsigned visibleLinesCount_;

	int firstVisibleLine_;

	int option_;

	ScrollBar * scrollbar_;

	sf::Texture backgroundTexture_;

	const unsigned imageChangingDelay_ = 5000;

	unsigned lastImageChangingTime_;

	unsigned image_;

	unsigned imagesCount_;

	bool onEnter ();

	bool onClear ();

	bool onCtrl ();

	bool onCtrlShift ();

	bool onScroll (int delta);

	bool onUpArrow ();

	bool onDownArrow ();

	bool onTab ();

	void updateBounds ();

};

GameConsole::GameConsole (double x, double y, double width, double height, sf::RenderWindow * window) :

	x_                 (x),
	y_                 (y),

	width_             (width),
	height_            (height),

	font_              (*DefaultFont),

	background_        (0, 0, 0, 100),
	foreground_        (sf::Color::Green),
	curColor_          (128, 255, 128),
	highlightingColor_ (255, 255, 255, 100),

	window_            (window),

	editBox_           (x_, y_, width_, height_, font_, window),

	buffer_            (),

	visibleLinesCount_ (10),

	firstVisibleLine_  (0),

	option_            (-1),

	scrollbar_         (nullptr),

	backgroundTexture_ (),

	lastImageChangingTime_      (GetTickCount ()),

	image_             (0)

{

	imagesCount_ = 0;
	for (imagesCount_; backgrounds[imagesCount_]; imagesCount_++);
	imagesCount_ --;

	sf::Image image;
	image.loadFromFile (backgrounds[image_]);

	setBackgroundImage (image);

}

//----------------------------------------------------------------

class ScrollBar 

{

public :

	ScrollBar (double x, double y, double width, double height, int value, int minvalue, int maxvalue, sf::RenderWindow * window);

	ScrollBar (GameConsole & console);

	void setPosition (double x, double y)

	{
	
		x_ = x;
		y_ = y;
	
	}

	void setSize (double width, double height)

	{
	
		width_ = width;
		height_ = height;

	}

	void setValue (int value) 
		
	{

		value_ = value;

		if (console_) console_ -> setFirstVisibleLine (value_);

	}

	void setMaxvalue (int value) 
		
	{

		maxvalue_ = value;

	}

	void setMinvalue (int value)

	{
	
		minvalue_ = value;

	}

	void setBackgroundColor (sf::Color color)

	{
	
		color1_ = color;

	}

	void setForegroundColor (sf::Color color)

	{
	
		color2_ = color;

	}

	void setWindow (sf::RenderWindow * window)

	{
	
		window_ = window;

	}

	void addValue (int value)

	{
	
		if (value_ + value <= maxvalue_ && value_ + value >= minvalue_) value_ += value;
		 
		if (console_) console_ -> setFirstVisibleLine (value_);

	}

	void setConsolePtr (GameConsole * console)

	{
	
		console_ = console;

	}

	int getValue ()

	{
	
		return value_;

	}

	void setBounds (sf::FloatRect bounds)

	{
	
		x_ = bounds.left;
		y_ = bounds.top;

		width_ = bounds.width;
		height_ = bounds.height;

	}

	sf::FloatRect getBounds ()

	{
	
		return sf::FloatRect (x_, y_, width_, height_);

	}

	void draw ();

	bool onMouseClick (const sf::Event & event);

    void update ();

private :

	double x_;
	double y_;

	double width_;
	double height_;

	int value_;
	int maxvalue_;
	int minvalue_;

	sf::Color color1_;
	sf::Color color2_;

	sf::RenderWindow * window_;

	int lastClicked_;

	const int clickDelay_ = 50;

	bool wasSliderPressed_;
	sf::Vector2i lastMousePosition_;

	GameConsole * console_;

};

ScrollBar::ScrollBar (double x, double y, double width, double height, int value, int minvalue, int maxvalue, sf::RenderWindow * window) :

	x_ (x),
	y_ (y),

	width_  (width),
	height_ (height),

	value_    (value),
	maxvalue_ (maxvalue),
	minvalue_ (minvalue),

	color1_ (sf::Color::White),
	color2_ (sf::Color (0, 150, 255)),

	window_ (window),

	lastClicked_ (0),

	wasSliderPressed_ (false),
	lastMousePosition_ (0, 0),

	console_ (nullptr)

{}

ScrollBar::ScrollBar (GameConsole & console) :

	x_ (0),
	y_ (0),

	width_  (10),
	height_ (0),

	value_    (0),
	maxvalue_ (0),
	minvalue_ (0),

	color1_ (sf::Color (40, 40, 40, 100)),
	color2_ (sf::Color (0, 150, 255)),

	window_ (console.getWindow ()),

	lastClicked_ (0),

	wasSliderPressed_ (false),
	lastMousePosition_ (0, 0),

	console_ (nullptr)

{

	console.attachScrollbar (*this);

}

/*struct intRect 

{

	int x_, y_, width_, height_;

	operator sf::IntRect () 

	{
	
		return {x_, y_, width_, height_};

	}

};

sf::IntRect rect = intRect {1, 1, 1, 1};*/

//----------------------------------------------------------------

int GetTextSizeX (sf::Text & text, int n);

bool ProcessGameConsoleEvents (const sf::Event & event, GameConsole & console);

bool ProcessScrollBarEvents (const sf::Event & event, ScrollBar & scrollbar);

std::string GetClipboardText ();

bool RectCollision (sf::IntRect rect1, sf::IntRect rect2);

//----------------------------------------------------------------

int main ()

{
	srand (time(0));

	sf::Font font;
	font.loadFromFile ("consola.ttf");

	DefaultFont = &font;

	sf::RenderWindow window (sf::VideoMode (wWidth, wHeight), "GameConsole");

	window.setFramerateLimit (60);

	GameConsole console (0, (int) 800 - (int) 440, 800, 40, &window);
	console.setVisibleLinesCount (10);
	
	sf::Image image;
	image.loadFromFile ("background.png");

	console.setBackgroundImage (image);

	ScrollBar scrollbar (console);

	while (window.isOpen ())

	{

		window.clear (sf::Color (40, 40, 40));

		sf::Event event;

		while (window.pollEvent (event))

		{

			if (event.type == sf::Event::Closed) console.print ("THERE IS NO EXIT!!!\n");

			ProcessScrollBarEvents (event, scrollbar);
			ProcessGameConsoleEvents (event, console);

		}

		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)) window.close ();

		console.draw ();

		scrollbar.update ();

		scrollbar.draw ();

		window.display ();

	}

}

//----------------------------------------------------------------

int EventHandler::addObject (EditBox * object)

{

	for (int n = 0; n < OBJ_MAX; n++)

	{
	
		if (objects_[n]) continue;

		objects_[n] = object;

		return n;

	}

	return -1;

}

//----------------------------------------------------------------

int EventHandler::removeObject (EditBox * object)

{

	for (int n = 0; n < OBJ_MAX; n++)

	{
	
		if (objects_[n] == object) 

		{
		
			objects_[n] = nullptr;

			delete (object);

			return n;

		}

	}

	return -1;

}

//----------------------------------------------------------------

void EventHandler::processEvents (const sf::Event & event)

{

	if (event.type == sf::Event::KeyPressed) 

		for (int n = 0; n < OBJ_MAX; n++)

		{
		
			if (!objects_[n]) continue;

			if (objects_[n] -> onKeyPressed (event)) break;

		}

	if (event.type == sf::Event::TextEntered)

		for (int n = 0; n < OBJ_MAX; n++)

		{
		
			if (!objects_[n]) continue;

			if (objects_[n] -> onTextEntered (event)) break; 

		}

}

//----------------------------------------------------------------

void EditBox::draw ()

{

	sf::RectangleShape rect;
	rect.setFillColor (background_);
	rect.setPosition (x_, y_);
	rect.setSize (sf::Vector2f (width_, height_));

	window_ -> draw (rect);

	sf::Text text;
	text.setString (line_);
	text.setFillColor (foreground_);
	text.setFont (font_);
	text.setPosition (x_ + 2, y_);
	text.setCharacterSize (height_ - 4);

	window_ -> draw (text);


	if (blinkCounter_ > blink_counter_limit_ / 2)

	{

		sf::RectangleShape rect;

		if (insertMode_)

		{

			rect.setFillColor (highlightingColor_);
			rect.setSize (sf::Vector2f (GetTextSizeX (text, cursorPos_ + 1) - GetTextSizeX (text, cursorPos_), text.getCharacterSize ()));
			rect.setPosition (x_ + GetTextSizeX (text, cursorPos_) + 4, y_ + 2);

		}

		else

		{

			rect.setFillColor (curColor_);
			rect.setPosition (x_ + GetTextSizeX (text, cursorPos_) + 4, y_ + 2);
			rect.setSize (sf::Vector2f (2, text.getCharacterSize ()));

		}

		window_ -> draw (rect);

	}

	blinkCounter_ ++;

	if (blinkCounter_ > blink_counter_limit_) blinkCounter_ = 0;

}

//----------------------------------------------------------------

bool EditBox::onKeyPressed (const sf::Event & event)

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::BackSpace)) if (onBackspace ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Delete))    if (onDelete    ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))      if (onArrow   (-1)) return true;
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))     if (onArrow    (1)) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Insert))    if (onInsert    ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Home))      if (onHome      ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::End))       if (onEnd       ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Enter))     if (onEnter     ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LControl))  if (onCtrl      ()) return true;

	return false;

}

//----------------------------------------------------------------

bool EditBox::onTextEntered (const sf::Event & event)

{

	if (onKeyEntered (event.key.code)) return true;

	return false;

}

//----------------------------------------------------------------

bool EditBox::onKeyEntered (char key)

{

	if (key <= '~' && ' ' <= key) 
		
	{

		if (insertMode_) line_.replace (cursorPos_, 1, 1, key);

		else             line_.insert  (cursorPos_, 1,    key);

		if (cursorPos_ < line_.length ()) cursorPos_ ++;

		return true;

	}

	return false;

}

//----------------------------------------------------------------

bool EditBox::onBackspace ()

{

	if (!line_.empty ()) 
			
		{

			line_.erase (cursorPos_ - 1, 1);

			cursorPos_ --;

			return true;

		}

	return false;

}

//----------------------------------------------------------------

bool EditBox::onDelete ()

{

	if (cursorPos_ < line_.length ())

	{
	
		line_.erase (cursorPos_, 1);

		return true;

	}

	return false;

}

//----------------------------------------------------------------

bool EditBox::onArrow (int arg)

{

	if (arg > 0)

		if (cursorPos_ < line_.length ()) 
			
		{

			cursorPos_ ++;
				
			return true;

		}

	if (arg < 0) 

		if (cursorPos_ > 0) 
			
		{

			cursorPos_ --;

			return true;

		}

	return false;

}

//----------------------------------------------------------------

bool EditBox::onInsert ()

{

	insertMode_ = !insertMode_;

	return true;

}

//----------------------------------------------------------------

bool EditBox::onHome ()

{

	cursorPos_ = 0;

	return true;

}

//----------------------------------------------------------------

bool EditBox::onEnd ()

{

	cursorPos_ = line_.length ();

	return true;

}

//----------------------------------------------------------------

bool EditBox::onEnter ()

{

	printf ("%s\n", line_.c_str ());

	line_.clear ();
	cursorPos_ = 0;

	return true;

}

//----------------------------------------------------------------

bool EditBox::onPaste ()

{

	std::string text = GetClipboardText ();

	insertString (text.c_str ());

	return true;

}

//----------------------------------------------------------------

bool EditBox::onCtrl ()

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LShift)) if (onCtrlShift ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::V))      if (onPaste     ()) return true;

	return false;

}

//----------------------------------------------------------------

bool EditBox::onCtrlShift ()

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::R)) if (onRandomString ()) return true;

	return false;

}

//----------------------------------------------------------------

bool EditBox::onRandomString ()

{

	char str [MAXLINE] = "";

	int len = floor (eu::rnd (1, 50));

	for (int i = 0; i < len; i++) str[i] = floor (eu::rnd (' ', '~'));

	insertString (str);

	return true;

}

//----------------------------------------------------------------

void EditBox::insertString (const char * str)

{

	line_.insert (cursorPos_, str);

	cursorPos_ += strlen (str);

}

//----------------------------------------------------------------

void EditBox::setBackgroundColor (sf::Color color)

{

	background_ = color;

}

//----------------------------------------------------------------

void EditBox::setForegroundColor (sf::Color color)

{

	foreground_ = color;

}

//----------------------------------------------------------------

void EditBox::setCursorColor (sf::Color color)

{

	curColor_ = color;

}

//----------------------------------------------------------------

void EditBox::setHighlightningColor (sf::Color color)

{

	highlightingColor_ = color;

}

//----------------------------------------------------------------

void EditBox::setString (const char * str)

{

	line_ = str;

	cursorPos_ = line_.length ();

}

//----------------------------------------------------------------

void EditBox::setFont (sf::Font font)

{

	font_ = font;

}

//----------------------------------------------------------------

void EditBox::setWindow (sf::RenderWindow & window)

{

	window_ = &window;

}

//----------------------------------------------------------------

const char * EditBox::getString ()

{

	return line_.c_str ();

}

//----------------------------------------------------------------

void EditBox::clear ()

{
	
	setString ("");

}

//----------------------------------------------------------------

void EditBox::setPosition (double x, double y)

{

	x_ = x;
	y_ = y;

}

//----------------------------------------------------------------

void GameConsole::draw ()

{

	sf::Vector2u size = backgroundTexture_.getSize ();

	sf::Sprite sprite;
	sprite.setTexture (backgroundTexture_);
	sprite.setPosition (x_, y_);
	sprite.setScale (width_ / size.x, height_ * (visibleLinesCount_ + 1) / size.y);

	window_ -> draw (sprite);

	for (int n = 0; n < visibleLinesCount_; n++)

	{
	
		double line_x = x_;
		double line_y = y_ + height_ * (visibleLinesCount_ - (n + 1));

		sf::RectangleShape rect;
		rect.setFillColor (background_);
		rect.setPosition (line_x, line_y);
		rect.setSize (sf::Vector2f (width_, height_));
		 
		window_ -> draw (rect);

		sf::Text text;
		text.setString (buffer_.getLine (firstVisibleLine_ + n));
		text.setFillColor (foreground_);
		text.setFont (font_);
		text.setPosition (line_x + 2, line_y + 2);
		text.setCharacterSize (height_ - 4);

		window_ -> draw (text);

	}
	
	editBox_.setPosition (x_, y_ + visibleLinesCount_ * height_);
	editBox_.draw ();

	if (scrollbar_) scrollbar_ -> draw ();

	if (GetTickCount () - lastImageChangingTime_ >= imageChangingDelay_)

	{

		lastImageChangingTime_ = GetTickCount ();
	
		image_ ++;

		if (image_ > imagesCount_) image_ = 0;

		sf::Image image;
		image.loadFromFile (backgrounds[image_]);

		setBackgroundImage (image);

	}

}

/*template <typename T, int MAXLINE>
constexpr size_t test (const T (& arr)[MAXLINE])

{

	return MAXLINE;

}

template <typename T>
constexpr size_t test (const T * arr)

{

	assert (!"Моя кошка прогает лучше тебя.........");
	return 0;

}

int arr[123] = {};

size_t size = test (arr);

int * arr2 = arr;

size_t size2 = test (arr2);*/

//----------------------------------------------------------------

bool GameConsole::onTextEntered (const sf::Event & event)

{

	option_ = -1;

	if (scrollbar_) scrollbar_ -> update ();

	return editBox_.onTextEntered (event);

}

//----------------------------------------------------------------

bool GameConsole::onKeyPressed (const sf::Event & event)

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Enter))    if (onEnter     ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LControl)) if (onCtrl      ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))       if (onUpArrow   ()) return true;
	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))     if (onDownArrow ()) return true;

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::Tab))      if (onTab       ()) return true;

	if (scrollbar_) scrollbar_ -> update ();

	return editBox_.onKeyPressed (event);

}

//----------------------------------------------------------------

bool GameConsole::onMouseWheel (const sf::Event & event)

{



	int delta = event.mouseWheel.delta;

	if (scrollbar_) scrollbar_ -> update ();

	if (onScroll (delta)) return true;

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onScroll (int delta)

{

	if (firstVisibleLine_ + delta >= 0 && firstVisibleLine_ + delta + visibleLinesCount_ < LINES)

	{

		firstVisibleLine_ += delta;

		if (scrollbar_) scrollbar_ -> setValue (firstVisibleLine_);

		return true;

	}

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onUpArrow ()

{

	if (option_ < LINES - 1)

	{

		option_++;
		setString (buffer_.getLine (option_));

		return true;

	}

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onDownArrow ()

{

	if (option_ > 0)

	{

		option_ --;
		setString (buffer_.getLine (option_));

		return true;

	}

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onEnter ()

{

	if (eu::fileExists (getString ()))

	{
	
		sf::Image image;
		image.loadFromFile (getString ());

		setBackgroundImage (image);

	}

	print (getString ());
	setString ("");

	return true;

}

//----------------------------------------------------------------

bool GameConsole::onClear ()

{

	clear ();

	return true;

}

//----------------------------------------------------------------

bool GameConsole::onCtrl ()

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::LShift)) if (onCtrlShift ()) return true;

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onCtrlShift ()

{

	if (sf::Keyboard::isKeyPressed (sf::Keyboard::C)) if (onClear ()) return true;

	return false;

}

//----------------------------------------------------------------

bool GameConsole::onTab ()

{

	if (option_ >= 0)
		
	{

		option_ = -1;
		setString ("");

		return true;

	}

	return false;

}

//----------------------------------------------------------------

void GameConsole::setBackgroundColor (sf::Color color)

{

	background_ = color;
	editBox_.setBackgroundColor (color);

}

//----------------------------------------------------------------

void GameConsole::setForegroundColor (sf::Color color)

{

	foreground_ = color;
	editBox_.setForegroundColor (color);

}

//----------------------------------------------------------------

void GameConsole::setCursorColor (sf::Color color)

{

	curColor_ = color;
	editBox_.setCursorColor (color);

}

//----------------------------------------------------------------

void GameConsole::setHighlightningColor (sf::Color color)

{

	highlightingColor_ = color;
	editBox_.setHighlightningColor (color);

}

//----------------------------------------------------------------

void GameConsole::setFont (sf::Font font)

{

	font_ = font;

	updateBounds ();

}

//----------------------------------------------------------------

void GameConsole::setString (const char * str)

{

	editBox_.setString (str);

}

//----------------------------------------------------------------

void GameConsole::setWindow (sf::RenderWindow & window)

{

	window_ = &window;
	editBox_.setWindow (window);

}

//----------------------------------------------------------------

void GameConsole::setVisibleLinesCount (unsigned count)

{

	if (count <= LINES)	visibleLinesCount_ = count;

	updateBounds ();

}

//----------------------------------------------------------------

const char * GameConsole::getString ()

{

	return editBox_.getString ();

}

//----------------------------------------------------------------

void GameConsole::print (const char * str)

{

	buffer_.addLine (str);

}

//----------------------------------------------------------------

void GameConsole::clear ()

{

	buffer_.clear ();
	editBox_.clear ();

}

//----------------------------------------------------------------

void GameConsole::attachScrollbar (ScrollBar & scrollBar)

{
	
	scrollbar_ = &scrollBar;
	scrollbar_ -> setConsolePtr (this);

	updateBounds ();

}

//----------------------------------------------------------------

void GameConsole::updateBounds ()

{

	if (scrollbar_)

	{

		sf::FloatRect bounds = scrollbar_ -> getBounds ();

		scrollbar_ -> setBounds (sf::FloatRect (x_ + width_ - bounds.width, y_, bounds.width, (getVisibleLinescount () + 1) * height_));
		scrollbar_ -> setMaxvalue (LINES - getVisibleLinescount ());

	}

	editBox_.setBounds (sf::FloatRect (x_, y_, width_, height_));
	editBox_.setFont (font_);

}

//----------------------------------------------------------------

void ScrollBar::draw ()

{

	sf::RectangleShape rect;
	rect.setFillColor (color1_);
	rect.setSize (sf::Vector2f (width_, height_));
	rect.setPosition (x_, y_);

	window_ -> draw (rect);
	 
	double height = (height_ / (maxvalue_ - minvalue_));

	rect.setFillColor (color2_);
	rect.setSize (sf::Vector2f (width_, height));
	rect.setPosition (x_, y_ + height_ - height * (value_ + 1));

	window_ -> draw (rect);

}

//----------------------------------------------------------------

void ScrollBar::update ()

{

	if (sf::Mouse::isButtonPressed (sf::Mouse::Left))

	{

		sf::Vector2i mPos = sf::Mouse::getPosition (*window_);

		if (RectCollision (sf::IntRect (x_, y_ + height_ - height_ / (maxvalue_ - minvalue_) * (value_ + 1), width_, height_ / (maxvalue_ - minvalue_)), sf::IntRect (mPos.x, mPos.y, 1, 1)))

		{

			if (wasSliderPressed_)

			{
			
				addValue ((mPos.y - lastMousePosition_.y) / height_ * (maxvalue_ - minvalue_));

			}

			wasSliderPressed_ = true;
			lastMousePosition_ = mPos;

		}

		else if (RectCollision (sf::IntRect (x_, y_, width_, height_), sf::IntRect (mPos.x, mPos.y, 1, 1)))

		{

			if (GetTickCount () - lastClicked_ >= clickDelay_)

			{

				lastClicked_ = GetTickCount ();

				if (mPos.y < y_ + height_ - (height_ / (maxvalue_ - minvalue_)) * (value_ + 1)) addValue (1);

				else addValue (-1);

			}

			wasSliderPressed_ = false;

		}

		else wasSliderPressed_ = false;

	}

	else wasSliderPressed_ = false;

}

//----------------------------------------------------------------

bool ScrollBar::onMouseClick (const sf::Event & event)

{

	return false;

}

//----------------------------------------------------------------

int GetTextSizeX (sf::Text & text, int n)

{

	std::string line = text.getString ();
	char * str = (char*) line.c_str ();

	if (n > line.length ()) line += ' ';

	char c = str[n];
	str[n] = '\0';

	text.setString (str);

	sf::FloatRect bounds = text.getGlobalBounds ();

	str[n] = c;

	return bounds.width;

}

//----------------------------------------------------------------

bool ProcessGameConsoleEvents (const sf::Event & event, GameConsole & console)

{

	if (event.type == sf::Event::TextEntered)     if (console.onTextEntered (event)) return true;

	if (event.type == sf::Event::KeyPressed)      if (console.onKeyPressed  (event)) return true;

	if (event.type == sf::Event::MouseWheelMoved) if (console.onMouseWheel  (event)) return true;

	return false;

}

//----------------------------------------------------------------

bool ProcessScrollBarEvents (const sf::Event & event, ScrollBar & scrollbar)

{

	if (event.type == sf::Event::MouseButtonPressed) if (scrollbar.onMouseClick (event)) return true;

	return false;

}

//----------------------------------------------------------------

std::string GetClipboardText ()

{

  assert (OpenClipboard (nullptr));

  HANDLE hData = GetClipboardData (CF_TEXT);
  assert (hData);

  std::string text = "";

  text = (const char *) GlobalLock (hData);

  GlobalUnlock (hData);

  CloseClipboard ();

  return text;

}

//----------------------------------------------------------------

bool RectCollision (sf::IntRect rect1, sf::IntRect rect2)

{

	return rect2.left >= rect1.left && rect2.top >= rect1.top && rect2.left < rect1.left + rect1.width && rect2.top < rect1.top + rect1.height;

}