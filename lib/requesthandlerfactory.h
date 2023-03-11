// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#ifndef HTTPSERV_REQUESTHANDLERFACTORY_H
#define HTTPSERV_REQUESTHANDLERFACTORY_H

#include <Poco/Net/HTTPRequestHandlerFactory.h>

#include <filesystem>

/**
 * \class LocalFileHttpRequestHandlerFactory
 * \brief the request handler factory
 * 
 * This class is responsible for creating instances of LocalFileHttpRequestHandler 
 * to handle the HTTP requests.
 */
class LocalFileHttpRequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
private:
  /**
   * \brief the directory in which the requested files are searched
   */
  std::filesystem::path m_root_path;

public:
  LocalFileHttpRequestHandlerFactory();
  explicit LocalFileHttpRequestHandlerFactory(std::filesystem::path rootPath);

protected:
  Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
};

#endif // HTTPSERV_REQUESTHANDLERFACTORY_H
