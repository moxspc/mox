
var assert = require('assert');
var mox = require(process.env.HOME+'/moxspc/mox/build/Release/mox');

describe('LineSegment', function() {
  it('Constructor', function () {
    var point1 = new mox.geom.Point(0,0,0);
    var point2 = new mox.geom.Point(1,0,0);
    var lineseg = new mox.geom.LineSegment(point1, point2);
    assert(!!lineseg); // not null/undefined
  });
});
