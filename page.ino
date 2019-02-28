void handlePage() {
  handleFileRead(Server.uri());
}

String getContentType(String filename) {
  if (filename.endsWith(".html") || filename.endsWith(".htm")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".png")) return "image/png";
  else if (filename.endsWith(".gif")) return "image/gif";
  else if (filename.endsWith(".jpg")) return "image/jpeg";
  else return "text/plain";
}

bool handleFileRead(String path) {
  bool isIndex = false;
  if (path.endsWith("/")) {
    path += "index.html";
    isIndex = true;
  }
  String contentType = getContentType(path);
  if (SPIFFS.exists(path)) {
    File file = SPIFFS.open(path, "r");
    Server.streamFile(file, contentType);
    file.close();
    return true;
  }
  else {
    Server.send (404, "text/plain", "404 not found");
    return false;
  }
}
