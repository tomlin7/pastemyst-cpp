#include "pch.h"
#include "CppUnitTest.h"

#include <map>
#include <iostream>
#include "../pastemyst/pastemyst.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pastemysttests
{
    // Sample PasteCreateInfo for public paste creation
    const auto newPublicPasteContent = R"(
        {
            "title": "pastemysttest",
            "expiresIn": "1h",
            "isPrivate": false,
            "isPublic": false,
            "tags": "pastemyst, test",
            "pasties": [
                {
                    "title": "testpublicpaste",
                    "language": "Autodetect",
                    "code": "test public paste content"
                }
            ]
        }
    )";
    
    // Sample PasteCreateInfo for private paste creation
    const auto newPrivatePasteContent = R"(
        {
            "title": "pastemystcpptest",
            "expiresIn": "1h",
            "isPrivate": true,
            "isPublic": false,
            "tags": "pastemyst, test",
            "pasties": [
                {
                    "title": "testprivatepaste",
                    "language": "Autodetect",
                    "code": "test private paste content"
                }
            ]
        }
    )";

    // Sample public profile
    const auto sampleUsername = "billyeatcookies";

	TEST_CLASS(pastemysttests)
	{
	public:
		// Creating the backend client and authorizing
        Client client = Client("token");

        TEST_METHOD(TestPasteEndpoint)
		{
            // PasteExists
            auto pasteExists = client.PasteExists("99is6n23");
			Assert::IsTrue(pasteExists);

            // GetPaste
            if (pasteExists)
            {
                std::string expectedTitle = "public paste example title";
                std::string expectedExpiresIn = "never";
                auto fetchedPaste = client.GetPaste("99is6n23");
                Assert::AreEqual(expectedTitle, fetchedPaste["title"].get<std::string>());
                Assert::AreEqual(expectedExpiresIn, fetchedPaste["expiresIn"].get<std::string>());
            }
			
            // CreatePaste Public
            json newPublicPaste = client.CreatePaste(newPublicPasteContent);
            std::string expectedTitle = "pastemysttest";
            std::string expectedExpiresIn = "1h";
            Assert::AreEqual(expectedTitle, newPublicPaste["title"].get<std::string>());
            Assert::AreEqual(expectedExpiresIn, newPublicPaste["expiresIn"].get<std::string>());

            if(client.IsAuthorized())
            {
                // CreatePaste Private
                json newPrivatePaste = client.CreatePaste(newPrivatePasteContent);
                auto newPasteID = newPrivatePaste["_id"].get<std::string>();
                expectedTitle = "pastemystcpptest";
                expectedExpiresIn = "1h";
                Assert::AreEqual(expectedTitle, newPrivatePaste["title"].get<std::string>());
                Assert::AreEqual(expectedExpiresIn, newPrivatePaste["expiresIn"].get<std::string>());
                Assert::IsTrue(newPrivatePaste["isPrivate"].get<bool>());

                // EditPaste
                /*newPrivatePaste = client.EditPaste(newPasteID, pasteEditContent);
                newPasteID = newPrivatePaste["_id"].get<std::string>();
                expectedTitle = "pastemystcpptestedit";
                expectedExpiresIn = "2h";
                Assert::AreEqual(expectedTitle, newPrivatePaste["title"].get<std::string>());
                Assert::AreEqual(expectedExpiresIn, newPrivatePaste["expiresIn"].get<std::string>());*/

                // DeletePaste
                auto pasteDeleted = client.DeletePaste(newPasteID);
                Assert::IsTrue(pasteDeleted);
            }
		}

        TEST_METHOD(TestUserEndpoint)
		{
            // UserExists
            auto userExists = client.UserExists(sampleUsername);
            Assert::IsTrue(userExists);

            if(userExists)
            {
                // GetUser
                auto fetchedProfile = client.GetUser(sampleUsername);
                Assert::AreEqual(std::string("billyeatcookies"), fetchedProfile["username"].get<std::string>());
                Assert::IsFalse(fetchedProfile["contributor"].get<bool>());
            }

            if(client.IsAuthorized())
            {
                // GetSelfUser
                auto fetchedSelfProfile = client.GetSelfUser();
                Assert::AreEqual(std::string("billyeatcookies"), fetchedSelfProfile["username"].get<std::string>());
                Assert::IsFalse(fetchedSelfProfile["contributor"].get<bool>());
            }
        }

        TEST_METHOD(TestDataEndpoint)
		{
            // GetLanguageByName
            auto fetchedLanguageUsingName = client.GetLanguageByName("C++");
            Assert::AreEqual(std::string("C++"), fetchedLanguageUsingName["name"].get<std::string>());
            Assert::AreEqual(std::string("clike"), fetchedLanguageUsingName["mode"].get<std::string>());

            // GetLanguageByExtension
            auto fetchedLanguageUsingExt = client.GetLanguageByExtension("cpp");
            Assert::AreEqual(std::string("C++"),fetchedLanguageUsingExt["name"].get<std::string>());
            Assert::AreEqual(std::string("clike"), fetchedLanguageUsingExt["mode"].get<std::string>());
        }

        TEST_METHOD(TestTimeEndpoint)
		{
            // ExpiresInToUnixTimestamp
            std::map<std::pair<unsigned long, std::string>, unsigned long> timeTests {
                {{1615242814, "2h"}, 1615250014},
                {{1615121479, "1d"}, 1615207879},
                {{1615297946, "1w"}, 1615902746},
                {{1588441258, "1w"}, 1589046058}
            };
            for (const auto& p : timeTests) 
            {
                auto fetchedTimestamp = client.ExpiresInToUnixTimestamp(p.first.first, p.first.second);
                Assert::AreEqual(fetchedTimestamp, p.second);
            }
        }
	};
}