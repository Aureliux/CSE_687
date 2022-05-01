#include "pch.h"
#include "CppUnitTest.h"
#include "..\Project_1\Workflow.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Project1Test
{

	TEST_CLASS(Project1Test)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string input = "c:\\User\\aturel\\source\\repos\\CSE_687\\Input.txt";
			std::string temp = "c:\\User\\aturel\\source\\repos\\CSE_687\\Input.txt";
			std::string output = "c:\\User\\aturel\\source\\repos\\CSE_687\\Input.txt";
			Workflow.workflow( input, temp, output );
		}
	};
}
