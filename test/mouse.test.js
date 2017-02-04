'use strict'

var anjian = require('../');
var assert = require('assert');
var screen = require('screen-info');

describe('mouse', function () {
    var mainScreen = screen.main();
    it('moveTo', function() {
        this.timeout(500000);
        for (var x = 0; x < mainScreen.width; x++) {
          for (var y = 0; y < mainScreen.height ; y++) {
              anjian.mouse().moveTo(x,y);
              var newPos = anjian.mouse().getCursorPos();
              assert.strictEqual(x, newPos.x);
              assert.strictEqual(y, newPos.y);
          }
        }
    });

    it('moveBy', function() {
        anjian.mouse().moveTo(0, 0);
        var oldPos = anjian.mouse().getCursorPos();
        anjian.mouse().moveBy(1, 1);
        var newPos = anjian.mouse().getCursorPos();
        assert.strictEqual(oldPos.x + 1, newPos.x);
        assert.strictEqual(oldPos.y + 1, newPos.y);
    });
});
