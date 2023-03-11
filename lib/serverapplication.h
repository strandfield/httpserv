// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#ifndef HTTPSERV_SERVERAPPLICATION_H
#define HTTPSERV_SERVERAPPLICATION_H

#include <Poco/Util/ServerApplication.h>

#include <memory>

class HttpServer;

/**
 * \brief the server application
 * 
 * The application sets up the server, making it listen to the requested port, 
 * and waits for a termination request.
 * 
 * The port number, 80 by default, can be specified using the --port command line 
 * option.
 */
class HttpServerApplication : public Poco::Util::ServerApplication
{
public:
  HttpServerApplication();
  ~HttpServerApplication();

  static HttpServerApplication& instance();

  HttpServer& httpServer() const;

protected:
  void initialize(Application& self) override;
  void uninitialize() override;
  void reinitialize(Application& self) override;
  void defineOptions(Poco::Util::OptionSet& options) override;
  void handleOption(const std::string& name, const std::string& value) override;
  int main(const std::vector<std::string>& args) override;

protected:
  void handlePortOption(const std::string& name, const std::string& value);

private:
  int m_port = 80;
  std::unique_ptr<HttpServer> m_http_server;
};

#endif // HTTPSERV_SERVERAPPLICATION_H
