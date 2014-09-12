// ======================================================================== //
// Copyright 2009-2014 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#include "triangle1.h"
#include "common/scene.h"

namespace embree
{
  SceneTriangle1 SceneTriangle1::type;
  TriangleMeshTriangle1 TriangleMeshTriangle1::type;

  Triangle1Type::Triangle1Type () 
      : PrimitiveType("triangle1",sizeof(Triangle1),1,false,1) {} 
  
  size_t Triangle1Type::blocks(size_t x) const {
    return x;
  }
    
  size_t Triangle1Type::size(const char* This) const {
    return 1;
  }

  BBox3fa SceneTriangle1::update(char* prim_i, size_t num, void* geom) const 
  {
    BBox3fa bounds = empty;
    Scene* scene = (Scene*) geom;
    Triangle1* prim = (Triangle1*) prim_i;
    
    while (true)
    {
      const unsigned geomID = prim->geomID();
      const unsigned primID = prim->primID();
      const TriangleMesh* mesh = scene->getTriangleMesh(geomID);
      const TriangleMesh::Triangle& tri = mesh->triangle(primID);
      const Vec3fa v0 = mesh->vertex(tri.v[0]);
      const Vec3fa v1 = mesh->vertex(tri.v[1]);
      const Vec3fa v2 = mesh->vertex(tri.v[2]);
      const bool last = prim->last();
      new (prim) Triangle1(v0,v1,v2,geomID,primID,mesh->mask,last);
      bounds.extend(merge(BBox3fa(v0),BBox3fa(v1),BBox3fa(v2)));
      if (last) break;
      prim++;
    }
    return bounds; 
  }

  BBox3fa TriangleMeshTriangle1::update(char* prim_i, size_t num, void* geom) const 
  {
    BBox3fa bounds = empty;
    const TriangleMesh* mesh = (const TriangleMesh*) geom;
    Triangle1* prim = (Triangle1*) prim_i;
    
    while (true)
    {
      const unsigned geomID = prim->geomID();
      const unsigned primID = prim->primID();
      const TriangleMesh::Triangle& tri = mesh->triangle(primID);
      const Vec3fa v0 = mesh->vertex(tri.v[0]);
      const Vec3fa v1 = mesh->vertex(tri.v[1]);
      const Vec3fa v2 = mesh->vertex(tri.v[2]);
      const bool last = prim->last();
      new (prim) Triangle1(v0,v1,v2,geomID,primID,mesh->mask,last);
      bounds.extend(merge(BBox3fa(v0),BBox3fa(v1),BBox3fa(v2)));
      if (last) break;
      prim++;
    }
    return bounds; 
  }
}
