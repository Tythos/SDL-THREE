/*
*/

#include "Material.h"

Material::Material() {

}

Material::~Material() {
    if (0 < this->programID) {
        glDeleteProgram(this->programID);
    }
}

void Material::loadProgram(std::istream v, std::istream f) {

}
