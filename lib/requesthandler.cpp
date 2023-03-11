// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#include "requesthandler.h"

#include <Poco/Net/HTTPServerResponse.h>

#include <filesystem>

/**
 * \brief constructs a request handler for the given file
 * \param filepath  the path of the file on the server filesystem
 * \param mediatype the MIME type of the file
 */
LocalFileHttpRequestHandler::LocalFileHttpRequestHandler(std::string filepath, std::string mediatype) : 
  m_filepath(std::move(filepath)),
  m_media_type(std::move(mediatype))
{

}

/**
 * \brief constructs a request handler for the given file
 * \param filepath the path of the file on the server filesystem
 * 
 * The MIME type of the file is deduced from its extension; see mediaTypes().
 */
LocalFileHttpRequestHandler::LocalFileHttpRequestHandler(std::string filepath) :
  m_filepath(std::move(filepath))
{
  auto extension = std::filesystem::path(m_filepath).extension();
  auto it = mediaTypes().find(extension.string());
  m_media_type = it != mediaTypes().end() ? it->second : "";
}

/**
 * \brief returns a built-in list of media types
 * 
 * The returned dict maps the file extension (as returned by std::filesystem::path::extension;
 * i.e., with the '.') to the MIME type.
 */
const LocalFileHttpRequestHandler::Dict& LocalFileHttpRequestHandler::mediaTypes()
{
  static const Dict static_types = {
    {".css", "text/css"},
    {".html", "text/html"},
    {".js", "text/javascript"},
    {".json", "application/json"},
    {".txt", "text/plain"},
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    {".ico", "image/x-icon"},
    {".ttf", "font/ttf"},
    {".woff2", "font/woff2"},
  };

  return static_types;
}

/**
 * \brief handles the request
 * 
 * This sends the file to the client.
 */
void LocalFileHttpRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& /* request */, Poco::Net::HTTPServerResponse& response)
{
  response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
  response.add("Cache-Control", "max-age=86400");
  response.sendFile(m_filepath, m_media_type);
}
