#pragma once

#include <iostream>

struct Edit {
    std::string id;
    int64_t edit_id;
    int64_t edit_type;
    std::vector<std::string> metadata;
    std::string edit;
    int64_t edited_at;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Edit, id, edit_id, edit_type, metadata, edit, edited_at)
};

struct Pasty {
    std::string id;
    std::string language;
    std::string title;
    std::string code;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Pasty, id, language, title, code)
};

struct Paste {
    std::string owner_id;
    std::vector<Edit> edits;
    int64_t deletes_at;
    bool is_public;
    std::string expires_in;
    int64_t stars;
    int64_t created_at;
    bool is_private;
    std::string title;
    std::string id;
    std::vector<std::string> tags;
    bool encrypted;
    std::vector<Pasty> pasties;

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Paste, owner_id, edits, deletes_at, is_public, expires_in, stars, created_at, is_private, title, id, tags, encrypted, pasties)
};

struct User {
    std::string username;
    bool contributor;
    std::string id;
    std::string avatar_url;
    bool public_profile;
    std::string default_lang;
    int64_t supporter_length;

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(User, username, contributor, id, avatar_url, public_profile, default_lang, supporter_length)
};

struct Language {
    std::vector<std::string> ext;
    std::string name;
    std::string color;
    std::string file;
    std::string mode;
    std::vector<std::string> mimes;

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Language, ext, name, color, file, mode, mimes)
};