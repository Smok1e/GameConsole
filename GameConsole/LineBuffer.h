#pragma once

class LineBuffer

{

public :

	LineBuffer ();

	void addLine (const std::string & line);

	const char * getLine (unsigned n);

	void clear ();

private :

	std::string lines_[LINES];

};

LineBuffer::LineBuffer () :

	lines_ ()

{}

//----------------------------------------------------------------

void LineBuffer::addLine (const std::string & line)

{

	for (int n = LINES - 1; n > 0; n--) lines_[n] = lines_[n - 1];

	lines_[0] = line;

}

//----------------------------------------------------------------

const char * LineBuffer::getLine (unsigned n)

{

	assert (n < LINES);

	return lines_[n].c_str ();

}

//----------------------------------------------------------------

void LineBuffer::clear ()

{

	for (int n = 0; n < LINES; n++) lines_[n].clear ();

}