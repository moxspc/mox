
#include "mox.h"

#include "point.h"
#include "vector.h"
#include "lineseg.h"

#include "vertex.h"
#include "edge.h"
#include "face.h"
#include "wire.h"
#include "ops.h"
#include "solid.h"
#include "buffermesh.h"

#include <gp.hxx>
#include "gp_XYZ.hxx"

void mox::doOCCMath(const FunctionCallbackInfo<Value>& args)
{
  Isolate* isolate = args.GetIsolate();

  gp_XYZ xyz(3,4,1);
  v8::Local<v8::Number> answer = v8::Number::New(isolate, xyz.Modulus());
  args.GetReturnValue().Set(answer);
}

void mox::doSomething(const FunctionCallbackInfo<Value>& args)
{
//  v8::Local<v8::Object> vtxObject = mox::Vertex::NewInstance();
//  mox::Vertex* vtx = Nan::ObjectWrap::Unwrap<mox::Vertex>(vtxObject);
}

void mox::init(Local<Object> exports)
{
  v8::Handle<Object> geom = Nan::New<v8::Object>();
  mox::Point::Init(geom);
  mox::Vector::Init(geom);
  mox::LineSegment::Init(geom);

  v8::Handle<Object> topo = Nan::New<v8::Object>();
  mox::Vertex::Init(topo);
  mox::Edge::Init(topo);
  mox::Face::Init(topo);
  mox::Wire::Init(topo);
  mox::Solid::Init(topo);

  v8::Handle<Object> ops = Nan::New<v8::Object>();
  mox::ops::Init(ops);

  v8::Handle<Object> tess = Nan::New<v8::Object>();
  mox::BufferMesh::Init(tess);

  exports->Set(Nan::New("geom").ToLocalChecked(), geom);
  exports->Set(Nan::New("topo").ToLocalChecked(), topo);
  exports->Set(Nan::New("ops").ToLocalChecked(), ops);
  exports->Set(Nan::New("tess").ToLocalChecked(), tess);

  NODE_SET_METHOD(exports, "doOCCMath", doOCCMath);
  NODE_SET_METHOD(exports, "doSomething", doSomething);
}

NODE_MODULE(mox, mox::init)


