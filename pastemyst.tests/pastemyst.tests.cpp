#include <iostream>
#include "pastemyst.h"

int main()
{
    Client client = Client();
    client.Authorize("token");

    std::cout << client.GetPaste("paste_id").text << std::endl;
    // std::cout << client.CreatePaste("{\"isPrivate\": true, \"pasties\": [{\"title\": \"new private paste\",\"language\": \"Autodetect\",\"code\": \"new private paste content\"}]}").text << std::endl;
    // std::cout << client.EditPaste("paste_id", "{\"pasties\": [{\"_id\": \"pasty_id\", \"title\": \"edited\",\"language\": \"Autodetect\",\"code\": \"edited paste content\"}]}").text << std::endl;
    // std::cout << client.DeletePaste("paste_id").text << std::endl;

    return 0;
}

