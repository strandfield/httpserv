// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#include "requesthandlerfactory.h"

#include "requesthandler.h"

#include <Poco/Net/HTTPServerRequest.h>

/**
 * \brief constructs a factory with the current working dir as root path
 */
LocalFileHttpRequestHandlerFactory::LocalFileHttpRequestHandlerFactory() : 
  LocalFileHttpRequestHandlerFactory(std::filesystem::current_path())
{

}

/**
 * \brief constructs a factory with a given root path
 * \param rootPath the directory in which the files are searched
 */
LocalFileHttpRequestHandlerFactory::LocalFileHttpRequestHandlerFactory(std::filesystem::path rootPath) :
  m_root_path(std::move(rootPath))
{

}

/**
 * \brief creates request handlers
 * \param request the http request a handler is created for
 * 
 * This function checks that a file exists under the request's URI, and 
 * returns a LocalFileHttpRequestHandler that will send the file to the client.
 * 
 * If the request's URI matches a directory, this function looks for a "index.html"
 * file in the directory.
 * 
 * If the requested file does not exist, no handler is created and nullptr is returned.
 */
Poco::Net::HTTPRequestHandler* LocalFileHttpRequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request)
{
  std::string uri = request.getURI();

  if (!uri.empty() && uri.at(0) == '/')
    uri.erase(0, 1);

  std::filesystem::path p = m_root_path / uri;

  if (std::filesystem::exists(p))
  {
    if (std::filesystem::is_directory(p))
    {
      if (std::filesystem::exists(p / "index.html"))
      {
        return new LocalFileHttpRequestHandler((p / "index.html").string());
      }
    }
    else
    {
      return new LocalFileHttpRequestHandler(p.string());
    }
  }
  else
  {
    return nullptr;
  }
}
