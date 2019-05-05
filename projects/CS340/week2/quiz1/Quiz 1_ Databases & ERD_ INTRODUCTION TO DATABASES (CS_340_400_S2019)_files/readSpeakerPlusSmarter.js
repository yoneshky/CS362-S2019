// ReadSpeaker
(function(){
    window.rsConf={
        params:"https://sf1-na.readspeaker.com/script/default/canvas/ReadSpeaker.js?pids=embhl&skin=ReadSpeakerToggleSkin2"
    };
    window.rsConf.toggle={
        customerParams:{customerid:"8840",lang:["en_us","es_mx","fr_fr","de_de"],region:"na",voice:null,readid:null,url:null
    },
    addPreserve:[".nav"],addSkip:[".nav"],
    readids:["course_home_content","discussion_container","assignment_show","content"],
    useIcons:!0
};
    var d=document.getElementsByTagName("HEAD").item(0),a=document.createElement("script");
    a.setAttribute("type","text/javascript");
    a.src="https://sf1-na.readspeaker.com/script/default/canvas/ReadSpeaker.js";
    var b=function(){
        ReadSpeaker.init()
    };
    a.onreadystatechange=a.onload=function(){
        var c=a.readyState;
        if(!b.done&&(!c||/loaded|complete/.test(c)))
            b.done=!0,b();
        ReadSpeaker.q(function(){
            ReadSpeaker.Toggle.init()
        })
    };
    (document.body||d).appendChild(a)
}
)
();
// SmarterServices
(function(){
  const ssInstall = document.createElement('script');
  ssInstall.type = 'text/javascript';
  ssInstall.async = true;
  ssInstall.src = 'https://client.smarterid.com/static/client/integration.js';
  ssInstall.onload = function(){
    SmarterServices.setup({
      deploymentSid: 'AD8aa6044ca70b439ea9abff63cd767652',
      consumerSid: 'CN6256dc6b77a740c8a55ab5fc50fc7063'
    });
  }
  document.body.appendChild(ssInstall);
})();