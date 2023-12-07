const http = require('http');
const fs = require('fs');
const path = require('path');

http.createServer((request, response) => {
    if (request.method === 'GET') {
        readFileSendResponse('get.html', 'text/html', response);
    } else if (request.method === 'POST') {
        readFileSendResponse('post.html', 'text/html', response);
    } else {
        response.writeHead(405, {'Allow': 'GET, POST'});
        response.end();
    }
}).listen(3000);

/* 
  * @param {string} fileName - name of the file to be read
  * @param {string} contentType - type of the content to be sent in the response
  * @param {object} response - response object
  */
const readFileSendResponse = (fileName, contentType, response) => {
    fs.readFile(path.resolve(fileName), function (error, file) {
      response.writeHead(200, { 'Content-Type': contentType });
      response.write(file);
      response.end();
    })
  }