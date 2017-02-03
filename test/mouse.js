var tap = require("tap")
var anjian = require("../build/Release/anjian");
tap.test("moveTo", function (t) {
  var oldPos = anjian.mouse().getCursorPos();
  anjian.mouse().moveBy(1,1);
  var newPos = anjian.mouse().getCursorPos();
  t.equal(oldPos.x + 1, newPos.x);
  t.equal(oldPos.y + 1, newPos.y);
  t.pass("cleaned!")
  t.end()
})
