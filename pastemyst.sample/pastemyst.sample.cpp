// pastemyst.sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
// NOTE: This is an example program showing all methods and how to use them correctly.

#include <iostream>
#include "../pastemyst/pastemyst.h"

// Comment this out if the extensive methods (e.g: GetSelfPastes, GetSelfPasteIDs)
// should NOT run.

// #define RUN_EXPENSIVE

// Sample private PasteCreateInfo
const auto newPasteContent = R"(
    {
        "isPrivate": true,
        "pasties": [
            {
                "title": "new private paste",
                "language": "Autodetect",
                "code": "new private paste content"
            }
        ]
    }
)";

const auto sampleUserName = "billyeatcookies";

int main()
{
    std::cout << "PasteMyst-CPP Example Project" << std::endl << std::endl;

    // Creating a new backend client.
    // can also do `Client client("token");`
    Client client;

    // If the Client is not authorized, it can be authorized,
    // using the `Authorize()` method.
    client.Authorize("d2PIZzNTOM3E6skD/5L/kELI27d3pQMwvT39MajT0GE=");

#pragma region PasteEndpointMethods

    // Checking whether a Paste exists.
    std::cout << "Checking whether a Paste exists Before Fetching" << std::endl
        << ((client.PasteExists("99is6n23"))
            ? "  Paste exists"
            : "  Paste doesn't exist")
        << std::endl;

    // Fetching a Paste.
    auto fetchedPaste = client.GetPaste("99is6n23");
    std::cout << "Fetching the Paste" << std::endl
        << "  Paste Title: " << fetchedPaste["title"].get<std::string>() << std::endl
        << "  Paste expiresIn: " << fetchedPaste["expiresIn"].get<std::string>()
        << std::endl;

    // Creating a new private Paste.
    json newPaste = client.CreatePaste(newPasteContent);
    auto newPasteID = newPaste["_id"].get<std::string>();
    std::cout << "Creating new private Paste" << std::endl
        << "  Created Paste ID: " << newPasteID << std::endl
        << "  Paste expiresIn: " << newPaste["expiresIn"].get<std::string>()
        << std::endl;

    //newPaste["title"] = "editedtitle";

    //// Editing the paste just created.
    //newPaste = client.EditPaste(newPasteID, newPaste);
    //newPasteID = newPaste["_id"].get<std::string>();
    //std::cout << "Editing the created private Paste" << std::endl
    //    << "  Edited Paste's ID: " << newPasteID << std::endl
    //    << "  Edited Paste's title: " << newPaste["title"].get<std::string>()
    //    << std::endl;

    // Deleting the created paste.
    std::cout << "Deleting the created-edited private Paste" << std::endl
        << ((client.DeletePaste(newPasteID))
            ? "  Paste Deleted Successfully"
            : "  Failed to Delete Paste")
        << std::endl;

#pragma endregion
#pragma region UserEndpointMethods

    // Checking whether a public user profile exists.
    std::cout << "Checking whether a public user profile exists Before Fetching" << std::endl
        << ((client.UserExists(sampleUserName))
            ? "  Profile exists"
            : "  Profile doesn't exist")
        << std::endl;

    // Fetching a public user profile.
    auto fetchedProfile = client.GetUser(sampleUserName);
    std::cout << "Fetching a public user profile" << std::endl
        << "  User Name: " << fetchedProfile["username"].get<std::string>() << std::endl
        << "  Is this user a contributor? " << fetchedProfile["contributor"].get<bool>()
        << std::endl;

    // Fetching the currently authorized user profile.
    auto fetchedSelfProfile = client.GetSelfUser();
    std::cout << "Fetching the currently authorized user profile" << std::endl
        << "  User Name: " << fetchedSelfProfile["username"].get<std::string>() << std::endl
        << "  Is this user a contributor? " << fetchedSelfProfile["contributor"].get<bool>()
        << std::endl;

#pragma endregion
#pragma region DataEndpointMethods

    // Fetching a language using it's name.
    auto fetchedLanguageUsingName = client.GetLanguageByName("C++");
    std::cout << "Fetching a language using it's name"
        << "  Language Name: " << fetchedLanguageUsingName["name"].get<std::string>() << std::endl
        << "  Language Mode: " << fetchedLanguageUsingName["mode"].get<std::string>()
        << std::endl;

    // Fetching a language using it's name.
    auto fetchedLanguageUsingExt = client.GetLanguageByExtension("cpp");
    std::cout << "Fetching a language using it's extension"
        << "  Language Name: " << fetchedLanguageUsingExt["name"].get<std::string>() << std::endl
        << "  Language Mode: " << fetchedLanguageUsingExt["mode"].get<std::string>()
        << std::endl;

#pragma endregion
#pragma region TimeEndpointFunction

    // Converting expiresIn value to a specific time 
    // when a paste should expire
    auto fetchedTimestamp = client.ExpiresInToUnixTimestamp(1615297946, "1w");
    std::cout << "Converting expiresIn value to a unix timestamp" << std::endl
        << "  Result: " << fetchedTimestamp
        << std::endl;

#pragma endregion

#ifdef RUN_EXPENSIVE

    // Expensive Methods
    // NOTE: These methods may take some time to complete
    // depending on some properties in your end.
#pragma region ExpensiveMethods

    std::vector<std::string> pasteIDs = { "asdfasdf", "hjklhjkl" };
    client.BulkDeletePastes(pasteIDs);

    // Remarks: Following are HEAVY methods depending on
    // the amount of pastes you have on your account
#pragma region HeavyMethods

    // Getting all pastes' IDs under the authorized user's account
    for (auto pasteID : client.GetSelfPasteIDs())
        std::cout << pasteID.get<std::string>() << std::endl;
    std::cout << std::endl;

    // Getting `amount` number of  pastes' IDs 
    // under the authorized user's account
    for (auto pasteID : client.GetSelfPasteIDsByAmount(2))
        std::cout << pasteID.get<std::string>() << std::endl;
    std::cout << std::endl;

    // Getting all pastes under the authorized user's account
    for (auto paste : client.GetSelfPastes())
        std::cout << paste["title"].get<std::string>() << std::endl;
    std::cout << std::endl;

    // Getting `amount` number of pastes 
    // under the authorized user's account
    for (auto paste : client.GetSelfPastesByAmount(2))
        std::cout << paste["title"].get<std::string>() << std::endl;
    std::cout << std::endl;

#pragma endregion
#pragma endregion
#endif // RUN_EXPENSIVE

    return 0;
}