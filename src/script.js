var manuallySearch = false;
var refreshButton = document.getElementById('refreshButton');
var backButton = document.getElementById('backButton');
var ssidText = document.getElementById('ssidText');
var ssidSelect = document.getElementById('ssidSelect');
var password = document.getElementById('password');
var changeInput = document.getElementById('changeInput');
var loadingLabel = document.getElementById('loadingLabel');
var networks = null;
var endpoint = 'http://' + location.host + '/scannetworks';

var xhr = new XMLHttpRequest();
xhr.onload = function() {
  if (xhr.status >= 200 && xhr.status < 300) {
    console.log('success!');
    networks = JSON.parse(xhr.responseText);
    printOptions();
    enableSelect();
    console.log(networks);
  } else {
    enableSelect();
    console.log('error');
  }
};

xhr.onerror = function() {
  console.log('error');
  enableSelect();
}

function cleanSelectoptions() {
  for (var i = 0; i < ssidSelect.length; i++) {
    ssidSelect.remove(1);
  }
}

function enableSelect() {
  ssidSelect.removeAttribute('disabled');
  loadingLabel.classList.add('hide');
  refreshButton.classList.remove('hide');
  changeInput.classList.remove('hide');
}

function disableSelect() {
  ssidSelect.setAttribute('disabled', 'disabled');
  loadingLabel.classList.remove('hide');
  refreshButton.classList.add('hide');
  changeInput.classList.add('hide');
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

function submitForm(form) {
  console.log('submit!');

  var _xhr = new XMLHttpRequest();

  _xhr.onload = function() {
    if (_xhr.status >= 200 && _xhr.status < 300) {
      console.log('success!');
      console.log(_xhr);
    } else {
      console.log('error');
    }
  };

  _xhr.onerror = function() {
    console.log('error');
  };

  _xhr.open('POST', '/connect');
  _xhr.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
  _xhr.timeout = 15000;
  _xhr.send(JSON.stringify({
    ssid: manuallySearch ? ssidText.value : ssidSelect.value,
    password: password.value
  }));
}

refreshButton.onclick = function() {
  console.log('refresh networks');
  disableSelect();
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