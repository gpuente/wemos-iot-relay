var endpoint = 'http://' + location.host + '/api/v1/relay/switch?id=';

function toggle(id) {
  var xhr = new XMLHttpRequest();

  xhr.onload = function() {
    if (xhr.status >= 200 && xhr.status < 300) {
      console.log('success!');
      response = JSON.parse(xhr.responseText);
      document.getElementById("myonoffswitch" + id).checked = response.status;
    } else {
      console.log('error');
      alert('error');
      document.getElementById("myonoffswitch" + id).checked = false;
    }
  };

  xhr.onerror = function() {
    console.log('error');
    alert('error');
    document.getElementById("myonoffswitch" + id).checked = false;
  };

  xhr.timeout = 5000;
  xhr.open('PUT', endpoint + id);
  xhr.send();
};