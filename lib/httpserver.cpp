// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#include "httpserver.h"

#include "requesthandlerfactory.h"

/**
 * \brief constructs the server
 * \param port the listening port
 */
HttpServer::HttpServer(int port) : Poco::Net::HTTPServer(new LocalFileHttpRequestHandlerFactory(), port)
{

}
