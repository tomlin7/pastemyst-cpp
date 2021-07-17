<p align="center">
    <a href="https://paste.myst.rs/">
        <img width="500" src="logo.png" alt="Logo" /><br>
    </a>
</p>

<h1 align="center"> 
    <a href="https://github.com/billyeatcookies/pastemyst-cpp/actions">
        <img alt="Build status" src="https://img.shields.io/github/issues-pr/billyeatcookies/pastemyst.cpp?style=for-the-badge">
    </a>
    <a href="https://github.com/billyeatcookies/pastemyst-cpp/issues">
        <img alt="GitHub issues" src="https://img.shields.io/github/issues/billyeatcookies/pastemyst-cpp?style=for-the-badge&logo=github">
    </a>
</h1>

<p align="center">
A fast API wrapper for PasteMyst written in C++. </br>
Official pastemyst API docs found <a href="https://paste.myst.rs/api-docs/index">here</a>.
</p>
<p align="center">
All aspects of the v2 endpoint are currently implemented.
</p>

---

## Usage

Clone this repository. Add reference to pastemyst in your project, and you are ready to go!

For example, information on a paste can be retrieved as such:

```cpp
#include "pastemyst.h"

int main()
{
    Client client;

    std::string pasteID = "paste_id";
    if(client.PasteExists(pasteID))
    {
        auto paste = client.GetPaste(pasteID);
    }
}
```
Have a look at this [complete sample project](https://github.com/billyeatcookies/pastemyst-cpp/tree/master/pastemyst.sample) for further usage instructions.

You can find a list of endpoints over on PasteMyst's [API docs](https://paste.myst.rs/api-docs/). Each of these endpoints has an equivalent wrapper method in the library. 

## Requirements

- [vcpkg](https://github.com/microsoft/vcpkg)
- [cpr](https://github.com/whoshuu/cpr)
- [nlohmann/json](https://github.com/nlohmann/json)

```cmd
> git clone https://github.com/microsoft/vcpkg
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg integrate install
> vcpkg install cpr nlohmann-json
```

## License

This project is available under a [MIT](./LICENSE) license.

## Acknowledgements

Thanks to [WaifuShork](https://github.com/WaifuShork) for helping me out on writing this, check [pastemystgo](https://github.com/WaifuShork/pastemystgo).
