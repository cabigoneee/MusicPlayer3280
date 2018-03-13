#include <stdio.h>
#include <iostream>
#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;


int Main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	testCLR::MyForm form;
	Application::Run(%form);

	return 0;
}