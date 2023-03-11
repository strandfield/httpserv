// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#include "serverapplication.h"

#include "httpserver.h"

#include <filesystem>
#include <stdexcept>

HttpServerApplication::HttpServerApplication()
{
  setUnixOptions(true);
}

HttpServerApplication::~HttpServerApplication()
{

}

HttpServerApplication& HttpServerApplication::instance()
{
  return static_cast<HttpServerApplication&>(Poco::Util::ServerApplication::instance());
}

HttpServer& HttpServerApplication::httpServer() const
{
  return *m_http_server;
}

void HttpServerApplication::initialize(Application& self)
{
  std::cout << "Initializing..." << std::endl;

  ServerApplication::initialize(self);

  std::cout << "Working directory is " << std::filesystem::current_path() << std::endl;

  std::cout << "Initialization completed!" << std::endl;
}

void HttpServerApplication::uninitialize()
{
  ServerApplication::uninitialize();
}

void HttpServerApplication::reinitialize(Application& self)
{
  ServerApplication::reinitialize(self);
}

void HttpServerApplication::defineOptions(Poco::Util::OptionSet& options)
{
  ServerApplication::defineOptions(options);

  options.addOption(Poco::Util::Option("port", "p")
    .argument("number")
    .description("the listening port used by the HTTP server")
    .repeatable(false)
    .callback(Poco::Util::OptionCallback<HttpServerApplication>(this, &HttpServerApplication::handlePortOption)));
}

void HttpServerApplication::handleOption(const std::string& name, const std::string& value)
{
  ServerApplication::handleOption(name, value);
}

void HttpServerApplication::handlePortOption(const std::string& /* name */, const std::string& value)
{
  try
  {
    m_port = std::stoi(value);
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Could not parse server port: " << ex.what() << ".";
  }
}

int HttpServerApplication::main(const std::vector<std::string>& args)
{
  std::cout << "Entering main()" << std::endl;

  m_http_server = std::make_unique<HttpServer>(m_port);

  std::cout << std::endl << "Starting server" << std::endl;
  m_http_server->start();
  std::cout << std::endl << "Server started" << std::endl;

  waitForTerminationRequest();  // wait for CTRL-C or kill

  std::cout << std::endl << "Shutting down..." << std::endl;
  m_http_server->stop();

  return Application::EXIT_OK;
}
