#include "EntityRenderer.hpp"
#include "World/EntityWorld.hpp"

#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtx/string_cast.hpp"
#include <iostream>

void EntityRenderer::activate(std::vector<Entity> *ep) {
   this->entitiesPointer = ep;
   shader = new EntityShader;
   shader->init();
}

void EntityRenderer::setGlobals(const glm::mat4 *projection, const glm::mat4 *view) {
   EntityShader *eShader = dynamic_cast<EntityShader*>(shader);
   eShader->loadP(projection);
   eShader->loadV(view);
}

void EntityRenderer::render(World *world) {
   EntityShader *eShader = dynamic_cast<EntityShader*>(shader);
   EntityWorld *eWorld = dynamic_cast<EntityWorld*>(world);

   // There's only one light as of now
   eShader->loadLight(eWorld->lights[0]);

   glm::mat4 M;
   for (unsigned int i = 0; i < entitiesPointer->size(); i++) {
      Entity *e = &(*entitiesPointer)[i];

      if (e->mesh == NULL) {
         continue;
      }

      // Bind mesh to shader
      // TODO : organized instanced rendering for textured meshes
      prepareMesh(e->mesh);

      // Material
      eShader->loadMaterial(e->texture.ambientColor, 
                            e->texture.diffuseColor, 
                            e->texture.specularColor);
      eShader->loadShine(e->texture.shineDamper);


      // Model matrix
      M = glm::mat4(1.f);
      M *= glm::translate(glm::mat4(1.f), e->position);
      M *= glm::rotate(glm::mat4(1.f), e->rotation.x, glm::vec3(1, 0, 0));
      M *= glm::rotate(glm::mat4(1.f), e->rotation.y, glm::vec3(0, 1, 0));
      M *= glm::rotate(glm::mat4(1.f), e->rotation.z, glm::vec3(0, 0, 1));
      M *= glm::scale(glm::mat4(1.f), e->scale);

      eShader->loadM(&M);
      
      // Draw
      glDrawElements(GL_TRIANGLES, (int)e->mesh->eleBuf.size(), GL_UNSIGNED_INT, (const void *)0);

      // Unbind mesh
      unPrepareMesh(e->mesh);
   }
}

// All Meshes are assumed to have valid vertices and element indices
// For Entities we assume meshes to include normal data
// TODO : allow for texture coords 
void EntityRenderer::prepareMesh(Mesh *mesh) {

   glBindVertexArray(mesh->vaoId);
   
   // Bind position buffer
   int pos = shader->getAttribute("vertexPos");
   glEnableVertexAttribArray(pos);
   glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBufId);
   glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);

   // Bind normal buffer
   pos = shader->getAttribute("vertexNormal");
   if (pos != -1 && mesh->norBufId != 0) {
      glEnableVertexAttribArray(pos);
      glBindBuffer(GL_ARRAY_BUFFER, mesh->norBufId);
      glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);
   }

   // TODO : texture coords

   // Bind element buffer
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->eleBufId);
}

void EntityRenderer::unPrepareMesh(Mesh *mesh) {
   glDisableVertexAttribArray(shader->getAttribute("vertexPos"));
   int pos = shader->getAttribute("vertexNormal");
   if (pos != -1) {
      glDisableVertexAttribArray(shader->getAttribute("vertexNormal"));
   }
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EntityRenderer::cleanUp() {
   shader->cleanUp();
}