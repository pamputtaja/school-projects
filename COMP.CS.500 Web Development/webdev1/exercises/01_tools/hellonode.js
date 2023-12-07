const _ = require("lodash");
const ver = _.VERSION;
console.log(ver);

var array = process.argv;
hithere(array);

function hithere(array) {
    var head = _.head(array);
    var last = _.last(array);
    var output = `${last} and ${head}`; 
    console.log(output);
    return output;
}

module.exports = hithere;
