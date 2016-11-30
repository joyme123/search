var server = "http://localhost/cgi-bin/";

function search() {
    var Request = new Object();
    Request = GetRequest();
    var keyword = Request['keyword'];
    $.ajax({
        url: server + "get.cgi",
        type: "GET",
        data: {
            'keyword': keyword
        },
        success: function(response) {
            var res = JSON.parse(response);
            var docs = res.docs;
            $(".result").html("总共有" + res.docCount + "个相关搜索结果，共耗时0.1s");
            console.log(docs);
            for (i = 0; i < res.docCount; i++) {
                $(".search_result_list").append('<li><p class="item_title"><a href="' + docs[i].url + '">' + docs[i].title + '</a></p><p class="item_url">' + docs[i].url + '</p><p class="item_content">' + docs[i].text + '</p></li>');

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