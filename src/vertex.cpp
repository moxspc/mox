
#include "helper.h"
#include "vertex.h"

#include <BRep_Tool.hxx>

Nan::Persistent<v8::Function> mox::Vertex::constructor;

mox::Vertex::Vertex()
{
}

mox::Vertex::Vertex(TopoDS_Vertex occVertex) : m_vertex(occVertex)
{
}

mox::Vertex::~Vertex()
{
}

void mox::Vertex::setOCC(TopoDS_Vertex occVertex)
{
  m_vertex = occVertex;
}

void mox::Vertex::Init(v8::Local<v8::Object> namespc)
{
  DEFINE_FUNCTION_TEMPLATE("Vertex", tpl);

  Nan::SetPrototypeMethod(tpl, "toString", toString);

  constructor.Reset(tpl->GetFunction());
  namespc->Set(Nan::New("Vertex").ToLocalChecked(), tpl->GetFunction());
}

v8::Local<v8::Object> mox::Vertex::NewInstance()
{
  Nan::EscapableHandleScope scope;

  const unsigned argc = 0;
  v8::Local<v8::Value> argv[] = {};
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  return scope.Escape(instance);
}

NAN_METHOD(mox::Vertex::New)
{
  if(info.IsConstructCall()) {
    Vertex *obj = new Vertex();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 0;
    v8::Local<v8::Value> argv[] = {};
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc,argv));
  }
}

NAN_METHOD(mox::Vertex::toString)
{
  GET_SELF(mox::Vertex, self);
  std::stringstream ss;
  if(self->m_vertex.IsNull()) {
    ss << "NULL";
  } else {
    gp_Pnt pnt = BRep_Tool::Pnt(self->m_vertex);
    ss << "[" << pnt.X() << "," << pnt.Y() << "," << pnt.Z() << "]";
  }
  TopAbs_Orientation orientation = self->m_vertex.Orientation();
  ss << " Orientation: ";
  switch(orientation) {
  case TopAbs_FORWARD:
    ss << "FWD";
    break;
  case TopAbs_REVERSED:
    ss << "RVS";
    break;
  case TopAbs_INTERNAL:
    ss << "INT";
    break;
  case TopAbs_EXTERNAL:
    ss << "EXT";
    break;
  default:
    ss << "UNK";
    break;
  }
  info.GetReturnValue().Set(Nan::New(ss.str()).ToLocalChecked());
}
