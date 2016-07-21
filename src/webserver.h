#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "utils.h"
#include "config.h"

// HTML Page maker
// ---------------
String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<style>";
  // Simple Reset CSS
  s += "*,*:before,*:after{-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}html{font-size:100%;-ms-text-size-adjust:100%;-webkit-text-size-adjust:100%}html,button,input,select,textarea{font-family:sans-serif}article,aside,details,figcaption,figure,footer,header,hgroup,main,nav,section,summary{display:block}body,form,fieldset,legend,input,select,textarea,button{margin:0}audio,canvas,progress,video{display:inline-block;vertical-align:baseline}audio:not([controls]){display:none;height:0}[hidden],template{display:none}img{border:0}svg:not(:root){overflow:hidden}body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}";
  // Basic CSS Styles
  s += "body{font-family:sans-serif;font-size:16px;font-size:1rem;line-height:22px;line-height:1.375rem;color:#585858;font-weight:400;background:#fff}p{margin:0 0 1em 0}a{color:#cd5c5c;background:transparent;text-decoration:underline}a:active,a:hover{outline:0;text-decoration:none}strong{font-weight:700}em{font-style:italic}h1{font-size:32px;font-size:2rem;line-height:38px;line-height:2.375rem;margin-top:0.7em;margin-bottom:0.5em;color:#343434;font-weight:400}fieldset,legend{border:0;margin:0;padding:0}legend{font-size:18px;font-size:1.125rem;line-height:24px;line-height:1.5rem;font-weight:700}label,button,input,optgroup,select,textarea{color:inherit;font:inherit;margin:0}input{line-height:normal}.input{width:100%}input[type='text'],input[type='email'],input[type='tel'],input[type='date']{height:36px;padding:0 0.4em}input[type='checkbox'],input[type='radio']{box-sizing:border-box;padding:0}";
  // Custom CSS
  s += "header{width:100%;background-color: #2c3e50;top: 0;min-height:60px;margin-bottom:21px;font-size:15px;color: #fff}.content-body{padding:0 1em 0 1em}header p{font-size: 1.25rem;float: left;position: relative;z-index: 1000;line-height: normal; margin: 15px 0 0 10px}";
  s += "</style>";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += "<header><p>" + DEVICE_TITLE + "</p></header>";
  s += "<div class=\"content-body\">";
  s += contents;
  s += "</div>";
  s += "</body></html>";
  return s;
}
void handleNotFound() {
	String message = "File Not Found\n\n";
	message += "URI: ";
	message += WEB_SERVER.uri();
	message += "\nMethod: ";
	message += (WEB_SERVER.method() == HTTP_GET) ? "GET" : "POST";
	message += "\nArguments: ";
	message += WEB_SERVER.args();
	message += "\n";
	for (uint8_t i = 0; i < WEB_SERVER.args(); i++) {
		message += " " + WEB_SERVER.argName(i) + ": " + WEB_SERVER.arg(i)
				+ "\n";
	}
	WEB_SERVER.send(404, "text/plain", message);
}

void handleRoot() {
	WEB_SERVER.send(200, "text/plain", "Webroot Empty!");
}

void handleSettings() {
	String s = "<h2>Wi-Fi Settings</h2>";
	s += "<p>Please select the SSID of the network you wish to connect to and then enter the password and submit.</p>";
	s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
	s += SSID_LIST;
	s += "</select><br><br>Password: <input name=\"pass\" length=64 type=\"password\"><br><br><input type=\"submit\"></form>";
	WEB_SERVER.send(200, "text/html", makePage("Wi-Fi Settings", s));
	WEB_SERVER.send(200, "text/plain", "hello");
}

#endif /* SRC_WEBSERVER_H_ */
