// Copyright (C) 2023 Vincent Chambrin
// This file is part of the 'httpserv' project.
// For conditions of distribution and use, see copyright notice in LICENSE.

#include "serverapplication.h"

int main(int argc, char *argv[])
{
  HttpServerApplication app;
  return app.run(argc, argv);
}
