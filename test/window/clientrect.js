var anjian = require('../../');
var d = anjian.desktop();

var notepad = d.childByClass('Notepad');

console.log(notepad.clientRect());
console.log(notepad.windowRect());
