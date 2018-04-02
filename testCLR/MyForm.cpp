#include <stdio.h>
#include <iostream>
#include "MyForm.h"

using namespace System::IO;
using namespace System;
using namespace System::Windows::Forms;

class Songs
{
public:
	int id;
	string title;
	string artist;
	string album;
	string duration;
	string location;
	string songLocation;
	string lyricsLocation;

	Songs(int _id, string _title, string _artist, string _album, string _duration, string _location, string _songLocation, string _lyricsLocation)
	{
		id = _id;
		title = _title;
		artist = _artist;
		album = _album;
		duration = _duration;
		location = _location;
		songLocation = _songLocation;
		lyricsLocation = _lyricsLocation;
	}
};

int Main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	testCLR::MyForm form;
	Application::Run(%form);

	return 0;
}