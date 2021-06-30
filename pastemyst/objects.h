#pragma once

#include <iostream>

struct Edit {
    std::string id;
    int64_t editId;
    int64_t editType;
    std::vector<std::string> metadata;
    std::string edit;
    int64_t editedAt;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Edit, id, editId, editType, metadata, edit, editedAt)
};

struct Pasty {
    std::string id;
    std::string language;
    std::string title;
    std::string code;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Pasty, id, language, title, code)
};

struct Paste {
    std::string ownerId;
    std::vector<Edit> edits;
    int64_t deletesAt;
    bool isPublic;
    std::string expiresIn;
    int64_t stars;
    int64_t createdAt;
    bool isPrivate;
    std::string title;
    std::string id;
    std::vector<std::string> tags;
    bool encrypted;
    std::vector<Pasty> pasties;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Paste, ownerId, edits, deletesAt, isPublic, expiresIn, stars, createdAt, isPrivate, title, id, tags, encrypted, pasties)
};

struct User {
    std::string username;
    bool contributor;
    std::string id;
    std::string avatarUrl;
    bool publicProfile;
    std::string defaultLang;
    int64_t supporterLength;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, username, contributor, id, avatarUrl, publicProfile, defaultLang, supporterLength)
};

struct Language {
    std::vector<std::string> ext;
    std::string name;
    std::string color;
    std::string file;
    std::string mode;
    std::vector<std::string> mimes;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Language, ext, name, color, file, mode, mimes)
};

struct PastyCreateInfo {
    std::string title;
    std::string code;
    std::string language;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PastyCreateInfo, language, title, code)
};

struct PasteCreateInfo {
    std::string title;
    std::string expiresIn;
    bool isPrivate;
    bool isPublic;
    std::string tags;
    std::vector<PastyCreateInfo> pasties;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(PasteCreateInfo, title, expiresIn, isPrivate, isPublic, tags, pasties)
};