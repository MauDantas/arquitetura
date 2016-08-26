if (self.CavalryLogger) { CavalryLogger.start_js(["CWLma"]); }

__d("NotifTestIDs",[],(function a(b,c,d,e,f,g){c.__markCompiled&&c.__markCompiled();f.exports={REACT_BLUE_BAR_JEWEL:"react_blue_bar_jewel",NON_REACT_BLUE_BAR_JEWEL:"non_react_blue_bar_jewel",REACT_NOTIF_LIST:"react_notif_list",SEE_ALL_LIST:"see_all_list",REACT_NOTIF_JEWEL_FLYOUT:"react_notif_jewel_flyout",NON_REACT_NOTIF_JEWEL_FLYOUT:"non_react_notif_jewel_flyout",CHEVRON:"chevron",REACT_MARK_ALL_AS_READ_LINK:"react_mark_all_as_read_link",NON_REACT_MARK_ALL_AS_READ_LINK:"non_react_mark_all_as_read_link",NOTIFICATION_SOUND_SETTING:"notifiation_sound_setting",NOTIFICATION_SOUND_SETTING_SELECTOR:"notifiation_sound_setting_selector",MESSAGE_SOUND_SETTING:"message_sound_setting",MESSAGE_SOUND_SETTING_SELECTOR:"message_sound_setting_selector",CLOSE_FRIEND_ACTIVITY_SELECTOR:"close_friend_activity_selector",BIRTHDAY_SELECTOR:"birthday_selector",ON_THIS_DAY_SELECTOR:"on_this_day_selector",TAGS_SELECTOR:"tags_selector",LIVE_VIDEO_SELECTOR:"live_video_selector",REACT_BADGE_COUNT_CONTAINER:"react_badge_count_container",NON_REACT_BADGE_COUNT_CONTAINER:"non_react_badge_count_container",BEEPER_LIST:"beeper_list",NON_REACT_SETTING_LINK:"non_react_setting_link",REACT_SETTING_LINK:"react_setting_link"};}),null);
__d("SyncRequestStatusEnum",[],(function a(b,c,d,e,f,g){c.__markCompiled&&c.__markCompiled();f.exports={PENDING:0,ACCEPTED:1,REJECTED:2,EXPIRED:3,CANCELED:4,namesByValue:["PENDING","ACCEPTED","REJECTED","EXPIRED","CANCELED"]};}),null);
__d('EgoAdsObjectSet',['csx','DataAttributeUtils','DOM'],(function a(b,c,d,e,f,g,h){if(c.__markCompiled)c.__markCompiled();var i=void 0;function j(l){'use strict';i=l;this._allEgoUnits=[];this._egoUnits=[];}j.prototype.init=function(l){'use strict';this._allEgoUnits=l;this._egoUnits=[];this._allEgoUnits.forEach(function(m){var n=k(m);if(!n||!n.holdout)this._egoUnits.push(m);},this);};j.prototype.getCount=function(){'use strict';return this._egoUnits.length;};j.prototype.forEach=function(l,m){'use strict';this._egoUnits.forEach(l,m);};j.prototype.getUnit=function(l){'use strict';return this._egoUnits[l];};j.prototype.getHoldoutAdIDsForSpace=function(l,m){'use strict';if(!l||!m)return [];var n=[];for(var o=0;l>0&&o<this._allEgoUnits.length;o++){var p=this._allEgoUnits[o],q=m(p),r=k(p);if(l>=q&&r&&r.holdout)n.push(r.adid);l-=q;}return n;};j.prototype.getHoldoutAdIDsForNumAds=function(l){'use strict';l=Math.min(l,this._allEgoUnits.length);var m=[];for(var n=0;n<l;n++){var o=this._allEgoUnits[n],p=k(o);if(p&&p.holdout)m.push(p.adid);}return m;};function k(l){var m=c('DOM').scry(l,i||"div._4u8")[0],n=m&&c('DataAttributeUtils').getDataAttribute(m,'data-ad');return n&&JSON.parse(n)||undefined;}f.exports=j;}),null);
__d('rayInterceptsBox',['invariant'],(function a(b,c,d,e,f,g,h){if(c.__markCompiled)c.__markCompiled();function i(k,l){var m=Object.keys(k);l.forEach(function(n){!(m.indexOf(n)!==-1)?h(0):void 0;!(typeof k[n]==='number')?h(0):void 0;});}var j={check:function(k,l){i(k,['minX','maxX','minY','maxY']);i(l,['x','y','dx','dy']);!(k.maxX>k.minX&&k.maxY>k.minY)?h(0):void 0;if(l.dx===0&&l.dy===0)return false;if(l.x>=k.minX&&l.x<=k.maxX&&l.y>=k.minY&&l.y<=k.maxY)return true;var m=(k.minX-l.x)/l.dx,n=(k.maxX-l.x)/l.dx,o=(k.minY-l.y)/l.dy,p=(k.maxY-l.y)/l.dy,q=Math.max(Math.min(m,n),Math.min(o,p)),r=Math.min(Math.max(m,n),Math.max(o,p));if(q<0)return false;if(q>r)return false;return true;}};f.exports=j;}),null);
__d('AdsMouseStateStore',['invariant','Arbiter','DOM','Event','Vector','$','keyMirrorRecursive','rayInterceptsBox','throttle'],(function a(b,c,d,e,f,g,h){'use strict';if(c.__markCompiled)c.__markCompiled();var i=30,j=500,k=c('keyMirrorRecursive')({STATIONARY:'',INTENT:'',HOVER:'',NO_INTENT:''}),l=void 0,m=void 0,n=void 0,o=void 0,p=void 0;function q(){l=k.STATIONARY;m=0;n=0;o=Date.now();p='pagelet_ego_pane';}q();function r(event){try{return {x:event.clientX||event.x,y:event.clientY||event.y};}catch(t){var u=Math.random()*1000;return {x:u,y:u};}}var s=Object.assign(new (c('Arbiter'))(),{getState:function(){return l;},updateRhcID:function(t){!c('$')(t)?h(0):void 0;p=t;},getRhcID:function(){return p;},onPageTransition:function(event){q();},onMouseMove:function(event){this.calculateState(r(event));},__updateMousePos:function(t){m=t.x;n=t.y;},isRhcPresent:function(){if(!c('DOM').scry(document.body,'#'+p).length)return false;var t=this.getRhcDimensions();return t.y>0&&t.x>0;},getRhc:function(){return c('$')(p);},getRhcPosition:function(){return c('Vector').getElementPosition(this.getRhc());},getRhcScreenPos:function(){var t=c('Vector').getScrollPosition(),u=this.getRhcPosition();return {x:u.x-t.x,y:u.y-t.y};},getRhcDimensions:function(){return c('Vector').getElementDimensions(this.getRhc());},getRhcBoundingBox:function(){var t=this.getRhcDimensions(),u=this.getRhcScreenPos();return {minX:u.x,maxX:u.x+t.x,minY:u.y,maxY:u.y+t.y};},isPosContainedInRhc:function(t){var u=this.getRhcBoundingBox();return (t.x>=u.minX&&t.x<=u.maxX&&t.y>=u.minY&&t.y<=u.maxY);},hasMovedMinDistance:function(t){var u=t.x-m,v=t.y-n;return u*u+v*v>=i*i;},tooSoon:function(){return Date.now()-o<j;},_updateTime:function(){o=Date.now();},calculateState:function(t){if(this.tooSoon())return;this._updateTime();if(!this.isRhcPresent())return;if(this.isPosContainedInRhc(t)){this.transitionToState(k.HOVER);this.__updateMousePos(t);this.scheduleCheckup();return;}else if(!this.hasMovedMinDistance(t)){this.transitionToState(k.STATIONARY);return;}var u=this.isMovingTowardsRhc(t)?k.INTENT:k.NO_INTENT;this.transitionToState(u);this.__updateMousePos(t);this.scheduleCheckup();},isMovingTowardsRhc:function(t){var u={x:m,y:n};if(this.isPosContainedInRhc(u))return true;var v=this.getRhcBoundingBox(),w={x:m,y:n,dx:t.x-m,dy:t.y-n};return c('rayInterceptsBox').check(v,w);},scheduleCheckup:function(){var t={x:m,y:n};setTimeout(function(){this.calculateState(t);}.bind(this),j*1.5);},transitionToState:function(t){if(t===l)return;l=t;s.inform('change');}});c('Event').listen(document,'mousemove',c('throttle')(s.onMouseMove.bind(s),j));c('Arbiter').subscribe('page_transition',s.onPageTransition);s.STATES=k;s.MIN_MOVE_DISTANCE=i;s.THROTTLE_TIME=j;f.exports=s;}),null);
__d('BusinessURI.brands',['BizSiteIdentifier.brands','BusinessConf','URI'],(function a(b,c,d,e,f,g){var h,i;if(c.__markCompiled)c.__markCompiled();h=babelHelpers.inherits(j,c('URI'));i=h&&h.prototype;function j(l,m){'use strict';i.constructor.call(this,l);if(c('BizSiteIdentifier.brands').isBizSite()){var n=m||c('BizSiteIdentifier.brands').getBusinessID();if(n)this.addQueryData(c('BusinessConf').BIZ_ID_PARAM_NAME,n);if(!this.$BusinessURI1(this.getSubdomain()))this.setSubdomain(c('BusinessConf').DOMAIN);}return this;}j.prototype.$BusinessURI1=function(l){'use strict';return l==='developers';};var k=function(l,m){return new j(l,m);};f.exports=k;}),null);
__d('FBProfilePhotoShadow.react',['cx','React','joinClasses'],(function a(b,c,d,e,f,g,h){var i,j;if(c.__markCompiled)c.__markCompiled();i=babelHelpers.inherits(k,c('React').Component);j=i&&i.prototype;k.prototype.render=function(){'use strict';var l=this.props,m=l.className,n=l.children,o=babelHelpers.objectWithoutProperties(l,['className','children']),p=c('React').Children.only(n);return (c('React').createElement('div',babelHelpers['extends']({},o,{className:c('joinClasses')(m,"_38vo")}),c('React').cloneElement(p,{className:c('joinClasses')(p.props.className,"_44ma")})));};function k(){'use strict';i.apply(this,arguments);}f.exports=k;}),null);
__d("ScriptPathState",["Arbiter"],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h,i,j,k,l=100,m={setIsUIPageletRequest:function(n){j=n;},setUserURISampleRate:function(n){k=n;},reset:function(){h=null;i=false;j=false;},_shouldUpdateScriptPath:function(){return i&&!j;},_shouldSendURI:function(){return Math.random()<k;},getParams:function(){var n={};if(m._shouldUpdateScriptPath()){if(m._shouldSendURI()&&h!==null)n.user_uri=h.substring(0,l);}else n.no_script_path=1;return n;}};c("Arbiter").subscribe("pre_page_transition",function(n,o){i=true;h=o.to.getUnqualifiedURI().toString();});f.exports=b.ScriptPathState=m;}),null);
__d('AjaxPipeRequest',['Arbiter','AsyncRequest','BigPipe','CSS','DOM','Env','PageEvents','PageletSet','ScriptPathState','URI','containsNode','ge','goOrReplace','performance','performanceAbsoluteNow'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h,i=0;function j(m,n){var o=c('ge')(m);if(!o)return;if(!n)o.style.minHeight='100px';var p=c('PageletSet').getPageletIDs();for(var q=0;q<p.length;q++){var r=p[q];if(c('containsNode')(o,c('ge')(r)))c('PageletSet').removePagelet(r);}c('DOM').empty(o);c('Arbiter').inform('pagelet/destroy',{id:null,root:o});}function k(m,n){var o=c('ge')(m);if(o&&!n)o.style.minHeight='100px';}function l(m,n){'use strict';this._uri=m;this._query_data=n;this._request=new (c('AsyncRequest'))();this._canvas_id=null;this._allow_cross_page_transition=true;this._arbiter=new (c('Arbiter'))();this._requestID=i++;}l.prototype.setCanvasId=function(m){'use strict';this._canvas_id=m;return this;};l.prototype.setURI=function(m){'use strict';this._uri=m;return this;};l.prototype.setData=function(m){'use strict';this._query_data=m;return this;};l.prototype.getData=function(m){'use strict';return this._query_data;};l.prototype.setAllowCrossPageTransition=function(m){'use strict';this._allow_cross_page_transition=m;return this;};l.prototype.setAppend=function(m){'use strict';this._append=m;return this;};l.prototype.send=function(){'use strict';this._arbiter.inform(c('PageEvents').AJAXPIPE_SEND,{rid:this._requestID,quickling:!!this._isQuickling,ts:c('performanceAbsoluteNow')()},c('Arbiter').BEHAVIOR_PERSISTENT);var m={ajaxpipe:1,ajaxpipe_token:c('Env').ajaxpipe_token};Object.assign(m,c('ScriptPathState').getParams());c('ScriptPathState').reset();this._request.setOption('useIframeTransport',true).setURI(this._uri).setData(Object.assign(m,this._query_data)).setPreBootloadHandler(this._preBootloadHandler.bind(this)).setInitialHandler(this._onInitialResponse.bind(this)).setHandler(this._onResponse.bind(this)).setMethod('GET').setReadOnly(true).setAllowCrossPageTransition(this._allow_cross_page_transition).setAllowIrrelevantRequests(this._allowIrrelevantRequests);if(this._automatic){this._relevantRequest=h;}else h=this._request;if(this._isQuickling){var n=c('performance').clearResourceTimings||c('performance').webkitClearResourceTimings;if(n)n.call(c('performance'));}this._request.send();return this;};l.prototype._preBootloadFirstResponse=function(m){'use strict';return false;};l.prototype._fireDomContentCallback=function(){'use strict';this._arbiter.inform(c('PageEvents').AJAXPIPE_DOMREADY,true,c('Arbiter').BEHAVIOR_STATE);};l.prototype._fireOnloadCallback=function(){'use strict';if(window.console&&console.timeStamp)console.timeStamp('perf_trace {"name": "e2e",'+' "parent": "PageEvents.AJAXPIPE_ONLOAD"}');this._arbiter.inform(c('PageEvents').AJAXPIPE_ONLOAD,{lid:this.pipe.lid,rid:this._requestID,ts:c('performanceAbsoluteNow')()},c('Arbiter').BEHAVIOR_STATE);};l.prototype._isRelevant=function(m){'use strict';return this._request==h||this._automatic&&this._relevantRequest==h||this._jsNonBlock||h&&h._allowIrrelevantRequests;};l.prototype._preBootloadHandler=function(m){'use strict';var n=m.getPayload();if(!n||n.redirect||!this._isRelevant(m))return false;var o=false;if(m.is_first){!this._append&&!this._displayCallback&&j(this._canvas_id,this._constHeight);o=this._preBootloadFirstResponse(m);this.pipe=new (c('BigPipe'))({arbiter:this._arbiter,rootNodeID:this._canvas_id,lid:this._request.lid,rid:this._requestID,isAjax:true,domContentCallback:this._fireDomContentCallback.bind(this),onloadCallback:this._fireOnloadCallback.bind(this),domContentEvt:c('PageEvents').AJAXPIPE_DOMREADY,onloadEvt:c('PageEvents').AJAXPIPE_ONLOAD,jsNonBlock:this._jsNonBlock,automatic:this._automatic,displayCallback:this._displayCallback,allowIrrelevantRequests:this._allowIrrelevantRequests});}return o;};l.prototype._redirect=function(m){'use strict';if(m.redirect){if(m.force||!this.isPageActive(m.redirect)){var n=['ajaxpipe','ajaxpipe_token'].concat(this.getSanitizedParameters());c('goOrReplace')(window.location,new (c('URI'))(m.redirect).removeQueryData(n),true);}else{var o=b.PageTransitions;o.go(m.redirect,true);}return true;}else return false;};l.prototype.isPageActive=function(m){'use strict';return true;};l.prototype.getSanitizedParameters=function(){'use strict';return [];};l.prototype._versionCheck=function(m){'use strict';return true;};l.prototype._onInitialResponse=function(m){'use strict';var n=m.getPayload();if(!this._isRelevant(m))return false;if(!n)return true;if(this._redirect(n)||!this._versionCheck(n))return false;return true;};l.prototype._processFirstResponse=function(m){'use strict';var n=m.getPayload();if(c('ge')(this._canvas_id)&&n.canvas_class!=null)c('CSS').setClass(this._canvas_id,n.canvas_class);};l.prototype.setFirstResponseCallback=function(m){'use strict';this._firstResponseCallback=m;return this;};l.prototype.setFirstResponseHandler=function(m){'use strict';this._processFirstResponse=m;return this;};l.prototype._onResponse=function(m){'use strict';var n=m.payload;if(!this._isRelevant(m))return c('AsyncRequest').suppressOnloadToken;if(m.is_first){this._processFirstResponse(m);this._firstResponseCallback&&this._firstResponseCallback();n.provides=n.provides||[];n.provides.push('uipage_onload');}if(n){if('content' in n.content&&this._canvas_id!==null){if(this._append)n.append=this._canvas_id;var o=n.content.content;delete n.content.content;n.content[this._canvas_id]=o;}if(n.secondFlushPayload){this.pipe.setSecondFlushPayload(n.secondFlushPayload);}else this.pipe.onPageletArrive(n);}if(m.is_last)k(this._canvas_id,this._constHeight);return c('AsyncRequest').suppressOnloadToken;};l.prototype.setNectarModuleDataSafe=function(m){'use strict';this._request.setNectarModuleDataSafe(m);return this;};l.prototype.setFinallyHandler=function(m){'use strict';this._request.setFinallyHandler(m);return this;};l.prototype.setErrorHandler=function(m){'use strict';this._request.setErrorHandler(m);return this;};l.prototype.setTransportErrorHandler=function(m){'use strict';this._request.setTransportErrorHandler(m);return this;};l.prototype.abort=function(){'use strict';this._request.abort();if(h==this._request)h=null;this._request=null;return this;};l.prototype.setJSNonBlock=function(m){'use strict';this._jsNonBlock=m;return this;};l.prototype.setAutomatic=function(m){'use strict';this._automatic=m;return this;};l.prototype.setDisplayCallback=function(m){'use strict';this._displayCallback=m;return this;};l.prototype.setConstHeight=function(m){'use strict';this._constHeight=m;return this;};l.prototype.setAllowIrrelevantRequests=function(m){'use strict';this._allowIrrelevantRequests=m;return this;};l.prototype.getAsyncRequest=function(){'use strict';return this._request;};l.getCurrentRequest=function(){'use strict';return h;};l.setCurrentRequest=function(m){'use strict';h=m;};f.exports=l;}),null);
__d("UIPageletContentCache",[],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h={cache:{},getContent:function(i){if(i in this.cache)return this.cache[i];return null;},setContent:function(i,j){this.cache[i]=j;}};f.exports=h;}),null);
__d('UIPagelet',['ActorURI','AjaxPipeRequest','AsyncRequest','DOM','HTML','ScriptPathState','UIPageletContentCache','URI','emptyFunction','ge','isElementNode'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();function h(i,j,k){'use strict';var l=i&&c('isElementNode')(i)?i.id:i;this._id=l||null;this._element=c('ge')(i||c('DOM').create('div'));this._src=j||null;this._context_data=k||{};this._data={};this._handler=c('emptyFunction');this._request=null;this._use_ajaxpipe=false;this._use_post_request=false;this._is_bundle=true;this._allow_cross_page_transition=false;this._append=false;this._cache_content=false;this._content_cache_key='';}h.prototype.getElement=function(){'use strict';return this._element;};h.prototype.setHandler=function(i){'use strict';this._handler=i;return this;};h.prototype.go=function(i,j){'use strict';if(arguments.length>=2||typeof i=='string'){this._src=i;this._data=j||{};}else if(arguments.length==1)this._data=i;this.refresh();return this;};h.prototype.setAllowCrossPageTransition=function(i){'use strict';this._allow_cross_page_transition=i;return this;};h.prototype.setBundleOption=function(i){'use strict';this._is_bundle=i;return this;};h.prototype.setErrorHandler=function(i){'use strict';this._errorHandler=i;return this;};h.prototype.setTransportErrorHandler=function(i){'use strict';this.transportErrorHandler=i;return this;};h.prototype.refresh=function(){'use strict';if(this._use_ajaxpipe){c('ScriptPathState').setIsUIPageletRequest(true);this._request=new (c('AjaxPipeRequest'))();this._request.setCanvasId(this._id).setAppend(this._append).setConstHeight(this._constHeight).setJSNonBlock(this._jsNonblock).setAutomatic(this._automatic).setDisplayCallback(this._displayCallback).setFinallyHandler(this._finallyHandler).setAllowIrrelevantRequests(this._allowIrrelevantRequests);if(this._errorHandler)this._request.setErrorHandler(this._errorHandler);if(this.transportErrorHandler)this._request.setTransportErrorHandler(this.transportErrorHandler);}else{if(this._cache_content){var i=c('UIPageletContentCache').getContent(this._content_cache_key);if(i!==null){this.handleContent(i);return this;}}var j=function(n){this._request=null;var o=c('HTML')(n.getPayload());this.handleContent(o);if(this._cache_content)c('UIPageletContentCache').setContent(this._content_cache_key,o);}.bind(this),k=this._displayCallback,l=this._finallyHandler;this._request=new (c('AsyncRequest'))().setMethod('GET').setReadOnly(true).setOption('bundle',this._is_bundle).setHandler(function(n){if(k){k(j.bind(null,n));}else j(n);l&&l();});if(this._errorHandler)this._request.setErrorHandler(this._errorHandler);if(this.transportErrorHandler)this._request.setTransportErrorHandler(this.transportErrorHandler);if(this._use_post_request)this._request.setMethod('POST');}var m=babelHelpers['extends']({},this._context_data,this._data);if(this._actorID)m[c('ActorURI').PARAMETER_ACTOR]=this._actorID;this._request.setURI(this._src).setAllowCrossPageTransition(this._allow_cross_page_transition).setData({data:JSON.stringify(m)}).send();return this;};h.prototype.handleContent=function(i){'use strict';if(this._append){c('DOM').appendContent(this._element,i);}else c('DOM').setContent(this._element,i);this._handler();};h.prototype.cancel=function(){'use strict';if(this._request)this._request.abort();};h.prototype.setUseAjaxPipe=function(i){'use strict';this._use_ajaxpipe=!!i;return this;};h.prototype.setUsePostRequest=function(i){'use strict';this._use_post_request=!!i;return this;};h.prototype.setAppend=function(i){'use strict';this._append=!!i;return this;};h.prototype.setJSNonBlock=function(i){'use strict';this._jsNonblock=!!i;return this;};h.prototype.setAutomatic=function(i){'use strict';this._automatic=!!i;return this;};h.prototype.setDisplayCallback=function(i){'use strict';this._displayCallback=i;return this;};h.prototype.setConstHeight=function(i){'use strict';this._constHeight=!!i;return this;};h.prototype.setFinallyHandler=function(i){'use strict';this._finallyHandler=i;return this;};h.prototype.setAllowIrrelevantRequests=function(i){'use strict';this._allowIrrelevantRequests=i;return this;};h.prototype.setActorID=function(i){'use strict';this._actorID=i;return this;};h.prototype.setCacheContent=function(i){'use strict';this._cache_content=i;return this;};h.prototype.setContentCacheKey=function(i){'use strict';this._content_cache_key=i;return this;};h.appendToInline=function(i,j){'use strict';var k=c('ge')(i),l=c('ge')(j);if(k&&l){while(l.firstChild)c('DOM').appendContent(k,l.firstChild);c('DOM').remove(l);}};h.loadFromEndpoint=function(i,j,k,l){'use strict';l=l||{};var m='/ajax/pagelet/generic.php/'+i;if(l.intern)m='/intern'+m;var n=new (c('URI'))(m.replace(/\/+/g,'/'));if(l.subdomain)n.setSubdomain(l.subdomain);var o=false,p='';if(l.contentCacheKey){o=true;p=i+','+String(l.contentCacheKey);}var q=new h(j,n,k).setUseAjaxPipe(l.usePipe).setBundleOption(l.bundle!==false).setAppend(l.append).setJSNonBlock(l.jsNonblock).setAutomatic(l.automatic).setDisplayCallback(l.displayCallback).setConstHeight(l.constHeight).setAllowCrossPageTransition(l.crossPage).setFinallyHandler(l.finallyHandler||c('emptyFunction')).setErrorHandler(l.errorHandler).setTransportErrorHandler(l.transportErrorHandler).setAllowIrrelevantRequests(l.allowIrrelevantRequests).setActorID(l.actorID).setCacheContent(o).setContentCacheKey(p).setUsePostRequest(l.usePostRequest);l.handler&&q.setHandler(l.handler);q.go();return q;};h.loadFromEndpointBatched=function(i,j,k){'use strict';var l=i.slice(0,k),m=i.slice(k);if(m.length>0){var n=l[l.length-1],o=c('emptyFunction');if(n.options&&n.options.finallyHandler)o=n.options.finallyHandler;n.options=babelHelpers['extends']({},n.options,{finallyHandler:function(){o();window.setTimeout(function(){h.loadFromEndpointBatched(m,j,k);},1);}});}l.forEach(function(p){h.loadFromEndpoint(p.controller,p.target_element,p.data,babelHelpers['extends']({},p.options,j,{bundle:true}));});};f.exports=h;}),null);
__d('TickerController',['invariant','Arbiter','AsyncSignal','Bootloader','CSS','DOM','Parent','UIPagelet','Vector','$','emptyFunction','ge'],(function a(b,c,d,e,f,g,h){if(c.__markCompiled)c.__markCompiled();var i=1,j=2,k=3,l=4,m=15000,n=null,o={},p={},q={setActiveInstance:function(r){n=r;},getActiveInstance:function(){return n;},clearRHCplaceholder:function(){o.pagelet_rhc_ticker=null;},registerInstance:function(r,s){!r?h(0):void 0;p[r]=s;q.setActiveInstance(s);},getInstance:function(r){if(!r)return null;var s=c('Parent').byClass(c('$')(r),'fbFeedTicker');return p[s.id]||null;},isLoaded:function(r){var s=o[r.id];return !s||s.status==k;},show:function(r,s){s=s||c('emptyFunction');for(var t in p){var u=c('ge')(t);if(!u||u.parentNode.id==r.id)continue;q.hide(u.parentNode);}q._doPositionChange(r);c('CSS').show(r);var v=o[r.id];if(v&&v.status==i){var w=(c('Vector').getElementDimensions(r).y||0)>0,x=r.id==='pagelet_rhc_ticker'&&!c('CSS').hasClass(r,'hidden_rhc_ticker');if(w||x){var y=c('DOM').scry(r,'.tickerPlaceholderSpinner')[0];y&&c('CSS').show(y);q._fetchTickerForPlaceholder(r,s);}else c('Arbiter').subscribe('Ticker/resized',function(){if(v.status==i)q._fetchTickerForPlaceholder(r,s);});}else{var z=c('DOM').scry(r,'.fbFeedTicker')[0],aa=q.getInstance(z);n=aa;aa&&aa._poll();o[r.id]={status:l,callback:s};s();}c('Arbiter').inform('ticker/show',{node:r,callback:s});},_doPositionChange:function(r){if(c('CSS').shown(r))return;new (c('AsyncSignal'))('/common/ods_endpoint.php',{k:'ticker.render.switch.'+r.id}).send();},hide:function(r){var s=c('DOM').scry(r,'.fbFeedTicker')[0],t=q.getInstance(s);t&&t.hideActiveStory();c('CSS').hide(r);},hideStoriesByClass:function(r){for(var s in p)c('DOM').scry(c('$')(s),r).forEach(c('CSS').hide);},hideStory:function(r){var s=q.getInstance(r);s&&s.hideStory(r);},replaceStory:function(r,s){var t=c('DOM').scry(document.body,'div.fbFeedTickerStory'),u=q.getInstance(t[0]);if(!u)return;var v=u._findStoryById(r);u.handleRemoveStory();c('CSS').hide(v);c('DOM').insertAfter(v,s);s.setAttribute('data-story-id',v.getAttribute('id'));var w=setTimeout(function(){return q.removeMarkup(s,v);},m);s.setAttribute('data-timeout-token',w);},removeMarkup:function(r,s){c('Bootloader').loadModules(["Animation"],function(t){c('CSS').addClass(r,'removedStoryMarkup');new t(r).to('height',0).duration(500).ondone(function(){c('DOM').remove(r);}).go();},'TickerController');},undoHideStory:function(r){var s=q.getInstance(r);s&&s.undoHideStory(r);},insertStoriesAtBottom:function(r){n.insertStoriesAtBottom(r);},_fetchTickerForPlaceholder:function(r,s){var t={handler:function(){o[r.id].status=k;s();}};c('UIPagelet').loadFromEndpoint('TickerEntStoryPagelet',r.id,o[r.id].pageletData,t);o[r.id].status=j;},registerStoryDialog:function(r,s){c('Arbiter').subscribe('ticker/init',function(){var t=c('ge')(r),u=q.getInstance(t);u&&u.registerStoryDialog(t,s);},c('Arbiter').SUBSCRIBE_ALL);},registerPlaceholder:function(r,s){var t=o[r];o[r]={status:i,pageletData:s};if(t&&t.status==l){q.show(c('$')(r));t.callback();}}};f.exports=q;}),null);
__d('tickerPhoteSnowLiftOpenStatus',['ArbiterMixin'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h='CheckIsOpen',i={registerOpenChecker:function(j){return i.subscribe(h,function(k,l){if(j())l.is_Open=true;});},checkIsOpen:function(){var j={is_Open:false};i.inform(h,j);return j.is_Open;}};Object.assign(i,c('ArbiterMixin'));f.exports=i;}),null);
__d('RequestsJewelStore',['Arbiter','ArbiterMixin','ChannelConstants'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h=babelHelpers['extends']({},c('ArbiterMixin'),{_initialized:false,_count:0,_requestList:{},addFriendRequests:function(i){Object.assign(this._requestList,i);},getRequestListKeys:function(){return Object.keys(this._requestList);},removeRequest:function(i){delete this._requestList[i];},getRequestCount:function(i){return this.getRequestListKeys().length;},decrementCount:function(){this.setCount(Math.max(0,this._count-1));},setCount:function(i){c('Arbiter').inform('jewel/count-updated',{jewel:'requests',count:i},c('Arbiter').BEHAVIOR_STATE);},setupListeners:function(){if(this._initialized)return;this._initialized=true;c('Arbiter').subscribe('jewel/count-updated',function(i,j){j.jewel==='requests'&&this._updateCount(j.count);}.bind(this));c('Arbiter').subscribe(c('ChannelConstants').getArbiterType('jewel_requests_add'),function(i,j){return this._addRequest(j);}.bind(this));c('Arbiter').subscribe(c('ChannelConstants').getArbiterType('jewel_friending_notifs'),function(i,j){return this._addNotification(j);}.bind(this));c('Arbiter').subscribe(c('ChannelConstants').getArbiterType('jewel_requests_remove_old'),function(i,j){return this._removeOldRequest(j);}.bind(this));c('Arbiter').subscribe(c('ChannelConstants').getArbiterType('friend_requests_seen'),function(i,j){return this.setCount(0);}.bind(this));},_updateCount:function(i){var j=this._count!==i;this._count=i;if(j)this.inform('countUpdated',i);},_addRequest:function(i){if(!i)return;var j=i.obj,k=j.from,l=j.suggester,m=this._requestList[k];if(!m)this.setCount(this._count+1);var n=m?m.type:null,o=n===19&&!l;this.inform('addRequest',{shouldReplace:o,previousType:n});},_addNotification:function(i){if(!i||i.obj.notif_type!=='friend_confirmed')return;this.inform('addNotification');},_removeOldRequest:function(i){if(!i)return;var j=this._requestList[i.obj.from];if(!j)return;this.inform('removeOldRequest',j);}});f.exports=h;}),null);
__d('ChatTabViewEvents',['Arbiter'],(function a(b,c,d,e,f,g){'use strict';if(c.__markCompiled)c.__markCompiled();f.exports=new (c('Arbiter'))();}),null);
__d("CSSClassTransition",[],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h=[];function i(){}Object.assign(i,{go:function(j,k,l,m){var n;for(var o=0;o<h.length;o++)if(h[o](j,k,l,m)===true)n=true;if(!n)j.className=k;},registerHandler:function(j){h.push(j);return {remove:function(){var k=h.indexOf(j);if(k>=0)h.splice(k,1);}};}});f.exports=i;}),null);
__d('DocumentTitle',['Arbiter'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h=document.title,i=null,j=1500,k=[],l=0,m=null,n=false;function o(){if(k.length>0){if(!n){p(k[l].title);l=++l%k.length;}else q();}else{clearInterval(m);m=null;q();}}function p(s){document.title=s;n=true;}function q(){r.set(i||h,true);n=false;}var r={get:function(){return h;},set:function(s,t){document.title=s;if(!t){h=s;i=null;c('Arbiter').inform('update_title',s);}else i=s;},blink:function(s){var t={title:s};k.push(t);if(m===null)m=setInterval(o,j);return {stop:function(){var u=k.indexOf(t);if(u>=0){k.splice(u,1);if(l>u){l--;}else if(l==u&&l==k.length)l=0;}}};}};f.exports=r;}),null);
__d('cxodecode',['invariant'],(function a(b,c,d,e,f,g,h){'use strict';if(c.__markCompiled)c.__markCompiled();var i=36,j=2;function k(l){if(!l)return '';var m=l.cxononce;!m?h(0):void 0;var n=m.substr(0,m.length-j),o=parseInt(m.substr(-j),i),p='';for(var q=0;q<n.length;q+=j)p+=String.fromCharCode(parseInt(n.substr(q,j),i)^o);return p;}f.exports=k;}),null);
__d('VideoPermalinkURI',[],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h={isValid:function(i){return h.parse(i)!==null;},parse:function(i){if(this.isValidLegacy(i)){var j=i.getQueryData();if(j.v)return {video_id:j.v,set_token:j.set};return null;}var k=i.getPath();if(k[k.length-1]==='/')k=k.substring(0,k.length-1);var l=k.split('/');if(l.length>=3&&l[2]==='videos')if(l.length===4&&/^\d+$/.exec(l[3])!==null){return {video_id:l[3],set_token:null};}else if(l.length===5&&/^\d+$/.exec(l[4])!==null)return {video_id:l[4],set_token:l[3]};return null;},isValidLegacy:function(i){var j=i.getPath();if(j[j.length-1]==='/')j=j.substring(0,j.length-1);if(j==='/photo.php'||j==='/force_photo/photo.php'||j==='/photo'||j==='/force_photo/photo/index.php'||j==='/photo/index.php'||j==='/force_photo/photo'||j==='/video.php'||j==='/video/video.php')return true;return false;}};f.exports=h;}),null);
__d('LikeConfirmer',['AsyncDialog','AsyncRequest'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();var h=false,i=false,j={likeContent:function(){},like:function(k,l){this.likeContent=k;if(i)return;if(h){this.likeContent();}else{var m=new (c('AsyncRequest'))().setURI('/like/confirm_like.php').setRelativeTo(l);c('AsyncDialog').send(m,function(n){i=true;n.subscribe('hide',this.onCloseLikeConfirmDialog.bind(this));n.setCausalElement(l);}.bind(this));}return false;},isShowingConfirmation:function(){return i;},onCloseLikeConfirmDialog:function(){i=false;},likeSkipConfirmation:function(k){h=k;this.likeContent();}};f.exports=j;}),null);
__d("arrayStableSort",[],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();function h(i,j){return i.map(function(k,l){return {data:k,index:l};}).sort(function(k,l){return j(k.data,l.data)||k.index-l.index;}).map(function(k){return k.data;});}f.exports=h;}),null);
__d('RangedCallbackManager',['CallbackManagerController','arrayStableSort','createObjectFrom'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();function h(i,j,k){'use strict';this.$RangedCallbackManager1=[];this.$RangedCallbackManager2=false;this.$RangedCallbackManager3=false;this.$RangedCallbackManager4={};this.$RangedCallbackManager5=new (c('CallbackManagerController'))(this.$RangedCallbackManager6.bind(this));this.$RangedCallbackManager7=i;this.$RangedCallbackManager8=j;this.$RangedCallbackManager9=k;}h.prototype.executeOrEnqueue=function(i,j,k,l,m){'use strict';return this.$RangedCallbackManager5.executeOrEnqueue({start:i,limit:j},k,{strict:!!l,skipOnStrictHandler:m});};h.prototype.unsubscribe=function(i){'use strict';this.$RangedCallbackManager5.unsubscribe(i);};h.prototype.getUnavailableResources=function(i){'use strict';var j=this.$RangedCallbackManager5.getRequest(i),k=[];if(j&&!this.$RangedCallbackManager2){var l=j.request,m=this.$RangedCallbackManager10(j.options),n=l.start+l.limit;for(var o=m.length;o<n;o++)k.push(o);}return k;};h.prototype.addResources=function(i){'use strict';i.forEach(function(j){if(!this.$RangedCallbackManager4[j]){this.$RangedCallbackManager4[j]=true;this.$RangedCallbackManager1.push(j);this.$RangedCallbackManager3=null;}}.bind(this));this.resortResources();this.$RangedCallbackManager5.runPossibleCallbacks();};h.prototype.addResourcesWithoutSorting=function(i,j){'use strict';var k=this.$RangedCallbackManager1.slice(0,j);k=k.concat(i);k=k.concat(this.$RangedCallbackManager1.slice(j));this.$RangedCallbackManager1=k;Object.assign(this.$RangedCallbackManager4,c('createObjectFrom')(i,true));this.$RangedCallbackManager3=null;this.$RangedCallbackManager5.runPossibleCallbacks();};h.prototype.removeResources=function(i){'use strict';i.forEach(function(j){if(this.$RangedCallbackManager4[j]){this.$RangedCallbackManager4[j]=false;var k=this.$RangedCallbackManager1.indexOf(j);if(k!=-1)this.$RangedCallbackManager1.splice(k,1);}}.bind(this));};h.prototype.removeAllResources=function(){'use strict';this.$RangedCallbackManager1=[];this.$RangedCallbackManager4={};};h.prototype.resortResources=function(){'use strict';this.$RangedCallbackManager1=c('arrayStableSort')(this.$RangedCallbackManager1,function(i,j){return (this.$RangedCallbackManager8(this.$RangedCallbackManager7(i),this.$RangedCallbackManager7(j)));}.bind(this));};h.prototype.setReachedEndOfArray=function(){'use strict';if(!this.$RangedCallbackManager2){this.$RangedCallbackManager2=true;this.$RangedCallbackManager3=null;this.$RangedCallbackManager5.runPossibleCallbacks();}};h.prototype.hasReachedEndOfArray=function(){'use strict';return this.$RangedCallbackManager2;};h.prototype.setError=function(i){'use strict';if(this.$RangedCallbackManager3!==i){this.$RangedCallbackManager3=i;this.$RangedCallbackManager5.runPossibleCallbacks();}};h.prototype.getError=function(i,j,k){'use strict';var l=this.$RangedCallbackManager10({strict:k});return i+j>l.length?this.$RangedCallbackManager3:null;};h.prototype.hasResource=function(i){'use strict';return this.$RangedCallbackManager4[i];};h.prototype.getResourceAtIndex=function(i){'use strict';return this.$RangedCallbackManager1[i];};h.prototype.getAllResources=function(){'use strict';return this.$RangedCallbackManager1.concat();};h.prototype.getCurrentArraySize=function(i){'use strict';return this.$RangedCallbackManager10(i).length;};h.prototype.$RangedCallbackManager10=function(i){'use strict';var j=this.$RangedCallbackManager1;if(i&&i.strict){var k=i.skipOnStrictHandler||this.$RangedCallbackManager9;if(k)j=j.filter(k);}return j;};h.prototype.$RangedCallbackManager6=function(i,j){'use strict';var k=this.$RangedCallbackManager10(j);if(!this.$RangedCallbackManager2&&!this.$RangedCallbackManager3&&i.start+i.limit>k.length){return false;}else{var l=k.slice(i.start,i.start+i.limit),m=i.start+i.limit>k.length?this.$RangedCallbackManager3:null;return [l,m];}};h.prototype.getElementsUntil=function(i){'use strict';var j=[];for(var k=0;k<this.$RangedCallbackManager1.length;k++){var l=this.$RangedCallbackManager7(this.$RangedCallbackManager1[k]);if(this.$RangedCallbackManager8(l,i)>0)break;j.push(this.$RangedCallbackManager1[k]);}return j;};f.exports=h;}),null);
__d('BootloadOnInteraction.react',['BootloadOnRender.react','React'],(function a(b,c,d,e,f,g){var h,i;if(c.__markCompiled)c.__markCompiled();h=babelHelpers.inherits(j,c('React').Component);i=h&&h.prototype;function j(k){'use strict';i.constructor.call(this,k);this.$BootloadOnInteraction1=function(){this.setState({hadUserInteraction:true});}.bind(this);this.state={hadUserInteraction:false};}j.prototype.render=function(){'use strict';if(!this.state.hadUserInteraction)return c('React').cloneElement(this.props.placeholder,{onFocus:this.$BootloadOnInteraction1,onMouseOver:this.$BootloadOnInteraction1,onClick:this.$BootloadOnInteraction1});var k=this.props,l=k.loader,m=k.component,n=k.placeholder;return (c('React').createElement(c('BootloadOnRender.react'),{placeholder:n,loader:l,component:m}));};f.exports=j;}),null);
__d('randomShuffle',['randomInt'],(function a(b,c,d,e,f,g){if(c.__markCompiled)c.__markCompiled();function h(i){for(var j=i.length-1;j>0;j--){var k=c('randomInt').call(this,j+1);if(k!=j){var l=i[k];i[k]=i[j];i[j]=l;}}return i;}f.exports=h;}),null);