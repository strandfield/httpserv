// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#ifndef HTTPSERV_HTTPSERVER_H
#define HTTPSERV_HTTPSERVER_H

#include <Poco/Net/HTTPServer.h>

/**
 * \class HttpServer
 * \brief the http server
 */
class HttpServer : public Poco::Net::HTTPServer
{
public:
  using HTTPServer::HTTPServer;

  explicit HttpServer(int port = 80);
};

#endif // HTTPSERV_HTTPSERVER_H
