// pastemyst.sample.cpp : This file contains the 'main' function. Program execution begins and ends here.


// NOTE: This is an example program showing all methods and how to use them correctly.

#include <iostream>
#include "../pastemyst/pastemyst.h"

// Comment out the following line if the extensive methods (e.g: GetSelfPastes, GetSelfPasteIDs)
// should NOT run.

// #define RUN_EXPENSIVE

// Sample PastyCreateInfo
const std::vector<PastyCreateInfo> newSamplePasties {
    {
        "New Sample Pasty Title",
        "New Sample Pasty Content",
        "AutoDetect"
    },
    {
        "New Second Sample Pasty Title",
        "New Second Sample Pasty Content",
        "AutoDetect"
    }
    // ... 
};

// Sample private PasteCreateInfo
PasteCreateInfo newSamplePasteCreateInfo{
    "New Sample Paste Title", "1h",
    true, false, "sample, private, paste",
    newSamplePasties
};

// Sample pastemyst username
const auto sampleUserName = "billyeatcookies";

int main()
{
    std::cout << "PasteMyst-CPP Example Project" << std::endl << std::endl;

    // Creating a new backend client instance.
    // can also do `Client client("token");`
    Client client;

    // If the Client is not authorized, it can be authorized using the `Authorize()` method.
    // NOTE: Replace the token with your pastemyst token, https://paste.myst.rs/user/settings
    client.Authorize("token here");

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
        << "  Paste Title: " << fetchedPaste.title << std::endl
        << "  Paste expiresIn: " << fetchedPaste.expiresIn
        << std::endl;

    //try {
    //    auto newPaste = client.test(newSamplePasteCreateInfo);
    //}
    //catch (nlohmann::detail::type_error e) {
    //    std::cout << e.what() << std::endl;
    //}
    
    // std::cout << newPaste.text;

    // Creating a new private Paste.
    auto newPaste = client.CreatePaste(newSamplePasteCreateInfo);
    auto newPasteID = newPaste._id;
    std::cout << "Creating new private Paste" << std::endl
        << "  Created Paste ID: " << newPasteID << std::endl
        << "  Paste expiresIn: " << newPaste.expiresIn
        << std::endl;

    newPaste.title = "editedtitle";

    // Editing the paste just created.
    newPaste = client.EditPaste(newPasteID, newPaste);
    newPasteID = newPaste._id;
    std::cout << "Editing the created private Paste" << std::endl
        << "  Edited Paste's ID: " << newPasteID << std::endl
        << "  Edited Paste's title: " << newPaste.title
        << std::endl;

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
        << "  User Name: " << fetchedProfile.username << std::endl
        << "  Is this user a contributor? " << fetchedProfile.contributor
        << std::endl;

    // Fetching the currently authorized user profile.
    auto fetchedSelfProfile = client.GetSelfUser();
    std::cout << "Fetching the currently authorized user profile" << std::endl
        << "  User Name: " << fetchedSelfProfile.username << std::endl
        << "  Is this user a contributor? " << fetchedSelfProfile.contributor
        << std::endl;

#pragma endregion
#pragma region DataEndpointMethods

    // Fetching a language using it's name.
    auto fetchedLanguageUsingName = client.GetLanguageByName("C++");
    std::cout << "Fetching a language using it's name"
        << "  Language Name: " << fetchedLanguageUsingName.name << std::endl
        << "  Language Mode: " << fetchedLanguageUsingName.mode
        << std::endl;

    // Fetching a language using it's name.
    auto fetchedLanguageUsingExt = client.GetLanguageByExtension("cpp");
    std::cout << "Fetching a language using it's extension"
        << "  Language Name: " << fetchedLanguageUsingExt.name << std::endl
        << "  Language Mode: " << fetchedLanguageUsingExt.mode
        << std::endl;

#pragma endregion
#pragma region TimeEndpointFunction

    // Converting expiresIn value to a specific time 
    // when a paste should expire
    auto fetchedTimestamp = client.ExpiresInToUnixTimestamp(1615297946, ExpiresIn::OneWeek);
    std::cout << "Converting expiresIn value to a unix timestamp" << std::endl
        << "  Result: " << fetchedTimestamp
        << std::endl;

#pragma endregion

#ifdef RUN_EXPENSIVE
    // Expensive Methods
    // NOTE: These methods may take some time to complete
    // depending on some properties in your end.

    std::vector<std::string> pasteIDs = { "asdfasdf", "hjklhjkl" };
    client.BulkDeletePastes(pasteIDs);

    // Remarks: Following are HEAVY methods depending on
    // the amount of pastes you have on your account
#pragma region HeavyMethods

    // Getting all pastes' IDs under the authorized user's account
    for (auto pasteID : client.GetSelfPasteIDs())
        std::cout << pasteID << std::endl;
    std::cout << std::endl;

    // Getting `amount` number of  pastes' IDs 
    // under the authorized user's account
    for (auto pasteID : client.GetSelfPasteIDsByAmount(2))
        std::cout << pasteID << std::endl;
    std::cout << std::endl;

    // Getting all pastes under the authorized user's account
    for (auto paste : client.GetSelfPastes())
        std::cout << paste.title << std::endl;
    std::cout << std::endl;

    // Getting `amount` number of pastes 
    // under the authorized user's account
    for (auto paste : client.GetSelfPastesByAmount(2))
        std::cout << paste.title << std::endl;
    std::cout << std::endl;

#pragma endregion
#endif // RUN_EXPENSIVE

    return 0;
}