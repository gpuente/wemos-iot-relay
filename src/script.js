var manuallySearch = false;
var refreshButton = document.getElementById('refreshButton');
var backButton = document.getElementById('backButton');
var ssidText = document.getElementById('ssidText');
var ssidSelect = document.getElementById('ssidSelect');
var changeInput = document.getElementById('changeInput');
var networks = null;
var endpoint = 'http://192.168.4.1/scannetworks';

var xhr = new XMLHttpRequest();
xhr.onload = function() {
  if (xhr.status >= 200 && xhr.status < 300) {
    console.log('success!');
    networks = JSON.parse(xhr.responseText);
    printOptions();
    console.log(networks);
  } else {
    console.log('error');
  }
};

function cleanSelectoptions() {
  for (var i = 0; i < ssidSelect.length; i++) {
    ssidSelect.remove(1);
  }
}

function printOptions() {
  var options = networks.data;
  options.forEach(function(network) {
    var option = document.createElement('option');
    option.text = network.ssid;
    option.value = network.ssid;

    ssidSelect.appendChild(option);
  });
}

refreshButton.onclick = function() {
  console.log('refresh networks');
  cleanSelectoptions();
  xhr.timeout = 5000;
  xhr.open('POST', endpoint);
  xhr.send();
};

changeInput.onclick = function() {
  backButton.classList.remove('hide');
  refreshButton.classList.add('hide');
  ssidText.classList.remove('hide');
  ssidSelect.classList.add('hide');
  changeInput.classList.add('hide');

  manuallySearch = true;
};

backButton.onclick = function() {
  backButton.classList.add('hide');
  refreshButton.classList.remove('hide');
  ssidText.classList.add('hide');
  ssidSelect.classList.remove('hide');
  changeInput.classList.remove('hide');

  manuallySearch = false;
};