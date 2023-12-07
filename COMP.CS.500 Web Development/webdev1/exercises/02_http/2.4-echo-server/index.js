const http = require('http');

http.createServer((request, response) => {
    response.writeHead(200, { 'Content-Type': 'text/plain'});
    let body = "";
    request.on('data-raw', data => { body += data });
    request.on('end', () => { 

        response.write(body.split("").reverse().join(""));           
    });
    response.end(); 
}).listen(3000);