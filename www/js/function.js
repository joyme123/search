 function trim(str) { //删除左右两端的空格
     return str.replace(/(^\s*)|(\s*$)/g, "");
 }

 function ltrim(str) { //删除左边的空格
     return str.replace(/(^\s*)/g, "");
 }

 function rtrim(str) { //删除右边的空格
     return str.replace(/(\s*$)/g, "");
 }

 function GetRequest() { //获取url参数
     var url = location.search; //获取url中"?"符后的字串 
     var theRequest = new Object();
     if (url.indexOf("?") != -1) {
         var str = url.substr(1);
         strs = str.split("&");
         for (var i = 0; i < strs.length; i++) {
             theRequest[strs[i].split("=")[0]] = unescape(decodeURI(strs[i].split("=")[1])); //decodeURI防止中文参数出现乱码
         }
     }
     return theRequest;
 }