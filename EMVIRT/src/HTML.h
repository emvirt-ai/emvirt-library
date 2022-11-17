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
"html{background:#eceff1}"
"body{position:absolute;left:10%;top:10%;transform:translate(-10%,-10%);width:300px;height:430px;padding:20px;background:#fff;font-family:RobotoDraft;box-shadow:0 2px 10px 0 rgba(#000,.16),0 2px 5px 0 rgba(#000,.26)}"
"@mixin e($myElement){@at-root &__#{$myElement}{@content}}@mixin m($myModifier){@at-root &--#{$myModifier}{@content}}"
".inputs{$inputHeight:30px !default;$inputPaddingTop:2px !default;$inputPaddingBottom:1px !default;$inputPaddingLeft:2px !default;$inputDefaultColor:#0000FF;$inputBorderDefaultWidth:1px !default;$inputBorderDefaultColor:$inputDefaultColor;$inputFilledDefault:$inputDefaultColor;$inputFocusColor:#673AB7;$inputBorderFocusWidth:2px !default;$inputBorderFocusColor:$inputFocusColor;$inputLineHeight:$inputHeight - ($inputPaddingTop+$inputPaddingBottom+$inputBorderDefaultWidth);$containerPaddingTop:2px;display:flex;flex-direction:column;position:relative;margin-bottom:8px;padding-top:$containerPaddingTop;@include m('inline'){display:inline-flex}"
"@include e('field'){box-sizing:border-box;@include m('text'){flex:1 1 auto;order:2;display:block;width:100%;padding-top:$inputPaddingTop;padding-bottom:$inputPaddingBottom;padding-left:$inputPaddingLeft;line-height:$inputLineHeight;-ms-flex-preferred-size:$inputLineHeight;-webkit-tap-highlight-color:transparent;-webkit-font-smoothing:antialiased;border-width:0;border-bottom:$inputBorderDefaultWidth solid rgba($inputBorderDefaultColor,.12);color:rgba($inputDefaultColor,.87);transition-property:border,padding;transition-duration:.3s;transition-timing-function:cubic-bezier(.25,.8,.25,1);&:focus~.inputs__label,&:valid~.inputs__label{transform:translate3d(0,6px,0) scale(.75);color:rgba($inputFilledDefault,.95)}&:focus{outline:0;padding-bottom:$inputBorderDefaultWidth+$inputBorderDefaultWidth - $inputBorderFocusWidth;// [1] border-bottom-color:$inputBorderFocusColor;// [3] border-bottom-width:$inputBorderFocusWidth;// [2] &~.inputs__label{color:$inputFocusColor;// [3]}}}}@include e('label'){box-sizing:border-box;position:relative;top:-$containerPaddingTop;// [1] order:1;z-index:1;padding-left:$inputPaddingLeft;transform:translate3d(0,$inputHeight - $containerPaddingTop,0) scale(1);transform-origin:left top;transition-property:transform,color;transition-duration:.3s;transition-timing-function:cubic-bezier(.25,.8,.25,1);pointer-events:none;color:rgba($inputDefaultColor,.87);-webkit-font-smoothing:antialiased}}"
"input[type=submit] {background-color: #04AA6D;border: none;color: white;padding: 16px 32px;text-decoration: none;margin: 4px 2px;cursor: pointer;width: 100%}"
"</style>"
"<body>"
"<h2 style= color:#FFA500;>Welcome to EMVIRT Solutions</h2>"
"<h4>Enter your Credentials</h4>"
"<form action=\"/\" method=\"post\">"
"<div class='inputs'>"

"<label class='inputs__label'>SSID:</label>"
"<input maxlength=\"30\" name=\"ssid\" class='inputs__field inputs__field--text' type='text' required><br>"

"<label class='inputs__label'>Pass:</label>"
"<input maxlength=\"30\" name=\"password\" class='inputs__field inputs__field--text' type='text' required><br>"

"<label class='inputs__label'>User:</label>"
"<input maxlength=\"30\" name=\"username\" class='inputs__field inputs__field--text' type='text' required><br>"

"<label class='inputs__label'>Fleet:</label>"
"<input maxlength=\"30\" name=\"fleetid\" class='inputs__field inputs__field--text' type='text' required><br>"

"</div>"
"<input type=\"submit\" value=\"Save\">"
"</form>"
"</body>"
"</html>";
#endif
