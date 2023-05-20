window.onload = function () {
    var url,
    i,
    jqxhr;
    
    for (i = 0; i < 1; i++) {
        url = document.URL + 'inputs/' + i;
        jqxhr = $.getJSON(url, function(data) {
        console.log('API response received');
        $('#input').append('<p>Temperature  = ' + data['temperature'] + ' *C ' +
            ' Humidity = ' + data['humidity'] + ' % </p>');
        });
    }
};