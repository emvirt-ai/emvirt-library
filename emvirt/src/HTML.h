#ifndef HTML_h
#define HTML_h
#include <Arduino.h>

const char INDEX_HTML[] =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta content=\"text/html; charset=ISO-8859-1\""
" http-equiv=\"content-type\">"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>Emvirt</title>"
"<style>"
"\"body { background-color: #FFA500; font-family: Arial, Helvetica, Sans-Serif; color: #0000FF; text-align:center;}\""
"</style>"
"</head>"
"<body>"
"<h2>Welcome to EMVIRT</h2>"
"<h4>Enter your Credentials</h4>"
"<form action=\"/\" method=\"post\">"
"<p>"
"<label>SSID:&nbsp;&nbsp;&nbsp;&nbsp;</label>"
"<input maxlength=\"30\" name=\"ssid\"><br><br>"
"<label>Pass:&nbsp;&nbsp;&nbsp;&nbsp;</label><input maxlength=\"30\" name=\"password\"><br><br>"

"<label>User:&nbsp;&nbsp;&nbsp;&nbsp;</label>"
"<input maxlength=\"30\" name=\"username\"><br><br>"

"<label>Fleet:&nbsp;&nbsp;&nbsp;</label>"
"<input maxlength=\"30\" name=\"fleetid\"><br><br>"

"<input type=\"submit\" value=\"Save\">"
"</p>"
"</form>"
"</body>"
"</html>";

#endif
