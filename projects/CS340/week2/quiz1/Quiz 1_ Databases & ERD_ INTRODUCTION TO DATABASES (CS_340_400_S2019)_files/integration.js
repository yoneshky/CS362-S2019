(function() {
  var SmarterServices = {
    installSid: null,
    installConsumersSid: null,
    setup: function(config) {
      SmarterServices.deploymentSid = config.deploymentSid;
      SmarterServices.consumerSid = config.consumerSid;
      SmarterServices.fetch();
    },
    fetch: function() {
      const services = document.createElement('script');
      services.type = 'text/javascript';
      services.async = true;
      services.src = 'https://client.smarterid.com/static/client/services.js?deploymentSid=' + SmarterServices.deploymentSid + '&consumerSid=' + SmarterServices.consumerSid + '&v=1.1';
      document.body.appendChild(services);
    }
  }

  // Format SmarterID LTI tool
  const links = document.querySelectorAll('a');

  for(var i = 0; i < links.length; i++) {
    if(links[i].innerHTML.indexOf('SmarterID') > -1) {
      links[i].innerHTML = links[i].innerHTML.replace('[SmarterID]', '');
      links[i].innerHTML = links[i].innerHTML.replace('{SmarterID}', '');
      links[i].innerHTML = links[i].innerHTML.replace('(SmarterID)', '');
    }
  }

  window.SmarterServices = SmarterServices;
}());
