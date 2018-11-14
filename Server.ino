void setupServer() {
	server.on("/", HTTP_GET, handleRoot);
  server.on("/panel", HTTP_GET, panel);
  server.on("/healthcheck", HTTP_GET, healthCheck);
  server.on("/reset", HTTP_GET, resetCredentials);
	server.on("/connect", HTTP_POST, handleConnect);
  server.on("/scannetworks", HTTP_POST, scanWifiNetworks);
	server.on("/api/v1/relay", HTTP_GET, getRelay);
	server.on("/api/v1/relays", HTTP_GET, getRelays);
	server.on("/api/v1/relay", HTTP_PUT, updateRelay);
  server.on("/api/v1/relay/switch", HTTP_PUT, switchRelay);
	server.on("/api/v1/relay", HTTP_DELETE, deleteRelay);
	server.on("/api/v1/relay", HTTP_POST, createRelay);
}





void resetCredentials() {
  clearEeprom();
  server.send(200, "application/json", "{\"status\":\"ok\",\"message\":\"credentials deleted\"}");
}






void healthCheck() {
  Serial.println("healthCheck: up");
  server.send(200, "application/json", "{\"status\":\"ok\",\"message\":\"wemos-iot-relay service is up\"}");
}







void handleRoot() {
	server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"><style>.btn,form,select{width:100%}.done-modal,.modal{position:fixed;top:0;bottom:0;left:0;right:0}body{background:#f5f6fa;color:#9c9c9c;font:1rem \"PT Sans\",sans-serif;margin:10px 20px}h1{font-size:1.5em}input{display:block;margin:0 auto}form{max-width:380px;display:inline-block}.form-container{text-align:center}input[type=password],input[type=text]{background:#fff;color:#a3a3a3;font:inherit;box-shadow:0 6px 10px 0 rgba(0,0,0,.1);border:0;outline:0;padding:12px 18px;width:100%;margin:20px 0;box-sizing:border-box;border-radius:4px}input[type=text]{margin-bottom:0}select{color:#a3a3a3;font-size:17px;margin-top:20px;padding:12px 18px;border:0!important;-webkit-appearance:none;-moz-appearance:none;appearance:none;box-shadow:0 6px 10px 0 rgba(0,0,0,.1);background:url(\"data:image/svg+xml;utf8,<svg xmlns='http://www.w3.org/2000/svg' width='100' height='100' fill='%238C98F2'><polygon points='0,0 100,0 50,50'/></svg>\") no-repeat #fff;background-size:12px;background-position:calc(100% - 20px) center}select[disabled]{background-color:#eaeaea}.btn{display:block;background:0 0;color:inherit;font:inherit;border:0;outline:0;padding:0;transition:all .2s ease-in;cursor:pointer}.btn-primary{background:#7f8ff4;color:#fff;box-shadow:0 0 10px 2px rgba(0,0,0,.1);border-radius:2px;padding:12px 36px}.btn-primary:hover{background:#6c7ff2}.btn-primary:active{background:#7f8ff4;box-shadow:inset 0 0 10px 2px rgba(0,0,0,.2)}#refresh-section{padding-top:5px;text-align:left;height:20px}.done-modal div,.modal-text{text-align:center;margin-top:50%}.hide{display:none}.right{float:right}.left{float:left}.modal{background-color:rgba(0,0,0,.8);color:#fff}.modal-text{font-size:24px}.done-modal{background:#f5f6fa}.done-modal div{padding:15px}.spin{width:70px;margin-top:20px;-webkit-animation-name:spin;-webkit-animation-duration:1.5s;-webkit-animation-iteration-count:infinite;-webkit-animation-timing-function:linear;-moz-animation-name:spin;-moz-animation-duration:1.5s;-moz-animation-iteration-count:infinite;-moz-animation-timing-function:linear;-ms-animation-name:spin;-ms-animation-duration:1.5s;-ms-animation-iteration-count:infinite;-ms-animation-timing-function:linear;animation-name:spin;animation-duration:1.5s;animation-iteration-count:infinite;animation-timing-function:linear}@-ms-keyframes spin{from{-ms-transform:rotate(0)}to{-ms-transform:rotate(360deg)}}@-moz-keyframes spin{from{-moz-transform:rotate(0)}to{-moz-transform:rotate(360deg)}}@-webkit-keyframes spin{from{-webkit-transform:rotate(0)}to{-webkit-transform:rotate(360deg)}}@keyframes spin{from{transform:rotate(0)}to{transform:rotate(360deg)}}</style><title>Config Wemos IoT Relay</title></head><body><div class=\"form-container\"><h1>Connect to Wifi Network</h1><p>Please provide wifi credentials to connect your wemos-iot-relay to network</p><form action=\"/connect\" method=\"POST\"><input type=\"text\" name=\"ssid\" id=\"ssidText\" placeholder=\"SSID\" class=\"hide\"> <select name=\"ssid\" id=\"ssidSelect\"><option value=\"\" disabled=\"disabled\" selected=\"selected\">Select a WiFi network</option></select><div id=\"refresh-section\"><a id=\"refreshButton\" href=\"#\" class=\"left\">refresh</a> <span id=\"loadingLabel\" class=\"left hide\">loading data...</span> <a id=\"backButton\" href=\"#\" class=\"right hide\">back</a> <a id=\"changeInput\" href=\"#\" class=\"right\">or write manually</a></div><input type=\"password\" name=\"password\" id=\"password\" placeholder=\"Password\"> <input type=\"button\" value=\"Connect\" class=\"btn btn-primary\" onclick=\"submitForm(this.form)\"></form></div><div id=\"modal\" class=\"modal hide\"><div class=\"modal-text\"><div>Connecting to AP...</div><img class=\"spin\" src=\"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAIAAAACACAYAAADDPmHLAAAAGXRFWHRTb2Z0d2FyZQBBZG9iZSBJbWFnZVJlYWR5ccllPAAAA2RpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADw/eHBhY2tldCBiZWdpbj0i77u/IiBpZD0iVzVNME1wQ2VoaUh6cmVTek5UY3prYzlkIj8+IDx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IkFkb2JlIFhNUCBDb3JlIDUuMC1jMDYwIDYxLjEzNDc3NywgMjAxMC8wMi8xMi0xNzozMjowMCAgICAgICAgIj4gPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4gPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIgeG1sbnM6eG1wTU09Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC9tbS8iIHhtbG5zOnN0UmVmPSJodHRwOi8vbnMuYWRvYmUuY29tL3hhcC8xLjAvc1R5cGUvUmVzb3VyY2VSZWYjIiB4bWxuczp4bXA9Imh0dHA6Ly9ucy5hZG9iZS5jb20veGFwLzEuMC8iIHhtcE1NOk9yaWdpbmFsRG9jdW1lbnRJRD0ieG1wLmRpZDo3ODkwNzY1QzM1QUVFMDExOUI0MDg3MzJEODFDNjBGNyIgeG1wTU06RG9jdW1lbnRJRD0ieG1wLmRpZDoxQUZEOEM5OEI3MDIxMUUwQjA2Q0VGMTREMDJDMzg0RSIgeG1wTU06SW5zdGFuY2VJRD0ieG1wLmlpZDoxQUZEOEM5N0I3MDIxMUUwQjA2Q0VGMTREMDJDMzg0RSIgeG1wOkNyZWF0b3JUb29sPSJBZG9iZSBQaG90b3Nob3AgQ1M1IFdpbmRvd3MiPiA8eG1wTU06RGVyaXZlZEZyb20gc3RSZWY6aW5zdGFuY2VJRD0ieG1wLmlpZDpFNDgxRDBEOTAwQjdFMDExQTVFMUI2QkYyMkQyMTM0OSIgc3RSZWY6ZG9jdW1lbnRJRD0ieG1wLmRpZDo3ODkwNzY1QzM1QUVFMDExOUI0MDg3MzJEODFDNjBGNyIvPiA8L3JkZjpEZXNjcmlwdGlvbj4gPC9yZGY6UkRGPiA8L3g6eG1wbWV0YT4gPD94cGFja2V0IGVuZD0iciI/PrEurG4AAA4BSURBVHja7F0PaFZHEp8mIRAIBHJ8h0dKikVIsVhSIh6RlIigKBHFw+KhKBZLi0VRIlcqhkpLpVKJKC0RxWIwtJycVBRDpdKgNDQoBKUBqSAXDBcIFwgEAoGAcPu7b1779fP7997O7Nv3koEhiSbv2zf729mZ2ZnZl/r6+ihllDG83HArfwWvMLzMcFOFz5gyPGl4nPmp4TH+fipNwqpJwTtgotcb7mDOCDxzGXNbgf+bMTzMfM/wgyUAuCVMzE7DG3jCGxx/fqPhrcyg2RwwfMuaYwkAwoRJ3sG8ycOxdTF/YXjI8DXDV1lbeE1Vno8PQr1h+L+GL3k4+YUI21Efj/mW4e1LAAhH1Yb3Gf6FBQhVW5vAraqaAfyd4V8N7/fxPXwCQL3hg4afGb5seFWKjO0W1mB4t+4Y7BavAYCVcoCF82UIVy2JBAO2NwcItYsdAJ2GH/Ke2UiLhxoYCA/Zm1l0AMAq/8bw3ZSp+rC00vAPbCc0LxYAdLNRtEvoefdSAITtLJPjvCWmEgDNvOJ72eCToh7Drxo+ZXg6wSCoM/yZ4Z8oG75OFQC2slvXqeR3I0Z/zPBfDP/N8O0EA6GdZbUrDQCAOkN07Iai65NrRD03fN3wZsMvG/6Uknl4U8820lltT0ETALDqfzT8DwcrphC4EJM/wVphi+GbCQTCYTYSG5MGABy/3ldS+YW0TEeZ3xk0vI3BAJthIkEg6GRZrkgKANo0B1yEuir8PWwHJw2/YngjZQ9tnicABMGCavcdAB1s6TfGsErC0h3Db7NW+NDwE89B0MjbwXpfAbCeB1gfg3BWWgRS4DqeNvya4XWUPdOf99g4vBVC4zkDQAcPrC5G4UiEVBFU2s0exBHKpoH5GC/4l5QmkABAmweTT8KqEYkc5wy/YXit4X7Dc56B4JaETWALABgn35Mfx5ubSCeMOmL4HdYKHxge9QgEkH1LXABo4AFkPBFII9sCWoTcv/OGVzNf5H+LkxpYE2RcAwAr7TvHrl4pmmD3zlUOHrTA+6wV3o3ZlcQcINJa6xIAn0i7IxFogVfhavbrEeBxnZELu2A5OT7BK0CwBc5G+cMoWcGY+I9ifNk5nvgzFH8KdkfMssilA2yvDGhqAOw138SE+Dn6PYp31IPJb4xRFsWoL+y2HBYAVyib1+aabrNL1kP+5NojcbWZ/KL6sKAMA4Bucp+XP8suGI53xz0SNLKXt5KftIaymUWiAGhiw88l4QTvdcoGYXwiuJq95Dcdr3QrqBQAX5C7GD9cKmT3bCH/6uyCMKzvhSq1lXoFlQAAlu4uRwOf44k/5algz5JdsGncoQ0T1CtaAQDGxJeOBoyz+nXkbz4fKpLfs/h7nDoiB2GtQ81WNqWsHADwwq0OBgqBvEX+xNnzqZldrKiEoBWSVdFo4gmDwIVRu4KN90gAwJ7/mSNLfzMLx0eqZtfKJskFnsxwzs8TDHgXmgAGYSYKAPaTfmZPsDLGyF/6hMrnHJYixC6+LaL1NpJ+LUN9KS1QVcKK7HYgXKyMIY8n3zbsjYk/WeL/H/MCWHAQt2gMA4CdpB/lOlZkZfhCENgVih7qHWKAlyNsDYccaIEDYQCgfcAx6MjVsyk1v2zx97Bn3g6xsnG41e9AC9RWAoAu0k2smKpwZdisXBivaNHyTwthRQ31TrNRG9bfP6TsGQTNtcoC4IAyEt9VMnwy7Pc+y7F82yMYsnB7o4Z6seK3RfRoEARDQqpmcsn+cgAASjQPfK6x+pcmRCpRXn2Y/hiyrqZwiZN17PJFDfVCs41YvMcIbwda1El5ZwT5ANhDeufbQPgRBbV2q4yfHiaH3ibU2yNk1Gofee8pBYCdih8sncGDbNj7FUxwpalrNqHem2XcvTCEyT+hOA87iwEAbl+b0ocG1TeSquznCl3Vlgp+D3l9FyzjBZJbJ7YBrQJWyGNVIQDsUETdaZIrrEDCw/chjbtSk1PN/r5NbQPsjhsklySyIKhRCtH2QgDQ6lY1J2jYrOLJr4ugMYqRbag3oFp2O9cIvesA6YWJN+QDoI70avkR4JAooMhEWPm5GqC6iOqWDHpBjqiXkOh1iALV80pz8pt7HACgg/Rq+6Re4oqFYBvpxXZ0WhnOTRQ9AFXIFtCIC1QHC74qBxEahPP9xwLPOSBgZOX//SXSy3DGgjoo8Bx4TUOKY1QHQL/AM4LQrti+R26yej8X2goGlMbXnguANUofItGY6TjJ5CW08zZnE+oN6xlIZFIPKm0DkENtFfvIGokfYwK+bIbs8vDyDbQu3p9dZfXuIftjdQSGRhTGBnm0AABaJ393BJ7RTbLp6BfIsp4+gmso0SZPyw5YWUV6zZqHBYT3nvCY4uhIvk/AwxpWGtsqAECrL62t2tpA6WghDw1me23MAyU7YHkV6aR+TZF9i9ZdlB6y7eo1SzpnA81aGkCi5976FAFAon/RmJYGyHgIgOCmz7SQRP8ijUaWmSqlfdb23L+V0ketMcu0oKFdRToZQLaDbUkhAFo8BIBat3DbY8w03hzWFLNMnQLAttIlk0IAZGKWqVMA2Gb/1KUQAA0xy9QpAJYoIVTlKdrnUyhr2xVcnyQA2HoW0ykEwEzMMnUKAFuDZzKFAJiMWaZFAaBxyGDr8jxKIQBs32mZFgBmPATAaAoBMBqzTAu6lloAsA17Spwm+mYA2vZA0oiOzgAAGseMqwSMlqEUAeC2wFarkbk1AQBoNCWoExjwzRQB4JqAPDUu5xjXAgCoTQAAsymY/HkBMCNrWyOR9SkAoNWirVVAcP0pAIDEPYRadRuPAYDHSg+XyOhBVfFCgicf+75ElW+XJgDGlVQtDEHbfEMET75OMAAGBLbYRiUNsBAAAPRASQASyD1Jfl3aGEbAEqtf6z7ER0EcADSiJIQ9As+AFjiaQAAcI5n+x1rZ0f+fc20N0C7kvqBM+l6CJh/CPSfwHM2ubX8AwBDpHcFKVffspmQcEsGe2ksyZyxaXdswtju5AMDkjyoCQOIsG5O/jfzOFci9F8CW4PcfVhonXP+ZXACABpU+DMkh+4SeBZD+neK9qrXUqpLsfo52blrJsb/dypILgGuKwkEfHqk8P0TVwjRidrXyMflS3c+h9j9WHO/VQgB4SnpRQSD5oODzrlP2sgUfLpGc4bFIdvLYT3oXc09QTm5CfkaQthaQrEKCV7A6Zu8A3tNfhcfQ4Gr1FwJAv+L+ismXbs2CKNs6yrZadxksgiH6IWUvf5K+66iXdAtjvi4FgAnSPYeHMajRj/Aryt4yetGBbYB9/k3KnlNIL5ZNVKClu7DGelIKAES67cpBl8k+bbzY3va+4VcZEHPCK/4iP3s36VTqQkNeUpb9C3NbVcTA0rzCDf0INC+jnOQt4U8cN7gaEQxzLAv49X9mcGne6KGt+qcLeSk1RfxZqLcLioNBhGtYWdsssMsYJGPgdBKhaeTW1XOgJeiP9Ijfe4a/f6S0ykv5/PscrP4Xgmgv9fUVvBATwsHVK8uUJwgG3AgtbkLm1E+kWw85z9vXVCVbQDA555RfHCC7oejvJoGaWAZ1DlZ/wSzrUpVB5x24Vqh2uUvp7AdQybv/6ODdsfqLXtFXCgA41TrpaBXcXWSaYBlPvotOKOeoRI1FudrAM+TmUmdMPq6AWbMIJh/p8vdJr0FnvkdUchGXAwBsgSOOBBNsB10pnvxONviaHX3e0XLbeCXVwYOkd1ScT3VsFB1M4eTDzfuB3HU/HaS8uH9UABBrAVfHrzgKRaDoCik1RXBMeAf42pfJXZfyijV3pQCAHfCpY8EhWPSQ9IoiXBBi+7+Q/nW8+XS6UtstTIMIuBKuCzYD4xBRyYYETXwDr3hccrXc8Wc/CrNYwwAAoVIchMTRvgV5hf+m7O0hPgOhju2XX0k/tFtM9e8Os12HbREDf3JvTMIN7g7yEQjY53G5xTO2X+Lqc4xDsFClflF6BN0m2WtgowIBwv7coUtViBDE+pjH0kvxNrjspwiHa1GbROGG67gPcaABPmLh3+fvmx1Nejf78/+h7MVQcV9sgX3/gyh/WGOx1+Cs/S7p3TkUhtYwQyM8YC01yoKZEJjwNmZUPHeQX4Ro3xaKWC9RY/HBMAY38urz6TAnAEPuOAGGJzn743N6sWtXK/1ehdPCwG4lv+8twHnNZrKomKoRQN9mVoe+WucZ9sc3UboIKx7ZSlap/BKNIsdYE6SxvauvhC0YxTHWcRmpTqEPeEBLIHAz+SiPEzmfkWwVO0j+VOukleZYxtelHijdKxiJnutIp/fgYicE4d4i4UoojWbRYzzQx0tzJkY42FlLCj2UtbqFTzAIRpbmTsS+gixVahI0bwyZ4e3g9NIcRqavWIZqfZO1r4yBxYoiSkSqppfms2KaZR//kLZn5erOIHgIb1K6GkBrEbbNNyQtfR8AAJpkF6aHkt39U1NbnuT93pkX5frWsKB16uvkLtE0CXSHNWQPOe5/FNe1cU/ZLthCbuoOfKUJ3us3xuU2x31v4CBrAyB/bhFN/Dxrwtdc7fW+AiB373vF8AlKdygZ1v0pftce8uDsxKebQzHxyGZ9md2fNIWTg37HeLdjPrnEPl4di1WBAAjq2fcm3HXE2cg7/C5nfNzmajwWHqzhAWZk5aBQZAf5X0CKeD3a7fVTAnob1yRkJSEUepoZxSJooR7k51V7stKhqa5Swg7Baih5FJSpgWsZBOBO/qpdf/ecJ/wefx2mBCfC1FCyaYFXXq6dgEROpIejJGslczOFTxmfZEMUx9tIKB3nn1N1q+n/BBgA7ZvBib2vTvwAAAAASUVORK5CYII=\" alt=\"\"></div></div><div id=\"doneModal\" class=\"done-modal hide\"><div>Your wemos-iot-relay is connected to your network. Close this connection and connect to your Network.</div></div></body><script>var manuallySearch=!1,refreshButton=document.getElementById(\"refreshButton\"),backButton=document.getElementById(\"backButton\"),ssidText=document.getElementById(\"ssidText\"),ssidSelect=document.getElementById(\"ssidSelect\"),password=document.getElementById(\"password\"),changeInput=document.getElementById(\"changeInput\"),loadingLabel=document.getElementById(\"loadingLabel\"),modal=document.getElementById(\"modal\"),doneModal=document.getElementById(\"doneModal\"),networks=null,endpoint=\"http://\"+location.host+\"/scannetworks\",attempsConnection=0,xhr=new XMLHttpRequest;function cleanSelectoptions(){ssidSelect.options.length=0}function enableSelect(){ssidSelect.removeAttribute(\"disabled\"),loadingLabel.classList.add(\"hide\"),refreshButton.classList.remove(\"hide\"),changeInput.classList.remove(\"hide\")}function disableSelect(){ssidSelect.setAttribute(\"disabled\",\"disabled\"),loadingLabel.classList.remove(\"hide\"),refreshButton.classList.add(\"hide\"),changeInput.classList.add(\"hide\")}function printOptions(){networks.data.forEach(function(e){var t=document.createElement(\"option\");t.text=e.ssid,t.value=e.ssid,ssidSelect.appendChild(t)})}function openModal(){modal.classList.remove(\"hide\")}function closeModal(){modal.classList.add(\"hide\")}function openDoneModal(){doneModal.classList.remove(\"hide\")}function submitForm(e){console.log(\"submit!\"),openModal();var t=new XMLHttpRequest,n=JSON.stringify({ssid:manuallySearch?ssidText.value:ssidSelect.value,password:password.value});function o(){t.open(\"POST\",\"/connect\"),t.setRequestHeader(\"Content-Type\",\"application/json;charset=UTF-8\"),t.timeout=15e3,t.send(n)}t.onload=function(){if(200<=t.status&&t.status<300){console.log(\"success!\");var e=JSON.parse(t.responseText);console.log(e),alert(\"connected to IP: \"+e.ip),closeModal(),openDoneModal()}else console.log(\"error\"),attempsConnection<2?(console.log(\"reconnecting:\",attempsConnection),++attempsConnection,o()):(attempsConnection=0,alert(\"Unable to connect\"),closeModal())},t.onerror=function(){console.log(\"error\"),attempsConnection<2?(console.log(\"reconnecting:\",attempsConnection),++attempsConnection,o()):(attempsConnection=0,alert(\"Unable to connect\"),closeModal())},o()}xhr.onload=function(){200<=xhr.status&&xhr.status<300?(console.log(\"success!\"),networks=JSON.parse(xhr.responseText),printOptions(),enableSelect(),console.log(networks)):(enableSelect(),console.log(\"error\"))},xhr.onerror=function(){console.log(\"error\"),enableSelect()},refreshButton.onclick=function(){console.log(\"refresh networks\"),disableSelect(),cleanSelectoptions(),xhr.timeout=7e3,xhr.open(\"POST\",endpoint),xhr.send()},changeInput.onclick=function(){backButton.classList.remove(\"hide\"),refreshButton.classList.add(\"hide\"),ssidText.classList.remove(\"hide\"),ssidSelect.classList.add(\"hide\"),changeInput.classList.add(\"hide\"),manuallySearch=!0},backButton.onclick=function(){backButton.classList.add(\"hide\"),refreshButton.classList.remove(\"hide\"),ssidText.classList.add(\"hide\"),ssidSelect.classList.remove(\"hide\"),changeInput.classList.remove(\"hide\"),manuallySearch=!1};</script></html>");
}





void panel() {
  server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1\"><meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"><style>body{font:14px/20px Arial,sans-serif;background:#ddd;padding:10px;color:#444}h1{text-align:center}.section{background:#fff;border:1px solid #bbb;display:block;border-radius:10px;padding:1em;margin:0 auto 15px;cursor:pointer;max-width:400px;width:100%;position:relative;box-sizing:border-box}.onoffswitch,.section-title{position:relative;display:inline-block}.section-title{padding:10px}.onoffswitch{width:122px;float:right;-webkit-user-select:none;-moz-user-select:none;-ms-user-select:none}.onoffswitch-checkbox{display:none}.onoffswitch-label{display:block;overflow:hidden;cursor:pointer;border-radius:44px}.onoffswitch-inner{width:200%;margin-left:-100%;-moz-transition:margin .3s ease-in 0s;-webkit-transition:margin .3s ease-in 0s;-o-transition:margin .3s ease-in 0s;transition:margin .3s ease-in 0s}.onoffswitch-inner:after,.onoffswitch-inner:before{float:left;width:50%;height:44px;padding:0;line-height:44px;font-size:16px;font-family:Helvetica,Arial,sans-serif;font-weight:700;-moz-box-sizing:border-box;-webkit-box-sizing:border-box;box-sizing:border-box;box-shadow:rgba(0,0,0,.1) 0 2px 2px 0 inset}.onoffswitch-inner:before{content:\"ON\";padding-left:27px;background-color:#FFBD2F;color:#FFF;border-radius:44px 0 0 44px}.onoffswitch-inner:after{content:\"OFF\";padding-right:27px;background-color:#EEE;color:#999;text-align:right;border-radius:0 44px 44px 0}.onoffswitch-switch{width:44px;margin:0;background:#FFF;border:1px solid #ccc;border-radius:44px;position:absolute;top:0;bottom:0;right:76px;-moz-transition:all .3s ease-in 0s;-webkit-transition:all .3s ease-in 0s;-o-transition:all .3s ease-in 0s;transition:all .3s ease-in 0s;background-image:-webkit-linear-gradient(top,#ddd 0,#fff 100%);box-shadow:rgba(0,0,0,.1) -1px 0 1px 1px,rgba(255,255,255,.5) 0 1px 0 1px inset}.onoffswitch-checkbox:checked+.onoffswitch-label .onoffswitch-inner{margin-left:0}.onoffswitch-checkbox:checked+.onoffswitch-label .onoffswitch-switch{right:0}</style><title>Config Wemos IoT Relay</title></head><body><h1>Wemos Panel</h1><div class=\"section\"><span class=\"section-title\">Relay 01</span><div class=\"onoffswitch\"><input type=\"checkbox\" name=\"onoffswitch1\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch1\" onclick=\"toggle(1)\"> <label class=\"onoffswitch-label\" for=\"myonoffswitch1\"><div class=\"onoffswitch-inner\"></div><div class=\"onoffswitch-switch\"></div></label></div></div><div class=\"section\"><span class=\"section-title\">Relay 02</span><div class=\"onoffswitch\"><input type=\"checkbox\" name=\"onoffswitch2\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch2\" onclick=\"toggle(2)\"> <label class=\"onoffswitch-label\" for=\"myonoffswitch2\"><div class=\"onoffswitch-inner\"></div><div class=\"onoffswitch-switch\"></div></label></div></div><div class=\"section\"><span class=\"section-title\">Relay 03</span><div class=\"onoffswitch\"><input type=\"checkbox\" name=\"onoffswitch3\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch3\" onclick=\"toggle(3)\"> <label class=\"onoffswitch-label\" for=\"myonoffswitch3\"><div class=\"onoffswitch-inner\"></div><div class=\"onoffswitch-switch\"></div></label></div></div><div class=\"section\"><span class=\"section-title\">Relay 04</span><div class=\"onoffswitch\"><input type=\"checkbox\" name=\"onoffswitch4\" class=\"onoffswitch-checkbox\" id=\"myonoffswitch4\" onclick=\"toggle(4)\"> <label class=\"onoffswitch-label\" for=\"myonoffswitch4\"><div class=\"onoffswitch-inner\"></div><div class=\"onoffswitch-switch\"></div></label></div></div></body><script>var endpoint=\"http://\"+location.host+\"/api/v1/relay/switch?id=\";function toggle(e){var o=new XMLHttpRequest;o.onload=function(){200<=o.status&&o.status<300?(console.log(\"success!\"),response=JSON.parse(o.responseText),document.getElementById(\"myonoffswitch\"+e).checked=response.status):(console.log(\"error\"),alert(\"error\"),document.getElementById(\"myonoffswitch\"+e).checked=!1)},o.onerror=function(){console.log(\"error\"),alert(\"error\"),document.getElementById(\"myonoffswitch\"+e).checked=!1},o.timeout=5e3,o.open(\"PUT\",endpoint+e),o.send()}</script></html>");
}







void handleConnect() {
 if (server.args() < 1) {
    handleError(404, "json object not provided");
    return;
  }

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg(0));

  if (!root.success()) {
    handleError(404, "parse json object failed");
    return;
  }

  if (!root.containsKey("ssid")) {
    handleError(404, "ssid not provided");
    return;
  }

  if (!root.containsKey("password")) {
    handleError(404, "password not provided");
    return;
  }

  String ssid = root["ssid"];
  String password = root["password"];

  Serial.println(ssid);
  Serial.println(password);

  ssid.toCharArray(ssidClient, 32);
  password.toCharArray(passwordClient, 64);

  bool connected = connectToAP();

  if (connected) {
    Serial.println("connected to ip: ");
    Serial.print(WiFi.localIP());
    saveCredentials();
    
    server.send(200, "application/json", "{\"status\":\"ok\",\"ip\":\"" + WiFi.localIP().toString() + "\"}");
  } else {
    Serial.println("Error to connect");
    handleError(400, "Error to connect");
  }
}






void scanWifiNetworks() {
  Serial.println("Scanning networks");
  int n = WiFi.scanNetworks();
  Serial.println("Scan done");

  StaticJsonBuffer<2200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  JsonArray& data = root.createNestedArray("data");

  if (n > 0) {
    int limit = (n > 15) ? 15 : n;
    
    for (int i = 0; i < limit; i++) {
      JsonObject& object = data.createNestedObject();
      object["index"] = i;
      object["ssid"] = WiFi.SSID(i);
      object["rssi"] = WiFi.RSSI(i);
      object["encryption"] = WiFi.encryptionType(i) == ENC_TYPE_NONE ? "none" : "*";
    }
  }
  
  char json[5000];
  root.printTo(json);

  server.send(200, "application/json", json);
}







bool connectToAP() {
  Serial.println("Connecting to: ");
  Serial.print(String(ssidClient));

  int attemps = 0;
  bool connected = false;

  WiFi.begin(ssidClient, passwordClient);

  while (WiFi.status() != WL_CONNECTED && attemps < 30) {
    ++attemps;
    Serial.print(".");
    delay(250);
  }

  if (attemps < 10) {
    connected = true;
  } 

  return connected;
}






/*
 * Send json of Relay by ID
 * 
 * use: http://host/api/v1/relay?id=1
 * method: GET
 */
void getRelay() {
	if (server.arg("id") == "") {
		handleError(404, "id element not provided");
		return;
	}

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }
  
  char json[120];
  Relay& relay = relayCollection.getByIndex(index);
  relay.toJson().printTo(json);

  Serial.println(relay.toString());
 
  server.send(200, "application/json", json);
}






/*
 * Return a json Array with all relays objects available.
 * 
 * use: http://host/api/v1/relays
 * method: GET
 */
void getRelays() {
  Relay*& collection = relayCollection.getCollection();
  Serial.println(collection[1].toString());

  int arrayLength = sizeof(collection);
  String response = "{\"data\":[";
  
  for (int i = 0; i < arrayLength; i++) {
    JsonObject& json = collection[i].toJson();
    char value[120];
    json.printTo(value);
    response = response + String(value);
 
    if (i < (arrayLength - 1)) {
      response = response + ",";
    }
  }

  response = response + "]}";
  
  server.send(200, "application/json", response);
}







/*
 * Update a relay by ID
 * This method gets an json object from request, encode and set 
 * parameters requested by client.
 * On error, method response with error response.
 * 
 * use: http://host/api/v1/relay
 * method: PUT
 * params: { "id": 1, "status": true, "alias": "some text", "enabled": true }
 */
void updateRelay() {
  if (server.args() < 1) {
    handleError(404, "json object not provided");
    return;
  }

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg(0));

  if (!root.success()) {
    handleError(404, "parse json object failed");
    return;
  }

  if (!root.containsKey("id")) {
    handleError(404, "id not provided");
    return;
  }

  int id = root["id"];
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  
  if (root.containsKey("status")) {
    bool status = root["status"];
    relay.setStatus(status);
  }

 
  if (root.containsKey("alias")) {
    String alias = root["alias"];
    relay.setAlias(alias);
  }

  
  if (root.containsKey("enabled")) {
    bool enabled = root["enabled"];
    relay.setEnabled(enabled);
  }

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}







/*
 * Change the enabled property of a relay to false
 * If property enable of a relay is false, the relay can't turn on
 * 
 * use: http://host/api/v1/relay?id=1
 * method: DELETE
 */
void deleteRelay() {
  if (server.arg("id") == "") {
    handleError(404, "id not provided");
    return;
  }

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  relay.setEnabled(false);

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}





/*
 * Switch status of a relay
 * 
 * use: http://host/api/v1/relay/switch?id=1
 * method: PUT
 */
void switchRelay() {
  if (server.arg("id") == "") {
    handleError(404, "id not provided");
    return;
  }

  int id = server.arg("id").toInt();
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
  relay.swap();

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}







/*
 * Send an error http response to client
 */
void handleError(int httpCode, String message) {
  StaticJsonBuffer<150> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();

  root["status"] = httpCode;
  root["message"] = message;

  char json[100];
  root.printTo(json);
  
	server.send(httpCode, "application/json", json);
}






/*
 * Set enabled true to a relay available
 * 
 * use: http://host/api/v1/relay
 * method: POST
 * params: { "id": 1, "alias": "some text" }
 */
void createRelay() {
  if (server.args() < 1) {
    handleError(404, "json object not provided");
    return;
  }

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(server.arg(0));

  if (!root.success()) {
    handleError(404, "parse json object failed");
    return;
  }

  if (!root.containsKey("id")) {
    handleError(404, "id not provided");
    return;
  }

  int id = root["id"];
  int index = relayCollection.getIndexById(id);

  if (index < 0) {
    handleError(404, "id is not valid");
    return;
  }

  Relay& relay = relayCollection.getByIndex(index);
 
  if (root.containsKey("alias")) {
    String alias = root["alias"];
    relay.setAlias(alias);
  }

  relay.setEnabled(true);
  relay.setStatus(false);

  Serial.println("Relay updated:");
  Serial.println(relay.toString());
  
  char json[120];
  relay.toJson().printTo(json);

  server.send(200, "application/json", json);
}





void saveCredentials() {
  wifiCredentials tempCredentials;
  strcpy(tempCredentials.ssid, ssidClient);
  strcpy(tempCredentials.password, passwordClient);

  EEPROM.put(0, tempCredentials);
  EEPROM.commit();

  Serial.println("Credentials stored");
}






void readCredentials() {
  EEPROM.get(0, credentials);
  Serial.println("Credentials restored");
}







void clearEeprom() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  Serial.println("Credentials deleted");
}
