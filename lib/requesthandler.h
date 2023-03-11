// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#ifndef HTTPSERV_REQUESTHANDLER_H
#define HTTPSERV_REQUESTHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>

#include <map>
#include <string>

/**
 * \class LocalFileHttpRequestHandler
 * \brief http request handler that sends a file to the client
 */
class LocalFileHttpRequestHandler : public Poco::Net::HTTPRequestHandler
{
private:
  /**
   * \brief the path of the file
   * 
   * This is the absolute file path on the server filesystem.
   */
  std::string m_filepath;

  /**
   * \brief the MIME type of the file
   */
  std::string m_media_type;

public:
  LocalFileHttpRequestHandler() = delete;
  ~LocalFileHttpRequestHandler() = default;

  LocalFileHttpRequestHandler(std::string filepath, std::string mediatype);
  explicit LocalFileHttpRequestHandler(std::string filepath);

  using Dict = std::map<std::string, std::string>;
  static const Dict& mediaTypes();

  void handleRequest(Poco::Net::HTTPServerRequest& /* request */, Poco::Net::HTTPServerResponse& response) override;
};

#endif // HTTPSERV_REQUESTHANDLER_H
