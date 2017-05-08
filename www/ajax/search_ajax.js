// var server = "http://localhost/cgi-bin/";

function search() {
    var Request = new Object();
    Request = GetRequest();
    var keyword = Request['keyword'];
    var page = Request['page'];
    $("#search_input").val(keyword);
    $.ajax({
        url:  "cgi-bin/get.fcgi",
        type: "GET",
        data: {
            'keyword': keyword,
            'page':page
        },
        success: function(response) {
            var res = JSON.parse(response);
            var docs = res.docs;
            $(".result").html("总共有" + res.docCount + "个相关搜索结果，共耗时0.1s");
            var totalPage = Math.ceil(res.docCount / res.pageSize);
            for (i = 0; i < res.docs.length; i++) {
                $(".search_result_list").append('<li><p class="item_title"><a href="' + docs[i].url + '">' + docs[i].title + '</a></p><p class="item_url">' + docs[i].url + '</p><p class="item_content">' + docs[i].text + '</p></li>');

            }

            

            $("#page").append('<span>当前页:'+res.pageIndex+"</span>");

            if(res.pageIndex > 1){
                $("#page").append('<span><a href="search.html?keyword='+keyword+'&page='+(res.pageIndex - 1)+'">上一页</a></span>');
            }

            if(res.pageIndex < totalPage){
                $("#page").append('<span><a href="search.html?keyword='+keyword+'&page='+(res.pageIndex + 1)+'">下一页</a></span>');
            }
        },
        error: function(error) {
            alert("无法连接服务器，请检查网络连接");
        }

    });
}

$(document).ready(function() {
    search();
});
