/* A "mesh" is (at least for the time being) primarily a scene graph node,
   which can (optionally) have a geometry and material attached to it. The
   Scene class, for example, is purely a top-level Mesh. Because it is
   effectively an abstract scene graph node class (including a 4x4
   transformation matrix, a set of children, and push/pop actions for
   traversal), it can also be extended to define non-mesh items like cameras
   and positional lights. Useful extensions for the Mesh object might include
   UUIDs for improved tracing/uniqueness, double-linked (parent) references,
   and (though let's not get ahead of ourselves) an explicitly-abstract scene
   graph node class that does not imply geometry or material properties.
*/

#ifndef SDLTHREE_MESH_H
#define SDLTHREE_MESH_H

#include <glm/glm.hpp>
#include "Geometry.h"
#include "Material.h"
#include <vector>

class Mesh {
public:
    Mesh();
    ~Mesh();
    void pushFrame();
    void popFrame();
    bool isVisible = true;
protected:
    glm::mat4* frame = NULL;
    Geometry* geometry = NULL;
    Material* material = NULL;
    std::vector<Mesh*> children;
private:
};

#endif
