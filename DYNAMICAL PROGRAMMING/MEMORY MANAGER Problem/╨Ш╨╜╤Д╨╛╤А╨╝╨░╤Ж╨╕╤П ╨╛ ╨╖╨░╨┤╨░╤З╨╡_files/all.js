function ruschar2hex(a) {
  if (a<=0xFF)
    return a.toString(16);
  else switch(a) {
    case 0x0430: return "c1"; break;
    case 0x0431: return "c2"; break;
    case 0x0432: return "d7"; break;
    case 0x0433: return "c7"; break;
    case 0x0434: return "c4"; break;
    case 0x0435: return "c5"; break;
    case 0x0451: return "a3"; break;
    case 0x0436: return "d6"; break;
    case 0x0437: return "da"; break;
    case 0x0438: return "c9"; break;
    case 0x0439: return "ca"; break;
    case 0x043A: return "cb"; break;
    case 0x043B: return "cc"; break;
    case 0x043C: return "cd"; break;
    case 0x043D: return "ce"; break;
    case 0x043E: return "cf"; break;
    case 0x043F: return "d0"; break;
    case 0x0440: return "d2"; break;
    case 0x0441: return "d3"; break;
    case 0x0442: return "d4"; break;
    case 0x0443: return "d5"; break;
    case 0x0444: return "c6"; break;
    case 0x0445: return "c8"; break;
    case 0x0446: return "c3"; break;
    case 0x0447: return "de"; break;
    case 0x0448: return "db"; break;
    case 0x0449: return "dd"; break;
    case 0x044A: return "df"; break;
    case 0x044B: return "d9"; break;
    case 0x044C: return "d8"; break;
    case 0x044D: return "dc"; break;
    case 0x044E: return "c0"; break;
    case 0x044F: return "d1"; break;
    case 0x0410: return "e1"; break;
    case 0x0411: return "e2"; break;
    case 0x0412: return "f7"; break;
    case 0x0413: return "e7"; break;
    case 0x0414: return "e4"; break;
    case 0x0415: return "e5"; break;
    case 0x0401: return "b3"; break;
    case 0x0416: return "f6"; break;
    case 0x0417: return "fa"; break;
    case 0x0418: return "e9"; break;
    case 0x0419: return "ea"; break;
    case 0x041A: return "eb"; break;
    case 0x041B: return "ec"; break;
    case 0x041C: return "ed"; break;
    case 0x041D: return "ee"; break;
    case 0x041E: return "ef"; break;
    case 0x041F: return "f0"; break;
    case 0x0420: return "f2"; break;
    case 0x0421: return "f3"; break;
    case 0x0422: return "f4"; break;
    case 0x0423: return "f5"; break;
    case 0x0424: return "e6"; break;
    case 0x0425: return "e8"; break;
    case 0x0426: return "e3"; break;
    case 0x0427: return "fe"; break;
    case 0x0428: return "fb"; break;
    case 0x0429: return "fd"; break;
    case 0x042A: return "ff"; break;
    case 0x042B: return "f9"; break;
    case 0x042C: return "f8"; break;
    case 0x042D: return "fc"; break;
    case 0x042E: return "e0"; break;
    case 0x042F: return "f1"; break;
    default: return "20"; break;
  }
}

function rus2hex(a) {
  var b="";
  for (var i=0; i<a.length; ++i)
    b+=ruschar2hex(a.charCodeAt(i));
  return b;
}
function findObj(theObj, theDoc)
{
  var p, i, foundObj;
  
  if(!theDoc) theDoc = document;
  /*
  if( (p = theObj.indexOf("?")) > 0 && parent.frames.length)
  {
    theDoc = parent.frames[theObj.substring(p+1)].document;
    theObj = theObj.substring(0,p);
  }
  if(!(foundObj = theDoc[theObj]) && theDoc.all) foundObj = theDoc.all[theObj];
  for (i=0; !foundObj && i < theDoc.forms.length; i++) 
    foundObj = theDoc.forms[i][theObj];
  for(i=0; !foundObj && theDoc.layers && i < theDoc.layers.length; i++) 
    foundObj = findObj(theObj,theDoc.layers[i].document);
  if(!foundObj && document.getElementById)
  */
  foundObj = theDoc.getElementById(theObj);
  
  return foundObj;
}


function readCookie(name)
{
  var cookieValue = "";
  var search = name + "=";
  if(document.cookie.length > 0)
  { 
    offset = document.cookie.indexOf(search);
    if (offset != -1)
    { 
      offset += search.length;
      end = document.cookie.indexOf(";", offset);
      if (end == -1) end = document.cookie.length;
      cookieValue = unescape(document.cookie.substring(offset, end))
    }
  }
  return cookieValue;
}

function writeCookie(name, value, hours)
{
  var expire = "";
  if(hours != null)
  {
    expire = new Date((new Date()).getTime() + hours * 3600000);
    expire = "; expires=" + expire.toGMTString();
  }
  document.cookie = name + "=" + escape(value) + expire;
}

function set_expand_cookie(index, value) {
  var default_expand="111101";
  var expand=readCookie("expand");
  while (expand.length<=index) {
    expand+=default_expand.charAt(expand.length);
  }
  var oldexp=expand;
  expand=expand.substr(0,index)+value+expand.substr(index+1);
  writeCookie("expand", expand, null);
}

function toggleBoxVisibility(divName, hiderName, unhiderName, index) {
  var a,b,c;

  a=findObj(divName);
  b=findObj(hiderName);
  c=findObj(unhiderName);
  if (a) {
    if (a.style) {
      if (a.style.display=="none") {
        a.style.display="block";
        if (b)
          b.style.display="inline";
        if (c)
          c.style.display="none";
        set_expand_cookie(index,"1");
      } else {
        a.style.display="none";
        if (b)
          b.style.display="none";
        if (c)
          c.style.display="inline";
        set_expand_cookie(index,"0");
      }
    }
  }
}


function selectParam(link, id1, id2) {
  var selWnd = open(link + "?id1="+id1+"&id2="+id2, "Select", 
    "width=620,height=420,scrollbars=yes,menubar=no,status=no,top=200,left=100");
//  selWnd.opener=document;
}

function normalize(prefix, theDoc) {
  var i,j,l,m,obj,obj2,obj3,objd;
  j=0;
  l=0;
  for (i=1; i<=5; ++i) {
    obj=findObj(prefix + "hidden_" + i, theDoc); // Поле hidden
    obj2=findObj(prefix + "text_" + i, theDoc);   // Поле text
    objd=findObj(prefix + "div_" + i, theDoc);      // Поле div
    if (obj && obj.value>"-1" && objd.style.display=="inline") {
      l=i-j;
      if (j>0) {
        obj3=findObj(prefix + "hidden_"+l, theDoc); // Поле hidden
        obj3.value=obj.value;
        obj.value="-1";
        obj3=findObj(prefix + "text_" + l, theDoc);    // Поле text
        obj3.value=obj2.value;
        obj2.value="";
        obj3=findObj(prefix + "div_" + l,theDoc);       // Поле div
        obj3.style.display="inline";
      }
    } else ++j;
  }
  if (l<5) {
    obj=findObj(prefix + "div_" + (l + 1), theDoc);
    if (obj)
      obj.style.display="inline";
    for (m=l+2; m<=5; ++m) {
      obj=findObj(prefix + "div_" + m, theDoc);
      if (obj)
        obj.style.display="none";
    }
  }
}

function normalizeSearch2(theDoc) {
	normalize("search2_subject_", theDoc);
	normalize("search2_source_", theDoc);
}

function doSelectParam(id1,id2,value1,value2) {
  var obj=findObj(id1,opener.document);
  if (obj)
    obj.value=value1;
  obj=findObj(id2,opener.document);
  if (obj)
    obj.value=value2;
  if (id1.substr(0,8)=="search2_")
    normalizeSearch2(opener.document);
  window.top.close();
}

function clearParam(id1,id2) {
  var obj=findObj(id1);
  if (obj)
    obj.value="";
  obj=findObj(id2);
  if (obj)
    obj.value="-1";
  if (id1.substr(0,8)=="search2_")
    normalizeSearch2(document);
}
