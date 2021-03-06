var assert = require('assert');
var mox = require(process.env.HOME+'/moxspc/mox/build/Release/mox');

describe('Face', function() {
  it('Constructor', function () {
    var point1 = new mox.geom.Point(0,0,0);
    var point2 = new mox.geom.Point(1,0,0);
    var point3 = new mox.geom.Point(1,1,0);
    var point4 = new mox.geom.Point(0,1,0);
    var lineseg1 = new mox.geom.LineSegment(point1, point2);
    var lineseg2 = new mox.geom.LineSegment(point2, point3);
    var lineseg3 = new mox.geom.LineSegment(point3, point4);
    var lineseg4 = new mox.geom.LineSegment(point4, point1);
    var edge1 = lineseg1.makeEdge();
    var edge2 = lineseg2.makeEdge();
    var edge3 = lineseg3.makeEdge();
    var edge4 = lineseg4.makeEdge();
    var wire = new mox.topo.Wire(edge1, edge2, edge3, edge4);
    var face = wire.makeFace();
    assert(!!face);
  });
});
