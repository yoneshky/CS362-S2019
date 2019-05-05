/**
* Store data
* (uses sessionStorage if supported or falls back to cookie)
* @param {name} string
* @param {data} string
**/
function storeData(name, data) {
  try {
    sessionStorage.setItem(name, data);
  } catch(error) {
    document.cookie = name + '=' + data;
  }
}

/**
* Retrieve data
* (uses sessionStorage if supported or falls back to cookie)
* @param {name} string
*/
function getData(name) {
  try {
    return sessionStorage.getItem(name);
  } catch(error) {
    const match = document.cookie.match(new RegExp(name + '=([^;]+)'));

    if(match) {
      return match[1];
    } else {
      return null;
    }
  }
}

/**
* Call the capabilities endpoint to get enabled services
**/
function getServices() {
  const xhr = new XMLHttpRequest();
  const url = 'https://api.smarterid.com/v1/deployments/' + SmarterServices.deploymentSid + '/capabilities?consumerSid=' + SmarterServices.consumerSid;

  xhr.open('GET', url, true);

  xhr.onloadend = function() {
    if(xhr.status === 200) {
      // Store the deploymentSid
      storeData('sid_deploymentSid', SmarterServices.deploymentSid);

      // Store the enabled services
      storeData('sid_services', this.response);

      // Parse the services
      const response = JSON.parse(this.response);

      // Load all the service script files
      insertScripts(response.services)
    } else {
      throwError(this.statusText);
    }
  }

  xhr.onerror = function() {
    throwError('An internal error has occurred.')
  }

  xhr.send();
}

/**
* Load all the script files for the enabled services
* @param {services} array
**/
function insertScripts(services) {
  if(!inIframe()) {
    services.forEach(function(service) {
      // Store required SmarterID data
      if(service.name.toLowerCase() === 'smarterid' && service.metadata) {
        storeData('sid_installSid', service.metadata.installSid);
        storeData('sid_installConsumerSid', service.metadata.installConsumerSid);
        storeData('sid_baseClass', service.baseClass);
      }

      // Check to make sure the script file doesn’t already exist
      const existingScript = document.querySelector('script[src*="'+service.file+'"]');

      if(!existingScript) {
        const script = document.createElement('script');
        script.type = 'text/javascript';
        script.async = true;
        script.src = service.file + '?v=' + (new Date()).getTime();
        document.body.appendChild(script);
      }
    });
  }
}

/**
* Display error message
* @param {error} string
**/
function throwError(error) {
  console.error(error);
}

/**
* Check if document is in an iframe
* @export
*/
function inIframe() {
  try {
    return window.self !== window.top;
  } catch(e) {
    return true;
  }
}

/**
* Initialize the script
**/
function init() {
  if(getData('sid_services') === null || getData('sid_installSid') === null || getData('sid_installConsumerSid') === null) {
    // Get the enabled services if we don’t already have them stored
    getServices();
  } else {
    // Otherwise, just parse the services and load the scripts
    const storedServices = JSON.parse(getData('sid_services'));
    const services = storedServices.services;
    insertScripts(services);
  }
}

window.onload = init;
