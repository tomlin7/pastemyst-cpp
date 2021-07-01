#include "pch.h"
#include "CppUnitTest.h"

#include <map>
#include <iostream>
#include "../pastemyst/pastemyst.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace pastemysttests
{
    // Sample Pasties
    const std::vector<PastyCreateInfo> newTestPasties {
        {
            "New Test Pasty Title",
            "New Test Pasty Content",
            "AutoDetect"
        },
        {
            "New Second Test Pasty Title",
            "New Second Test Pasty Content",
            "AutoDetect"
        }
        // ... 
    };


    // Sample PasteCreateInfo for public paste creation
    PasteCreateInfo newTestPublicPaste {
        "pastemystcpptest-public", "1h", false, false,
        "pastemyst, test", newTestPasties
    };

    // Sample PasteCreateInfo for private paste creation
    PasteCreateInfo newTestPrivatePaste = {
        "pastemystcpptest-private", "1h", true, false,
        "pastemyst, test", newTestPasties
    };

    // Sample public profile
    const auto sampleUsername = "billyeatcookies";

    TEST_CLASS(pastemysttests)
    {
    public:
        // Creating the backend client and authorizing
        Client client = Client("P9Q1UqWyJusxiqO3bsgDXnWFH/etNE3Jzoq7gRLoSfI=");

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
                Assert::AreEqual(expectedTitle, fetchedPaste.title);
                Assert::AreEqual(expectedExpiresIn, fetchedPaste.expiresIn);
            }

            // CreatePaste Public
            auto newPublicPaste = client.CreatePaste(newTestPublicPaste);
            std::string expectedTitle = "pastemystcpptest-public";
            std::string expectedExpiresIn = "1h";
            Assert::AreEqual(expectedTitle, newPublicPaste.title);
            Assert::AreEqual(expectedExpiresIn, newPublicPaste.expiresIn);

            if (client.IsAuthorized())
            {
                // CreatePaste Private
                auto newPrivatePaste = client.CreatePaste(newTestPrivatePaste);
                auto newPasteID = newPrivatePaste._id;
                expectedTitle = "pastemystcpptest-private";
                expectedExpiresIn = "1h";
                Assert::AreEqual(expectedTitle, newPrivatePaste.title);
                Assert::AreEqual(expectedExpiresIn, newPrivatePaste.expiresIn);
                Assert::IsTrue(newPrivatePaste.isPrivate);

                // EditPaste
                newPrivatePaste.title = "pastemystcpptestedit";
                newPrivatePaste = client.EditPaste(newPasteID, newPrivatePaste);
                newPasteID = newPrivatePaste._id;
                expectedTitle = "pastemystcpptestedit";
                Assert::AreEqual(expectedTitle, newPrivatePaste.title);

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

            if (userExists)
            {
                // GetUser
                auto fetchedProfile = client.GetUser(sampleUsername);
                Assert::AreEqual(std::string("billyeatcookies"), fetchedProfile.username);
                Assert::IsFalse(fetchedProfile.contributor);
            }

            if (client.IsAuthorized())
            {
                // GetSelfUser
                auto fetchedSelfProfile = client.GetSelfUser();
                Assert::AreEqual(std::string("billyeatcookies"), fetchedSelfProfile.username);
                Assert::IsFalse(fetchedSelfProfile.contributor);
            }
        }

        TEST_METHOD(TestDataEndpoint)
        {
            // GetLanguageByName
            auto fetchedLanguageUsingName = client.GetLanguageByName("C++");
            Assert::AreEqual(std::string("C++"), fetchedLanguageUsingName.name);
            Assert::AreEqual(std::string("clike"), fetchedLanguageUsingName.mode);

            // GetLanguageByExtension
            auto fetchedLanguageUsingExt = client.GetLanguageByExtension("cpp");
            Assert::AreEqual(std::string("C++"), fetchedLanguageUsingExt.name);
            Assert::AreEqual(std::string("clike"), fetchedLanguageUsingExt.mode);
        }

        TEST_METHOD(TestTimeEndpoint)
        {
            // ExpiresInToUnixTimestamp
            std::map<std::pair<unsigned long, std::string>, unsigned long> timeTests{
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