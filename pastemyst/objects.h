#pragma once

#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct Edit {
    std::string _id;
    unsigned long editId;
    unsigned long editType;
    std::vector<std::string> metadata;
    std::string edit;
    unsigned long editedAt;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Edit,_id, editId, editType, 
        metadata, edit, editedAt
    )
};

struct Pasty {
    std::string _id;
    std::string language;
    std::string title;
    std::string code;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Pasty, _id, language, 
        title, code
    )
};

struct Paste {
    std::string _id;
    std::string ownerId;
    std::string title;
    unsigned long createdAt;
    std::string expiresIn;
    unsigned long deletesAt;
    unsigned long stars;
    bool isPrivate;
    bool isPublic;
    std::vector<std::string> tags;
    std::vector<Pasty> pasties;
    std::vector<Edit> edits;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Paste, _id, ownerId, title, 
        createdAt, expiresIn, deletesAt, 
        edits, stars, isPrivate, isPublic, 
        tags, pasties, edits
    )
};

struct User {
    std::string username;
    bool contributor;
    std::string _id;
    std::string avatarUrl;
    bool publicProfile;
    std::string defaultLang;
    unsigned long supporterLength;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        User, username, contributor, 
        _id, avatarUrl, publicProfile, 
        defaultLang, supporterLength
    )
};

struct UserPlus {
    std::string username;
    bool contributor;
    std::string _id;
    std::string avatarUrl;
    bool publicProfile;
    std::string defaultLang;
    unsigned long supporterLength;

    std::vector<std::string> stars;
    json serviceIds;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        UserPlus, username, contributor,
        _id, avatarUrl, publicProfile,
        defaultLang, supporterLength,
        stars, serviceIds
    )
};

struct Language {
    std::string name;
    std::string mode;
    std::vector<std::string> mimes;
    std::vector<std::string> ext;
    std::string color;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        Language, name, mode, 
        mimes, ext, color
    )
};

struct PastyCreateInfo {
    std::string title;
    std::string code;
    std::string language = "AutoDetect";

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        PastyCreateInfo, title, 
        code, language
    )
};

struct PasteCreateInfo {
    std::string title = "(Untitled)";
    std::string expiresIn = "never";
    bool isPrivate = false;
    bool isPublic = false;
    std::string tags = "";
    std::vector<PastyCreateInfo> pasties;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(
        PasteCreateInfo, title, expiresIn, 
        isPrivate, isPublic, tags, pasties
    )
};