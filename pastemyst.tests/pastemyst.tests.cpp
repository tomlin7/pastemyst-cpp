#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pastemysttests
{
	TEST_CLASS(pastemysttests)
	{
	public:
		
		TEST_METHOD(TestPasteEndpoint)
		{
			Client client;
			std::string expectedTitle = "Public Paste Example";
			std::string pasteTitle = client.GetPaste("oebww9n2")["title"];

			Assert::AreEqual(expectedTitle, pasteTitle);
		}
	};
}