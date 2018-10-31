void setupServer() {
    server.on("/test", testRoute);
}

void testRoute() {
  server.send(200, "text/html", "<h1>Connected! IP: ");
}
