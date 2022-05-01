#include "pch.h"
#include "CppUnitTest.h"
#include <istream>
#include "../Project_1/Workflow.h"
#include "../Project_1/FileManager.h"
#include "../Project_1/Mapper.h"
#include "../Project_1/Sorter.h"
#include "../Project_1/Reducer.h"
#include "../Project_1/Workflow.cpp"
#include "../Project_1/FileManager.cpp"
#include "../Project_1/Mapper.cpp"
#include "../Project_1/Sorter.cpp"
#include "../Project_1/Reducer.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Project1Test
{

	TEST_CLASS(Project1Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Workflow workflow;
			string input("C:\\Users\\aurel\\source\\repos\\CSE_687\\Input_Text");
			string temp("C:\\Users\\aurel\\source\\repos\\CSE_687\\Temp_Text");
			string output("C:\\Users\\aurel\\source\\repos\\CSE_687\\Output_Text");

			// Call Workflow class and pass the user-designated file paths.
			workflow.workflow(input, temp, output);
			
		}

		TEST_METHOD(TestMethod2)
		{
			FileManager filemanager;
			string filename("output.txt");
			string inputpath("C:\\Users\\aurel\\source\\repos\\CSE_687\\Input_Text");
			string temppath("C:\\Users\\aurel\\source\\repos\\CSE_687\\Temp_Text");
			string outputpath("C:\\Users\\aurel\\source\\repos\\CSE_687\\Output_Text");
			string mappedstring("");
			string outputstring("");
			
			// Test every FileManager method.
			filemanager.opentxtfile(inputpath);
			filemanager.createtempfile(temppath);
			filemanager.writetotemp(temppath, mappedstring);
			filemanager.createsortedfile(temppath);
			filemanager.readtempfile(temppath);
			filemanager.writetosortedfile(temppath, mappedstring);
			filemanager.createoutputfile(outputpath, filename);
			filemanager.readsortedfile(temppath);
			filemanager.writetooutput(outputpath, filename, outputstring);
			filemanager.deletetemp(temppath);
		}

	};
}
