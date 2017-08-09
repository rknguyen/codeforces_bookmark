function decodeHTMLEntities(text) {
    var entities = [
        ['amp', '&'],
        ['apos', '\''],
        ['#x27', '\''],
        ['#x2F', '/'],
        ['#39', '\''],
        ['#47', '/'],
        ['lt', '<'],
        ['gt', '>'],
        ['nbsp', ' '],
        ['quot', '"']
    ];

    for (var i = 0, max = entities.length; i < max; ++i)
        text = text.replace(new RegExp('&' + entities[i][0] + ';', 'g'), entities[i][1]);

    return text;
}

function getTest() {

    if (window.location.href.indexOf('http://codeforces.com/problemset/problem/') == -1) {
        alert('Loi lien ket!');
        return;
    }

    String.prototype.replaceAll = function(search, replacement) {
        var target = this;
        return target.split(search).join(replacement);
    };

    function _sendRequest(info, callback) {
        var request = new XMLHttpRequest();
        request.onreadystatechange = function() {
            if (request.readyState == 4 && request.status == 200) {
                callback(request.responseText);
            }
        }
        request.open('GET', 'http://localhost/codeforces/api.php?info=' + info, true);
        request.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded; charset=UTF-8');
        request.send();
    };
    var inp = document.querySelectorAll('.input'),
        out = document.querySelectorAll('.output'),
        testCase = [];
    for (var tcs = 0; tcs < (inp).length; tcs++) {
        var preInput = decodeHTMLEntities(inp[tcs].querySelector('pre').innerHTML).replaceAll('<br>', "\n"),
            preOutput = decodeHTMLEntities(out[tcs].querySelector('pre').innerHTML).replaceAll('<br>', "\n");
        testCase[tcs] = {
            input: preInput,
            output: preOutput
        };
    }
    var name = document.title.split('-')[1];
    name = name.substr(1, name.length - 2);
    var info = {
        name: name,
        testcase: testCase
    };
    var par = encodeURI(JSON.stringify(info));
    console.log(par);
    _sendRequest(par, function(response) {
        if (response.length > 1) alert(response);
    });
}

getTest();
 
